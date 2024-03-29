#pragma once
//---------------------------------------------------------------------------
#ifndef WfCommonH
#define WfCommonH
//---------------------------------------------------------------------------
// ��� �������������� �������
// ����� ������ � ��������� Wf �.�. Common ����������� � ����� �� ������� � 
// CLR-�����������.
// ������������ ������ ����� � ����������� CLR!
//---------------------------------------------------------------------------
#include <string>	// ��� ������������� std::string
#include <stdio.h>	// ��� ������ � �������
//---------------------------------------------------------------------------
class WfCommon
{
protected:

private:

public:
	WfCommon(void);	// ����������� ������
	~WfCommon();		// ���������� ������

	// ����������

	// �������
	static std::string IntToStr(int Value);		// �������������� int � std::string
	static int StrToInt(std::string String);	// �������������� std::string � int

	static bool FileExists(std::string File);	// �������� ����� �� �������������
	static std::string GetPath(std::string FullFileName);	// �� ����� ����� � ����� ���������� ������ ����
};
//---------------------------------------------------------------------------
#endif