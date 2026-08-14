#pragma once
#ifndef _CHARGEITEMDEFINITIONDAO1_H_
#define _CHARGEITEMDEFINITIONDAO1_H_

#include "BaseDAO.h"
#include "domain/do/chinapres1/ChargeItemDefinitionDO1.h"

class ChargeItemDefinitionDAO1 : public BaseDAO
{
public:
	PtrChargeItemDefinitionDO selectByInstanceId(const string& instanceId);
};

#endif // !_CHARGEITEMDEFINITIONDAO1_H_