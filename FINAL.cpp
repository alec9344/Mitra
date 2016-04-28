/*
	In this code, we have method for input and calculates the number of alternatins between two words. And we are working on the
	calculation of the edgeweight between two vertexes.
*/


#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>

using namespace std;

struct realm {
	string name;
	int numMagi;
	vector<int> valueMagi;
	int num_Connections;
};

struct edge {
	realm start;
	realm end;
	int cost_in_magi;
	int edge_wieght_in_gems;
};

vector<edge> connections;

/*
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
*/

void findSubstrings(const string & word, set<string> & substrings) {
	int l = word.length();
	for (int start = 0; start < l; start++) {
		for (int length = 1; length < l - start + 1; length++) {
			substrings.insert(word.substr(start, length));
		}
	}
}

vector <string> lcs(const string & first, const string & second) {
	set<string> firstSubstrings, secondSubstrings;
	findSubstrings(first, firstSubstrings);
	findSubstrings(second, secondSubstrings);
	set<string> common;
	set_intersection(firstSubstrings.begin(), firstSubstrings.end(),
		secondSubstrings.begin(), secondSubstrings.end(),
		inserter(common, common.begin()));
	vector<string> commonSubs(common.begin(), common.end());
	sort(commonSubs.begin(), commonSubs.end(), [](const string &s1,
		const string &s2) { return s1.length() > s2.length(); });
	return commonSubs;
}

void removeSubstrs(string& s, string& p) {
	string::size_type n = p.length();
	for (string::size_type i = s.find(p);
		i != string::npos;
		i = s.find(p))
		s.erase(i, n);
}

void remove_comm_subs(string& a, string&b){
	int value = max(a.length(), b.length());
	for (int i = 0; i < value; i++)
	{
		vector <string> common = lcs(a, b);
		if (common.empty()){ break; }
		removeSubstrs(a, common[0]);
		removeSubstrs(b, common[0]);
	}
}

int cost_in_gems(realm a, realm b){
	string world1 = a.name;
	string world2 = b.name;
	remove_comm_subs(world1, world2);
	int cost = max(world1.length(), world2.length());
	cout << cost << endl;
	vector <int> values = a.valueMagi;
	//WE NEED TO FIND THE LARGEST CONSECUATIVE SET OF NUMBERS AND COMPARE THAT TO COST 
	//IF COST IS MORE THAN LARGEST SET OF NUMBERS IMPOSSIBLE RETURN -1;
	//IF COST IS LESS THAN LARGEST SET OF NUMBERS DELETE SET OF CONSEQUATIVE NUMBERS
	//RETURN SUM OF CONSEQUATIVE NUMBERS

	return 0;
}



int main(){
	realm world1;
	world1.name = "sitting";
	world1.numMagi = 6;
	world1.valueMagi.push_back(1);
	world1.valueMagi.push_back(2);
	world1.valueMagi.push_back(1);
	world1.valueMagi.push_back(3);
	world1.valueMagi.push_back(2);
	world1.valueMagi.push_back(4);

	realm world2;
	world2.name = "kneeding";
	world2.numMagi = 4;
	world2.valueMagi.push_back(4);
	world2.valueMagi.push_back(2);
	world2.valueMagi.push_back(3);
	world2.valueMagi.push_back(1);



	cost_in_gems(world1, world2);
}
