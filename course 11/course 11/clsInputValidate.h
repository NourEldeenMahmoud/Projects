#pragma once
#include<iostream>
#include "clsDate.h"
using namespace std;
class clsInputValidate
{
public:
	static bool IsNumberBetween(short Number, short From, short To)
	{
		if (Number>=From&&Number<=To)
		{
			return true;
		}
		return false;
	}
	static bool IsNumberBetween(float Number, float From, float To)
	{
		if (Number >= From && Number <= To)
		{
			return true;
		}
		return false;
	}
	static bool IsNumberBetween(int Number, int From, int To)
	{
		if (Number >= From && Number <= To)
		{
			return true;
		}
		return false;
	}
	static bool IsNumberBetween(double Number, double From, double To)
	{
		if (Number >= From && Number <= To)
		{
			return true;
		}
		return false;
	}
	
	static bool isDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		if ((clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
			&&
			(clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To)))
		{
			return true;
		}
		if ((clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
			&&
			(clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From)))
		{
			return true;
		}
		else
			return false;
	}

	static int ReadIntNumber(string ErrorMassage = "Invalid Number , Please enter another number.")
	{
		int Number=0;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMassage;
		}
		return Number;
	}
	static double ReadDblNumber(string ErrorMassage = "Invalid Number , Please enter another number.")
	{
		double Number = 0;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMassage;
		}
		return Number;
	}

	static	int ReadNumberBetween(int From, int To, string ErrorMassage = "Invalid Number , Please enter another number.")
	{
		int Number = ReadIntNumber();
		while (!IsNumberBetween(Number,From,To))
		{
			cout << ErrorMassage;
			Number = ReadIntNumber();
		}
		return Number;
	}
	static	double ReadNumberBetween(double From, double To, string ErrorMassage = "Invalid Number , Please enter another number.")
	{
		double Number = ReadDblNumber();
		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMassage;
			Number = ReadIntNumber();
		}
		return Number;
	}
	static bool IsValidDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}
};

