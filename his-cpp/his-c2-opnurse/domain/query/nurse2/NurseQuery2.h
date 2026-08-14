#pragma

#ifndef _NurseQuery_H_
#define _NurseQuert_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

//get请求
class NurseQuery2 : public PageQuery
{
	//初始化
	DTO_INIT(NurseQuery2, PageQuery);  //继承谁这第二个参数就是谁

	//这些是学长自定义宏 用来减少写代码量 ctrl进去查看具体写法
	//具体参考arch-demo下的同集目录 这个在/domian/query/user 这个user是学长写的一个利用宏的例子

	// 姓名/排队号 -->获取患者队列
	API_DTO_FIELD_REQUIRE(String, name_code, ZH_WORDS_GETTER("nurse2.field.name_code"),false);
	//获取患者执行项目 (注射/处置)
	API_DTO_FIELD_REQUIRE(String, execu_project, ZH_WORDS_GETTER("nurse2.field.execu_project"),false);
	//获取患者耗材项目
	API_DTO_FIELD_REQUIRE(String, use_project, ZH_WORDS_GETTER("nurse2.field.use_project"),false);

};

#include OATPP_CODEGEN_END(DTO)


#endif // !_NurseQuery_H_
