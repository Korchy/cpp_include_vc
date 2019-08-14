#pragma once
//---------------------------------------------------------------------------
#ifndef CommonH
#define CommonH
//---------------------------------------------------------------------------
// ��� �������������� �������
//---------------------------------------------------------------------------
#include <string>	// ��� ������������� std::string
#include <stdio.h>	// ��� ������ � �������
#include <stdlib.h>	// ��� f_cvt_s
//---------------------------------------------------------------------------
class Common
{
protected:

private:

public:
	Common(void);	// ����������� ������
	~Common();		// ���������� ������

	// ����������

	// �������
	static std::string IntToStr(int Value);		// �������������� int � std::string
	static int StrToInt(std::string String);	// �������������� std::string � int
	static std::string FloatToStr(float Value);	// �������������� float � std::string
	static float StrToFloat(std::string String);	// �������������� std::string � float

	static bool FileExists(std::string File);	// �������� ����� �� �������������
	static std::string GetPath(std::string FullFileName);	// �� ����� ����� � ����� ���������� ������ ����
};
#endif