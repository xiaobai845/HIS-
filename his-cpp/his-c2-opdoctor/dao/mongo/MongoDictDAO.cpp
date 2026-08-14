#include "dao/mongo/MongoDictDAO.h"
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/builder/stream/document.hpp>

static mongocxx::instance g_instance{};

MongoDictDAO::MongoDictDAO() {}
MongoDictDAO::~MongoDictDAO() {}

std::string MongoDictDAO::getDictName(const std::string& dictType, const std::string& dictCode)
{
	try {
		
		mongocxx::uri uri("mongodb://kobe:123456@192.168.204.132:27017/firstDb");
		mongocxx::client client(uri);

		auto db = client["firstDb"];
		auto coll = db["sys_dict"];

		using bsoncxx::builder::stream::document;
		using bsoncxx::builder::stream::finalize;

		auto filter = document{}
			<< "dict_type" << dictType
			<< "code" << dictCode
			<< finalize;

		auto result = coll.find_one(filter.view());
		if (result) {
			auto view = result->view();
			auto nameField = view["name"];
			if (nameField) {
				return std::string(nameField.get_string().value);
			}
		}
	}
	catch (const std::exception& e) {
		// 打印到控制台，方便排查
		std::cerr << "MongoDictDAO error: " << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "MongoDictDAO unknown error" << std::endl;
	}

	return dictCode;
}