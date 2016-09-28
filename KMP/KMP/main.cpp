#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

bool KMP(const string & s1, const string & s2);

vector<int> findMatchInFrontAndBack(const string & s2);
int partPi(const string & amatch);

int main()
{
	cout << "Õâ¸ö³ÌÐòÄÜ¹»ÅÐ¶Ïs1ÄÚÊÇ·ñ°üº¬s2" << endl;
	string s1, s2;
	cout << "ÇëÊäÈë×Ö·û´®1" << endl;
	cin >> s1;
	cout << "ÇëÊäÈë×Ö·û´®2" << endl;
	cin >> s2;

	KMP(s1, s2);

	cout << endl;
	system("pause");

	return 0;
}

bool KMP(const string & s1, const string & s2)
{
	if (s2.size()>s1.size())
	{
		cout << "×Ö·û´®1ÀïÃæ²»°üº¬×Ö·û´®2" << endl;

		return false;
	}
	else
	{
		vector<int> nodes = findMatchInFrontAndBack(s2);

		int histroySite = 0;

		while (s1.size() - s2.size() >= histroySite)
		{
			int matchNum = 0;

			bool allOverMatch = true;
			for (int i = 0; i<s2.size(); ++i)
			{
				if (s1[histroySite + i] != s2[i])
				{
					allOverMatch = false;

					if (matchNum == 0)
					{
						++histroySite;
					}
					else
					{
						histroySite += (matchNum - nodes[i]);
					}
					break;
				}
				else
				{
					++matchNum;
				}
			}

			if (allOverMatch)
			{
				cout << "s1ÖÐ°üº¬s2" << endl;

				cout << s1 << endl;

				for (int i = 0; i<histroySite; ++i)
				{
					cout << " ";
				}
				cout << s2 << endl;

				return true;
			}
		}

		cout << "×Ö·û´®1ÀïÃæ²»°üº¬×Ö·û´®2" << endl;
		return false;
	}
}

vector<int> findMatchInFrontAndBack(const string & s2)
{
	if (s2.size() == 1)
	{
		vector<int> nodeOfMatch = { 0 };
		return nodeOfMatch;
	}
	else
	{
		vector<int> nodeOfMatch(s2.size() - 1, 0);

		auto be = s2.begin();

		auto en = be + 2;

		for (int i = 1; i<s2.size() - 1; ++i)
		{
			string amatch;

			amatch.insert(amatch.end(), be, en);

			nodeOfMatch[i] = partPi(amatch);

			++en;
		}

		nodeOfMatch.push_back(0);

		return nodeOfMatch;
	}
}

int partPi(const string & amatch)
{
	vector<string> frontOfString;
	vector<string> backOfString;

	auto startOne = amatch.begin();
	auto nextOne = startOne + 1;

	for (int i = 0; i<amatch.size() - 1; ++i)
	{
		string fs, bs;

		fs.insert(fs.end(), startOne, nextOne);
		bs.insert(bs.end(), nextOne, amatch.end());

		frontOfString.push_back(fs);
		backOfString.push_back(bs);

		++nextOne;
	}

	sort(frontOfString.begin(), frontOfString.end());
	sort(backOfString.begin(), backOfString.end());

	int highestNum = 0;

	while (frontOfString.size() != 0 && backOfString.size() != 0)
	{
		auto s1 = frontOfString.begin();
		auto s2 = backOfString.begin();

		if (*s1 == *s2)
		{
			if (s1->size()>highestNum)
			{
				highestNum = s1->size();
			}

			frontOfString.erase(s1);
			backOfString.erase(s2);
		}
		else if (*s1<*s2)
		{
			frontOfString.erase(s1);
		}
		else
		{
			backOfString.erase(s2);
		}
	}

	return highestNum;
}