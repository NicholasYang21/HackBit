#pragma once

#include "../user.h"

#include <string>
#include <vector>

#include <ctime>

using std::string;
using std::vector;

namespace hackbit {

typedef int(*CmdFunc)(const vector<string>& argv, const User& user);

typedef string mode;
extern mode default_mode;

string GetTime();

class File {
public:
  File() = default;
  File(const string& fn, int uid);
  File(const string& fn, const string& content, int uid);

  int creator_id;
  string c_time;
  string name;
  string content;
  mode mode_;
};

class Executable : public File {
private:
  CmdFunc cmd;

public:
  Executable() = default;
  Executable(const string& fn, const CmdFunc& func, int uid);

  void Run(const vector<string>& argv, const User& user);
};

} // HackBit