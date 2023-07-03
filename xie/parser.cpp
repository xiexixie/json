#include "parser.h"
#include <string>
#include <iostream>

using namespace xie::json;

Parser::Parser() : m_str(""), m_index(0) {}
void Parser::load(const std::string &str)
{
  m_str = str;
  m_index = 0;
}

void Parser::skip_blank()
{
  while (m_str[m_index] == ' ' || m_str[m_index] == '\n' || m_str[m_index] == '\r' || m_str[m_index] == '\t')
    m_index++;
}
char Parser::get_next_token()
{
  skip_blank();
  return m_str[m_index++];
}

Json Parser::parse()
{
  char ch = get_next_token();
  switch (ch)
  {
  case 'n':
    m_index--;
    return parse_null();
  case 't':
  case 'f':
    m_index--;
    return parse_bool();
  case '-':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    m_index--;
    return parse_number();
  case '"':
    return Json(parse_string());
  case '[':
    return parse_array();
  case '{':
    return parse_obj();

  default:
    break;
  }
  throw std::logic_error("unexpected char");
}
Json Parser::parse_null()
{
  if (m_str.compare(m_index, 4, "null") == 0)
    return Json();
  throw new std::logic_error("parse null error");
}
Json Parser::parse_bool()
{
  if (m_str.compare(m_index, 4, "true") == 0)
    return Json(true);
  else if (m_str.compare(m_index, 5, "false") == 0)
    return Json(false);
  throw new std::logic_error("parse bool error");
}
Json Parser::parse_number()
{
  int pos = m_index;
  if (m_str[m_index] == '-')
    m_index++;
  if (m_str[m_index] > '9' || m_str[m_index] < '0')
    throw new std::logic_error("parse number error");
  while (m_str[m_index] >= '0' && m_str[m_index] <= '9')
    m_index++;
  if (m_str[m_index] != '.')
  {
    int i = std::atoi(m_str.c_str() + pos);
    return Json(i);
  }
  m_index++;
  if (m_str[m_index] > '9' || m_str[m_index] < '0')
    throw new std::logic_error("parse number error");
  while (m_str[m_index] >= '0' && m_str[m_index] <= '9')
    m_index++;
  double f = std::atof(m_str.c_str() + pos);
  return Json(f);
}
Json Parser::parse_array()
{
  return Json();
}
Json Parser::parse_obj()
{
  return Json();
}
std::string Parser::parse_string()
{
  return std::string("");
}