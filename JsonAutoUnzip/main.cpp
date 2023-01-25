//我觉得应该不需要注释吧... 这输出都很明显了
#include <iostream>
#include <filesystem>
#include <sstream>
#include <Windows.h>

#include "includes/SimpleIni.h"
#include "util.h"

using namespace std;

static CSimpleIni ini;

const string tpDirName = "\\teleports";
const string zipDirName = "\\zip";

int main(int argc, char* argv[]) {
	string CurrentPath = filesystem::current_path().u8string();
	//ini.SetUnicode();
	ini.LoadFile("cfg.ini");
	
	string inputDir = CurrentPath + zipDirName + "\\*";
	vector<string> ZipList = GetFileList(inputDir);

	auto LastZip = ini.GetValue("AutoUnzip", "LastZip");
	if (LastZip == nullptr) {
		if (ZipList.size() == 0) {
			printf("[ERROR] 目录 %s 里没有文件，请将zip文件放入该目录！\n", (CurrentPath + zipDirName).c_str());
			system("pause");
			exit(0);
		}
		printf("[INFO] cfg.ini 中没有保存上次的记录\n从 %s 开始解压\n", ZipList[0].c_str());
		ini.SetValue("AutoUnzip", "LastZip", ZipList[0].c_str());
	}
	else {
		if (CheckFile(ZipList, LastZip))
			cout << "[INFO] 读取zip配置成功!\n上次的文件: " << LastZip << endl;
		else {
			cout << "[ERROR] 读取zip配置失败，文件不存在!\n文件名: " << LastZip << endl;
			#ifdef _DEBUG
				cout << endl;
				for (int i = 0; i < ZipList.size(); i++) {
					cout << ZipList[i] << endl;
				}
				cout << endl;
			#endif
			system("pause");
			exit(0);
		}
	}

	inputDir = CurrentPath + tpDirName + "\\*";
	vector<string> TpList = GetFileList(inputDir);
	auto LastTp = ini.GetValue("AutoUnzip", "LastTp");
	if (LastTp != nullptr)
		cout << "[INFO] 读取tp文件配置成功!\n上次的文件: " << LastTp << endl;
	ini.SaveFile("cfg.ini");

	DecompressZip(ZipList[0]);
	DeleteDir(CurrentPath + tpDirName);

	ini.SaveFile("cfg.ini");
	system("pause");
	return 0;
}