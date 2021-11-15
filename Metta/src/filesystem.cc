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
Directory::Directory(string name, int id, Directory* parent) {
  this->name_ = name;
  this->owner_ = id;

  time_t time_; time(&time_);
  char tmp[80]; struct tm* tmp_tm = localtime(&time_);
  strftime(tmp, 80, "(%a) %b %d, %Y [%H:%M:%S]", tmp_tm);

  this->date_ = string(tmp);

  this->parent_ = parent;
}

// class DirOp
void DirOp::AddFile(Directory* d, File* add) {
  d->subfiles.emplace_back(add);
}

void DirOp::AddDir(Directory *d, Directory *add) {
  add->parent_ = d;
  d->subdirs.emplace_back(add);
}

void DirOp::DeleteFile(Directory* d, const string &name) {
  for (auto a = 0; a < d->subdirs.size(); ++a) {
    if (d->subfiles[a]->GetName() == name) {
      (new FileOp())->Write(d->subfiles[a], "");
      d->subdirs.erase(d->subdirs.begin() + a);
    }
  }
}

void DirOp::DeleteDir(Directory *d, const string &name) {
  for (auto a = 0; a < d->subdirs.size(); ++a) {
    if (d->subfiles[a]->GetName() == name) {
      d->subdirs[a]->subdirs.clear(); d->subdirs[a]->subfiles.clear();
      d->subdirs.erase(d->subdirs.begin() + a);
    }
  }
}

int DirOp::FindDir(Directory* d, string name) {
  int where = -1;
  for (int i = 0; i < d->subdirs.size(); ++i) {
    if (d->subdirs.at(i)->GetName() == name) {
      where = i;
    }
  }
  return where;
}

// class Program
Program::Program(std::string name, int (*func)(vector<string>), int id) {
  this->name_ = name;
  this->owner_ = id;

  time_t time_; time(&time_);
  char tmp[80]; struct tm* tmp_tm = localtime(&time_);
  strftime(tmp, 80, "(%a) %b %d, %Y [%H:%M:%S]", tmp_tm);

  this->date_ = string(tmp);

  this->func_ = func;
}

void Program::Run(vector<string> params) {
  this->func_(params);
}

// class FileSystem
FileSystem::FileSystem() {
  DirOp temp;

  root = Directory("", 0, nullptr);
  curr = root;

  temp.AddDir(&root, new Directory("System", 0, &root));
  temp.AddDir(&root, new Directory("Downloads", 0, &root));
  temp.AddDir(&root, new Directory("SoftWares", 0, &root));
  temp.AddDir(&root, new Directory("Bin", 0, &root));

  auto Bin = FindPath("Bin");
}

void VectorPrint(vector<string> vec) {
  for (auto & a : vec) {
    std::cout << "\"" + a + "\"" << " ";
  }
  std::cout << "\n" << flush;
}

Directory* FileSystem::FindPath(string path) {
  auto path_vec = Tools::Split(path);

  Directory* path_ = &curr;

  for (auto i = 0; i < path_vec.size(); ++i) {
    if (path_vec[i] == "" && i == 0) {
      path_ = &root;
    } else if (path_vec[i] == ".") {
      continue;
    } else if (path_vec[i] == "..") {
      path_ = path_->parent_;
    } else {
      auto subscript = DirOp::FindDir(path_, path_vec[i]);
      if (subscript == -1) path_ = nullptr;
      else path_ = path_->subdirs[subscript];
    }
  }

  return path_;
}

// namespace Tools
vector<string> Tools::Split(string str, string separator) {
  vector<string> ret;
  string s = str, sep = separator;

  int beg = 0, flag;

  while ((flag = s.find(sep, beg)) != -1) {
    ret.emplace_back(s.substr(beg, flag - beg));
    beg = flag + sep.length();
  }

  if (beg < s.length())
    ret.emplace_back(s.substr(beg, s.length() - beg));

  return ret;
}

} // namespace hackbit::filesystem