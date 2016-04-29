#include <vector>
#include <string>
using namespace std;

struct World {

	string charm; //string representing this world's charm
	int charmLength; //number of characters in this world's charm
	int numOfMagi; //number of magi on this world
	vector<int> magiLevels; //magi levels in order that they would be met on this world

	//get longest increasing magi subsequence
	vector<int> magi_LIS();
};