//Helping my friend JIM.... 
//He could just walk to his goal
//but he decided to jump so...

//Luis Henrique Baster Massud
//U43063745

//Implementention uses graph to keep 
//track of trace and possibilities for nodes 
//visited using DFS search

#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

//Creating the structure of a node
struct node{
    
    int x, y, jump;
    bool discarded, inResult;
    stack <vector<int> > possibilities;

};

int main(){

	//Inputing from file
	//and creating matrix using vectors to store nodes
	int maxX, maxY;
	ifstream inFile("input.txt");
	inFile >> maxY;
	inFile >> maxX;
	vector<vector<struct node> > maze(maxX, vector<struct node> (maxY));

	//Filling the Matrix with data from input file
	for (int i=0; i<maxY; i++){
		for (int j=0; j<maxX; j++){
			node inputNode;
			inFile >> inputNode.jump;
			inputNode.x = j;
			inputNode.y = i;
			inputNode.discarded = false;
			maze[j][i] = inputNode;
		}
	}

	//Generating stack and a string to keep track of the nodes and direction of solution
	stack <struct node> resultStack;
	string resultDirection("");

	//Starting JIM at position 0x0
	resultStack.push(maze[0][0]);
	maze[0][0].inResult = true;
	bool resultFound; resultFound = false;

	//Filling possibilities for the specific node being visited at the time	
	do {
		int tempx = resultStack.top().x;
		int tempy = resultStack.top().y;
		int tempjump = resultStack.top().jump;
		int right = tempx + tempjump;
		int down = tempy + tempjump;
		int left = tempx - tempjump;
		int up = tempy - tempjump;

		//Tracing Purposes
		cout << "\nI am at the node: ";
		cout << tempx << ", " << tempy << " and I can jump: " << tempjump;
		
		//Creating the stack of possibilities within the node struct for the node visited
		//Conditions implemented in such a way that JIM prioritizes going RIGHT, DOWN, LEFT, UP in this order

		if (tempjump != 0){
			if (up >= 0 && up < maxY){
				if (maze[tempx][up].discarded == false && maze[tempx][up].inResult == false){
					vector<int> tempvect; tempvect.push_back(tempx); tempvect.push_back(up);
					maze[tempx][tempy].possibilities.push(tempvect);
				} 
			} 
			if (left >= 0 && left < maxX){
				if (maze[left][tempy].discarded == false && maze[left][tempy].inResult == false){
					vector<int> tempvect; tempvect.push_back(left); tempvect.push_back(tempy);
					maze[tempx][tempy].possibilities.push(tempvect);
				}
			}
			if (down >= 0 && down < maxY){
				if (maze[tempx][down].discarded == false && maze[tempx][down].inResult == false){
					vector<int> tempvect; tempvect.push_back(tempx); tempvect.push_back(down);
					maze[tempx][tempy].possibilities.push(tempvect);
				}
			}
			if (right >= 0 && right < maxX){
				if (maze[right][tempy].discarded == false && maze[right][tempy].inResult == false){
					vector<int> tempvect; tempvect.push_back(right); tempvect.push_back(tempy);
					maze[tempx][tempy].possibilities.push(tempvect);
				}
			}
		}

		//Condition to define if solution was found
		//meaning JIM reached the desired GOAL
		if (tempx == maxX - 1 && down == maxY - 1){
			resultFound = true;
		} else if (right == maxX - 1 && tempy == maxY - 1){
			resultFound = true;
		} 
	
		//Checking if the node found is not taking us
		//anywhere useful...
		if (maze[tempx][tempy].possibilities.empty()){

			//Removing from the stack/string if not useful
			resultStack.pop();
			resultDirection.pop_back();
			resultDirection.pop_back();
			maze[tempx][tempy].discarded = true;

			//Tracing Purposes
			cout << "\nI am discarded because I will not take you anywhere JIM...";
		} else {

			//If it is useful add to result for now
			int topx = maze[tempx][tempy].possibilities.top().at(0);
			int topy = maze[tempx][tempy].possibilities.top().at(1);
			resultStack.push(maze[topx][topy]);

			//Adds to the string using the proper format
			if (topx > tempx && topy == tempy){
				resultDirection.append("E ");
			} else if (topx < tempx && topy == tempy){
				resultDirection.append("W ");
			} else if (topx == tempx && topy < tempy){
				resultDirection.append("N ");
			} else if (topx == tempx && topy > tempy){
				resultDirection.append("S ");
			}
			maze[topx][topy].inResult = true;
		}
		
		//Deleting possibilities so that next time the discarded can be avoided
		stack <vector<int> > clearing;
		maze[tempx][tempy].possibilities.swap(clearing);
	} while (resultFound == false);

	cout << "\n\n";
	cout << resultDirection;

	//OUTPUT to File
	ofstream outFile("output.txt");
	outFile << resultDirection;
	cout << "\n";
}