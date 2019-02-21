#include <cstdio>
#include <iostream>
#include "parser.h"
#include <string>
#include <fstream>
#include <vector>
using namespace std;

// A node object to record the information of a list node
template <class H>
void Heapify( string* words, H *sorted, H parent, H end ){
	
	H left_child = 2 * parent + 1;
	H right_child = 2 * parent + 2;
	H maxNode = parent;
	
	if( left_child < end && words[sorted[left_child]] > words[sorted[maxNode]] )
		maxNode = left_child;	
   	if( right_child < end && words[sorted[right_child]] > words[sorted[maxNode]] )
		maxNode = right_child;
	if( maxNode != parent ){
		H temp = sorted[parent];
		sorted[parent] = sorted[maxNode];
		sorted[maxNode] = temp;
		Heapify<H>( words, sorted, maxNode, end ); 
	}
}

template <class E>
void HeapSort( string* words,  E *sorted, E size ){
	for ( E i = size/2 - 1; i >= 0; i--){
		Heapify<E>(words, sorted, i, size);
		if(i == 0)
			break;
	}	
	for( E i = size - 1; i >= 0; i-- ){
		E temp = sorted[0];
		sorted[0] = sorted[i];
		sorted[i] = temp;
		Heapify<E>( words, sorted, 0, i );
		if(i == 0)
			break;
	}
}
template <class O>
void output(char **argv, AlgParser p, O size){
	// Pass the arguement 1 as the input file name
	p.Parse( argv[1] );
	// The list of sorted element
	
	O *sorted = new O[size];
	string* words = new string[size];
	O *indexs = new O[size];
	// Store all strings and word numbers
	for( O i = 0 ; i < size; i++ ){
		words[i] = p.QueryString(i);
		sorted[i] = i;
		indexs[i] = i + 1;
	}
	HeapSort<O>(words, sorted, size);

	// Write output file
	ofstream file;
	file.open(argv[2]);
	file << size << '\n';
	for( O j = 0; j < size; j++ ){
		file << words[sorted[j]] << " " << indexs[sorted[j]];
	   if(j != size - 1)
			file << '\n';
	}
	file.close();
}
int main( int argc, char** argv ){
	// Declare the functional objects
	AlgParser p;
	AlgTimer t;
	// Pass the arguement 1 as the input file name
	p.Parse( argv[1] );
	// Start timer
	t.Begin();
	// The list of sorted element
	unsigned int size = p.QueryTotalStringCount();
	if( size <= 65534 && size > 0 ){
		output<unsigned short>(argv, p, (unsigned short)size);
	}
	else if( size > 65535 )
		output<unsigned int>(argv, p, size);
	else
		cout << "input file error( size <= 0 )"	<< endl;
	// Display the accumulated time
	cout << "The execution spends " << t.End() << " seconds" << endl;
	return 1;
}
