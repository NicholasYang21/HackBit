#include "../include/fs.h"

namespace hackbit::fs {

// class 'File' :

File::File(File src, int uid) {
  // copies members.
  this->m_name = src.m_name;
  this->m_content = src.m_content;
  this->m_other_read = src.m_read;
  this->m_other_write = src.m_write;
  // sets uid.
  this->m_uid = uid;
}

void
File::Rename(std::string new_name) {
  // renames this.
  this->m_name = new_name;
}

void
File::Clear() {
  // clears the content.
  this->m_content = "";
}

constexpr const char*
File::GetName() {
  // return the name of this file.
  return this->m_name.c_str();
}

// class 'Directory':

Directory::Directory(Directory src, int uid, Directory* prt) {
  // copies members.
  this->m_name = src.m_name;
  this->m_sub_files = src.m_sub_files;
  this->m_sub_dirs = src.m_sub_dirs;
  this->m_other_read = src.m_read;
  this->m_other_write = src.m_write;
  // sets uid.
  this->m_uid = uid;
  // sets parent directory.
  this->m_parent = prt;
}

void
Directory::Remove() {
  // if this directory's subfiles vector is not empty:
  if ( !this->m_sub_files.empty() ) {
    // traversing vector:
    for ( auto &a : this->m_sub_files ) {
      // clear the contents.
      a->Clear();
      // change pointer address to zero (null pointer)
      a = nullptr;
    }
  }

  // if this directory is a leaf node in directory tree:
  if ( this->m_sub_dirs.empty() ) {
    return; // return.
  } else {
    // this directory is not a leaf node in directory tree:
    // recursively access subnode(s):
    for ( auto & a : this->m_sub_dirs ) {
      a->Remove();
    }
  }
}

constexpr const char *
Directory::GetName() {
  return this->m_name.c_str();
}

int
Directory::RemoveAll(int executor_uid) {
  int uid = executor_uid;

  // check permission.
  auto has_permission = CheckPermission(this->m_uid, uid, this->m_write);

  // if this user has write permission:
  if ( has_permission ) {
    this->Remove();
    return 0;
  }

  return -1; // oops: user has not permission to execute.
}

int
Directory::Create(std::string name, int executor_uid, int type) {
  int uid = executor_uid;

  // check permission.
  auto has_permission = CheckPermission(this->m_uid, uid, this->m_write);

  // if this user has write permission:
  if ( has_permission ) {
    // if user want to create a file:
    if ( type == 1 ) {
      // create a object pointer and push back.
      this->m_sub_files.push_back(new File(name, executor_uid));
    }
    // if user want to create a directory:
    if ( type == 2 ) {
      // create a object pointer and push back.
      this->m_sub_dirs.push_back(new Directory(name, executor_uid));
    }
  }

  return -1; // oops: user has not permission to execute.
}

int
Directory::RemoveSingle(std::string name, int executor_uid) {
  int uid = executor_uid;

  // check permission.
  auto has_permission = CheckPermission(this->m_uid, uid, this->m_write);

  // if this user has write permission:
  if ( has_permission ) {
    // if not such file or directory: we return 1.
    if ( this->m_sub_files.empty() && this->m_sub_dirs.empty() ) return 1;

    // traversing subfiles vector:
    for ( auto a = this->m_sub_files.begin(); a != this->m_sub_files.end(); ++a ) {
      // if find this file:
      if ( (*a)->GetName() == name ) {
        // erase the pointer.
        m_sub_files.erase(a);
        // return successful value.
        return 0;
      }
    }

    // traversing subdirectories vector:
    for ( auto a = this->m_sub_dirs.begin(); a != this->m_sub_dirs.end(); ++a ) {
      // if find this directory:
      if ( (*a)->GetName() == name ) {
        // erase the pointer.
        m_sub_dirs.erase(a);
        // return successful value.
        return 0;
      }
    }

    return 1; // no such file or directory.
  }

  return -1; // oops: user has not permission to execute.
}

// other functions:
bool
CheckPermission(int need_check_uid, int check_uid, bool is_given) {
  // if the check uid equals need check uid or check uid is 0 (Administrator):
  if ( need_check_uid == check_uid || check_uid == 0 ) return true;
  // if the permission was not give:
  if ( !is_given ) return false;
  // else, the permission has been given:
  return true;
}

} // namespace hackbit::fs