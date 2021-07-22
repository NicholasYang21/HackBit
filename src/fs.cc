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

Directory::Directory(Directory src, int uid) {
  // copies members.
  this->m_name = src.m_name;
  this->m_sub_files = src.m_sub_files;
  this->m_sub_dirs = src.m_sub_dirs;
  this->m_other_read = src.m_read;
  this->m_other_write = src.m_write;
  // sets uid.
  this->m_uid = uid;
}

void
Directory::AuxiliaryRemoveAll() {
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
      a->AuxiliaryRemoveAll();
    }
  }
}

int
Directory::RemoveAll(int executor_uid) {
  int uid = executor_uid;

  // uid is 0 indicating executor is administrator.
  if ( uid == 0 || uid == this->m_uid ) {
    AuxiliaryRemoveAll();
    return 0;
  }

  // if other users can change this directory
  if ( m_write ) {
    AuxiliaryRemoveAll();
    return 0;
  }
  return -1; // oops: user has not permission to execute.
}

} // namespace hackbit::fs