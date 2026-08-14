/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/08/04 21:04:43

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#include "../include/BaseDO.h"

DOField::DOField(std::string column, std::string type, ValueGetter getter, bool isNullable /*= true*/, bool isPrimaryKey /*= false*/)
	:column(column), type(type), getter(std::move(getter)), isNullable(isNullable), isPrimaryKey(isPrimaryKey)
{

}

DOField::DOField(DOField&& other) noexcept
	:column(std::move(other.column)), type(std::move(other.type)), getter(std::move(other.getter)), isPrimaryKey(other.isPrimaryKey), isNullable(other.isNullable)
{

}

std::string DOField::getColumn() const
{
	return column;
}

std::string DOField::getType() const
{
	return type;
}

bool DOField::getIsPrimaryKey() const
{
	return isPrimaryKey;
}

bool DOField::getIsNullable() const
{
	return isNullable;
}

void* DOField::get()
{
	return getter();
}

void BaseDO::addColField(DOField* field)
{
	// 判断是否是主键域
	if (field->getIsPrimaryKey())
	{
		if (_primaryField) delete _primaryField;
		_primaryField = field;
		return;
	}
	// 如果已经存在字段域，则删除
	auto iter = std::find_if(_fields.begin(), _fields.end(), [field](DOField* f) { return field->getColumn() == f->getColumn(); });
	if (iter != _fields.end()) {
		delete* iter;
		_fields.erase(iter);
	}
	// 添加字段域
	_fields.emplace_back(field);
}

BaseDO::BaseDO(std::string table)
	:_table(table)
{
	_primaryField = nullptr;
}

BaseDO::BaseDO(BaseDO&& other) noexcept
	: _table(std::move(other._table)), _primaryField(other._primaryField), _fields(std::move(other._fields))
{
	other._primaryField = nullptr;
}

BaseDO& BaseDO::operator=(BaseDO&& other) noexcept
{
	if (this != &other) {
		_table = std::move(other._table);
		_fields = std::move(other._fields);
		_primaryField = other._primaryField;
		other._primaryField = nullptr;
	}
	return *this;
}

BaseDO::~BaseDO()
{
	for (auto field : _fields)
		delete field;
	_fields.clear();
	if (_primaryField)
		delete _primaryField;
}

std::string BaseDO::getTable() const
{
	return _table;
}

DOField* BaseDO::getPrimaryField() const
{
	return _primaryField;
}

const std::vector<DOField*>& BaseDO::getFields() const
{
	return _fields;
}
