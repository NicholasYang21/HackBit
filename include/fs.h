#ifndef HACKBIT_FS_H
#define HACKBIT_FS_H

#include <string>
#include <vector>

namespace hackbit::fs {

// NAME:
//   File
// DESCRIPTION:
//   This class declared a part of filesystem.
//   the file has filename, content.
//   and r-w permission.

class File {
private:
  std::string m_name; // name of file
  std::string m_content; // contents of file

  int m_uid; // UID of creator

  bool m_other_read = true; // other users' read permission
  bool m_other_write = false; // other users' read permission
  bool& m_read = this->m_other_read; // a reference
  bool& m_write = this->m_other_write; // a reference

public:
  // NAME:
  //   File
  // PARAMS:
  //   None
  // DESCRIPTION:
  //   the default constructor of class 'File'.
  File() = default;

  // NAME:
  //   File
  // PARAMS:
  //   name: std::string, uid: int
  // DESCRIPTION:
  //   sets 'm_name', 'm_uid' and clears 'm_content'.
  File(std::string name, int uid) :
    m_name{name}, m_content{}, m_uid{uid}
  { }

  // NAME:
  //   File
  // PARAMS:
  //   name: std::string; content: std::string; uid: int
  // DESCRIPTION:
  //   sets 'm_name', 'm_uid' and writes some content to 'm_content'.
  File(std::string name, std::string content, int uid) :
    m_name{name}, m_content{std::move(content)}, m_uid{uid}
  { }

  // NAME:
  //   File
  // PARAMS:
  //   src: const File&, uid: int
  // DESCRIPTION:
  //   copies all members from 'src', and sets 'm_uid'.
  File(File src, int uid);

  // NAME:
  //   Rename
  // PARAMS:
  //   new_name: std::string
  // RETURNS:
  //   None
  // DESCRIPTION:
  //   renames the name of this file.
  void
  Rename(std::string new_name);

  // NAME:
  //   Clear
  // PARAMS:
  //   None
  // RETURNS:
  //   None
  // DESCRIPTION:
  //   clears the contents of this file.
  void
  Clear();

  // NAME:
  //   GetName
  // PARAMS:
  //   None
  // RETURNS:
  //   A C-Style string
  // DESCRIPTION:
  //   gets the name of file.
  constexpr const char*
  GetName();
};

// NAME:
//   Directory
// DESCRIPTION:
//   this class declared a part of filesystem.
//   the directory has name, subfiles, subdirectories.
//   and r-w permission.

class Directory {
private:
  Directory* m_parent; // parent directory

  std::vector<File*> m_sub_files; // subfiles of this directory
  std::vector<Directory*> m_sub_dirs; // subdirectories of this directory
  std::string m_name; // name of directory

  int m_uid; // UID of creator

  bool m_other_read = true; // other users' read permission
  bool m_other_write = false; // other users' read permission
  bool& m_read = this->m_other_read; // a reference
  bool& m_write = this->m_other_write; // a reference

private:
  // NAME:
  //   Removing
  // PARAMS:
  //   None
  // RETURNS:
  //   None
  // DESCRIPTION:
  //   a auxiliary function. to removes all data from this directory.
  void
  Remove();

public:
  // NAME:
  //   Directory
  // PARAMS:
  //   None
  // DESCRIPTION:
  //   the default constructor of class 'Directory'.
  Directory() = default;

  // NAME:
  //   Directory
  // PARAMS:
  //   name: std::string, uid: int, prt: Directory* (default = nullptr)
  // DESCRIPTION:
  //   sets 'm_name', 'm_uid'.
  Directory(std::string name, int uid, Directory* prt = nullptr) :
    m_name{name}, m_uid{uid}, m_parent{prt}
  {}

  // NAME:
  //   Directory
  // PARAMS:
  //   src: const Directory&, uid: int, prt: Directory* (default = nullptr)
  // DESCRIPTION:
  //   copies all members from 'src' and sets 'm_uid'.
  Directory(Directory src, int uid, Directory* prt = nullptr);

  // NAME:
  //   GetName
  // PARAMS:
  //   None
  // RETURNS:
  //   A C-Style string
  // DESCRIPTION:
  //   gets the name of directory.
  constexpr const char*
  GetName();

  // NAME:
  //   RemoveAll
  // PARAMS:
  //   executor_uid: int
  // RETURNS:
  //   an integer, indicates whether executed was successful.
  // DESCRIPTION:
  //   recursively removes all subfiles and subdirectories.
  int
  RemoveAll(int executor_uid);

  // NAME:
  //   Create
  // PARAMS:
  //   name: std::string, executor_uid: int, type: int (default = 1)
  // IMPORTANT PARAMS:
  //   type: 1 indicates file, 2 indicates directory.
  // RETURNS:
  //   an integer, indicates whether executed was successful.
  // DESCRIPTION:
  //   creates a file or directory to this directory.
  int
  Create(std::string name, int executor_uid, int type = 1);

  // NAME:
  //   Remove
  // PARAMS:
  //   name: std::string, executor_uid: int
  // NOTE:
  //   the subfiles vector or subdirectories vector may be null.
  //   if two vectors are null, or cannot finds the file (directory),
  //   we return a special value: 1.
  // RETURNS:
  //   an integer, indicates whether executed was successful.
  // DESCRIPTION:
  //   removes a file or directory from this directory.
  int
  RemoveSingle(std::string name, int executor_uid);
};

class FileSystem {
private:
  Directory m_root; // the root directory of filesystem.
  Directory* m_working; // working directory.

public:
  // TODO
};

// NAME:
//   CheckPermission
// PARAMS:
//   need_check_uid: int, check_uid: int, is_given: bool
// IMPORTANT PARAMS:
//   is_given: indicates the permission has been given.
// RETURNS:
//   a boolean, indicates whether the user has permission to execute commands.
// DESCRIPTION:
//   check the permission, then transfer to other functions.
bool
CheckPermission(int need_check_uid, int check_uid, bool is_given);

} // namespace hackbit::fs

#endif // HACKBIT_FS_H