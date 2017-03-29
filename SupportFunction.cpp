
#include "SupportFunction.h"


void DaoBit(int &a)
{
	a = (-1) - a;
}
void TimSoBu2(int a[4], int b[4])
{
	for (int i = 0; i < 4; i++)
	{
		b[i] = a[i];
	}
	/*if (((a[0] >> 31) & 1) == 1){
		return; }
	else{*/		
		for (int i = 0; i < 4; i++)
		{
			DaoBit(b[i]);
		}
		for (int i = 3; i >= 0; i--)
			{
				if (b[i] == -1){ b[i] = 0; }
				else
				{
					b[i] += 1; break;
				}
			}
	/*}*/
}
void QIntToStringBit(int data[4], string &a)
{
	a.resize(32*4);
	for (int i = 0; i < 32*4; i++)
	{
		a[i] = 48;
	}
	for (int i = 0; i <4; i++)
	{
		int b = data[i];
		for (int j = 32; j >= 1; j--)
		{
			
			a[j+32*i-1] = (b & 1)+48;
			b = b >> 1;
		}
	}
}

void ChiaChuoiCho2(string sochia, string &thuong, bool &du)
{
	if (sochia.size() > 0){
	thuong.resize(sochia.size());
	thuong[0] = (sochia[0] - 48) / 2 + 48;
	int i = 1;
	while (1)
	{
		if (i == sochia.size()){ break; }
		if ((sochia[i - 1] - 48) % 2 == 0){ thuong[i] = (sochia[i] - 48) / 2 + 48; }
		else{
			thuong[i] = (sochia[i] - 48+10) / 2 + 48;
		}
		i++;
	}
	du = (sochia[sochia.size() - 1] - 48)%2;
	}
	
	if (thuong[0] == '0')
	{
		
		if (thuong.size() > 1){
		for (int j = 0; j < thuong.size()-1; j++)
		{
			thuong[j] = thuong[j + 1];
		}		
		thuong.pop_back();
		}
	}
}
void NhanChuoiCho2(string so, string& kq, bool nho)
{
	kq.resize(so.size() + 1); 
	int i = so.size() ; char temp = nho;
	while (1)
	{
		if (i == 0){ kq[i] = (temp + 48); break; }
		if ((so[i - 1]-48) >= 5){
	
			kq[i] = (so[i-1] - 48) * 2 - 10 + 48+temp; temp = 1;
		}
		else{
			kq[i] = (so[i-1] - 48) * 2  + 48 + temp; temp = 0;
		}
		i--;
	}
	if (kq[0] == '0'&&kq.size()>1)
	{
		for (int i = 0; i < kq.size() - 1; i++)
		{
			kq[i] = kq[i + 1];
		}
		kq.pop_back();
	}
}
void StringBitToStringNumber(int data[4], string &kq)
{
	string temp;
	temp.resize(1);
	temp[0] = '0'; 
	if ((data[0] >> 31) == 0)
	{
		int m = 31,n=0;
		while (((data[n] >> m)&1) != 1)
		{
				
			if (n == 4){  break; }
			if (m != 0){ m--;  }
			else{ m = 31; n++;  }
		}
		
		if (n != 4){

		for (int i = n; i <=3; i++)
		{

			if (i >n)
			{
				
				for (int j = 31; j >=0; j--)
				{
					bool tam = (data[i] >> j) & 1;
					NhanChuoiCho2(temp, kq, tam);
					temp.resize(kq.size());
					for (int k = 0; k < kq.size(); k++)
					{
						temp[k] = kq[k];
					}
				}
			}
			if (i == n)
			{

				for (int j = m; j >=0; j--)
				{
					bool tam = (data[i] >> j) & 1;
					NhanChuoiCho2(temp, kq, tam);
					temp.resize(kq.size());
					for (int k = 0; k < kq.size(); k++)
					{
						temp[k] = kq[k];
					}
				}
			}

		
			
		}
		}
		else{ kq.resize(1); kq[0] = 48; }
	}
	
	if (((data[0] >> 31)&1) == 1)
	{
		
		
		for (int i = 3; i >= 0; i--)
		{
			if (data[i] == 0){ data[i] = -1; }
			else
			{
				data[i] -= 1; break;
			}
		}
		
		for (int i = 0; i < 4; i++)
		{
			DaoBit(data[i]);
		}
		
		int m = 31, n = 0;
		while (((data[n] >> m) & 1) != 1)
		{

			if (n == 4){ break; }
			if (m != 0){ m--; }
			else{ m = 31; n++; }
		}

		if (n != 4){

			for (int i = n; i <= 3; i++)
			{

				if (i >n)
				{

					for (int j = 31; j >= 0; j--)
					{
						bool tam = (data[i] >> j) & 1;
						NhanChuoiCho2(temp, kq, tam);
						temp.resize(kq.size());
						for (int k = 0; k < kq.size(); k++)
						{
							temp[k] = kq[k];
						}
					}
				}
				if (i == n)
				{

					for (int j = m; j >= 0; j--)
					{
						bool tam = (data[i] >> j) & 1;
						NhanChuoiCho2(temp, kq, tam);
						temp.resize(kq.size());
						for (int k = 0; k < kq.size(); k++)
						{
							temp[k] = kq[k];
						}
					}
				}



			}
		}
		else{  kq.resize(1); kq[0] = 48; }
		kq.resize(kq.size()+1);
		for (int i = kq.size()-1; i>=1; i--)
		{
			kq[i] = kq[i-1];
		}
		kq[0] = '-';

	}
}
