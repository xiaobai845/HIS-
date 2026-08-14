#pragma once
#ifndef _PRACTITIONER_MAPPER_1_H_
#define _PRACTITIONER_MAPPER_1_H_

#include "Mapper.h"
#include "../../../domain/do/order/PractitionerDO1.h"

/**
 * 医务人员表字段匹配映射
 */
class PractitionerMapper1 : public Mapper<PractitionerDO1>
{
public:
    PractitionerDO1 mapper(ResultSet* resultSet) const override
    {
        PractitionerDO1 data;
        data.setId(resultSet->getString("id"));
        data.setTenantId(resultSet->getString("tenant_id"));
        data.setName(resultSet->getString("name"));
        data.setNameJson(resultSet->getString("name_json"));
        data.setPyStr(resultSet->getString("py_str"));
        data.setWbStr(resultSet->getString("wb_str"));
        data.setGenderEnum(resultSet->getString("gender_enum"));
        data.setBirthDate(resultSet->getString("birth_date"));
        data.setDeceasedDate(resultSet->getString("deceased_date"));
        data.setPhone(resultSet->getString("phone"));
        data.setAddressProvince(resultSet->getString("address_province"));
        data.setAddressCity(resultSet->getString("address_city"));
        data.setAddressDistrict(resultSet->getString("address_district"));
        data.setAddressStreet(resultSet->getString("address_street"));
        data.setAddressJson(resultSet->getString("address_json"));
        data.setStatusEnum(resultSet->getString("status_enum"));
        data.setActiveFlag(resultSet->getInt("active_flag"));
        data.setBusNo(resultSet->getString("bus_no"));
        data.setYbNo(resultSet->getString("yb_no"));
        data.setUserId(resultSet->getString("user_id"));
        data.setOrgId(resultSet->getString("org_id"));
        data.setDrProfttlCode(resultSet->getInt("dr_profttl_code"));
        data.setPharPracCertNo(resultSet->getString("phar_prac_cert_no"));
        data.setPrscDrCertCode(resultSet->getString("prsc_dr_cert_code"));
        data.setSignature(resultSet->getString("signature"));
        data.setKpdCode(resultSet->getString("kpd_code"));
        data.setPosNo(resultSet->getString("pos_no"));
        return data;
    }
};

/**
 * 医务人员表字段匹配映射-智能指针版本
 */
class PtrPractitionerMapper1 : public Mapper<PtrPractitionerDO1>
{
public:
    PtrPractitionerDO1 mapper(ResultSet* resultSet) const override
    {
        auto data = std::make_shared<PractitionerDO1>();
        data->setId(resultSet->getString("id"));
        data->setTenantId(resultSet->getString("tenant_id"));
        data->setName(resultSet->getString("name"));
        data->setNameJson(resultSet->getString("name_json"));
        data->setPyStr(resultSet->getString("py_str"));
        data->setWbStr(resultSet->getString("wb_str"));
        data->setGenderEnum(resultSet->getString("gender_enum"));
        data->setBirthDate(resultSet->getString("birth_date"));
        data->setDeceasedDate(resultSet->getString("deceased_date"));
        data->setPhone(resultSet->getString("phone"));
        data->setAddressProvince(resultSet->getString("address_province"));
        data->setAddressCity(resultSet->getString("address_city"));
        data->setAddressDistrict(resultSet->getString("address_district"));
        data->setAddressStreet(resultSet->getString("address_street"));
        data->setAddressJson(resultSet->getString("address_json"));
        data->setStatusEnum(resultSet->getString("status_enum"));
        data->setActiveFlag(resultSet->getInt("active_flag"));
        data->setBusNo(resultSet->getString("bus_no"));
        data->setYbNo(resultSet->getString("yb_no"));
        data->setUserId(resultSet->getString("user_id"));
        data->setOrgId(resultSet->getString("org_id"));
        data->setDrProfttlCode(resultSet->getInt("dr_profttl_code"));
        data->setPharPracCertNo(resultSet->getString("phar_prac_cert_no"));
        data->setPrscDrCertCode(resultSet->getString("prsc_dr_cert_code"));
        data->setSignature(resultSet->getString("signature"));
        data->setKpdCode(resultSet->getString("kpd_code"));
        data->setPosNo(resultSet->getString("pos_no"));
        return data;
    }
};

#endif // !_PRACTITIONER_MAPPER_1_H_