#pragma once
#ifndef RECEPTIONPATIENTSERVICE_H_
#define RECEPTIONPATIENTSERVICE_H_

#include "domain/dto/cycleCtrl1/ReceptionPatientDTO.h"
#include "domain/query/cycleCtrl1/ReceptionPatientQuery.h"
#include "dao/cycleCtrl1/ReceptionPatientDAO.h"
#include <ctime>
#include <chrono>
#include <sstream>
#include <iomanip>
#include "EnumDictUtil.h"
#include "service/ClientManager.h"

class ReceptionPatientService
{
public:
	//∑µªÿ‘⁄’Ôªº’ﬂ
	RecePatientDTO::Wrapper getRecePatient(const RecePatientQuery::Wrapper& query, 
		const string& tenantId, const string& practitionerId);

	static int calcAge(const std::string& birthDate);

	ReceptionPatientService()
	{
		m_mongoClient = ClientManager::getMongoClient();
	}

private:
	ReceptionPatientDAO m_dao;
	std::shared_ptr<MongoClient> m_mongoClient;

};




#endif // !RECEPTIONPATIENTSERVICE_H_
