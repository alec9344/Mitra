#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

struct realm {
	string name;
	int numMagi;
	vector<int> valueMagi;
};


vector<realm>  inputRealms()
{
	int numRealms; 
	cin >> numRealms; //input firs tline
	
	vector <realm> Realms;
	
	for (int i = 0; i < numRealms; i++)
	{
		realm cRealm;
		cin >> cRealm.name;
		cin >> cRealm.numMagi;


		for (int j = 0; j < cRealm.numMagi; j++)
		{
			int value; cin >> value;
			cRealm.valueMagi.push_back(value);
		}

		Realms.push_back(cRealm);
		//cout << "realm" << i << "finsihed" << endl;
	}

	return Realms;
}

int main()
{
	vector<realm> Realms;
	Realms = inputRealms();
	string startRealm, endRealm;
	cin >> startRealm; cin>> endRealm;
	/*
	for (int i = 0; i < 4; i++)
	{
		cout << Realms[i].name << endl;
		cout << Realms[i].numMagi << endl;
		for (int j = 0; j < Realms[i].numMagi; j++)
		{
			cout << Realms[i].valueMagi[j];
		}
		cout << endl;
	}
	*/
	 //Printing result
	//system("pause");
}
