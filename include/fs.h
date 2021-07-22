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
  //   AuxiliaryRemoveAll
  // PARAMS:
  //   None
  // RETURNS:
  //   None
  // DESCRIPTION:
  //   a auxiliary function, to remove all data from this directory.
  void
  AuxiliaryRemoveAll();

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
  //   name: std::string, uid: int
  // DESCRIPTION:
  //   sets 'm_name', 'm_uid'.
  Directory(std::string name, int uid) :
    m_name{name}, m_uid{uid}
  {}

  // NAME:
  //   Directory
  // PARAMS:
  //   src: const Directory&
  // DESCRIPTION:
  //   copies all members from 'src' and sets 'm_uid'.
  Directory(Directory src, int uid);

  // NAME:
  //   RemoveAll
  // PARAMS:
  //   executor_uid: int
  // RETURNS:
  //   an integer, indicates whether executing is successful.
  // DESCRIPTION:
  //   recursively removes all subfiles and subdirectories.
  int
  RemoveAll(int executor_uid);
};

} // namespace hackbit::fs

#endif // HACKBIT_FS_H