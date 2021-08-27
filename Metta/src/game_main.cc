// Copyright (c) Ink, 2021. All rights reserved.
// LICENSE(MIT)
// If you want to use this file, please reserve this note and the License.
// this file is a part of HackBit.

#include "../include/filesystem.h"

int main() {
  hackbit::filesystem::File f("nmsl", 0);
  hackbit::filesystem::FileOp op;
  op.Write(&f, "f\nu\nc\nk\n♂", 1);
  op.Display(&f);
}