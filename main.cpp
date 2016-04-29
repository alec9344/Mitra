//Group members: Jorge Agnese, Jiantao Shen, Shawn Newsome, Darian Miranda

#include "Graph.h"
#include <unordered_map>
#include <iostream>
#include <string>

#define DEBUG 0

#define INF INT_MAX

int main() {

	//get number of worlds
	int n;
	cin >> n;

	Graph* g = new Graph(n);
	
	//associates each world's charm with an int representing that world's position in worlds[]
	unordered_map<string,int> map; 

	//array of World pointers
	World** worlds;
	worlds = new World*[n];
	for (int i = 0; i < n; i++)
		worlds[i] = new World;

	string charm;
	for (int i = 0; i < n; i++) {
		cin.ignore();
		cin >> charm;
		worlds[i]->charm = charm;
		worlds[i]->charmLength = charm.size();
		cin >> worlds[i]->numOfMagi;
		for (int j = 0; j < worlds[i]->numOfMagi; j++) {
			int level;
			cin >> level;
			worlds[i]->magiLevels.push_back(level);
		}
		map.insert( make_pair(charm,i) );
	}
	
	//add the worlds to the graph
	for (int i = 0; i < n; i++) {
		g->addWorld(worlds[i],i);
	}

	g->initialize();

	//get source world charm
	string sourceCharm;
	cin.ignore();
	cin >> sourceCharm;

	//get destination world charm
	string destinationCharm;
	cin.ignore();
	cin >> destinationCharm;
	
	int sourceIndex = map.find(sourceCharm)->second;
	int destIndex = map.find(destinationCharm)->second;

	vector<int> pathToDest = g->shortestPath(sourceIndex,destIndex);
	vector<int> pathFromDest = g->shortestPath(destIndex,sourceIndex);

	if ( pathToDest.size() == 0 )
		cout << "IMPOSSIBLE" << endl;
	else {
		cout << g->numberOfIncantations( sourceIndex , destIndex ) << " ";
		cout << g->numberOfGems( sourceIndex , destIndex ) << endl;
	}
	if ( pathFromDest.size() == 0 )
		cout << "IMPOSSIBLE" << endl;
	else {
		cout << g->numberOfIncantations( destIndex , sourceIndex ) << " ";
		cout << g->numberOfGems( destIndex , sourceIndex ) << endl;
	}

	if ( DEBUG ) {

		cout << endl << endl;
		cout << "TO DESTINATION:\n\n";
		vector<int> pathToDest = g->shortestPath(sourceIndex,destIndex);
		cout << endl << endl;
		cout << "FROM DESTINATION:\n\n";
		vector<int> pathFromDest = g->shortestPath(destIndex,sourceIndex);

		cout << endl;
		cout << "shortest path to destination is: ";
		if ( pathToDest.size() == 0 )
			cout << "IMPOSSIBLE" << endl;
		else {
			for (size_t i = 0; i < pathToDest.empty(); i++) {
				cout << worlds[ pathToDest[i] ]->charm << " ";
			}
			cout << endl;
		}
		cout << "shortest path from destination is: ";
		if ( pathFromDest.empty() )
			cout << "IMPOSSIBLE" << endl;
		else {
			for (size_t i = 0; i < pathFromDest.size(); i++) {
				cout << worlds[ pathFromDest[i] ]->charm << " ";
			}
		}
	}
	//system("PAUSE");
	return 0;
}