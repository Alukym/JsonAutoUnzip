#include <iostream>
#include <filesystem>
#include <sstream>
#include <Windows.h>

#include "includes/unzip.h"
#include "includes/SimpleIni.h"
#include "util.h"

using namespace std;

static CSimpleIni ini;

const string tpDirName = "\\teleport";
const string zipDirName = "\\zip";

int main(int argc, const char* argv[]) {
	string CurrentPath = filesystem::current_path().u8string();
	ini.SetUnicode();
	ini.LoadFile("cfg.ini");
	
	string inputDir = CurrentPath + zipDirName + "\\*";
	vector<string> ZipList = GetZipList(inputDir);

	auto LastZip = ini.GetValue("AutoUnzip", "LastZip");
	if (LastZip == nullptr) {
		if (ZipList.size() == 0) {
			printf("[ERROR] Ŀ¼ %s ��û���ļ����뽫zip�ļ������Ŀ¼��\n", (CurrentPath + zipDirName).c_str());
			system("pause");
			exit(-1);
		}
		LastZip = ZipList[0].c_str();
		char startFileName[512] = {};
		sprintf(startFileName, "%s%s%c%s", CurrentPath.c_str(), zipDirName.c_str(), '\\', LastZip);
		printf("[INFO] cfg.ini ��û�б����ϴεļ�¼\n�� %s ��ʼ��ѹ\n", startFileName);
		ini.SetValue("AutoUnzip", "LastZip", startFileName);
	}
	else {
		cout << "[INFO] ��ȡ���óɹ�!\n�ϴε��ļ�: " << LastZip << endl;
	}

	ini.SaveFile("cfg.ini");
	system("pause");
	return 0;
}