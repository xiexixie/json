#include "json.h"
#include "parser.h"
#include <sstream>
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
  clear();
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
    clear();
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
Json &Json::operator[](const std::string &key)
{
  if (m_type != json_object)
  {
    clear();
    m_type = json_object;
    m_value.m_object = new std::map<std::string, Json>();
  }
  return (*(m_value.m_object))[key];
}
Json &Json::operator[](const char *key)
{
  if (m_type != json_object)
  {
    clear();
    m_type = json_object;
    m_value.m_object = new std::map<std::string, Json>();
  }
  std::string name(key);
  return (*(m_value.m_object))[name];
}
bool Json::operator==(const Json &other)
{
  if (m_type != other.m_type)
    return false;
  switch (m_type)
  {
  case json_null:
    return true;
  case json_int:
    return m_value.m_int == other.m_value.m_int;
  case json_double:
    return m_value.m_double == other.m_value.m_double;
  case json_bool:
    return m_value.m_bool == other.m_value.m_bool;
  // 接下来均有坑，简单实现，你就说实现的简单不简单吧
  case json_string:
    return m_value.m_string == other.m_value.m_string;
  case json_array:
    return m_value.m_array == other.m_value.m_array;
  case json_object:
    return m_value.m_object == other.m_value.m_object;
  default:
    break;
  }
  return false;
}
bool Json::operator!=(const Json &other)
{
  return !((*this) == other);
}

void Json::append(const Json &j)
{
  if (m_type != json_array)
  {
    clear();
    m_type = json_array;
    m_value.m_array = new std::vector<Json>();
  }
  m_value.m_array->push_back(j);
}

std::string Json::str() const
{
  std::stringstream ss;
  switch (m_type)
  {
  case json_null:
    ss << "null";
    break;
  case json_bool:
    if (m_value.m_bool)
      ss << "true";
    else
      ss << "false";
    break;
  case json_int:
    ss << m_value.m_int;
    break;
  case json_double:
    ss << m_value.m_double;
    break;
  case json_string:
    ss << '\"' << *(m_value.m_string) << '\"';
    break;
  case json_array:
    ss << '[';
    for (auto it = m_value.m_array->begin(); it != m_value.m_array->end(); it++)
    {
      if (it != m_value.m_array->begin())
        ss << ',';
      ss << it->str();
    }
    ss << ']';
    break;
  case json_object:
    ss << '{';
    for (auto it = m_value.m_object->begin(); it != m_value.m_object->end(); it++)
    {
      if (it != m_value.m_object->begin())
        ss << ',';
      ss << '\"' << it->first << '\"' << ':' << it->second.str();
    }
    ss << '}';
    break;
  default:
    break;
  }
  return ss.str();
}

void Json::clear()
{
  switch (m_type)
  {
  case json_null:
    break;
  case json_int:
    m_value.m_int = 0;
    break;
  case json_double:
    m_value.m_double = 0.0;
    break;
  case json_bool:
    m_value.m_bool = false;
    break;
  case json_string:
    delete m_value.m_string;
    break;
  case json_array:
    for (auto it = m_value.m_array->begin(); it != m_value.m_array->end(); it++)
      it->clear();
    delete m_value.m_array;
    break;
  case json_object:
    for (auto it = m_value.m_object->begin(); it != m_value.m_object->end(); it++)
      (it->second).clear();
    delete m_value.m_object;
    break;
  default:
    break;
  }
  m_type = json_null;
}

bool Json::has(int index)
{
  if (m_type != json_array)
    return false;
  int size = m_value.m_array->size();
  return (index >= 0 && index < size);
}
bool Json::has(const std::string &key)
{
  if (m_type != json_object)
    return false;
  return ((m_value.m_object->find(key)) != (m_value.m_object->end()));
}
bool Json::has(const char *key)
{
  std::string name(key);
  return has(name);
}
void Json::remove(int index)
{
  if (m_type != json_array)
    return;
  if (!has(index))
    return;
  m_value.m_array->at(index).clear();
  m_value.m_array->erase(m_value.m_array->begin() + index);
}
void Json::remove(const std::string &key)
{
  if (m_type != json_object)
    return;
  if (!has(key))
    return;
  (*(m_value.m_object))[key].clear();
  m_value.m_object->erase(key);
}
void Json::remove(const char *key)
{
  std::string name(key);
  remove(name);
}
void Json::parse(const std::string &str)
{
  Parser p;
  p.load(str);
  *this = p.parse();
}
