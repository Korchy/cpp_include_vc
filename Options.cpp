//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include "stdafx.h"		// Для правильной линковки
#include "Options.h"
//---------------------------------------------------------------------------
Options::Options(void) {
        // Конструктор класса
File = "";
Data = NULL;
}
//---------------------------------------------------------------------------
Options::~Options() {
        // Деструктор класса
        // Удаляем все структуры из списка настроек
while(Data!=NULL) {
        DataStruc* TmpStruc = Data->pr;
        delete Data;
        Data = TmpStruc;
        }
}
//---------------------------------------------------------------------------
bool Options::Load() {
        // Загрузка данных из файла
if(File=="") return false;
        // Получить данные из файла
FILE *F;
long FileSize;
char *TmpFile;
if(fopen_s(&F,File.c_str(),"rb")==NULL) {
	fseek(F,0,SEEK_END);
	FileSize = ftell(F);	// Возвращает на 1 байт больще, что и нужно т.к. еще нужен "конец строки"
	TmpFile = new char[FileSize];
	fseek(F,0,SEEK_SET);
	fread(TmpFile,FileSize,1,F);
	TmpFile[FileSize-1] = 0;	// Добавить "конец строки"
	fclose(F);
}
else return false;
std::string TmpStr = std::string(TmpFile);
//MessageBox(NULL,(TmpStr).c_str(),"",MB_OK);
delete [] TmpFile;
	// Загрузить в структуру
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
	// Сохранение данных в файл
if(File=="") return false;
	// Создать строку с данными
std::string TmpStr;
	// Загрузить в нее данные из структур
DataStruc* TmpStruc = Data;
while(TmpStruc!=NULL) {
	TmpStr += TmpStruc->Name + "=" + TmpStruc->Value + ";" + TmpStruc->Comment+"\n";
	TmpStruc = TmpStruc->pr;
}
	// Сохранить в файл
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
	// Получить значение по имени
if(Data==NULL) return "";
	// Возвращаемое значение
std::string Rez = "";
	// Пробежать по всем структурам, проверяя имена
DataStruc* TmpStruc = Data;
while(TmpStruc!=NULL) {
	if(TmpStruc->Name==Name) {
		// Если это нужное - получить значение
		Rez = TmpStruc->Value;
		break;
	}
	TmpStruc = TmpStruc->pr;
}
	// Возврат найденного значения
return Rez;
}
//---------------------------------------------------------------------------
void Options::SetByName(std::string Name, std::string Value) {
	// Записать значение по его имени
if(Data==NULL) return;
	// Пробежать по всем структурам, проверяя имена
DataStruc* TmpStruc = Data;
while(TmpStruc!=NULL) {
	if(TmpStruc->Name==Name) {
		// Если это нужное - занести значение
		TmpStruc->Value = Value;
		break;
	}
	TmpStruc = TmpStruc->pr;
}
}
//---------------------------------------------------------------------------