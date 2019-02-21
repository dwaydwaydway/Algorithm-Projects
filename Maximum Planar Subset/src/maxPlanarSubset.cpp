#include<iostream>
#include<assert.h>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<fstream>
#include<map>
#include<unordered_map>
using namespace std;

// A map with j as key and i as value that represents each chord
unordered_map<int, int> chord_map;

// Check if the input chord is reversed
unordered_map<int, bool> reversed;

// A unordered_map iterator
unordered_map<int, int>::iterator iter;

// A map with i as key and j as value that represents chrds that was used
map<int, int> chords;

// A map iterator
map<int, int>::iterator miter;

// A chart that records the optimal substructure
int* MIS;

// A chart that records which cases we used to fill MIS
bool* cases;

// This function fills MIS(i, j) with v and cases(i, j) with c
void put(int i, int j, int v, bool c){
	MIS[j*(j-1)/2 + i] = v;
	cases[j*(j-1)/2 + i] = c;
}

// This function returns the case of MIS(i, j)
bool checkCase(int i, int j){
	if(i < 0 || j <= 0 || i >= j)
		return 0;
	return cases[j*(j-1)/2 + i];
}

// This function returns MIS(i, j)
int get(int i, int j){
	if(i < 0 || j <= 0 || i >= j)
		return 0;
	return MIS[j*(j-1)/2 + i];
}

// This function recursively find the chords of the done-filling MIS chart
void findChord(int i, int j){
	if( i < j && checkCase(i, j) ){
		if( reversed[j] )
			chords[j] = chord_map[j];
		else
			chords[chord_map[j]] = j;
		findChord( i, chord_map[j] - 1 );
		findChord( chord_map[j] + 1, j-1 );
	}
	else if( i < j ){
		findChord(i, j-1);
	}
}

int main( int argc, char *argv[]){
	
	// Read file
	std::ifstream infile( argv[1] );
	int num_of_node;
	infile >> num_of_node;

	// Output stream	
	ofstream output;
	output.open( argv[2] );

	//Make a map whose (value, key) represents a chord
	int a, b, flag;
	while( infile >> a >> b ){
		if( flag == b )
			break;
		if(a > b){
			reversed[a] = true;
			chord_map[a] = b;
		}
		else
			chord_map[b] = a;
		flag = b;
	}

	//Make history recorder with j as key and the result as value 
	MIS = new int[num_of_node * (num_of_node - 1) / 2];
	cases = new bool[num_of_node * (num_of_node - 1) / 2];
	
	// Start calculating
	for(int j = 0; j < num_of_node; j++){
		
		iter = chord_map.find(j);
		
		// If found a chord within (i, j)
		if( iter != chord_map.end() ){
			int k = iter->second;	
			
			for(int i = 0; i < j; i++){

				// Case 1 : MIS(im k-1) + MIS(+k1, j-1) + 1 > MIS(i, j-1)
				if( i <= k && get(i, k-1) + get(k+1, j-1) + 1 >= get(i, j-1) ){
					put( i, j, (get(i, k-1) + get(k+1, j-1) + 1), true );
				}
				
				// Case 2 : MIS(im k-1) + MIS(+k1, j-1) + 1 <= MIS(i, j-1)
				else{
					put( i, j, get(i, j-1), false );
				}
			}
		}

		// Case 3 : No chord was found
		else{
			for(int i = 0; i < j; i++){
				put(i, j, get(i, j-1), false);
			}
		}
	}

	//Totel chord	
	output << get(0, num_of_node - 1);	

	//Find each chord
	findChord(0, num_of_node - 1);
	for(miter = chords.begin(); miter != chords.end(); miter++){
		output<<"\n"<<miter->first<<" "<<miter->second;
	}

	delete[] MIS;
	delete[] cases;
}
