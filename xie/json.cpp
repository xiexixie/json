#include "json.h"
#include <iostream>

using namespace xie::json;

Json::Json()
    : m_type(json_null){};
Json::Json(bool value)
    : m_type(json_bool)
{
  m_value.m_bool = value;
}
Json::Json(int value)
    : m_type(json_int)
{
  m_value.m_int = value;
}
Json::Json(double value)
    : m_type(json_double)
{
  m_value.m_double = value;
}
Json::Json(const std::string &value)
    : m_type(json_string)
{
  m_value.m_string = new std::string(value);
}
Json::Json(const char *value)
    : m_type(json_string)
{
  m_value.m_string = new std::string(value);
}
Json::Json(const Json &other)
{
  m_type = other.m_type;
  switch (m_type)
  {
  case json_null:
    break;
  case json_bool:
    m_value.m_bool = other.m_value.m_bool;
    break;
  case json_int:
    m_value.m_int = other.m_value.m_int;
    break;
  case json_double:
    m_value.m_double = other.m_value.m_double;
    break;
  case json_string:
    m_value.m_string = other.m_value.m_string;
    break;
  case json_array:
    m_value.m_array = other.m_value.m_array;
    break;
  case json_object:
    m_value.m_object = other.m_value.m_object;
    break;
  default:
    break;
  }
}
Json::Json(Type type)
{
  m_type = type;
  switch (m_type)
  {
  case json_null:
    break;
  case json_bool:
    m_value.m_bool = false;
    break;
  case json_int:
    m_value.m_int = 0;
    break;
  case json_double:
    m_value.m_double = 0.0;
    break;
  case json_string:
    m_value.m_string = new std::string("");
    break;
  case json_array:
    m_value.m_array = new std::vector<Json>();
    break;
  case json_object:
    m_value.m_object = new std::map<std::string, Json>();
    break;
  default:
    break;
  }
}

Json::operator bool()
{
  return m_value.m_bool;
}
Json::operator int()
{
  return m_value.m_int;
}
Json::operator double()
{
  return m_value.m_double;
}
Json::operator std::string()
{
  return *m_value.m_string;
}

Json &Json::operator[](int index)
{
  if (m_type != json_array)
  {
    m_type = json_array;
    m_value.m_array = new std::vector<Json>();
  }
  if (index < 0)
    throw new std::logic_error("array index out of rande");
  if (index >= (m_value.m_array->size()))
  {
    m_value.m_array->push_back(Json());
  }
  return m_value.m_array->at(index);
}

void Json::append(const Json &j)
{
  if (m_type != json_array)
  {
    m_type = json_array;
    m_value.m_array = new std::vector<Json>();
  }
  m_value.m_array->push_back(j);
}