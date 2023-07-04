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
  {
    m_index++;
  }
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
    m_index--;
    return parse_array();
  case '{':
    // m_index--;
    return parse_obj();

  default:
    break;
  }
  throw std::logic_error("unexpected char");
}
Json Parser::parse_null()
{
  if (m_str.compare(m_index, 4, "null") == 0)
  {
    m_index += 4;
    return Json();
  }
  throw new std::logic_error("parse null error");
}
Json Parser::parse_bool()
{
  if (m_str.compare(m_index, 4, "true") == 0)
  {
    m_index += 4;
    return Json(true);
  }
  else if (m_str.compare(m_index, 5, "false") == 0)
  {
    m_index += 5;
    return Json(false);
  }
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
  Json arr = Json(Json::json_array);
  char ch = get_next_token();
  // m_index--;
  if (ch == ']')
    return arr;
  // m_index--;
  while (true)
  {
    arr.append(parse());
    ch = get_next_token();
    if (ch == ']')
      break;
    if (ch != ',')
      throw new std::logic_error("parse array error");
    skip_blank();
  }
  return arr;
}
Json Parser::parse_obj()
{
  Json obj(Json::json_object);
  char ch = get_next_token();
  if (ch == '}')
    return obj;
  m_index--;
  while (true)
  {
    ch = get_next_token();
    if (ch != '"')
      throw new std::logic_error("parse obj error");
    std::string key = parse_string();
    ch = get_next_token();
    if (ch != ':')
      throw new std::logic_error("parse obj error");
    obj[key] = parse();
    ch = get_next_token();
    if (ch == '}')
      break;
    if (ch != ',')
      throw new std::logic_error("parse obj error");
    skip_blank();
  }
  return obj;
}
std::string Parser::parse_string()
{
  std::string out;
  while (true)
  {
    char ch = m_str[m_index++];
    if (ch == '"')
      break;
    if (ch == '\\')
    {
      ch = m_str[m_index++];
      switch (ch)
      {
      case '\n':
        out += '\n';
        break;
      case '\t':
        out += '\t';
        break;
      case '\r':
        out += '\r';
        break;
      case '\b':
        out += '\b';
        break;
      case '\f':
        out += '\f';
        break;
      case '"':
        out += "\\\"";
        break;
      case '\\':
        out += "\\\\";
        break;
      case 'u':
        out += "\\u";
        for (int i = 0; i < 4; i++)
          out += m_str[m_index++];
        break;
      default:
        break;
      }
    }
    else
      out += ch;
  }
  return out;
}