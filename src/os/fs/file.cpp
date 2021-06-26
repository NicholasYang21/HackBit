#pragma warning(disable : 4996)
#include "../../../include/os/fs/file.h"

// R: Read, W: Write, A: Action
hackbit::mode hackbit::default_mode = "RWAR--"; // default open mode

using hackbit::File;
using hackbit::Executable;

File::File(const string& fn, int uid) {
  this->name = fn;
  this->content.clear();
  this->mode_ = default_mode;
  this->c_time = GetTime();
  this->c_time = GetTime(); this->creator_id = uid;
}

File::File(const string& fn, const string& content, int uid) {
  this->name = fn;
  this->content = content;
  this->mode_ = default_mode;
  this->c_time = GetTime();
  this->c_time = GetTime(); this->creator_id = uid;
}

string hackbit::GetTime() {
  char tmp[64];
  auto tm = time(nullptr);
  strftime(tmp, 64, "%b %d %Y %H:%M", localtime(&tm));
  return string(tmp);
}

Executable::Executable(const string& fn, const CmdFunc& func, int uid) {
  this->name = fn;
  this->content = content;
  this->mode_ = default_mode;
  this->c_time = GetTime();
  this->cmd = func;
  this->c_time = GetTime(); this->creator_id = uid;
}

void Executable::Run(const vector<string>& argv, const User& user) {
  this->cmd(argv, user);
}