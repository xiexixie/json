#pragma once

#include <string>
#include <vector>
#include <map>

namespace xie
{
  namespace json
  {
    class Json
    {
    public:
      enum Type
      {
        json_null,
        json_bool,
        json_int,
        json_double,
        json_string,
        json_array,
        json_object
      };

      // 构造函数
      Json();
      Json(bool value);
      Json(int value);
      Json(double value);
      Json(const std::string &value);
      Json(const char *value);
      Json(const Json &other);
      Json(Type type);

      // 将类转换为其他类型的转换函数,隐式转换
      operator bool();
      operator int();
      operator double();
      operator std::string();

      // 运算符重载
      Json &operator[](int index);
      Json &operator[](const std::string &key);
      Json &operator[](const char *key);
      bool operator==(const Json &other);
      bool operator!=(const Json &other);

      // 功能函数
      void append(const Json &j);
      std::string str() const;
      void clear();
      std::vector<Json>::iterator begin()
      {
        return m_value.m_array->begin();
      }
      std::vector<Json>::iterator end()
      {
        return m_value.m_array->end();
      }
      bool is_null() const { return m_type == json_null; }
      bool is_bool() const { return m_type == json_bool; }
      bool is_int() const { return m_type == json_int; }
      bool is_double() const { return m_type == json_double; }
      bool is_string() const { return m_type == json_string; }
      bool is_arr() const { return m_type == json_array; }
      bool is_obj() const { return m_type == json_object; }
      bool has(int index);
      bool has(const std::string &key);
      bool has(const char *key);
      void remove(int index);
      void remove(const char *key);
      void remove(const std::string &key);

    private:
      union Value
      {
        bool m_bool;
        int m_int;
        double m_double;
        std::string *m_string;
        std::vector<Json> *m_array;
        std::map<std::string, Json> *m_object;
      };

      Type m_type;
      Value m_value;
    };
  }
}