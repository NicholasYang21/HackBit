#pragma once

#include "directory.h"
#include "file.h"

#include <cstring>

namespace hackbit {

#define SYSTEM_NAME "sFS" // simple File System
#define VERSION "0.0.1" // eFS version

class FileSystem {
private:
  Directory root;
  Directory working; // work directory

public:
  FileSystem();
  
  void GenericBasic();

  static bool CheckFilePermission(const User& user, const File& file, char check);
  static bool CheckDirPermission(const User& user, const Directory& dir, char check);

  Directory* GetDirectory(const string& path);

  int AddFile(const string& fn, const User& user);
  int AddDirectory(const string& dn, const User& user);
  int DeleteFile(const string& fn, const User& user);
  int DeleteDirectory(const string& dn, const User& user);
  int ChangeDirectory(const string& dn, const User& user);
  
};

} // hackbit