#pragma once

#include "afxwin.h"
#include <string>
#include <iostream>
#include "QInt.h"
using namespace std;

class CMyApp_ : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainForm :public CFrameWnd
{
public:
	CMainForm();
	~CMainForm();
protected:

	QInt m_Curent;
	QInt m_Num2;
	QInt m_Sum;
	int m_iXPos;
	int m_iYPos;
	int m_iWidth;
	int m_iHeight;
	int m_iCounter;
	string m_CurentString;
	string m_OldString;
	CStatic m_Line1; // Top line
	CStatic m_Line2; // Bot line
	CStatic m_BinaryLine; // binary line ìnormation
	CStatic m_HexLine; // hexa line ìnormation
	CStatic m_DecLine; // hexa line ìnormation
	CButton m_Number[16];
	CButton m_ClearAll;
	CButton m_ClearBack;
	CButton m_Calculate; // =
	CButton m_Operator[4]; // +-*/
	CButton m_BitOperator[6];
	CButton m_About;
	CFont m_MainFont;
	// 1+ 2- 3* 4/ 5<< 6>> 7| 8^ 9~ 10&
	int m_iOperator;
	// 1dec 2bin 3hex
	int m_InputType; 
	afx_msg void OnPushButtonClicked_A();
	afx_msg void OnPushButtonClicked_B();
	afx_msg void OnPushButtonClicked_C();
	afx_msg void OnPushButtonClicked_D();
	afx_msg void OnPushButtonClicked_E();
	afx_msg void OnPushButtonClicked_F();
	afx_msg void OnPushButtonClicked_0();
	afx_msg void OnPushButtonClicked_1();
	afx_msg void OnPushButtonClicked_2();
	afx_msg void OnPushButtonClicked_3();
	afx_msg void OnPushButtonClicked_4();
	afx_msg void OnPushButtonClicked_5();
	afx_msg void OnPushButtonClicked_6();
	afx_msg void OnPushButtonClicked_7();
	afx_msg void OnPushButtonClicked_8();
	afx_msg void OnPushButtonClicked_9();
	afx_msg void OnPushButtonClearAll();
	afx_msg void OnPushButtonClearBack();
	afx_msg void OnPushButtonOperator1(); // +
	afx_msg void OnPushButtonOperator2(); // -
	afx_msg void OnPushButtonOperator3(); // *
	afx_msg void OnPushButtonOperator4(); // /
	afx_msg void OnPushButtonCalculate(); // /
	afx_msg void OnPushButtonInputBin(); // 
	afx_msg void OnPushButtonInputDec(); // /
	afx_msg void OnPushButtonInputHex(); // /
	afx_msg void OnPushButtonShiftLeft(); // /
	afx_msg void OnPushButtonShiftRight(); // /
	afx_msg void OnPushButtonOr(); // /
	afx_msg void OnPushButtonXor(); // /
	afx_msg void OnPushButtonNot(); // /
	afx_msg void OnPushButtonAnd(); // /
	afx_msg void OnPushButtonAbout(); // /
	DECLARE_MESSAGE_MAP()

};

