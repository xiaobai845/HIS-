/*
 Copyright Zero One Star. All rights reserved.
 @Author: sqdxy
 @Date: 2026/07/23
*/
#include "stdafx.h"
#include "PrintTplRender.h"

// Generic table-style render: title + field key-value rows
static void renderTable(YAML::Node* tpl, PdfComponent* pdf, void* realData)
{
	auto accessor = static_cast<IDataAccessor*>(realData);
	if (!accessor->hasNext()) return;
	// Read first element (do NOT call moveNext before reading)

	auto node = *tpl;
	auto top = node["top"] ? node["top"].as<HPDF_REAL>() : 30;
	auto left = node["left"] ? node["left"].as<HPDF_REAL>() : 40;
	auto rowHeight = node["rowheight"] ? node["rowheight"].as<HPDF_REAL>() : 22;
	auto titleFontSize = node["titlefontsize"] ? node["titlefontsize"].as<HPDF_REAL>() : 18;
	auto contentFontSize = node["contentfontsize"] ? node["contentfontsize"].as<HPDF_REAL>() : 11;
	auto title = node["title"] ? node["title"].as<std::string>() : "";

	// Create page with Chinese font
	HPDF_Font font = pdf->getCnSFont("SimHei");
	auto page = pdf->getNewPage(font, contentFontSize);

	HPDF_REAL pageH = pdf->getCurrPageHeight();

	// Draw title
	if (!title.empty())
	{
		pdf->setCurrPageFontAndSize(font, titleFontSize);
		pdf->drawTextCenterH(title, pageH - top);
		pdf->setCurrPageFontAndSize(font, contentFontSize);
	}

	// Draw field rows
	HPDF_REAL startY = pageH - top - titleFontSize - 15;
	auto fields = node["fields"];
	if (fields)
	{
		for (size_t i = 0; i < fields.size(); i++)
		{
			auto field = fields[i].begin();
			auto fieldName = field->first.as<std::string>();
			auto fieldConfig = field->second;
			std::string label = fieldConfig["title"] ? fieldConfig["title"].as<std::string>() : fieldName;
			std::string prop = fieldConfig["prop"] ? fieldConfig["prop"].as<std::string>() : fieldName;
			std::string value = accessor->getField(prop);

			HPDF_REAL y = startY - i * rowHeight;
			pdf->drawText(label + ": " + value, left, y, page);
		}
	}

	// Reprint watermark
	if (node["watermark"] && node["watermark"].as<bool>())
	{
		pdf->setCurrPageFontAndSize(font, 48);
		pdf->drawTextCenter("补打", page);
		pdf->setCurrPageFontAndSize(font, contentFontSize);
	}

	// Footer: print time
	pdf->drawTextCenterH("打印时间: " + accessor->getField("printTime"), 20, page);
}

void PrintTplRender::registerAll()
{
	PdfComponent::registerTplRender("treatment", renderTable);
	PdfComponent::registerTplRender("prescription", renderTable);
	PdfComponent::registerTplRender("charge_receipt", renderTable);
	PdfComponent::registerTplRender("reg_receipt", renderTable);
	PdfComponent::registerTplRender("infusion_label", renderTable);
	PdfComponent::registerTplRender("daily_settlement", renderTable);
	PdfComponent::registerTplRender("exam_request", renderTable);
	PdfComponent::registerTplRender("lab_request", renderTable);
}
