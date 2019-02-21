#include <cstdio>
#include <iostream>
#include "parser.h"
#include <string>
#include <fstream>
#include <vector>
using namespace std;
template<class P>
void merge(string *words, P* sorted, P start, P middle, P end ){

	P *Left_set = new P[middle - start + 1];
	for (P j = 0; j < middle - start + 1 ; j++){
		Left_set[j] = sorted[start + j]; 
	}	

	P *Right_set = new P[end - middle];
	for (P j = 0; j < end - middle ; j++){
		Right_set[j] = sorted[middle + 1 + j]; 
	}	
	
	P i;
    P lp = 0;
	P rp = 0;

	for ( i = start; i <= end; i++ ){
		bool flag = false;
		if( words[Left_set[lp]] <= words[Right_set[rp]] ){
			sorted[i] = Left_set[lp];
			lp ++;
			if(lp == middle - start + 1){
				for(P j = i + 1; j <= end; j++){
					sorted[j] = Right_set[rp];
					rp++;
				}
				flag = true;
			}	
		}
		else{	
			sorted[i] = Right_set[rp];
			rp ++;
			if(rp == end - middle){
				for(P j = i + 1; j <= end; j++){
					sorted[j] = Left_set[lp];
					lp++;
				}
				flag = true;
			}
		}
		if(flag == true)
			break;
	}
}
template <class Q>
void mergeSort( string* words, Q* sorted, Q start, Q end){
	if( end > start ){
		Q middle = ( start + end ) / 2;
		mergeSort<Q>( words, sorted, start, middle );
		mergeSort<Q>( words, sorted, middle + 1, end );
		merge<Q>( words, sorted, start, middle, end );
	}
}
template <class T>
void output( char **argv , AlgParser p, T size){
	// The list of sorted element
	T* sorted = new T[size];
	string* words = new string[size];
	T* indexs = new T[size];
	// Display all strings and word numbers
	for( T i = 0 ; i < size; i++ ){
		words[i] = p.QueryString(i);
		sorted[i] = i;
		indexs[i] = i + 1;
	}

	mergeSort<T>(words, sorted, 0, size - 1);

	ofstream file;
	file.open(argv[2]);
	file << size << '\n';
	for( T j = 0; j < size; j++ ){
		file << words[sorted[j]] << " " << indexs[sorted[j]];
		if(j != size - 1)
			file << '\n';
	}
	file.close();
}
int main( int argc, char** argv )
{
	// Declare the functional objects
	AlgParser p;
	AlgTimer t;
	
	// Pass the arguement 1 as the input file name
	p.Parse( argv[1] );

	// Start timer
	t.Begin();
	unsigned int size = p.QueryTotalStringCount();
	if( size <= 65533 && size > 0){
		output<unsigned short>(argv, p, size);
	}
	else if( size > 65534){
		output<unsigned int>(argv, p, size);
	}
	else{
		cout << "input file error(size <= 0)" << endl;
	}
	// Display the accumulated time
	cout << "The execution spends " << t.End() << " seconds" << endl;
	return 1;
}
