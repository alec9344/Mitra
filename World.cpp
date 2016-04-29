#include "World.h"

vector<int> World::magi_LIS() {
	vector<vector<int>> LIS(numOfMagi); //the LIS vector

	//for the LIS ending with index 0, the value at index 0
	//is the LIS for this subproblem
	LIS[0].push_back(magiLevels[0]); 

	//LIS[i] is the LIS ending with the value at index i. This is set for each 
	//i using dynamic programming.
	for (int i = 1; i < numOfMagi; i++) {

		//for every j from 0 to i-1, LIS[i] is set to LIS[j] if both a)LIS[j] is longer than 
		//the current length of LIS[i] AND b)LIS[j]'s last value is less than the value at i.
		//the value at i is then appended to LIS[i]. 
		for (int j = 0; j < i; j++) {
			if ( magiLevels[j] < magiLevels[i] && LIS[j].size()+1 > LIS[i].size() ) {
				LIS[i] = LIS[j];
			}
		}

		//append the value at i to LIS[i]
		LIS[i].push_back(magiLevels[i]);
	}

	//compare the lengths of each LIS generated, and return the longest one.
	vector<int> longest = LIS[0];
	for (int i = 1; i < numOfMagi; i++) {
		if ( LIS[i].size() > longest.size() && LIS[i][0] <= longest[0] )
			longest = LIS[i];
	}
	return longest;
}