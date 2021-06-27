#include "../../include/functions/split.h"

vector<string> split(const string& str, const string& delim) {
  vector<string> ret;
  size_t beg = 0, flag = str.find(delim);

  while (flag != string::npos) {
    ret.push_back(str.substr(beg, flag - beg));

    beg = flag + delim.size();
    flag = str.find(delim, beg);
  }

  if (beg != str.size()) {
    ret.push_back(str.substr(beg, str.size() - beg));
  }
  return ret;
}