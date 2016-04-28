#include "Graph.h"
#include <iostream>
#include <algorithm>
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

//find index that holds the minimum value in array
//does not consider the indices in the exclude vector
int minIndex( int* arr , int size1 , vector<int> exclude ) {
	int min_index = -1;
	for (int i = 0; i < size1; i++) {
		//if i is not in the exclude vector 
		if ( binarySearch(exclude,i,0,exclude.size()-1) == -1 ) {
			//if min_index is -1, change it to i
			if ( min_index == -1 ) {
				min_index = i;
			}
			//if min_index is not -1, but arr[i] < arr[min_index], change it to i
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
			
			//this code for testing purposes
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

void Graph::initialize() {
	vector<int> LIS_lengths(numberOfWorlds); //length of LIS for each world
	for (int i = 0; i < numberOfWorlds; i++) {
		LIS_lengths[i] = worlds[i]->magi_LIS().size();
	}
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
	
	/*

	cout << "\n\nCOST MATRIX:\n\n";
	for (int i = 0; i < numberOfWorlds; i++) {
		for (int j = 0; j < numberOfWorlds; j++) {
			cout << costMatrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl << endl;

	*/
	
}

vector<int> Graph::shortestPath( int source, int dest ) {
	
	vector<int> visited;
	int visited_size = 0;

	int* dist = new int[numberOfWorlds];
	int* prev = new int[numberOfWorlds];
	
	int i = source;
	visited.push_back(i);

	int iteration = 1;
	while ( 1 ) {
		for (int j = 0; j < numberOfWorlds; j++) {
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
			else {
				if ( ( i != j ) && ( costMatrix[i][j] != INF ) ) {
					dist[j] = min( dist[j] , dist[i] + costMatrix[i][j] );
					if ( dist[j] == dist[i] + costMatrix[i][j] ) {
						prev[j] = i;
					}
				}
			}
		}

		/*	SOME DEBUG STUFF

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

		*/

		i = minIndex(dist,numberOfWorlds,visited);
		visited.push_back(i);
		visited_size++;
		sort(visited.begin(),visited.end());
		if ( i == dest ) {
			break;
		}
	}
	vector<int> path;
	if ( prev[i] != -1 ) {
		while ( i != source ) {
			path.emplace( path.begin() , i );
			i = prev[i];
		}
		path.emplace( path.begin() , i );
	}
	return path;
}

int Graph::numberOfGems( int source , int dest ) {
	vector<int> path = shortestPath( source , dest );
	int gems = 0;
	for (size_t i = 1; i < path.size(); i++) {
		int a = path[i-1];
		int b = path[i];
		vector<int> LIS = worlds[a]->magi_LIS();
		int sum = 0;
		int numOfEdits = costMatrix[a][b];
		for ( int j = 0; j < numOfEdits; j++) {
			sum += LIS[j];
		}
		gems += sum;
	}
	return gems;
}

int Graph::numberOfIncantations( int source , int dest ) {
	vector<int> path = shortestPath( source , dest );
	int incantations = 0;
	for (size_t i = 1; i < path.size(); i++) {
		int a = path[i-1];
		int b = path[i];
		incantations += costMatrix[a][b];
	}
	return incantations;
}

World** Graph::getWorlds() {
	return worlds;
}
