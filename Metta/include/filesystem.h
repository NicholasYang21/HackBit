// This file is a part of HackBit.
// Copyright (c) 2021, Ink. All rights reserved.

#ifndef HACKBIT_FILESYSTEM_H
#define HACKBIT_FILESYSTEM_H

#include <time.h>

#include <map>
#include <string>
#include <vector>
#include <iostream>

using std::map;
using std::cout;
using std::flush;
using std::string;
using std::vector;

/**
 *
 * @brief This namespace includes three classes:
 *        File, Directory, Filesystem.
 *        These classes simulates a simple filesystem.
 */
namespace hackbit::filesystem {

/**
 *
 * @brief This is a basic unit in the HackBit-filesystem(HFS).
 *        This class simulates a file.
 *        And the class describe the necessary elements of a file.
 */
class File {
 public:
  File() = default;

  /**
   * @brief This constructor will sets the name and owner's UID.
   * @param [in] name filename.
   * @param [in] id owner's UID.
   */
  explicit File(string name, int id);

  /**
   * @brief Gets the name of this file.
   * @return name of this file.
   */
  string& GetName();

  /**
   * @brief Gets the owner's UID.
   * @return UID of owner of this file.
   */
  int GetOwner();

  /**
   * @brief Gets the created date.
   * @return the created date of this file.
   */
  string GetDate();

 protected:
  int owner_; /**< the UID of owner of this file. */

  string date_; /**< created date of this file. */

  string name_; /**< the name of file. */

 private:
  friend class FileOp; friend class Interpreter;

  string content_; /**< the contents of file. */
};

/**
 *
 * @brief This is a auxiliary unit in the HackBit-filesystem(HFS).
 *        This class declared necessary actions of a file.
 */
class FileOp {
 public:
  /**
   * @brief This function will set the new owner's UID to a file.
   * @param [in] f will be operated file.
   * @param [in] new_uid need binds UID.
   */
  static void SetUID(File* f, int new_uid);

  /**
   * @brief This function will writes some contents to file follows the 'mode'.
   * @param [in] f will be operated file.
   * @param [in] contents writes content.
   * @param [in] mode writing mode, mode == 0, clears all current contents and write.
   *                  mode == 1, appends the contents.
   */
  static void Write(File* f, string contents, int mode = 0);

  /**
   * @brief This function displays the contents of a file.
   * @param [in] f will be displayed file.
   */
  static void Display(File* f);
};

/**
 *
 * @brief This is a basic unit in the HackBit-filesystem(HFS).
 *        This class simulates a directory.
 *        And the class describe the necessary elements of a directory.
 */
class Directory : public File {
 public:
  Directory() = default;

  /**
   * @brief This constructor will sets the directory's name and owner's UID.
   * @param name the name of dir.
   * @param id the owner's UID of dir.
   */
  explicit Directory(string name, int id, Directory* parent);

 private:
  friend class DirOp;
  friend class FileSystem;

  Directory* parent_; /**< The parent of directory. */

  vector<File*> subfiles; /**< The sub files of this directory. */
  vector<Directory*> subdirs; /**< The sub directories of this directory. */
};

/**
 *
 * @brief This is a auxiliary unit in the HackBit-filesystem(HFS).
 *        This class declared necessary actions of a directory.
 */
class DirOp {
 public:
  /**
   * @brief add a file to a directory.
   * @param [in] d destination directory.
   * @param [in] add will be added file.
   */
  static void AddFile(Directory* d, File* add);

  /**
   * @brief add a directory to another directory.
   * @param [in] d destination directory.
   * @param [in] add will be added directory.
   */
  static void AddDir(Directory* d, Directory* add);

  /**
   * @brief delete a file from directory.
   * @param [in] d parent directory.
   * @param [in] name will be deleted directory's name.
   */
  static void DeleteFile(Directory* d, const string& name);

  /**
   * @brief delete a directory from its parent directory.
   * @param [in] d parent directory.
   * @param [in] name will be deleted directory's name.
   */
  static void DeleteDir(Directory* d, const string& name);

  /**
   * @brief find a subdir.
   * @param [in] d parent directory.
   * @param [in] name
   * @return find operation was success or not.
   */
  static int FindDir(Directory* d, string name);
};

class Program : public File {
 public:
  /**
   * @brief This constructor will sets the name, function, and the id of the file.
   * @param name file's name.
   * @param func program.
   * @param id owner's UID.
   */
  Program(std::string name, int (*func)(vector<string>), int id);

  /**
   * @brief Run this program.
   */
  void Run(vector<string>);

 private:
  int (*func_)(vector<string>);
};

/**
 *
 * @brief This is the main(core) unit in the HackBit-filesystem(HFS).
 *        This class simulated a filesystem.
 */
class FileSystem {
 public:
  /**
   * @brief Init this filesystem.
   */
  FileSystem();

  /**
   *
   * @brief Find the path of a directory/file.
   * @param [in] path The path to be found.
   * @return a directory indicates the file/dirs' parent directory.
   */
  Directory* FindPath(string path);

 private:
  Directory root; /**< root directory in a filesystem. */
  Directory curr; /**< working directory */
};

/**
 *
 * @brief This is the auxiliary unit in the HackBit-Main-Part(HMP).
 *        This class supplies the tool functions.
 */
class Tools {
 public:
  /**
   *
   * @brief This function can split a string follow some rule (separator).
   * @param [in] str The string to be split.
   * @param [in] separator The rule(separator).
   * @return a vector, all substrings are in it.
   */
  static vector<string> Split(string str, string separator = "/");
};

} // namespace hackbit::filesystem

#endif // HACKBIT_FILESYSTEM_H
