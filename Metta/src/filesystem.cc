// This file is a part of HackBit.
// Copyright (c) 2021, Ink. All rights reserved.

#include "../include/filesystem.h"

namespace hackbit::filesystem {

// class File

File::File(string name, int id) {
  this->name_ = name;
  this->owner_ = id;

  time_t time_; time(&time_);
  char tmp[80]; struct tm* tmp_tm = localtime(&time_);
  strftime(tmp, 80, "(%a) %b %d, %Y [%H:%M:%S]", tmp_tm);

  this->date_ = string(tmp);

  // this->Write("", 0);
}

string& File::GetName() {
  return this->name_;
}

int File::GetOwner() {
  return this->owner_;
}

string File::GetDate() {
  return this->date_;
}

// class FileOp

void FileOp::SetUID(File* f, int new_uid) {
  f->owner_ = new_uid;
}

void FileOp::Write(File* f, string contents, int mode) {
  switch (mode) {
    case 0:
      f->content_.clear(); f->content_.append(contents); break;
    case 1:
      f->content_.append(contents); break;
    default:
      break;
  }
}

void FileOp::Display(File* f) {
  cout << f->content_ << flush;
}

// class Directory
Directory::Directory(string name, int id) {
  this->name_ = name;
  this->owner_ = id;

  time_t time_; time(&time_);
  char tmp[80]; struct tm* tmp_tm = localtime(&time_);
  strftime(tmp, 80, "(%a) %b %d, %Y [%H:%M:%S]", tmp_tm);

  this->date_ = string(tmp);
}

} // namespace hackbit::filesystem