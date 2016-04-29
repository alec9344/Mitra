#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <limits.h>
using namespace std;

#define DEBUG 0

#define INF INT_MAX

#define INSERT_COST 1
#define DELETE_COST 1
#define REPLACE_COST 1

//returns index of val
int binarySearch(vector<int> &list, int val, int first, int last) {
	if ( first > last )
		return -1;
	if ( first == last ) {
		if ( list[first] == val )
			return first;
		else 
			return -1;
	}
	int mid = (first + last)/2;
	if (val > list[mid])
		return binarySearch(list, val, mid+1, last);
	else 
		return binarySearch(list, val, first, mid);
}

//find index that holds the minimum value in array.
//does not consider the indices in the exclude vector.
//this is used in the implementation of Dijkstra's Shortest Path
//to find the vertex (realm) with the shortest subpath after each
//iteration, excluding the already visited vertices.
//returns -1 if all vertices are in the exclude vector (already visited).
int minIndex( int* arr , int size1 , vector<int> exclude ) {
	int min_index = -1;
	for (int i = 0; i < size1; i++) {

		//if i is not in the exclude vector 
		if ( binarySearch(exclude,i,0,exclude.size()-1) == -1 ) {

			//if min_index is -1, change it to i
			if ( min_index == -1 ) {
				min_index = i;
			}

			//if min_index is not -1, and arr[i] < arr[min_index], i is the new min_index
			else if ( arr[i] < arr[min_index] ) {
				min_index = i;
			}
		}
	}
	return min_index;
}

Graph::Graph() {
	numberOfWorlds = 0;
	costMatrix = NULL;
	worlds = NULL;
}
Graph::Graph( int NUMBEROFWORLDS ) {
	numberOfWorlds = NUMBEROFWORLDS;
	worlds = new World*[NUMBEROFWORLDS];
	costMatrix = new int*[NUMBEROFWORLDS];
	for (int i = 0; i < NUMBEROFWORLDS; i++) {
		costMatrix[i] = new int[NUMBEROFWORLDS];
	}
	for (int i = 0; i < NUMBEROFWORLDS; i++) {
		for (int j = 0; j < NUMBEROFWORLDS; j++) {
			if ( i == j )
				costMatrix[i][j] = 0;
			else
				costMatrix[i][j] = INF;
		}
	}
}

void Graph::initialize() {

	//get the length of LIS for each world
	vector<int> LIS_lengths(numberOfWorlds); 
	for (int i = 0; i < numberOfWorlds; i++) {
		LIS_lengths[i] = worlds[i]->magi_LIS().size();
	}

	//set up the cost matrix, with edge weights corresponding 
	//to number of incantations needed to get from i to j.
	for (int i = 0; i < numberOfWorlds; i++) {
		for (int j = 0; j < numberOfWorlds; j++) {
			if ( i == j )
				costMatrix[i][j] = 0;
			else {
				int editDist_ij = editDistBetweenWorlds(i,j);
				if ( LIS_lengths[i] >= editDist_ij )
					costMatrix[i][j] = editDist_ij;
			}
		}
	}
	
	//used during testing only
	if ( DEBUG ) {
		cout << "\n\nCOST MATRIX:\n\n";
		for (int i = 0; i < numberOfWorlds; i++) {
			for (int j = 0; j < numberOfWorlds; j++) {
				cout << costMatrix[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
}

void Graph::addWorld( World* &world , int index ) {
	worlds[index] = world;
}
int Graph::editDistBetweenWorlds( int w1 , int w2 ) {
	const char* s1 = worlds[w1]->charm.c_str();
	int size1 = worlds[w1]->charmLength;
	const char* s2 = worlds[w2]->charm.c_str();
	int size2 = worlds[w2]->charmLength;

	//initialize cost matrix
	int** cost = new int*[size1+1];
	for (int i = 0; i < size1+1; i++)
		cost[i] = new int[size2+1];
	for (int i = 0; i < size1+1; i++) {
		for (int j = 0; j < size2+1; j++) {
			if ( i == 0 ) 
				cost[i][j] = j;
			else if ( j == 0 )
				cost[i][j] = i;
			else 
				cost[i][j] = -1;
		}
	}
	for (int i = 1; i <= size1; i++) {
		for (int j = 1; j <= size2; j++) {
			int x = INSERT_COST + cost[i][j-1];
			int y = DELETE_COST + cost[i-1][j];
			//if s1[i-1] == s2[j-1], we don't need to do anything to that character
			int z = (s1[i-1] != s2[j-1])*REPLACE_COST + cost[i-1][j-1];
			cost[i][j] = min( min(x,y) , z );
			
			//used during testing only
			if ( DEBUG ) {
				for (int k = 0; k <= size1; k++) {
					for (int l = 0; l <= size2; l++)
						cout << cost[k][l] << " ";
					cout << endl;
				}
				system("PAUSE");
			}
		}
	}
	
	return cost[size1][size2];
}
vector<int> Graph::shortestPath( int source, int dest ) {
	
	//vector of visited vertices (realms)
	vector<int> visited;

	//array of shortest distance from source to each vertex (realm)
	int* dist = new int[numberOfWorlds];

	//array of previous vertex (realm) in shortest path
	int* prev = new int[numberOfWorlds];
	
	//at first, i = source and i is added to the vector of visitied vertices (realms)
	int i = source;
	visited.push_back(i);
	

	int iteration = 1; //variable only used during testing

	//loop terminates when shortest path from source to dest has been found
	while ( 1 ) {
		//for every j, cost of the shortest path from source to j is the minimum of 
		//a)the cost of the current shortest path from source to j and b)the cost 
		//of the current shortest path from source to j + the cost of getting from
		//i to j
		for (int j = 0; j < numberOfWorlds; j++) {

			//if i is the source, there are no existing shortest paths yet, so 
			//this subproblem is simplified to dist[j] = 0 if j == source and 
			//dist[j] = costMatrix[i][j] otherwise. prev[j] is -1 if there is 
			//no path from source to j and prev[j] = source otherwise.
			if ( i == source ) {
				if ( j == source ) {
					dist[j] = 0;
					prev[j] = -1;
				}
				else if ( costMatrix[i][j] == INF ) {
					dist[j] = INF;
					prev[j] = -1;
				}
				else {
					dist[j] = costMatrix[i][j];
					prev[j] = source;
				}
			}

			//if i is not the source, dist[j] is the minimum of 
			//a)the cost of the current shortest path from source to j and b)the cost 
			//of the current shortest path from source to j + the cost of getting from
			//i to j
			else {
				if ( ( i != j ) && ( costMatrix[i][j] != INF ) ) {
					dist[j] = min( dist[j] , dist[i] + costMatrix[i][j] );
					if ( dist[j] == dist[i] + costMatrix[i][j] ) {
						prev[j] = i;
					}
				}
			}
		}

		//only used during testing
		if ( DEBUG ) {
			cout << "iteration " << iteration++ << endl;
			cout << endl << "d: ";
			for (int k = 0; k < numberOfWorlds; k++) {
				cout << dist[k] << " ";
			}
			cout << endl << "p: ";
			for (int k = 0; k < numberOfWorlds; k++) {
				cout << prev[k] << " ";
			}
			cout << endl << endl;
		}

		//set i to the index of the last realm in the current shortest calculated
		//subpath from source to dest, excluding previously visited realms. Add this
		//realm to the previously visited realms.
		i = minIndex(dist,numberOfWorlds,visited);
		visited.push_back(i);
		//sort the vector of visited realms for use of binarySort() in minIndex()
		std::sort(visited.begin(),visited.end());
		//if the shortest subpath from source to dest ends at dest, then this is 
		//the shortest path from source to dest. Terminate the loop.
		if ( i == dest ) {
			break;
		}
	}
	//if i == -1, there is no path from source to dest, and we return an empty path vector.
	//Otherwise, trace back: starting with realm i (destination realm), add a realm to the 
	//front of the path vector and set i = prev[i]. Repeat until i is the source
	//realm, then do one more insertion of i at the front of path.
	vector<int> path;
	if ( prev[i] != -1 ) {
		while ( i != source ) {
			if (  i == -1 ) {
				vector<int> empty;
				return empty;
			}
			//if we run into an infinite loop, there is no path from source to dest
			if ( i == prev[prev[i]] ) {
				vector<int> empty;
				return empty;
			}
			path.emplace( path.begin() , i );
			try {
				i = prev[i];
			}
			catch (exception e) {
				i = 0;
				vector<int> empty;
				return empty;
			}
		}
		path.emplace( path.begin() , i );
	}
	return path;
}
int Graph::numberOfGems( int source , int dest ) {

	//get the indices of the realms on the shortest path from source to dest
	vector<int> path = shortestPath( source , dest );
	int gems = 0;
	for (size_t i = 1; i < path.size(); i++) {

		int a = path[i-1]; //the index of ith realm on the shortest path
		int b = path[i]; //the index of the i+1th realm on the shortest path
		vector<int> LIS = worlds[a]->magi_LIS(); //the LIS of the ith realm on shortest path
		int sum = 0; //used to calculate # of gems from ith realm to i+1th realm
		int numOfEdits = costMatrix[a][b]; //number of incantations required from ith realm to i+1th realm
		
		//for the number of incantations from ith to i+1th realm, sum the number of gems
		//required for each incantaion.
		for ( int j = 0; j < numOfEdits; j++) {
			sum += LIS[j];
		}

		//add the number of gems required to get from ith to i+1th realm 
		//to the total number of gems
		gems += sum;
	}
	return gems;
}
int Graph::numberOfIncantations( int source , int dest ) {

	//get the indices of the realms on the shortest path from source to dest
	vector<int> path = shortestPath( source , dest );
	int incantations = 0;

	//total number incantations is the sum of incantations needed to get from 
	//each ith realm to each i+1th realm.
	for (size_t i = 1; i < path.size(); i++) {

		int a = path[i-1]; //the index of ith realm on the shortest path
		int b = path[i]; //the index of the i+1th realm on the shortest path
		incantations += costMatrix[a][b]; //add number of incantations from i to i+1th realm to the total number of incantations
	}
	return incantations;
}
