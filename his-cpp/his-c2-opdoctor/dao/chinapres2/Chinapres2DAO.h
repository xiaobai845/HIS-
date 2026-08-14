#pragma once
/*
 Copyright Zero One Star. All rights reserved.
 @Author: awei
 @Date: 2026/07/25
*/
#ifndef _CHINAPRES2_DAO_
#define _CHINAPRES2_DAO_

#include "BaseDAO.h"
#include "../../domain/do/chinapres2/Chinapres2MainDO.h"
#include "../../domain/do/chinapres2/Chinapres2DetailDO.h"
#include "../../domain/do/chinapres2/Chinapres2ViewDO.h"
#include "../../domain/query/chinapres2/Chinapres2Query.h"

/**
 * 中医处方数据访问层
 * 包含主表查询、明细表查询、联表分页查询、插入、更新、软删除
 */
class Chinapres2DAO : public BaseDAO
{
private:
    /**
     * 构建分页查询的 WHERE 条件
     * @param query 查询条件对象
     * @param params 输出参数，用于参数化查询
     * @return WHERE 子句字符串
     */
     // inline std::string queryConditionBuilder(const Chinapres2Query::Wrapper& query, SqlParams& params);

public:

    // 新增：检查就诊是否存在且未删除
    bool isEncounterEditable(const std::string& encounterId);
    // 新增：检查单位编码是否在字典表中且有效
    bool isUnitValid(const std::string& unitCode);
    // ========== 统计 ==========
    /**
     * 统计符合条件的处方总数（用于分页）
     */
     //uint64_t count(const Chinapres2Query::Wrapper& query);

     // ========== 查询 ==========
     /**
      * 分页查询处方列表（联查诊断名、医生名、药材汇总）
      * @return 视图 DO 列表（包含扩展字段）
      */
      //std::list<PtrChinapres2ViewDO> selectWithPage(const Chinapres2Query::Wrapper& query);

      /**
       * 根据主表 ID 查询单条处方
       * @return 主表 DO
       */
    PtrChinapres2MainDO selectById(const std::string& id);

    /**
     * 根据主表 ID 查询明细列表（智能指针版本）
     */
    std::list<PtrChinapres2DetailDO> selectDetailsByRequestIdPtr(const std::string& requestId);

    // ========== 插入 ==========
    /**
     * 插入主表
     * @param data 主表 DO
     * @return 是否成功
     */
    bool insertMain(const Chinapres2MainDO& data);

    /**
     * 批量插入明细表
     * @param details 明细列表（智能指针）
     * @return 是否成功
     */
    bool insertDetailsPtr(const std::list<PtrChinapres2DetailDO>& details);

    // ========== 更新 ==========
    /**
     * 更新主表
     * @param data 主表 DO
     * @return 是否成功
     */
    bool updateMain(const Chinapres2MainDO& data);

    // ========== 删除（软删除） ==========
    /**
     * 根据 ID 软删除单条处方（主表+明细表）
     * @param id 主表 ID
     * @return 是否成功
     */
    bool softDeleteById(const std::string& id);

    /**
     * 批量软删除处方
     * @param ids ID 列表
     * @return 是否成功
     */
    bool softDeleteBatch(const std::list<std::string>& ids);


    // 新增：带条件删除（乐观锁 + 状态 + 就诊校验）
    bool removeWithCondition(const std::string& id, const std::string& encounterId, int64_t version, const std::string& operatorId, std::string& newVersion, std::string& updatedAt);

    // 查询处方状态和版本（用于幂等判断）
    bool getPresenceStatus(const std::string& id, std::string& status, int64_t& version, std::string& encounterId);
};

#endif // !_CHINAPRES2_DAO_