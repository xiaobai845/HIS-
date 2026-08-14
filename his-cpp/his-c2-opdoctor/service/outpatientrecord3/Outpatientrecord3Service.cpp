#include "stdafx.h"
#include "Outpatientrecord3Service.h"
#include "id/SnowFlake.h"
#include "SimpleDateTimeFormat.h"
#include <sstream>
#include <algorithm>

// ==================== Helper: encounter editability check ====================
bool outpatientrecord3Service::isEncounterEditable(const std::string& statusEnum)
{
	// Encounter statuses that prevent editing: finished, cancelled, completed, entered-in-error
	static const std::string NON_EDITABLE[] = {
		"finished", "cancelled", "completed", "entered-in-error"
	};
	for (const auto& s : NON_EDITABLE) {
		if (statusEnum == s)
			return false;
	}
	return true;
}

// ==================== Helper: content validation ====================
bool outpatientrecord3Service::validateContent(const std::string& content, std::string& errorMsg)
{
	// Size check
	if (content.size() > MAX_CONTENT_SIZE) {
		std::ostringstream oss;
		oss << "Content exceeds maximum size of " << (MAX_CONTENT_SIZE / 1024) << " KB";
		errorMsg = oss.str();
		return false;
	}
	if (content.empty()) {
		errorMsg = "Content cannot be empty";
		return false;
	}

	// Basic JSON structure check: must start with { or [
	char first = content[0];
	if (first != '{' && first != '[') {
		errorMsg = "Content is not valid JSON structure";
		return false;
	}

	// Simple nesting depth guard: count max consecutive open-brackets
	int depth = 0, maxDepth = 0;
	for (char c : content) {
		if (c == '{' || c == '[') {
			depth++;
			if (depth > maxDepth) maxDepth = depth;
		}
		else if (c == '}' || c == ']') {
			if (depth > 0) depth--;
		}
	}
	if (maxDepth > 50) {
		errorMsg = "Content JSON nesting depth exceeds limit (50)";
		return false;
	}

	return true;
}

// ==================== Main save/upsert entry ====================
outpatientrecord3SaveResultVO::Wrapper outpatientrecord3Service::save(
	const outpatientrecord3SaveDTO::Wrapper& dto,
	const PayloadDTO& payload)
{
	auto resultVo = outpatientrecord3SaveResultVO::createShared();

	// ===================== 1. Parameter validation =====================
	auto encounterId = dto->encounterId;
	if (!encounterId || encounterId.getValue("") == "") {
		resultVo->code = 400;
		resultVo->message = "Parameter cannot be empty: encounterId is required";
		return resultVo;
	}

	auto content = dto->content;
	if (!content || content.getValue("") == "") {
		resultVo->code = 400;
		resultVo->message = "Parameter cannot be empty: content is required";
		return resultVo;
	}

	// ===================== 2. Prepare common fields =====================
	auto now = SimpleDateTimeFormat::format();
	auto currentUser = payload.getUsername();
	auto orgId = payload.getId();

	std::string encId = encounterId.getValue("");
	std::string contentStr = content.getValue("");

	// ===================== 3. Look up adm_encounter =====================
	auto encounter = admEncounterDAO.selectById(encId, orgId);
	if (!encounter) {
		resultVo->code = 404;
		resultVo->message = "Encounter not found, please check encounter ID";
		return resultVo;
	}

	std::string patientId = encounter->getPatientId();
	std::string statusEnum = encounter->getStatusEnum();

	// ===================== 4. Status validation =====================
	if (!isEncounterEditable(statusEnum)) {
		resultVo->code = 409;
		std::ostringstream msg;
		msg << "Encounter is not editable (status: " << statusEnum << ")";
		resultVo->message = msg.str().c_str();
		return resultVo;
	}

	// ===================== 5. Content validation =====================
	std::string contentError;
	if (!validateContent(contentStr, contentError)) {
		resultVo->code = 400;
		resultVo->message = contentError.c_str();
		return resultVo;
	}

	// ===================== 6. Title auto-generation =====================
	std::string titleValue;
	auto titleField = dto->title;
	if (titleField && titleField.getValue("") != "") {
		titleValue = titleField.getValue("");
	}
	else {
		std::ostringstream titleStream;
		titleStream << ZH_WORDS_GETTER("outpatientrecord3.tags.tag") << "-" << now;
		titleValue = titleStream.str();
	}

	// ===================== 7. Upsert logic =====================
	auto existing = emrDocument3DAO.selectByEncounterId(encId);

	if (!existing) {
		// ---------- Insert new record ----------
		auto snowFlake = SnowFlake::getInstance();

		EmrDocument3DO doc;
		doc.setId(std::to_string(snowFlake->nextId()));
		doc.setPatientId(patientId);
		doc.setEncounterId(encId);
		doc.setDocumentTypeCode("OUTPATIENT_RECORD");
		doc.setTitle(titleValue);
		doc.setContent(contentStr);
		doc.setStatus("DRAFT");

		// Optional template ID
		auto tplId = dto->templateId;
		if (tplId && tplId.getValue("") != "") {
			doc.setSourceTemplateId(tplId.getValue(""));
		}

		doc.setCreatedAt(now);
		doc.setCreatedBy(currentUser);
		doc.setTenantId(orgId);

		emrDocument3DAO.insert(doc);

		// Assemble response
		auto resultData = outpatientrecord3SaveResultDTO::createShared();
		resultData->id = doc.getId().c_str();
		resultData->encounterId = encId.c_str();
		resultData->updatedAt = now.c_str();
		resultVo->success(resultData);
		resultVo->message = "Medical record saved successfully";
	}
	else {
		// ---------- Update existing record ----------
		// Idempotency check: skip write if content unchanged
		if (existing->getContent() == contentStr) {
			auto resultData = outpatientrecord3SaveResultDTO::createShared();
			resultData->id = existing->getId().c_str();
			resultData->encounterId = encId.c_str();
			resultData->updatedAt = existing->getUpdatedAt().c_str();
			resultVo->success(resultData);
			resultVo->message = "Medical record unchanged, skipped save";
			return resultVo;
		}

		// Update fields
		existing->setPatientId(patientId);
		existing->setTitle(titleValue);
		existing->setContent(contentStr);
		existing->setStatus("DRAFT");

		auto tplId = dto->templateId;
		if (tplId && tplId.getValue("") != "") {
			existing->setSourceTemplateId(tplId.getValue(""));
		}

		existing->setUpdatedAt(now);
		existing->setUpdatedBy(currentUser);

		emrDocument3DAO.update(*existing);

		// Assemble response
		auto resultData = outpatientrecord3SaveResultDTO::createShared();
		resultData->id = existing->getId().c_str();
		resultData->encounterId = encId.c_str();
		resultData->updatedAt = now.c_str();
		resultVo->success(resultData);
		resultVo->message = "Medical record updated successfully";
	}

	return resultVo;
}
