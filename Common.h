#pragma once
//---------------------------------------------------------------------------
#ifndef CommonH
#define CommonH
//---------------------------------------------------------------------------
// Все дополнительные функции
//---------------------------------------------------------------------------
#include <string>	// Для использования std::string
#include <stdio.h>	// Для работы с файлами
#include <stdlib.h>	// Для f_cvt_s
//---------------------------------------------------------------------------
class Common
{
protected:

private:

public:
	Common(void);	// Конструктор класса
	~Common();		// Деструктор класса

	// Переменные

	// Функции
	static std::string IntToStr(int Value);		// Преобразование int в std::string
	static int StrToInt(std::string String);	// Преобразование std::string в int
	static std::string FloatToStr(float Value);	// Преобразование float в std::string
	static float StrToFloat(std::string String);	// Преобразование std::string в float

	static bool FileExists(std::string File);	// Проверка файла на существование
	static std::string GetPath(std::string FullFileName);	// От имени файла с путем возвращает только путь
};
#endif