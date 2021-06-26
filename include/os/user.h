#pragma once

#include <string>
using std::string;

namespace hackbit {

class User {
public:
  User() = default;
  User(const string& name, int uid) : name(name), uid(uid) {}
  User(const string& name, const string& passwd, int uid) : name(name), passwd(passwd), uid(uid) {}

  string name;
  string passwd;
  int uid;
};

} // hackbit