#pragma once

#include <string>
#include "json.h"

namespace xie
{
  namespace json
  {
    class Parser
    {
    public:
      Parser();
      void load(const std::string &str);
      Json parse();

    private:
      Json parse_null();
      Json parse_bool();
      Json parse_number();
      Json parse_array();
      Json parse_obj();
      std::string parse_string();
      void skip_blank();
      char get_next_token();

    private:
      std::string m_str;
      int m_index;
    };
  }
}