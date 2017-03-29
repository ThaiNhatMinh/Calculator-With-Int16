#include "QInt.h"


void QInt::SetData(string a)
{
	if (a[0] != '-')
	{
		for (char i = 0; i < 4; i++)
		{
			Data[i] = 0;
		}
		
	bool du;
	string thuong;
	char i = 3; int vt = 0;
	while (1)
	{
		ChiaChuoiCho2(a, thuong, du);
		Data[i] += (du<<vt); 
		a.resize(thuong.size());
		for (int k = 0; k < a.size(); k++)
		{
			a[k] = thuong[k];
		}
		if (vt == 31){ i--; vt = 0; }
		else{ vt++; }
		if (thuong == "0"){  break; }
	}

	}

	if (a[0] == '-')
	{
		string b;
		b.resize(a.size() - 1);
		for (int i = 0; i < b.size(); i++)
		{
			b[i] = a[i + 1];
		}
		for (char i = 0; i < 4; i++)
		{
			Data[i] = 0;
		}

		bool du;
		string thuong;
		char i = 3; int vt = 0;
		while (1)
		{
			ChiaChuoiCho2(b, thuong, du);
			Data[i] += (du<<vt);
			
			
			b.resize(thuong.size());
			for (int k = 0; k < b.size(); k++)
			{
				b[k] = thuong[k];
			}
			if (vt == 31){ i--; vt = 0; }
			else{ vt++; }
			if (thuong == "0"){ break; }
		}
		
		int temp[4]; 
		TimSoBu2(Data, temp);
		for (char i = 0; i < 4; i++)
		{
			Data[i] = temp[i];
		}
	}
}
char QInt::SetData16(string a)
{
	char b[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != '0'&&a[i] != '1'&&a[i] != '2'&&a[i] != '3'&&a[i] != '4'&&a[i] != '5'&&a[i] != '6'&&
			a[i] != '7'&&a[i] != '8'&&a[i] != '9'&&a[i] != 'A'&&a[i] != 'B'&&a[i] != 'C'&&a[i] != 'D'&&
			a[i] != 'E'&&a[i] != 'F') {
			return -1;//loi ki tu ko hop le
		}
	}
	string bit; bit.resize(0);
	string temp; temp.resize(0); int i = 0;
	for (; i < a.size(); i++)
	{
		if (a[i] != '0') { break; }
	}
	for (; i < a.size(); i++)
	{
		temp.push_back(a[i]);
	}
	if (temp.size()>32) { return -1; }//loi tran bo nho
	for (int j = 0; j <temp.size(); j++)
	{
		switch (temp[j])
		{
		case '0': {bit.push_back('0'); bit.push_back('0'); bit.push_back('0'); bit.push_back('0'); break; }
		case '1': {bit.push_back('0'); bit.push_back('0'); bit.push_back('0'); bit.push_back('1'); break; }
		case '2': {bit.push_back('0'); bit.push_back('0'); bit.push_back('1'); bit.push_back('0'); break; }
		case '3': {bit.push_back('0'); bit.push_back('0'); bit.push_back('1'); bit.push_back('1'); break; }
		case '4': {bit.push_back('0'); bit.push_back('1'); bit.push_back('0'); bit.push_back('0'); break; }
		case '5': {bit.push_back('0'); bit.push_back('1'); bit.push_back('0'); bit.push_back('1'); break; }
		case '6': {bit.push_back('0'); bit.push_back('1'); bit.push_back('1'); bit.push_back('0'); break; }
		case '7': {bit.push_back('0'); bit.push_back('1'); bit.push_back('1'); bit.push_back('1'); break; }
		case '8': {bit.push_back('1'); bit.push_back('0'); bit.push_back('0'); bit.push_back('0'); break; }
		case '9': {bit.push_back('1'); bit.push_back('0'); bit.push_back('0'); bit.push_back('1'); break; }
		case 'A': {bit.push_back('1'); bit.push_back('0'); bit.push_back('1'); bit.push_back('0'); break; }
		case 'B': {bit.push_back('1'); bit.push_back('0'); bit.push_back('1'); bit.push_back('1'); break; }
		case 'C': {bit.push_back('1'); bit.push_back('1'); bit.push_back('0'); bit.push_back('0'); break; }
		case 'D': {bit.push_back('1'); bit.push_back('1'); bit.push_back('0'); bit.push_back('1'); break; }
		case 'E': {bit.push_back('1'); bit.push_back('1'); bit.push_back('1'); bit.push_back('0'); break; }
		case 'F': {bit.push_back('1'); bit.push_back('1'); bit.push_back('1'); bit.push_back('1'); break; }
		default:break;
		}
	}
	BinToDec(bit);
	return 1;
}
void QInt::Bintohex(string &a)
{
	a.resize(0);
	char Mang16[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', ' B', ' C', 'D', 'E', 'F' };
	int b[128];
	for (int i = 0; i<128; i++)
	{
		b[i] = (Data[i / 32] >> (32 - 1 - i % 32)) & 1;
	}
	
	int j = 0, k = 0;
	for (int i = 4; i <= 128; i = i + 4)
	{
		
		int x = 0;
		while (j < i)
		{
			if (b[j] == 1)
			{
				if (j % 4 == 0){ x += pow(2, 3); }
				if (j % 4 == 1){ x += pow(2, 2); }
				if (j % 4 == 2){ x += pow(2, 1); }
				if (j % 4 == 3){ x += pow(2, 0); }
			}
			j++;
		}
		a.resize(k + 1);
		a[k] = Mang16[x];
		k++;
	}
}
void QInt::Dectohex(string a, string &b)
{
	SetData(a);
	Bintohex(b);
}
void QInt::ToDec(string &a)
{
	StringBitToStringNumber(Data, a);
}

void QInt::DecToBit(string &a)
{
	string temp;
	a.erase();
	QIntToStringBit(Data,temp );
	int i = 0;
	for (; i < temp.size(); i++)
	{
		if (temp[i] == '1'){ break; }
	}
	for (; i < temp.size(); i++)
	{
		a.push_back(temp[i]);
	}
	
}
char QInt::ScanQInt()
{
	string temp;
	getline(cin, temp);
	
		if (temp[0] == '-')
		{
			for (int i = 1; i < temp.size(); i++)
			{
				if (temp[i]<48 || temp[i]>57){ return -1; }
			}
		}
		else
		{
			for (int i = 0; i < temp.size(); i++)
			{
				if (temp[i]<48 || temp[i]>57){ return -1; }
			}
		}
		SetData(temp);
		return 1;

}
void QInt::PrintQInt()
{
	string temp;
	ToDec(temp);
	cout << temp;
}
char QInt::BinToDec(string bit)
{

	for (int m = 0; m < bit.size(); m++)
	{
		if (bit[m] != '0' && bit[m] != '1'){ return -1; }
	}
	string temp; int i = 0;
	for (; i < bit.size(); i++)
	{
		if (bit[i] == '1'){ break; }
	}
	for (; i < bit.size(); i++)
	{
		temp.push_back(bit[i]);
	}
	

	if (temp.size()>128){ return -1; }
	for (int j = 0; j < 4; j++)
	{
		Data[j] = 0;
	}
	int k = 0,vt=3,l=temp.size()-1;
	while (1)
	{
		Data[vt] = (Data[vt] ) + ((temp[l] - 48)<<k);
		l--; k++;
		if (l == -1){ return 1; }
		if (k == 32){ vt--; k = 0; }

	}
	
}


void QInt::SHR(int num)
{
	/*
	bool temp = 0;
	bool firstBit;
	for (int i = 0; i < 4; i++)
	{
		firstBit = GetBit(Data[i], 0);
		Data[i] = Data[i] >> num;
		if (i)
		{
			if (temp) Data[i - 1] = OnBit(Data[i - 1], 31);
			else Data[i - 1] = OffBit(Data[i - 1], 31);

		}
		temp = firstBit;
	}*/
	for (int i = 0; i < num; i++)
	{
		bool bit = GetBit(Data[0], 0);
		Data[0] = Data[0] >> 1;

		bool bit1 = GetBit(Data[1], 0);
		Data[1] = Data[1] >> 1;
		if (bit) Data[1] = OnBit(Data[1], 31);
		else Data[1] = OffBit(Data[1], 31);

		bool bit2 = GetBit(Data[2], 0);
		Data[2] = Data[2] >> 1;
		if (bit1) Data[2] = OnBit(Data[2], 31);
		else Data[2] = OffBit(Data[2], 31);


		bool bit3 = GetBit(Data[3], 0);
		Data[3] = Data[3] >> 1;
		if (bit2) Data[3] = OnBit(Data[3], 31);
		else Data[3] = OffBit(Data[3], 31);
	}
}

void QInt::SHL(int num)
{
	/*
	bool temp = 0;
	bool lastbit;
	for (int i = 0; i <4; i++)
	{
		int id = 3 - i;
		lastbit = GetBit(Data[id], 31);
		Data[id] = Data[id] << num;
		if (i)
		{
			if (temp) Data[id + 1] = OnBit(Data[id + 1], 31);
			else Data[id + 1] = OffBit(Data[id + 1], 31);

		}
		temp = lastbit;
	}
	*/
	for (int i = 0; i < num; i++)
	{
		bool bit3 = GetBit(Data[3], 31);
		Data[3] = Data[3] << 1;

		bool bit2 = GetBit(Data[2], 31);
		Data[2] = Data[2] << 1;
		if (bit3) Data[2] = OnBit(Data[2], 0);
		else Data[2] = OffBit(Data[2], 0);

		bool bit1 = GetBit(Data[1], 31);
		Data[1] = Data[1] << 1;
		if (bit2) Data[1] = OnBit(Data[1], 0);
		else Data[1] = OffBit(Data[1], 0);

		bool bit = GetBit(Data[0], 31);
		Data[0] = Data[0] << 1;
		if (bit1) Data[0] = OnBit(Data[0], 0);
		else Data[0] = OffBit(Data[0], 0);

	}


	
}

QInt QInt::operator~()
{
	QInt result;
	for (int i = 0; i < 128; i++)
	{
		int id = 3 - i / 32;		// index on Data[]
		int index = i % 32;
		bool bit = GetBit(Data[id], index);
		if (!bit) result.Data[id] = OnBit(result.Data[id], index);
	}
	return result;
}

QInt QInt::operator&(const QInt & a)
{
	QInt result;
	for (int i = 0; i < 128; i++)
	{
		int id = 3 - i / 32;		// index on Data[]
		int index = i % 32;
		bool bit = GetBit(Data[id], index) & GetBit(a.Data[id],index);
		if (bit) result.Data[id] = OnBit(result.Data[id], index);
	}
	return result;
}

QInt QInt::operator|(const QInt & a)
{
	QInt result;
	for (int i = 0; i < 128; i++)
	{
		int id = 3 - i / 32;		// index on Data[]
		int index = i % 32;
		bool bit = GetBit(Data[id], index) | GetBit(a.Data[id], index);
		if (bit) result.Data[id] = OnBit(result.Data[id], index);
	}
	return result;
}

QInt QInt::operator^(const QInt & a)
{
	QInt result;
	for (int i = 0; i < 128; i++)
	{
		int id = 3 - i / 32;		// index on Data[]
		int index = i % 32;
		bool bit = GetBit(Data[id], index) ^ GetBit(a.Data[id], index);
		if (bit) result.Data[id] = OnBit(result.Data[id], index);
	}
	return result;
}

QInt::QInt()
{
	memset(&Data[0], 0, sizeof(int) * 4);
}

QInt & QInt::operator=(const QInt & d)
{
	memcpy(Data, d.Data, sizeof(int) * 4); 
#if defined(_DEBUG)
	//cout << "Assign Operator" << endl;
#endif
	return *this; 
}


QInt operator+(const QInt& a, const QInt& b)
{
	QInt result;
	bool bonus = 0;
	for (int i = 0; i < 128; i++)
	{
		int id = 3 - i / 32;		// index on Data[]
		int index = i % 32;			// bit index

		bool bita = GetBit(a.Data[id], index);
		bool bitb = GetBit(b.Data[id], index);

		if (bita && bitb)
		{
			if (bonus) result.Data[id] = OnBit(result.Data[id], index);
			else bonus = 1;
		}
		else
		{
			bool sum = bita | bitb;
			if (bonus ^ sum)
			{
				result.Data[id] = OnBit(result.Data[id], index);
				bonus = 0;
			}
		}

	}
	return result;
}

QInt operator-(const QInt& a, const QInt& b)
{
	QInt result;
	QInt negativeb;
	TimSoBu2((int*)b.Data, negativeb.Data);
	result = a + negativeb;
	return result;

}

// M x Q
QInt operator*(const QInt& a, const QInt& b)
{
	QInt M;
	QInt Q;
	if (GetBit(a.Data[0], 31) && GetBit(b.Data[0], 31))
	{
		QInt negative_a;
		QInt negative_b;
		TimSoBu2((int*)a.Data, negative_a.Data);
		TimSoBu2((int*)b.Data, negative_b.Data);
		M = a;
		Q = b;
	}
	else if (GetBit(a.Data[0], 31) && !GetBit(b.Data[0], 31))
	{
		M = b;
		Q = a;
	}
	else
	{
		M = a;
		Q = b;
	}
	QInt A;
	A.SetData("0");
	bool Check = 0; // Q-1
	for (int i = 0; i < 128; i++)
	{
		int id = 3 - i / 32;		// index on Data[]
		int index = i % 32;			// bit index

		bool Bit = GetBit(Q.Data[3], 0);
		if (Bit && !Check) A = A - M;
		else if (!Bit && Check) A = A + M;

		Check = Bit;
		bool FirstBit = GetBit(A.Data[3], 0);
		A.SHR(1);
		Q.SHR(1);
		if (FirstBit) Q.Data[0] = OnBit(Q.Data[0], 31);
		else Q.Data[0] = OffBit(Q.Data[0], 31);

		
	}
	return Q;
}

// Q/M
// a/b
QInt operator/(const QInt& a, const QInt& b)
{
	QInt Q ;
	QInt M ;

	if (GetBit(a.Data[0], 31) && GetBit(b.Data[0], 31))
	{
		QInt negative_a;
		QInt negative_b;
		TimSoBu2((int*)a.Data, negative_a.Data);
		TimSoBu2((int*)b.Data, negative_b.Data);
		M = negative_b;
		Q = negative_a;
	}
	else if (GetBit(a.Data[0], 31) && !GetBit(b.Data[0], 31))
	{
		Q = b;
		M = a;
	}
	else
	{
		Q = a;
		M = b;
	}

	QInt A;
	if (GetBit(Q.Data[0], 31))
	{
		for (int i = 0; i < 128; i++)
		{
			int id = 3 - i / 32;		// index on Data[]
			int index = i % 32;			// bit index
			A.Data[id] = OnBit(A.Data[id], index);
		}
	}

	for (int i = 0; i < 128; i++)
	{

		//string bit;
		//A.DecToBit(bit);
		//cout << "A " << bit << endl;
		//Q.DecToBit(bit);
		//cout << "B " << bit << endl;
		int id = 3 - i / 32;		// index on Data[]
		int index = i % 32;			// bit index

		bool lastbit = GetBit(Q.Data[0], 31);
		Q.SHL(1);
		A.SHL(1);
		if (lastbit) A.Data[3] = OnBit(A.Data[3], 0);
		else A.Data[3] = OffBit(A.Data[3], 0);
		
		if (GetBit(M.Data[0], 31))	A = A + M;
		else A = A - M;

		if (GetBit(A.Data[0], 31))
		{
			Q.Data[3] = OffBit(Q.Data[3], 0);
			//A = A + M;
			if (GetBit(M.Data[0], 31))	A = A - M;
			else A = A + M;
		}
		else Q.Data[3] = OnBit(Q.Data[3], 0);
	}

	return Q;

}
