#pragma once
#ifndef _CHINAPRESSERVICE1_H_
#define _CHINAPRESSERVICE1_H_

#include "domain/dto/chinapres1/ChinapresListDTO1.h"
#include "domain/dto/chinapres1/ChinapresDetailDTO1.h"
#include "domain/query/chinapres1/ChinapresQuery1.h"
#include "domain/query/chinapres1/ChinapresDetailQuery1.h"

class ChinapresService1
{
public:
	ChinapresListDTO1::Wrapper queryList(const ChinapresQuery1::Wrapper& query);
	ChinapresDetailDTO1::Wrapper queryDetail(const ChinapresDetailQuery1::Wrapper& query);
};

#endif