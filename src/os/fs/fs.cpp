#include "../../../include/os/fs/fs.h"

using hackbit::FileSystem;
using hackbit::Directory;

FileSystem::FileSystem() {
  GenericBasic();
}

void FileSystem::GenericBasic() {

}

bool FileSystem::CheckFilePermission(const User& user, const File& file, char check) {
  if (user.uid == 0) return true;
  if (user.uid == file.creator_id) {
    if (file.mode_.substr(0, 3).find(check) != string::npos) {
      return true;
    }
    return false;
  }
  return (file.mode_.substr(3, 3).find(check) != string::npos);
}

bool FileSystem::CheckDirPermission(const User& user, const Directory& dir, char check) {
  if (user.uid == 0) return true;
  if (user.uid == dir.creator_id) {
    if (dir.mode_.substr(0, 3).find(check) != string::npos) {
      return true;
    }
    return false;
  }
  return (dir.mode_.substr(3, 3).find(check) != string::npos);
}

Directory* FileSystem::GetDirectory(const string& path) {
  Directory* ret = nullptr;
  vector<string> Path = split(path, "/");

  if (Path.empty()) return nullptr;
  if (Path[0].empty()) ret = &root;
  for (auto & a : Path) {
    if (a.empty() && a != Path[0]) {
      return nullptr;
    }
    if (a == ".") continue;
    if (a == "..") {
      if (ret->father != nullptr) {
        ret = ret->father;
      }
      else return nullptr;
    } else {
      if (ret->dirs.empty()) return nullptr;
      for (auto & p : ret->dirs) {
        if (a == p->name) { ret = p; break; }
        if (a != p->name && p == *(ret->dirs.end() - 1)) return nullptr;
      }
      continue;
    }
  }
  return ret;
}

int FileSystem::AddFile(const string& fn, const User& user) {
  
}