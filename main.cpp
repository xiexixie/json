#include <iostream>
#include <fstream>
#include <sstream>
#include "json.h"

using namespace xie::json;

int main()
{
  // const std::string &str = "{\"a\":\"world\",\"b\":[1,2,3,true,\"qqq\"],\"hello\":null}";
  std::ifstream fin("./test.json");
  std::stringstream ss;
  ss << fin.rdbuf();
  const std::string &str = ss.str();
  Json v;
  v.parse(str);
  Json a = v["tasks"]["args"];
  std::cout << a.str();
  a.clear();
  v.clear();
  return 0;
}