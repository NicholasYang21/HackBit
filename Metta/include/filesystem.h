// This file is a part of HackBit.
// Copyright (c) 2021, Ink. All rights reserved.

#ifndef HACKBIT_FILESYSTEM_H
#define HACKBIT_FILESYSTEM_H

#include <time.h>

#include <string>
#include <vector>
#include <iostream>

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
  friend class FileOp;

  string content_; /**< the contents of file. */
};

class FileOp {
 public:
  /**
   * @brief This function will set the new owner's UID to a file.
   * @param [in] f will be operated file.
   * @param [in] new_uid need binds UID.
   */
  void SetUID(File* f, int new_uid);

  /**
   * @brief This function will writes some contents to file follows the 'mode'.
   * @param [in] f will be operated file.
   * @param [in] contents writes content.
   * @param [in] mode writing mode, mode == 0, clears all current contents and write.
   *                  mode == 1, appends the contents.
   */
  void Write(File* f, string contents, int mode = 0);

  /**
   * @brief This function displays the contents of a file.
   * @param [in] f will be displayed file.
   */
  void Display(File* f);
};

/**
 *
 * @brief This is a basic unit in the HackBit-filesystem(HFS).
 *        This class simulates a directory.
 *        And the class describe the necessary elements of a directory.
 */
class Directory : public File {
 public:


 private:
  vector<File*> subfiles; /**< The sub files of this directory. */
  vector<Directory*> subdirs; /**< The sub directories of this directory. */
};

} // namespace hackbit::filesystem

#endif // HACKBIT_FILESYSTEM_H
