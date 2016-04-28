#include "World.h"

vector<int> World::magi_LIS() {
	vector<vector<int>> LIS(numOfMagi);
	LIS[0].push_back(magiLevels[0]);
	for (int i = 1; i < numOfMagi; i++) {
		for (int j = 0; j < i; j++) {
			if ( magiLevels[j] < magiLevels[i] && LIS[j].size()+1 > LIS[i].size() ) {
				LIS[i] = LIS[j];
			}
		}
		LIS[i].push_back(magiLevels[i]);
	}
	vector<int> longest = LIS[0];
	for (int i = 1; i < numOfMagi; i++) {
		if ( LIS[i].size() > longest.size() && LIS[i][0] <= longest[0] )
			longest = LIS[i];
	}
	return longest;
}