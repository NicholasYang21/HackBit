// This file is a part of HackBit.
// Copyright (c) 2021, Ink. All rights reserved.

#ifndef HACKBIT_FILESYSTEM_H
#define HACKBIT_FILESYSTEM_H

#include <string>
#include <vector>

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


 private:
  string name; /**< the name of file. */
  string content; /**< the contents of file. */
};

} // namespace hackbit::filesystem

#endif // HACKBIT_FILESYSTEM_H
