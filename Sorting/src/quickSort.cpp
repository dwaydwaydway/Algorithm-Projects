#include <cstdio>
#include <iostream>
#include "parser.h"
#include <string>
#include <fstream>
#include <vector>
using namespace std;

template <class Q>
Q partition(string *words, Q *sorted, Q left, Q right ){
	Q m = left;
	left --;
	right ++;
	while(1){
		do
			left ++;
		while( words[sorted[left]] < words[sorted[m]] );
		do
			right --;
		while( words[sorted[m]] <  words[sorted[right]] );
		
		if ( left < right ){
			Q temp = sorted[left];
			sorted[left] = sorted[right];
			sorted[right] = temp;
		}
		else 
			return right;
	}
}

template <class V>
void quickSort( string* words, V* sorted, V start, V end){
	if( start < end ){
		V q = partition<V>( words, sorted, start, end );
		quickSort<V>( words, sorted, start, q);
		quickSort<V>( words, sorted, q+1, end);
	}
}


template <class T>
void output( char **argv, AlgParser &p, T size){
	
	// The list of sorted element
	T * sorted = new T[size];
	string *words = new string[size];
	T * indexs = new T[size];
	// Store all strings and word numbers
	for( T i = 0 ; i < size; i++ ){
		sorted[i] = i;
		indexs[i] = i + 1;
		words[i] = p.QueryString(i);
	}
	quickSort<T>( words, sorted, 0, (size - 1));
	
	// Write output file
	ofstream file;
	file.open(argv[2]);
	file << size << '\n';
	for( T j = 0; j < size; j++ ){
		file << words[sorted[j]] << " " << indexs[sorted[j]];
		if( j != size - 1)
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
	unsigned int size = p.QueryTotalStringCount();
	if( size <= 65534 && size > 0)
		output<unsigned short>( argv, p, (unsigned short)size);
	else if( size > 65534)
		output<unsigned int>( argv, p, size);
	else
		cout << "input file error(size <= 0)"<< endl;
	
	// Display the accumulated time
	cout << "The execution spends " << t.End() << " seconds" << endl;
	return 1;
}
