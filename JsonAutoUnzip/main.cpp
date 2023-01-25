//�Ҿ���Ӧ�ò���Ҫע�Ͱ�... ���������������
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
			printf("[ERROR] Ŀ¼ %s ��û���ļ����뽫zip�ļ������Ŀ¼��\n", (CurrentPath + zipDirName).c_str());
			system("pause");
			exit(0);
		}
		printf("[INFO] cfg.ini ��û�б����ϴεļ�¼\n�� %s ��ʼ��ѹ\n", ZipList[0].c_str());
		ini.SetValue("AutoUnzip", "LastZip", ZipList[0].c_str());
	}
	else {
		if (CheckFile(ZipList, LastZip))
			cout << "[INFO] ��ȡzip���óɹ�!\n�ϴε��ļ�: " << LastZip << endl;
		else {
			cout << "[ERROR] ��ȡzip����ʧ�ܣ��ļ�������!\n�ļ���: " << LastZip << endl;
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
		cout << "[INFO] ��ȡtp�ļ����óɹ�!\n�ϴε��ļ�: " << LastTp << endl;
	ini.SaveFile("cfg.ini");

	DecompressZip(ZipList[0]);
	DeleteDir(CurrentPath + tpDirName);

	ini.SaveFile("cfg.ini");
	system("pause");
	return 0;
}