#pragma once

#ifndef CHINAPRESDAO1
#define CHINAPRESDAO1

#include"BaseDAO.h"
#include"domain/do/chinapres1/ChinapresDO1.h"
#include"domain/dto/chinapres1/ChinapresDTO1.h"
#include"domain/query/chinapres1/ChinapresQuery1.h"
#include"domain/query/chinapres1/ChinapresDetailQuery1.h"

class ChinapresDAO1 :public BaseDAO 
{
public:
	//查处方
	std::list<PtrChinapresDO> selectAll(const ChinapresQuery1::Wrapper& query);
	//查处方详情
	std::list<PtrChinapresDO> selectDetail(const ChinapresDetailQuery1::Wrapper& query);
};


#endif // !CHINAPRESDAO1

