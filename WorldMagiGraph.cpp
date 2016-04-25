#include <iostream>
#include <stack>
using namespace std;




class World_Magi {
	string name;
	int num_of_magi;
	int num_of_connections;
	World_Magi * connections;
public:
	World_Magi() { 
		name = ""; 
		num_of_magi = 0; 
		num_of_connections = 0; 
		connections = new World_Magi[num_of_connections]; 
	};
	void setName(string aName)
	{
		name = aName;
	};
	void setNum(int aNum)
	{
		num_of_magi = aNum;
	};
	void setConnection(WorldMagi to_be_connected)
	{
		num_of_connections++;
		connections[num_of_connections] = to_be_connected;
	};
	string getName() { return name; };
	int getNum(){ return num_of_magi; }
};

// Tree class
class Graph {
	Graph* root;
public:
	Graph();
	~Graph();
	Graph* Root() { return root; };
	int numberOfVertices();
	int numberOfEdges();
	bool existsEdge(int, int);
};
