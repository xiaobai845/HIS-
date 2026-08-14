#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: awei
 @Date: 2026/07/25
*/
#ifndef _CHINAPRES2_SERVICE_
#define _CHINAPRES2_SERVICE_

#include "../../domain/query/chinapres2/Chinapres2Query.h"
#include "../../domain/vo/chinapres2/Chinapres2VO.h"
#include "../../domain/dto/chinapres2/Chinapres2AddDTO.h"
#include "../../domain/dto/chinapres2/Chinapres2DetailDTO.h"
#include "../../dao/chinapres2/Chinapres2DAO.h"
#include "../../domain/dto/chinapres2/Chinapres2AddRespDTO.h"
#include "../../domain/dto/chinapres2/Chinapres2RemoveRespDTO.h"

/**
 * 中医处方 Service 层
 * 负责 DTO ↔ DO 转换和业务逻辑
 */
class Chinapres2Service
{
private:
    Chinapres2DAO dao;

    /**
     * 将 ViewDO 列表转换为 DetailDTO 列表
     */
     //oatpp::List<Chinapres2DetailDTO::Wrapper> convertToDTOList(const std::list<PtrChinapres2ViewDO>& doList);

public:
    // ========== 查询 ==========
    /**
     * 分页查询历史处方
     * @param query 查询条件
     * @return 分页结果 DTO
     */
     //Chinapres2DetailPageDTO::Wrapper listAll(const Chinapres2Query::Wrapper& query);

     // ========== 新增 ==========
     /**
      * 新增处方（主表 + 明细表）
      * @param dto 新增 DTO
      * @param payload 用户信息
      * @return 新生成的处方 ID
      */
    Chinapres2AddRespDTO::Wrapper saveData(const Chinapres2AddDTO::Wrapper& dto, const PayloadDTO& payload);
    // ========== 删除 ==========
    /**
     * 软删除处方（主表 + 明细表）
     * @param id 处方 ID
     * @return 是否成功
     */
    bool removeData(const std::string& id);
    Chinapres2RemoveRespDTO::Wrapper removeDataEnhanced(const std::string& id, const std::string& encounterId, int64_t version, const PayloadDTO& payload);
};

#endif // !_CHINAPRES2_SERVICE_