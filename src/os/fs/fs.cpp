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
  vector<string> Path;
  if (path[0] == '/') ret = &root;
  auto tok = strtok((char*)path.c_str(), "/");
  while (tok != nullptr) {
    tok = strtok(nullptr, "/");
    
  }
}

int FileSystem::AddFile(const string& fn, const User& user) {
  
}