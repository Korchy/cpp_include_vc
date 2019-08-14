//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "stdafx.h"		// ��� ���������� ��������
#include "Options.h"
//---------------------------------------------------------------------------
Options::Options(void) {
        // ����������� ������
File = "";
Data = NULL;
}
//---------------------------------------------------------------------------
Options::~Options() {
        // ���������� ������
        // ������� ��� ��������� �� ������ ��������
while(Data!=NULL) {
        DataStruc* TmpStruc = Data->pr;
        delete Data;
        Data = TmpStruc;
        }
}
//---------------------------------------------------------------------------
bool Options::Load() {
        // �������� ������ �� �����
if(File=="") return false;
        // �������� ������ �� �����
FILE *F;
long FileSize;
char *TmpFile;
if(fopen_s(&F,File.c_str(),"rb")==NULL) {
	fseek(F,0,SEEK_END);
	FileSize = ftell(F);	// ���������� �� 1 ���� ������, ��� � ����� �.�. ��� ����� "����� ������"
	TmpFile = new char[FileSize];
	fseek(F,0,SEEK_SET);
	fread(TmpFile,FileSize,1,F);
	TmpFile[FileSize-1] = 0;	// �������� "����� ������"
	fclose(F);
}
else return false;
std::string TmpStr = std::string(TmpFile);
//MessageBox(NULL,(TmpStr).c_str(),"",MB_OK);
delete [] TmpFile;
	// ��������� � ���������
DataStruc* TmpStruc1,* TmpStruc2;
while(!TmpStr.empty()) {
	TmpStruc1 = new DataStruc();
	TmpStruc1->Name = TmpStr.substr(0,TmpStr.find("=",0));
	TmpStr.erase(0,TmpStr.find("=",0)+1);
	TmpStruc1->Value = TmpStr.substr(0,TmpStr.find(";",0));
	TmpStr.erase(0,TmpStr.find(";",0)+1);
	if(TmpStr.find("\n",0)!=-1) {
		TmpStruc1->Comment = TmpStr.substr(0,TmpStr.find("\n",0));
		TmpStr.erase(0,TmpStr.find("\n",0)+1);
	}
	else {
		TmpStruc1->Comment = TmpStr;
		TmpStr = "";
	}
	TmpStruc1->pr = NULL;
	if(Data==NULL) Data = TmpStruc1;
	else TmpStruc2->pr = TmpStruc1;
	TmpStruc2 = TmpStruc1;
}
return true;
}
//---------------------------------------------------------------------------
bool Options::Save() {
	// ���������� ������ � ����
if(File=="") return false;
	// ������� ������ � �������
std::string TmpStr;
	// ��������� � ��� ������ �� ��������
DataStruc* TmpStruc = Data;
while(TmpStruc!=NULL) {
	TmpStr += TmpStruc->Name + "=" + TmpStruc->Value + ";" + TmpStruc->Comment+"\n";
	TmpStruc = TmpStruc->pr;
}
	// ��������� � ����
FILE *F;
if(fopen_s(&F,File.c_str(),"wb")==NULL) {
	fwrite(TmpStr.c_str(),TmpStr.size(),1,F);
	fclose(F);
}
else return false;
return true;
}
//---------------------------------------------------------------------------
std::string Options::FindByName(std::string Name) {
	// �������� �������� �� �����
if(Data==NULL) return "";
	// ������������ ��������
std::string Rez = "";
	// ��������� �� ���� ����������, �������� �����
DataStruc* TmpStruc = Data;
while(TmpStruc!=NULL) {
	if(TmpStruc->Name==Name) {
		// ���� ��� ������ - �������� ��������
		Rez = TmpStruc->Value;
		break;
	}
	TmpStruc = TmpStruc->pr;
}
	// ������� ���������� ��������
return Rez;
}
//---------------------------------------------------------------------------
void Options::SetByName(std::string Name, std::string Value) {
	// �������� �������� �� ��� �����
if(Data==NULL) return;
	// ��������� �� ���� ����������, �������� �����
DataStruc* TmpStruc = Data;
while(TmpStruc!=NULL) {
	if(TmpStruc->Name==Name) {
		// ���� ��� ������ - ������� ��������
		TmpStruc->Value = Value;
		break;
	}
	TmpStruc = TmpStruc->pr;
}
}
//---------------------------------------------------------------------------