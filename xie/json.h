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

      // 将类转换为其他类型的转换函数
      operator bool();
      operator int();
      operator double();
      operator std::string();

      // 运算符重载
      Json &operator[](int index);

      void append(const Json &j);

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