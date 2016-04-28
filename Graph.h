#include "World.h"
#include <vector>
using namespace std;

class Graph {

	int numberOfWorlds; // Number of worlds
	int** costMatrix; //Matrix of edge costs
	World** worlds; //array of world pointers

public:
	//constructors
	Graph();
	Graph( int numberOfWorlds );

	//add a world
	void addWorld( World* &world , int index );
	//get edit distance between worlds at index w1 and w2
	int editDistBetweenWorlds( int w1, int w2 );
	//set the edges of the graph based on its worlds
	void initialize();
	//calculates shortest path from source to destination
	vector<int> shortestPath( int source , int dest );
	//calculates number of gems on shortest path from source to destination
	int numberOfGems( int source , int dest );
	//calculated total number of incantations on shortest path from source to destination
	int numberOfIncantations( int source , int dest );
	//return the World* array worlds[]
	World** getWorlds();
};