#pragma once
#ifndef _MONGODICTDAO_H_
#define _MONGODICTDAO_H_

#include <string>

class MongoDictDAO
{
public:
	MongoDictDAO();
	~MongoDictDAO();

	// 根据字典类型和编码查询中文名称
	// dictType: 字典类型，如 "medication_status"
	// code: 枚举编码，如 "DRAFT"
	// 返回: 中文名称，如 "草稿"；查不到返回原 code
	std::string getDictName(const std::string& dictType, const std::string& code);
};

#endif // !_MONGODICTDAO_H_