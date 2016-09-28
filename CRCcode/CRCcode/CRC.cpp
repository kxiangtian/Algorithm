#include "CRC.h"

using namespace std;

//模二除法
void division(vector<int> &d1, const vector<int> &d2, vector<int> &f3)
{
	/////初始化每轮的临时被除数数组和临时余数数组/////
	vector<int> eachBeiChuShu;
	vector<int> eachYuShu;

	//标记已用长度
	int flag = d2.size();

	for (int i = 0; i<d2.size(); ++i)
	{
		eachBeiChuShu.push_back(d1[i]);
		eachYuShu.push_back(0);
	}
	////////初始化结束////////////////////////////////

	while(1)
	{
		XORfunc(eachBeiChuShu,d2,eachYuShu);

		//余数去前置0化
		int needBit = 0;
		for (auto iter=eachYuShu.begin();iter!=eachYuShu.end();iter=eachYuShu.begin())
		{
			if ((*iter)==1)
			{
				break;
			}
			else
			{
				eachYuShu.erase(iter);

				++needBit;
			}
		}

		if ((flag+needBit)>d1.size())
		{
			int R = d2.size() - 1;
			R -= eachYuShu.size();

			for (int i=0;i<R;++i)
			{
				eachYuShu.insert(eachYuShu.begin(),0);
			}

			f3 = eachYuShu;

			break;
		}
		else
		{
			int backFlag = flag + 1;
			flag += needBit;

			vector<int> newEachBeiChuShu;
			newEachBeiChuShu = eachYuShu;

			for (int i= backFlag;i<=flag;++i)
			{
				newEachBeiChuShu.push_back(d1[i-1]);
			}

			eachBeiChuShu = newEachBeiChuShu;

			vector<int> newYS;
			for (int i=0;i<d2.size();++i)
			{
				newYS.push_back(0);
			}
			eachYuShu=newYS;
		}
	}	
}

void XORfunc(const vector<int> &eachBeiChuShu,const vector<int> &d2, vector<int> &eachYuShu)
{
	vector<int> newYuShu;

	for (int i=0;i<eachBeiChuShu.size();++i)
	{
		if (eachBeiChuShu[i]==d2[i])
		{
			newYuShu.push_back(0);
		}
		else
		{
			newYuShu.push_back(1);
		}
	}

	eachYuShu = newYuShu;
}

string CRC(const string &dividend,const string &divisor)
{
	//被除式-原始码
	vector<int> codeOfDividend;
	//除式-生成码
	vector<int> codeOfDivisor;
	//余数-要被放在原始码后面
	vector<int> codeOfRemainder;

	//CRC冗余校验码
	vector<int> codeOfCRC;

	////把字符状态的除式和被除式变成数组形态////////
	for (auto &c : dividend)
	{
		if (c == '0')
		{
			codeOfDividend.push_back(0);
		}
		else
		{
			codeOfDividend.push_back(1);
		}
	}

	for (auto &c : divisor)
	{
		if (c == '0')
		{
			codeOfDivisor.push_back(0);
		}
		else
		{
			codeOfDivisor.push_back(1);
		}
	}

	codeOfCRC = codeOfDividend;

	//被除数右侧填R个0位///////////////////////
	int R = codeOfDivisor.size() - 1;

	for (int i = 0; i<R; ++i)
	{
		codeOfDividend.push_back(0);
	}
	//////////////////////////////////////////////

	/////进行模二除法/////////////////////////////
	division(codeOfDividend, codeOfDivisor, codeOfRemainder);
	//////////////////////////////////////////////

	//////////把余数填到原始码后，生成CRC/////////
	for (int i = 0; i<R; ++i)
	{
		codeOfCRC.push_back(codeOfRemainder[i]);
	}
	//////////////////////////////////////////////

	string theReturnString;
	for (auto &s:codeOfCRC)
	{
		if (s==0)
		{
			theReturnString += '0';
		}
		else
		{
			theReturnString += '1';
		}
	}

	return theReturnString;
}