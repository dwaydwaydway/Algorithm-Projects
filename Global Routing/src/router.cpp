#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "graph_class.h"
#include <fstream>
#include <string>
#include <typeinfo>
#include <sstream>
#include <stack>
using namespace std;

int get_number( string str ){
	stringstream ss;
	ss << str;
	string temp;
	int found;
	while(!ss.eof()){
		ss >> temp;
		if(stringstream(temp) >> found)
			return found;
	}
}
int main( int agrc, char *argv[] ){
	int temp[3];
	// Read file
	ifstream infile( argv[1] );
	string line;
	for( int i = 0; i < 3; i++ ){
		getline(infile, line);
		temp[i] = get_number(line);
	}
	int size = temp[0];
	int capa = temp[1];
	int num_nets = temp[2];
	int** nets = new int*[num_nets];
	for( int i = 0; i < num_nets; i++){
		getline(infile, line);
		istringstream iss(line);
		nets[i] = new int[4];
		if(!(iss >> temp[0] >> nets[i][0] >> nets[i][1] >> nets[i][2] >> nets[i][3])){
			cout << "error\n";
			break;
		}
	}
	// Output stream
	ofstream output;
	output.open( argv[2] );

	// Create the graph
	graph_class graph(size, capa);

	// Run all nets
/*	stack<int*>** history = new stack<int*>*[num_nets];
	for( int i = 0; i < num_nets; i++){	
		graph.initialize( nets[i][0], nets[i][1] );
		for( int j = 0; j < size * size ; j++ ){
			 int *min_position;
			min_position = graph.extract_min();
			graph.relax( min_position );
		}
		history[i] = graph.get_path( nets[i] );
	}
*/
	for(int i = 0; i < num_nets; i++){
//		graph.delete_path(history[i]);
		graph.initialize( nets[i][0], nets[i][1] );
		for( int j = 0; j < size * size ; j++ ){
			 int *min_position;
			min_position = graph.extract_min();
			graph.relax( min_position );
		}
		stack<int*>* path = graph.get_path( nets[i] );
		if( i != 0 )
			output << endl;
		int route = path->size();
		output << i << " " << route - 1;
		for(int u = 0; u < route - 1; u++){
			output << endl << path->top()[0] << " " << path->top()[1] << " ";
			path->pop();
			output << path->top()[0] << " " << path->top()[1];
		}
	}
	return 0;
}
