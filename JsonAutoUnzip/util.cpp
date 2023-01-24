#include <Windows.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <filesystem>

using namespace std;

vector<string> GetZipList(string InputDir) {
	vector<string> ret;
	WIN32_FIND_DATA fd;

	HANDLE hFind = FindFirstFile(InputDir.c_str(), &fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		DWORD errCode = GetLastError();
		printf("[ERROR] 查找目录 %s 时错误,请确认zip目录是否存在!\n[DEBUG] GetLastError = %d\n", InputDir.c_str(), errCode);
		system("pause");
		exit(errCode);
	}

	do {
		if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			ret.push_back(fd.cFileName);
		}
	} while (FindNextFile(hFind, &fd) != NULL);

	FindClose(hFind);
	return ret;
}