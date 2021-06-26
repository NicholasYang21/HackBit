#include "../../../include/os/fs/directory.h"

using hackbit::Directory;

Directory::Directory(const string& dn, int uid) {
  this->name = dn;
  this->files.clear();
  this->dirs.clear();
  this->mode_ = default_mode;
  this->c_time = GetTime();
  this->creator_id = uid;
}