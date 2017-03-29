#include "MainForm.h"

int ID = 1;


BOOL CMyApp_::InitInstance()
{
	m_pMainWnd = new CMainForm;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}



CMainForm::CMainForm() :m_iXPos(400), m_iYPos(200), m_iWidth(600),m_iHeight(325), m_iCounter(0)
{
	m_iOperator = 1;
	CRect rect;
	rect.top = m_iYPos;
	rect.left = m_iXPos;
	rect.right = m_iXPos + m_iWidth;
	rect.bottom = m_iYPos + m_iHeight;
	Create(NULL, _T("Calculator with BigInt"), WS_OVERLAPPED|WS_SYSMENU, rect,NULL);

	m_MainFont.CreatePointFont(160, _T("Arial"));
	int w = 30;
	int h = 30;
	int x = 10;
	int y = m_iHeight/2;
	char title[2] = { 'A' };
	
	for (int i = 0; i < 6; i++)
	{
		
		m_Number[i].Create(_T(title), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(x, y, x + w, y + h), this, ID);
		if (i%2!=0)
		{
			x = 10;
			y += h;
		}
		else x += w;
		title[0] += 1;
		ID++;
		m_Number[i].EnableWindow(FALSE);
	}
	y = m_iHeight / 2;
	x = 10 + w * 2;
	title[0] = '0';

	for (int i = 0; i < 10; i++)
	{

		m_Number[i+6].Create(_T(title), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(x, y, x + w, y + h), this, ID);
		if (i % 3 ==2)
		{
			x = 10 + w * 2;
			y += h;
		}
		else x += w;
		title[0] += 1;
		ID++;
	}

	m_ClearAll.Create(_T("C"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(m_iWidth - w - 20-10, m_iHeight / 2, m_iWidth - w - 20 + w, m_iHeight / 2 + h), this, ID);
	ID++;
	m_ClearBack.Create(_T("<"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(m_iWidth - w -20-10, m_iHeight / 2  + h, m_iWidth - w - 20 + w, m_iHeight / 2 + h*2), this, ID);
	ID++;
	
	char o[5][2] = { "+","-","*","/" };
	x = 10 + w * 5+10;
	y = m_iHeight / 2;
	for (int i = 0; i < 4; i++)
	{
		m_Operator[i].Create(_T(o[i]), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(x, y, x + w, y + h), this, ID);
		ID++;
		y += h;
	}

	m_Calculate.Create(_T("="), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(m_iWidth - w - 20 - 10, m_iHeight / 2 + h * 2, m_iWidth - w - 20 + w, m_iHeight / 2 + h * 3), this, ID);
	ID++;

	m_BinaryLine.Create("BIN: ", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOTIFY, CRect(0, 10 + (30 + 10) * 2, m_iWidth - 20, 10 + (30 + 10) * 2 + 15), this, ID);
	ID++;

	m_HexLine.Create("HEX: ", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOTIFY, CRect(0, 10 + (30 + 10) * 2 + 15 + 10, m_iWidth - 20, 10 + (30 + 10) * 2 + 15 + 10 + 15), this, ID);
	ID++;

	m_DecLine.Create("DEC: ", WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOTIFY, CRect(0, 10 + (30 + 10) * 2 + (15 + 10)*2, m_iWidth - 20, 10 + (30 + 10) * 2 + (15 + 10)*2 + 15), this, ID);
	ID++;

	x += 10 + w;
	y = m_iHeight / 2;
	char c[6][4] = { "<<",">>","Or","Xor","Not","And" };
	for (int i = 0; i < 6; i++)
	{
		m_BitOperator[i].Create(_T(c[i]), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(x, y, x + w, y + h), this, ID);
		ID++;
		y += h;
		if (i % 4 == 3)
		{
			y = m_iHeight / 2;
			x += 10 + w;
		}
	}

	m_About.Create(_T("About"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(m_iWidth - w - 20 - 10, m_iHeight / 2 + h * 3, m_iWidth - w - 20 + w, m_iHeight / 2 + h * 4), this, ID);
	ID++;
	m_Line1.Create("", WS_CHILD | WS_VISIBLE | SS_RIGHT, CRect(0, 10, m_iWidth-20, 10 + 30), this, ID);
	ID++;
	m_Line1.SetFont(&m_MainFont, 1);

	m_Line2.Create("", WS_CHILD | WS_VISIBLE | SS_RIGHT, CRect(0, 10 + 30 + 10, m_iWidth - 20, 10 + (30 + 10) + 30), this, ID);
	ID++;
	m_Line2.SetFont(&m_MainFont, 0);

	
	//m_Sum.BinToDec("OOOO");
	m_CurentString = "";
	m_OldString = "";
	m_InputType = 1;
}


CMainForm::~CMainForm()
{
}

void CMainForm::OnPushButtonClicked_A()
{
	m_CurentString += "A";
	m_Line2.SetWindowText(m_CurentString.c_str());
	string bin;
	m_Curent.SetData16(m_CurentString);
	m_Curent.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
	m_Curent.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());
}

void CMainForm::OnPushButtonClicked_B()
{
	m_CurentString += "B";
	m_Line2.SetWindowText(m_CurentString.c_str());
	string bin;
	m_Curent.SetData16(m_CurentString);
	m_Curent.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
	m_Curent.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());
}
void CMainForm::OnPushButtonClicked_C()
{
	m_CurentString += "C";
	m_Line2.SetWindowText(m_CurentString.c_str());
	string bin;
	m_Curent.SetData16(m_CurentString);
	m_Curent.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
	m_Curent.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());
}
void CMainForm::OnPushButtonClicked_D()
{
	m_CurentString += "D";
	m_Line2.SetWindowText(m_CurentString.c_str());
	string bin;
	m_Curent.SetData16(m_CurentString);
	m_Curent.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
	m_Curent.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());
}
void CMainForm::OnPushButtonClicked_E()
{
	m_CurentString += "E";
	m_Line2.SetWindowText(m_CurentString.c_str());
	string bin;
	m_Curent.SetData16(m_CurentString);
	m_Curent.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
	m_Curent.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());
}
void CMainForm::OnPushButtonClicked_F()
{
	m_CurentString += "F";
	m_Line2.SetWindowText(m_CurentString.c_str());
	string bin;
	m_Curent.SetData16(m_CurentString);
	m_Curent.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
	m_Curent.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());
}


void CMainForm::OnPushButtonClicked_0()
{
	if (m_CurentString.size() == 0) return;
	m_CurentString += "0";

	m_Line2.SetWindowText(m_CurentString.c_str());

	string bin;
	if (m_InputType == 1)
	{
		m_Curent.SetData(m_CurentString);
		m_Curent.DecToBit(bin);
		m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
		m_DecLine.SetWindowText(("DEC: " + m_CurentString).c_str());
	}
	else if (m_InputType == 2)
	{
		m_Curent.BinToDec(m_CurentString);
		m_Curent.DecToBit(bin);
		m_BinaryLine.SetWindowText(("BIN: " + m_CurentString).c_str());
		m_Curent.ToDec(bin);
		m_DecLine.SetWindowText(("DEC: " + bin).c_str());
	}

	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
}


void CMainForm::OnPushButtonClicked_1()
{
	m_CurentString += "1";
	m_Line2.SetWindowText(m_CurentString.c_str());
	string bin;
	if (m_InputType == 1)
	{
		m_Curent.SetData(m_CurentString);
		m_Curent.DecToBit(bin);
		m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
		m_DecLine.SetWindowText(("DEC: " + m_CurentString).c_str());
	}
	else if (m_InputType == 2)
	{
		m_Curent.BinToDec(m_CurentString);
		m_Curent.DecToBit(bin);
		m_BinaryLine.SetWindowText(("BIN: " + m_CurentString).c_str());
		m_Curent.ToDec(bin);
		m_DecLine.SetWindowText(("DEC: " + bin).c_str());
	}

	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
}


void CMainForm::OnPushButtonClicked_2()
{
	m_CurentString += "2";
	m_Line2.SetWindowText(m_CurentString.c_str());
	string bin;
	m_Curent.SetData(m_CurentString);
	m_Curent.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
	m_Curent.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());
}


void CMainForm::OnPushButtonClicked_3()
{
	m_CurentString += "3";
	m_Line2.SetWindowText(m_CurentString.c_str());
	string bin;
	m_Curent.SetData(m_CurentString);
	m_Curent.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
	m_Curent.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());
}


void CMainForm::OnPushButtonClicked_4()
{
	m_CurentString += "4";
	m_Line2.SetWindowText(m_CurentString.c_str());
	string bin;
	m_Curent.SetData(m_CurentString);
	m_Curent.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
	m_Curent.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());
}


void CMainForm::OnPushButtonClicked_5()
{
	m_CurentString += "5";
	m_Line2.SetWindowText(m_CurentString.c_str());
	string bin;
	m_Curent.SetData(m_CurentString);
	m_Curent.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
	m_Curent.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());
}


void CMainForm::OnPushButtonClicked_6()
{
	m_CurentString += "6";
	m_Line2.SetWindowText(m_CurentString.c_str());
	string bin;
	m_Curent.SetData(m_CurentString);
	m_Curent.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
	m_Curent.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());
}


void CMainForm::OnPushButtonClicked_7()
{
	m_CurentString += "7";
	m_Line2.SetWindowText(m_CurentString.c_str());
	string bin;
	m_Curent.SetData(m_CurentString);
	m_Curent.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
	m_Curent.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());
}


void CMainForm::OnPushButtonClicked_8()
{
	m_CurentString += "8";
	m_Line2.SetWindowText(m_CurentString.c_str());
	string bin;
	m_Curent.SetData(m_CurentString);
	m_Curent.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
	m_Curent.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());
}


void CMainForm::OnPushButtonClicked_9()
{
	m_CurentString += "9";
	m_Line2.SetWindowText(m_CurentString.c_str());
	string bin;
	m_Curent.SetData(m_CurentString);
	m_Curent.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
	m_Curent.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());
}

void CMainForm::OnPushButtonClearAll()
{
	m_Sum.SetData("0");
	m_Curent.SetData("0");
	m_CurentString.erase();
	m_Line2.SetWindowText(m_CurentString.c_str());

	m_OldString.erase();
	m_Line1.SetWindowText(m_OldString.c_str());
	m_BinaryLine.SetWindowText(("BIN: " + m_CurentString).c_str());
	m_HexLine.SetWindowText(("HEX: " + m_CurentString).c_str());
	m_DecLine.SetWindowText(("DEC: " + m_CurentString).c_str());
}


void CMainForm::OnPushButtonClearBack()
{
	if (m_CurentString.size() <= 0) return;

	m_CurentString.pop_back();
	m_Line2.SetWindowText(m_CurentString.c_str());

	string bin;
	m_Curent.SetData(m_CurentString);
	m_Curent.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());
	m_Curent.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());
	m_Curent.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());
}

void CMainForm::OnPushButtonOperator1()
{
	if (m_CurentString.size() == 0) return;
	if(m_InputType==1) m_Curent.SetData(m_CurentString);
	else if (m_InputType == 2) m_Curent.BinToDec(m_CurentString);
	else m_Curent.Bintohex(m_CurentString);
	switch (m_iOperator)
	{
	case 1:
		m_Sum = m_Sum + m_Curent;
		break;
	case 2:
		m_Sum = m_Sum - m_Curent;
		break;
	case 3:
		m_Sum = m_Sum * m_Curent;
		break;
	case 4:
		m_Sum = m_Sum / m_Curent;
		break;
	case 5:
	{		
		int num = atoi(m_CurentString.c_str());
		m_Sum.SHL(num);
		break;
	}
	case 6:
	{
		int num1 = atoi(m_CurentString.c_str());
		m_Sum.SHR(num1);
		break;
	}
	case 7:
		m_Sum = m_Sum | m_Curent;
		break;
	case 8:
		m_Sum = m_Sum ^ m_Curent;
		break;
	//case 9:
	case 10:
		m_Sum = m_Sum & m_Curent;
		break;
	}
	if (m_InputType == 1) m_Sum.ToDec(m_CurentString);
	else if (m_InputType == 2) {}//m_Sum.DecToBit(m_CurentString);
								 // else 

	m_iOperator = 1;

	m_OldString = m_CurentString + string(" +");
	m_Line1.SetWindowText(m_OldString.c_str());
	m_CurentString.erase();
	m_Line2.SetWindowText(m_CurentString.c_str());
	//m_BinaryLine.SetWindowText(m_CurentString.c_str());
}

void CMainForm::OnPushButtonOperator2()
{
	if (m_CurentString.size() == 0) return;
	if (m_InputType == 1) m_Curent.SetData(m_CurentString);
	else if (m_InputType == 2) m_Curent.BinToDec(m_CurentString);
	else m_Curent.Bintohex(m_CurentString);
	switch (m_iOperator)
	{
	case 1:
		m_Sum = m_Sum + m_Curent;
		break;
	case 2:
		m_Sum = m_Sum - m_Curent;
		break;
	case 3:
		m_Sum = m_Sum * m_Curent;
		break;
	case 4:
		m_Sum = m_Sum / m_Curent;
		break;
	case 5:
	{
		int num = atoi(m_CurentString.c_str());
		m_Sum.SHL(num);
		break;
	}
	case 6:
	{
		int num1 = atoi(m_CurentString.c_str());
		m_Sum.SHR(num1);
		break;
	}
	case 7:
		m_Sum = m_Sum | m_Curent;
		break;
	case 8:
		m_Sum = m_Sum ^ m_Curent;
		break;
		//case 9:
	case 10:
		m_Sum = m_Sum & m_Curent;
		break;
	
	}
	if (m_InputType == 1) m_Sum.ToDec(m_CurentString);
	else if (m_InputType == 2) {}//m_Sum.DecToBit(m_CurentString);
								 // else


	m_iOperator = 2;
	m_OldString = m_CurentString + string(" -");
	m_Line1.SetWindowText(m_OldString.c_str());
	m_CurentString.erase();
	m_Line2.SetWindowText(m_CurentString.c_str());
}

void CMainForm::OnPushButtonOperator3()
{
	if (m_CurentString.size() == 0) return;
	if (m_InputType == 1) m_Curent.SetData(m_CurentString);
	else if (m_InputType == 2) m_Curent.BinToDec(m_CurentString);
	else m_Curent.Bintohex(m_CurentString);
	switch (m_iOperator)
	{
	case 1:
		m_Sum = m_Sum + m_Curent;
		break;
	case 2:
		m_Sum = m_Sum - m_Curent;
		break;
	case 3:
		m_Sum = m_Sum * m_Curent;
		break;
	case 4:
		m_Sum = m_Sum / m_Curent;
		break;
	case 5:
	{
		int num = atoi(m_CurentString.c_str());
		m_Sum.SHL(num);
		break;
	}
	case 6:
	{
		int num1 = atoi(m_CurentString.c_str());
		m_Sum.SHR(num1);
		break;
	}
	case 7:
		m_Sum = m_Sum | m_Curent;
		break;
	case 8:
		m_Sum = m_Sum ^ m_Curent;
		break;
		//case 9:
	case 10:
		m_Sum = m_Sum & m_Curent;
		break;

	}
	if (m_InputType == 1) m_Sum.ToDec(m_CurentString);
	else if (m_InputType == 2) {}//m_Sum.DecToBit(m_CurentString);
								 // else


	m_iOperator = 3;
	m_OldString = m_CurentString + string(" *");
	m_Line1.SetWindowText(m_OldString.c_str());
	m_CurentString.erase();
	m_Line2.SetWindowText(m_CurentString.c_str());
}

void CMainForm::OnPushButtonOperator4()
{
	if (m_CurentString.size() == 0) return;

	if (m_InputType == 1) m_Curent.SetData(m_CurentString);
	else if (m_InputType == 2) m_Curent.BinToDec(m_CurentString);
	else m_Curent.Bintohex(m_CurentString);
	switch (m_iOperator)
	{
	case 1:
		m_Sum = m_Sum + m_Curent;
		break;
	case 2:
		m_Sum = m_Sum - m_Curent;
		break;
	case 3:
		m_Sum = m_Sum * m_Curent;
		break;
	case 4:
		m_Sum = m_Sum / m_Curent;
		break;
	case 5:
	{
		int num = atoi(m_CurentString.c_str());
		m_Sum.SHL(num);
		break;
	}
	case 6:
	{
		int num1 = atoi(m_CurentString.c_str());
		m_Sum.SHR(num1);
		break;
	}
	case 7:
		m_Sum = m_Sum | m_Curent;
		break;
	case 8:
		m_Sum = m_Sum ^ m_Curent;
		break;
		//case 9:
	case 10:
		m_Sum = m_Sum & m_Curent;
		break;

	}


	if (m_InputType == 1) m_Sum.ToDec(m_CurentString);
	else if (m_InputType == 2) {}//m_Sum.DecToBit(m_CurentString);
	// else


	m_iOperator = 4;
	m_OldString = m_CurentString + string(" /");
	m_Line1.SetWindowText(m_OldString.c_str());
	m_CurentString.erase();
	m_Line2.SetWindowText(m_CurentString.c_str());
}

void CMainForm::OnPushButtonCalculate()
{
	// Calculate operator
	// result is save on m_OutputString string
	// ...

	if (m_CurentString.size() == 0) return;

	if (m_InputType == 1) m_Curent.SetData(m_CurentString);
	else if (m_InputType == 2) m_Curent.BinToDec(m_CurentString);
	else m_Curent.Bintohex(m_CurentString);
	
	switch (m_iOperator)
	{
	case 1:
		m_Sum = m_Sum + m_Curent;
		break;
	case 2:
		m_Sum = m_Sum - m_Curent;
		break;
	case 3:
		m_Sum = m_Sum * m_Curent;
		break;
	case 4:
		m_Sum = m_Sum / m_Curent;
		break;
	case 5:
	{
		int num = atoi(m_CurentString.c_str());
		m_Sum.SHL(num);
		break;
	}
	case 6:
	{
		int num1 = atoi(m_CurentString.c_str());
		m_Sum.SHR(num1);
		break;
	}
	case 7:
		m_Sum = m_Sum | m_Curent;
		break;
	case 8:
		m_Sum = m_Sum ^ m_Curent;
		break;
		//case 9:
	case 10:
		m_Sum = m_Sum & m_Curent;
		break;

	}
	if (m_InputType == 1) m_Sum.ToDec(m_CurentString);
	else if (m_InputType == 2) m_Sum.DecToBit(m_CurentString);
	// else
	// Print
	m_OldString.erase();
	m_Line1.SetWindowText(m_OldString.c_str());
	m_Line2.SetWindowText(m_CurentString.c_str());
	
	string bin;
	m_Sum.DecToBit(bin);
	m_BinaryLine.SetWindowText(("BIN: " + bin).c_str());

	m_Sum.Bintohex(bin);
	m_HexLine.SetWindowText(("HEX: " + bin).c_str());

	m_Sum.ToDec(bin);
	m_DecLine.SetWindowText(("DEC: " + bin).c_str());

	m_CurentString.erase();
	m_Sum.SetData("0");
	m_iOperator = 1;
}

void CMainForm::OnPushButtonInputBin()
{
	if (m_InputType == 2) return;

	QInt temp = m_Sum;
	string bin;
	if (m_InputType == 1)
	{
		if (m_CurentString.size() > 0)
		{
			temp.SetData(m_CurentString);
			temp.DecToBit(m_CurentString);
			m_Line2.SetWindowText(m_CurentString.c_str());
		}
		else
		{
			temp.DecToBit(bin);
			m_Line2.SetWindowText(bin.c_str());
		}
	}
	else if (m_InputType == 3)
	{
		if (m_CurentString.size() > 0)
		{
			temp.SetData16(m_CurentString);
			temp.DecToBit(m_CurentString);
			m_Line2.SetWindowText(m_CurentString.c_str());
		}
		else
		{
			temp.DecToBit(bin);
			m_Line2.SetWindowText(bin.c_str());
		}
	}

	m_InputType = 2;
	for (int i = 0; i < 16; i++)
	{
		if (i == 6 || i == 7) continue;
		m_Number[i].EnableWindow(FALSE);
	}

	
	
}

void CMainForm::OnPushButtonInputHex()
{
	if (m_InputType == 3) return;

	QInt temp = m_Sum;
	string bin;
	if (m_InputType == 1)
	{
		if (m_CurentString.size() > 0)
		{
			temp.SetData(m_CurentString);
			temp.Bintohex(m_CurentString);
			m_Line2.SetWindowText(m_CurentString.c_str());
		}
		else
		{
			temp.Bintohex(bin);
			m_Line2.SetWindowText(bin.c_str());
		}
	}
	else if (m_InputType == 2)
	{
		if (m_CurentString.size() > 0)
		{
			temp.BinToDec(m_CurentString);
			temp.Bintohex(m_CurentString);
			m_Line2.SetWindowText(m_CurentString.c_str());
		}
		else
		{
			temp.Bintohex(bin);
			m_Line2.SetWindowText(bin.c_str());
		}
	}

	m_InputType = 3;
	for (int i = 0; i < 16; i++)
	{
		m_Number[i].EnableWindow(TRUE);
	}

}

void CMainForm::OnPushButtonShiftLeft()
{
	if (m_CurentString.size() == 0) return;

	if (m_InputType == 1) m_Curent.SetData(m_CurentString);
	else if (m_InputType == 2) m_Curent.BinToDec(m_CurentString);
	else m_Curent.Bintohex(m_CurentString);
	switch (m_iOperator)
	{
	case 1:
		m_Sum = m_Sum + m_Curent;
		break;
	case 2:
		m_Sum = m_Sum - m_Curent;
		break;
	case 3:
		m_Sum = m_Sum * m_Curent;
		break;
	case 4:
		m_Sum = m_Sum / m_Curent;
		break;
	case 5:
	{
		int num = atoi(m_CurentString.c_str());
		m_Sum.SHL(num);
		break;
	}
	case 6:
	{
		int num1 = atoi(m_CurentString.c_str());
		m_Sum.SHR(num1);
		break;
	}
	case 7:
		m_Sum = m_Sum | m_Curent;
		break;
	case 8:
		m_Sum = m_Sum ^ m_Curent;
		break;
		//case 9:
	case 10:
		m_Sum = m_Sum & m_Curent;
		break;

	}


	if (m_InputType == 1) m_Sum.ToDec(m_CurentString);
	else if (m_InputType == 2) {}//m_Sum.DecToBit(m_CurentString);
								 // else


	m_iOperator = 5;
	m_OldString = m_CurentString + string(" <<");
	m_Line1.SetWindowText(m_OldString.c_str());
	m_CurentString.erase();
	m_Line2.SetWindowText(m_CurentString.c_str());

}

void CMainForm::OnPushButtonShiftRight()
{

	if (m_CurentString.size() == 0) return;

	if (m_InputType == 1) m_Curent.SetData(m_CurentString);
	else if (m_InputType == 2) m_Curent.BinToDec(m_CurentString);
	else m_Curent.Bintohex(m_CurentString);
	switch (m_iOperator)
	{
	case 1:
		m_Sum = m_Sum + m_Curent;
		break;
	case 2:
		m_Sum = m_Sum - m_Curent;
		break;
	case 3:
		m_Sum = m_Sum * m_Curent;
		break;
	case 4:
		m_Sum = m_Sum / m_Curent;
		break;
	case 5:
	{
		int num = atoi(m_CurentString.c_str());
		m_Sum.SHL(num);
		break;
	}
	case 6:
	{
		int num1 = atoi(m_CurentString.c_str());
		m_Sum.SHR(num1);
		break;
	}
	case 7:
		m_Sum = m_Sum | m_Curent;
		break;
	case 8:
		m_Sum = m_Sum ^ m_Curent;
		break;
		//case 9:
	case 10:
		m_Sum = m_Sum & m_Curent;
		break;

	}


	if (m_InputType == 1) m_Sum.ToDec(m_CurentString);
	else if (m_InputType == 2) {}//m_Sum.DecToBit(m_CurentString);
								 // else


	m_iOperator = 6;
	m_OldString = m_CurentString + string(" >>");
	m_Line1.SetWindowText(m_OldString.c_str());
	m_CurentString.erase();
	m_Line2.SetWindowText(m_CurentString.c_str());
}

void CMainForm::OnPushButtonOr()
{
	if (m_CurentString.size() == 0) return;

	if (m_InputType == 1) m_Curent.SetData(m_CurentString);
	else if (m_InputType == 2) m_Curent.BinToDec(m_CurentString);
	else m_Curent.Bintohex(m_CurentString);
	switch (m_iOperator)
	{
	case 1:
		m_Sum = m_Sum + m_Curent;
		break;
	case 2:
		m_Sum = m_Sum - m_Curent;
		break;
	case 3:
		m_Sum = m_Sum * m_Curent;
		break;
	case 4:
		m_Sum = m_Sum / m_Curent;
		break;
	case 5:
	{
		int num = atoi(m_CurentString.c_str());
		m_Sum.SHL(num);
		break;
	}
	case 6:
	{
		int num1 = atoi(m_CurentString.c_str());
		m_Sum.SHR(num1);
		break;
	}
	case 7:
		m_Sum = m_Sum | m_Curent;
		break;
	case 8:
		m_Sum = m_Sum ^ m_Curent;
		break;
		//case 9:
	case 10:
		m_Sum = m_Sum & m_Curent;
		break;

	}


	if (m_InputType == 1) m_Sum.ToDec(m_CurentString);
	else if (m_InputType == 2) {}//m_Sum.DecToBit(m_CurentString);
								 // else


	m_iOperator = 7;
	m_OldString = m_CurentString + string(" Or");
	m_Line1.SetWindowText(m_OldString.c_str());
	m_CurentString.erase();
	m_Line2.SetWindowText(m_CurentString.c_str());
}

void CMainForm::OnPushButtonXor()
{
	if (m_CurentString.size() == 0) return;

	if (m_InputType == 1) m_Curent.SetData(m_CurentString);
	else if (m_InputType == 2) m_Curent.BinToDec(m_CurentString);
	else m_Curent.Bintohex(m_CurentString);
	switch (m_iOperator)
	{
	case 1:
		m_Sum = m_Sum + m_Curent;
		break;
	case 2:
		m_Sum = m_Sum - m_Curent;
		break;
	case 3:
		m_Sum = m_Sum * m_Curent;
		break;
	case 4:
		m_Sum = m_Sum / m_Curent;
		break;
	case 5:
	{
		int num = atoi(m_CurentString.c_str());
		m_Sum.SHL(num);
		break;
	}
	case 6:
	{
		int num1 = atoi(m_CurentString.c_str());
		m_Sum.SHR(num1);
		break;
	}
	case 7:
		m_Sum = m_Sum | m_Curent;
		break;
	case 8:
		m_Sum = m_Sum ^ m_Curent;
		break;
		//case 9:
	case 10:
		m_Sum = m_Sum & m_Curent;
		break;

	}


	if (m_InputType == 1) m_Sum.ToDec(m_CurentString);
	else if (m_InputType == 2) {}//m_Sum.DecToBit(m_CurentString);
								 // else


	m_iOperator = 8;
	m_OldString = m_CurentString + string(" Xor");
	m_Line1.SetWindowText(m_OldString.c_str());
	m_CurentString.erase();
	m_Line2.SetWindowText(m_CurentString.c_str());
}

void CMainForm::OnPushButtonNot()
{
	if (m_CurentString.size() == 0) return;

	if (m_InputType == 1) m_Curent.SetData(m_CurentString);
	else if (m_InputType == 2) m_Curent.BinToDec(m_CurentString);
	else m_Curent.Bintohex(m_CurentString);

	m_Curent = ~m_Curent;

	if (m_InputType == 1) m_Curent.SetData(m_CurentString);
	else if (m_InputType == 2) m_Curent.BinToDec(m_CurentString);
	else m_Curent.Bintohex(m_CurentString);
	m_Line2.SetWindowText(m_CurentString.c_str());
}

void CMainForm::OnPushButtonAnd()
{
	if (m_CurentString.size() == 0) return;

	if (m_InputType == 1) m_Curent.SetData(m_CurentString);
	else if (m_InputType == 2) m_Curent.BinToDec(m_CurentString);
	else m_Curent.Bintohex(m_CurentString);
	switch (m_iOperator)
	{
	case 1:
		m_Sum = m_Sum + m_Curent;
		break;
	case 2:
		m_Sum = m_Sum - m_Curent;
		break;
	case 3:
		m_Sum = m_Sum * m_Curent;
		break;
	case 4:
		m_Sum = m_Sum / m_Curent;
		break;
	case 5:
	{
		int num = atoi(m_CurentString.c_str());
		m_Sum.SHL(num);
		break;
	}
	case 6:
	{
		int num1 = atoi(m_CurentString.c_str());
		m_Sum.SHR(num1);
		break;
	}
	case 7:
		m_Sum = m_Sum | m_Curent;
		break;
	case 8:
		m_Sum = m_Sum ^ m_Curent;
		break;
		//case 9:
	case 10:
		m_Sum = m_Sum & m_Curent;
		break;

	}


	if (m_InputType == 1) m_Sum.ToDec(m_CurentString);
	else if (m_InputType == 2) {}//m_Sum.DecToBit(m_CurentString);
								 // else


	m_iOperator = 10;
	m_OldString = m_CurentString + string(" And");
	m_Line1.SetWindowText(m_OldString.c_str());
	m_CurentString.erase();
	m_Line2.SetWindowText(m_CurentString.c_str());
}

void CMainForm::OnPushButtonAbout()
{

	MessageBox(_T("Simple Calculator with integer 128bit.\n\nCode by:\n\tThai Nhat Minh\n\tPham Quoc Duy\n\tNguyen Tien Dung\n\nComputer Architecture and Assembly Course\nUniversity of Science."),
		_T("About"), MB_ICONINFORMATION | MB_OK);
}


void CMainForm::OnPushButtonInputDec()
{
	if (m_InputType == 1) return;

	QInt temp;
	string bin;
	if (m_InputType == 2)
	{
		if (m_CurentString.size() > 0)
		{
			temp.BinToDec(m_CurentString);
			temp.ToDec(m_CurentString);
			m_Line2.SetWindowText(m_CurentString.c_str());
		}
		else
		{
			temp = m_Sum;
			temp.ToDec(bin);
			m_Line2.SetWindowText(bin.c_str());
		}
	}
	else if (m_InputType == 3)
	{
		if (m_CurentString.size() > 0)
		{
			temp.SetData16(m_CurentString);
			temp.ToDec(m_CurentString);
			m_Line2.SetWindowText(m_CurentString.c_str());
		}
		else
		{
			temp.ToDec(bin);
			m_Line2.SetWindowText(bin.c_str());
		}
	}

	m_InputType = 1;
	for (int i = 0; i < 16; i++)
	{
		if (i < 6)
		{
			m_Number[i].EnableWindow(FALSE);
			continue;
		}
		m_Number[i].EnableWindow(TRUE);
	}

}
BEGIN_MESSAGE_MAP(CMainForm, CFrameWnd)
	ON_BN_CLICKED(ID + 0, OnPushButtonClicked_A)
	ON_BN_CLICKED(ID + 1, OnPushButtonClicked_B)
	ON_BN_CLICKED(ID + 2, OnPushButtonClicked_C)
	ON_BN_CLICKED(ID + 3, OnPushButtonClicked_D)
	ON_BN_CLICKED(ID + 4, OnPushButtonClicked_E)
	ON_BN_CLICKED(ID + 5, OnPushButtonClicked_F)
	ON_BN_CLICKED(ID + 6, OnPushButtonClicked_0)
	ON_BN_CLICKED(ID + 7, OnPushButtonClicked_1)
	ON_BN_CLICKED(ID + 8, OnPushButtonClicked_2)
	ON_BN_CLICKED(ID + 9, OnPushButtonClicked_3)
	ON_BN_CLICKED(ID + 10, OnPushButtonClicked_4)
	ON_BN_CLICKED(ID + 11, OnPushButtonClicked_5)
	ON_BN_CLICKED(ID + 12, OnPushButtonClicked_6)
	ON_BN_CLICKED(ID + 13, OnPushButtonClicked_7)
	ON_BN_CLICKED(ID + 14, OnPushButtonClicked_8)
	ON_BN_CLICKED(ID + 15, OnPushButtonClicked_9)
	ON_BN_CLICKED(ID + 16, OnPushButtonClearAll)
	ON_BN_CLICKED(ID + 17, OnPushButtonClearBack)
	ON_BN_CLICKED(ID + 18, OnPushButtonOperator1)
	ON_BN_CLICKED(ID + 19, OnPushButtonOperator2)
	ON_BN_CLICKED(ID + 20, OnPushButtonOperator3)
	ON_BN_CLICKED(ID + 21, OnPushButtonOperator4)
	ON_BN_CLICKED(ID + 22, OnPushButtonCalculate)
	ON_STN_CLICKED(ID + 23, OnPushButtonInputBin)
	ON_STN_CLICKED(ID + 24, OnPushButtonInputHex)
	ON_STN_CLICKED(ID + 25, OnPushButtonInputDec)
	ON_BN_CLICKED(ID + 26, OnPushButtonShiftLeft)
	ON_BN_CLICKED(ID + 27, OnPushButtonShiftRight)
	ON_BN_CLICKED(ID + 28, OnPushButtonOr)
	ON_BN_CLICKED(ID + 29, OnPushButtonXor)
	ON_BN_CLICKED(ID + 30, OnPushButtonNot)
	ON_BN_CLICKED(ID + 31, OnPushButtonAnd)
	ON_BN_CLICKED(ID + 32, OnPushButtonAbout)

END_MESSAGE_MAP()


