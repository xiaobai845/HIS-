#ifndef __CHINAPRES2CONTROLLER_H_
#define __CHINAPRES2CONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/dto/chinapres2/Chinapres2AddDTO.h"
#include "domain/dto/chinapres2/Chinapres2AddRespDTO.h"
#include "domain/dto/chinapres2/Chinapres2RemoveDTO.h"
#include "domain/dto/chinapres2/Chinapres2RemoveRespDTO.h" // 确保头文件已包含
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("chinapres2.tags.tag")
class Chinapres2Controller : public oatpp::web::server::api::ApiController
{
    // 定义控制器访问入口
    API_ACCESS_DECLARE(Chinapres2Controller);
public:
    // 定义接口

     // 3.1 定义分页查询接口描述
   // API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("chinapres2.query.summary"), queryChinapre, Chinapres2Query, Chinapres2DetailPageJsonVO::Wrapper, API_TAG);
    // 3.2 定义分页查询接口处理
   // API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/chinapres2", queryChinapre, Chinapres2Query, execQueryChinapre(query));

    // 新增处方接口（直接返回 DTO）
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("chinapres2.add.summary"), addPrescription,
        Chinapres2AddRespDTO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/chinapres2/add", addPrescription,
        BODY_DTO(Chinapres2AddDTO::Wrapper, dto),
        execAddChinapre(dto, authObject->getPayload()));

    //// 3.1 定义删除接口描述
    //API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("chinapres2.remove.summary"), removePrescription, BooleanJsonVO::Wrapper, API_TAG);
    //// 3.2 定义删除接口处理
    //API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/chinapres2/{id}", removePrescription, PATH(String, id), execRemoveChinapre(id));

    // 新增删除接口（增强版）
    API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("chinapres2.remove.summary"), removePrescriptionEnhanced,
        Chinapres2RemoveDTO::Wrapper, API_TAG);
    API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/chinapres2/remove", removePrescriptionEnhanced,
        BODY_DTO(Chinapres2RemoveDTO::Wrapper, dto),
        execRemoveChinapreEnhanced(dto, authObject->getPayload()));

private: // 定义接口执行函数
    //Chinapres2DetailPageJsonVO::Wrapper execQueryChinapre(const Chinapres2Query::Wrapper& query);


    // 执行函数声明（返回类型与接口宏一致）
    Chinapres2AddRespDTO::Wrapper execAddChinapre(const Chinapres2AddDTO::Wrapper& dto,
        const PayloadDTO& payload);

    Chinapres2RemoveRespDTO::Wrapper execRemoveChinapreEnhanced(const Chinapres2RemoveDTO::Wrapper& dto, const PayloadDTO& payload);

    BooleanJsonVO::Wrapper execRemoveChinapre(const String& id);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !__CHINAPRES2CONTROLLER_H_