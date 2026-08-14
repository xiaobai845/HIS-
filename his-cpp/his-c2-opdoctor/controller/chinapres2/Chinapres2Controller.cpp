#include "stdafx.h"
#include "Chinapres2Controller.h"
#include "../../dao/chinapres2/Chinapres2DAO.h"
#include <chrono>
#include "../../service/chinapres2/Chinapres2Service.h"

Chinapres2AddRespDTO::Wrapper
Chinapres2Controller::execAddChinapre(const Chinapres2AddDTO::Wrapper& dto, const PayloadDTO& payload) {


    if (!dto) {
        std::cerr << "[ERROR] dto is nullptr, request body may be invalid JSON" << std::endl;
        throw std::runtime_error("请求体格式错误或缺少必填字段");
    }

    std::string err = dto->validate();
    if (!err.empty()) {
        throw std::runtime_error(err);
    }

    Chinapres2Service service;
    return service.saveData(dto, payload);
}


// ========== 2. Query Prescription List ==========
/*
Chinapres2DetailPageJsonVO::Wrapper Chinapres2Controller::execQueryChinapre(const Chinapres2Query::Wrapper& query) {
    auto jvo = Chinapres2DetailPageJsonVO::createShared();

    Chinapres2Service service;
    auto pageDto = service.listAll(query);

    jvo->success(pageDto);
    return jvo;
}
*/

// ========== 3. Delete Prescription（使用 Service） ==========

// ========== 增强删除 ==========
Chinapres2RemoveRespDTO::Wrapper
Chinapres2Controller::execRemoveChinapreEnhanced(const Chinapres2RemoveDTO::Wrapper& dto, const PayloadDTO& payload) {
    if (!dto) throw std::runtime_error("dto is null");
    if (!dto->id || dto->id->empty() || !dto->encounterId || dto->encounterId->empty() || !dto->version) {
        throw std::runtime_error("id, encounterId, version are required");
    }
    Chinapres2Service service;
    return service.removeDataEnhanced(
        dto->id->c_str(),
        dto->encounterId->c_str(),
        *dto->version,
        payload
    );
}


BooleanJsonVO::Wrapper Chinapres2Controller::execRemoveChinapre(const String& id) {
    auto jvo = BooleanJsonVO::createShared();

    if (!id || id->empty()) {
        jvo->fail("id is empty");
        return jvo;
    }

    Chinapres2Service service;
    bool ok = service.removeData(id.getValue(""));

    if (ok) {
        jvo->success(true);
    }
    else {
        jvo->fail("delete failed");
    }
    return jvo;
}