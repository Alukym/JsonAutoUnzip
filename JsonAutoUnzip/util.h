#pragma once
#include <vector>
#include <iostream>
#include <string>

std::vector<std::string> GetFileList(std::string InputDir);
inline bool CheckFile(std::vector<std::string> FileList, std::string FileName);
inline void DecompressZip(std::string FileName);
inline void DeleteDir(std::string DirName);