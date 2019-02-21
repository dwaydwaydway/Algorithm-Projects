#include <cstdio>
#include <iostream>
#include <list>
#include <vector>
#include "parser.h"
#include <string>
#include <typeinfo>
#include <fstream>
using namespace std;
bool isSmaller(string A, string B, short n){
	/*return either if index is out of range, A if both*/
	if(B.length() == n) return false;
    if(A.length() == n) return true;
	 /*return either if the ascii order of the nth index is smaller, recursivly search if the same*/
	if( int(A[n]) < int(B[n]) ){
		return true;
	}
	else if( int(A[n]) > int(B[n]) ){
		return false;
	}
	else{
		return isSmaller(A, B, n + 1);
	}
}

// A node object to record the information of a list node
template <class K>
class node{
	public:
		node();
		node(string word, K index){
			this->word = word;
			this->index = index;
		}
		void set(string word, K index){
			this->word = word;
			this->index = index;
		}		
 		string word;
 		K index;
};
template <class T>
	void output(char **argv, AlgParser p, T size){
		// Pass the arguement 1 as the input file name
		p.Parse( argv[1] );

		T* sorted = new T[size];
		string *words = new string[size];
		T* indexs = new T[size];
		
		for( T i = 0 ; i < size; i++ ){
			//node<T> *temp = new node<T>(p.QueryString(i), i + 1);
			sorted[i] = i;
			words[i] = p.QueryString(i);
			indexs[i] = i + 1;
			//store.push_back(*temp);
			//sorted.push_back(temp);
		}
		for(T u = 1; u < size; u++){
			//node<T> *key = sorted[u];
			T key = sorted[u];
			T j = u-1;
			bool flag = false;
			while (j >=0 && words[key] < words[sorted[j]]) {
				sorted[j+1] = sorted[j];
				if(j == 0){
					flag = true;
					break;
				}
				j--;
			}
			if(flag == true)
				sorted[j] = key;
			else
				sorted[j+1] = key;
		}
		cout << "finish sorting" << endl;	
		// Display all strings and word numbers
		ofstream file;
		file.open(argv[2]);
		file << size << '\n';
		for(T i = 0; i < size; i++){
			file << words[sorted[i]] << " " << indexs[sorted[i]];
			if(i != size - 1)
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
	
	// The list of sorted element
	int size = p.QueryTotalStringCount();
	if( size <= 65534 && size >= 0)
		output<unsigned short>(argv, p, size);
	else if( size > 65534)
		output<unsigned int>(argv, p, size);
	else
		cout << "input file error(size = 0)" << endl;

	// Display the accumulated time
	cout << "The execution spends " << t.End() << " seconds" << endl;
	return 1;
}
