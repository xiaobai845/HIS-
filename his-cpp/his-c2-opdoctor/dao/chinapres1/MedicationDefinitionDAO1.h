#pragma once
#ifndef _MEDICATIONDEFINITIONDAO1_H_
#define _MEDICATIONDEFINITIONDAO1_H_

#include "BaseDAO.h"
#include "domain/do/chinapres1/MedicationDefinitionDO1.h"

class MedicationDefinitionDAO1 : public BaseDAO
{
public:
	PtrMedicationDefinitionDO selectById(const string& id);
};

#endif // !_MEDICATIONDEFINITIONDAO1_H_