#include <Windows.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include <filesystem>

#include "includes/unzip.h"

using namespace std;

vector<string> GetFileList(string InputDir) {
	vector<string> ret;
	WIN32_FIND_DATA fd;

	HANDLE hFind = FindFirstFile(InputDir.c_str(), &fd);

	if (hFind == INVALID_HANDLE_VALUE) {
		printf("[ERROR] Ä¿Â¼ %s ²»´æÔÚ!\n", InputDir.c_str());
		#ifdef _DEBUG
			printf("[DEBUG] GetLastError = %d\n", GetLastError());
		#endif
		system("pause");
		exit(0);
	}

	InputDir.pop_back();
	do
		if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			ret.push_back(InputDir + fd.cFileName);
	while (FindNextFile(hFind, &fd) != NULL);

	FindClose(hFind);
	return ret;
}

inline bool CheckFile(vector<string> FileList, string FileName) {
	for (int i = 0; i < FileList.size(); i++) {
		if (FileList[i] == FileName)
			return true;
	}
	return false;
}

inline void DecompressZip(string FileName) {
	HZIP hz = OpenZip(FileName.c_str(), 0);

	ZIPENTRY ze;
	GetZipItem(hz, -1, &ze);
	
	int cnt = ze.index;

	for (int i = 0; i < cnt; i++) {
		GetZipItem(hz, i, &ze);
		UnzipItem(hz, i, ze.name);
	}

	CloseZip(hz);
}

inline void DeleteDir(string DirName) {
	char cmd[256] = {};
	sprintf(cmd, "del /f /q %s", DirName.c_str());
	system(cmd);
}