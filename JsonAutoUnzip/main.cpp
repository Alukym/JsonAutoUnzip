#include <iostream>
#include <filesystem>
#include <sstream>
#include <Windows.h>

#include "unzip.h"
#include "SimpleIni.h"
#include "util.h"

using namespace std;

static CSimpleIni ini;

const string tpDirName = "\\teleport";
const string zipDirName = "\\zip";

int main(int argc, const char* argv[]) {
	string CurrentPath = filesystem::current_path().u8string();
	FILE* fp = fopen("cfg.ini", "a");
	fclose(fp);
	ini.SetUnicode();
	ini.LoadFile("cfg.ini");
	ini.SetValue("section", "key", "newvalue");
	
	string inputDir = CurrentPath + zipDirName + "\\*";
	vector<string> ZipList = GetZipList(inputDir);

	auto LastZip = ini.GetValue("AutoUnzip", "LastZip");
	if (LastZip == nullptr) {
		if (ZipList.size() == 0) {
			printf("[ERROR] 目录 %s 里没有zip文件，请检查目录是否为空！\n", (CurrentPath + zipDirName).c_str());
			system("pause");
			exit(-1);
		}
		LastZip = ZipList[0].c_str();
		char startFileName[512] = {};
		sprintf(startFileName, "%s%s%c%s", CurrentPath.c_str(), zipDirName.c_str(), '\\', LastZip);
		printf("[INFO] cfg.ini 中没有保存上次的记录\n从 %s 开始解压\n", startFileName);
		ini.SetValue("AutoUnzip", "LastZip", startFileName);
	}
	else {
		cout << "[INFO] 读取配置成功!\n上次的文件: " << LastZip << endl;
	}

	system("pause");
	return 0;
}