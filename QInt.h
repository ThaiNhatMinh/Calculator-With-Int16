#pragma once
#include<string>
#include<iostream>
#include "SupportFunction.h"
using namespace std;

#define GetBit(x,i) (((x) >> (i)) & 1)
#define OnBit(x,i)  ((1 << (i)) | (x))
#define OffBit(x,i) (~(1 << (i)) & (x))

class QInt
{
public:
	int Data[4];
public:
	//Chuyen du lieu so thap phan duoi dang chuoi thanh dang bit luu vao Data[4]
	void SetData(string a);
	//Chuyen du lieu dang chuoi he 16 sang he 2,neu chuoi string a cho vao ko hop le thi tra ve -1 ngc lai tra ve 1
	char SetData16(string a);
	//tu he 2 sang he 16
	void Bintohex(string &a);
	//Chuyen kieu du lieu dang chuoi bit sang QInt,neu chuoi bit ko hop le tra ve -1, neu hop le tra ve 1;
	char BinToDec(string bit);
	//tu he 10 sang 16
	void Dectohex(string a, string &b);
	//Chuyen du lieu dang bit Data[4] thanh dang so thap phan va luu vao chuoi a
	void ToDec(string &a);
	//luu du lieu dang bit Data[4] vao mang a
	void DecToBit(string &a);
	//Nhap kieu du lieu Qint ,neu nhap khong hop le tra ve -1,neu hop le tra ve 1
	char ScanQInt();
	//Xuat ra man hinh kieu du lieu Qint
	void PrintQInt();
	
	void SHR(int num);
	void SHL(int num);

	QInt operator~();
	QInt operator&(const QInt& a);
	QInt operator|(const QInt& a);
	QInt operator^(const QInt& a);
	QInt();
	~QInt() {};

	QInt& operator=(const QInt& d);
};


QInt operator+(const QInt& a, const QInt& b);
QInt operator-(const QInt& a, const QInt& b);
QInt operator*(const QInt& a, const QInt& b);
QInt operator/(const QInt& a, const QInt& b);