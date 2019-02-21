#include <math.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <map>
#include "node.h"
#include <stack>
#include <limits>
using namespace std;

class graph_class{
	public:
		graph_class( int size, int capa ){
			this->size = size;
			this->capa = (double)capa;
			vertex = new node*[size];
			for( int i = 0; i < size; i++ )
				vertex[i] = new node[size];
		}

		int size;
		double capa;
		node** vertex;
		int neighbor[4][2] = { {0, 1}, {0, -1}, {-1, 0}, {1, 0}	};
		int reverse_index[4] = { 1, 0, 3, 2 };
		multimap< double, int > min_map;
		
		int hash_position( int &x, int &y ){
			return size*x + y;
		}

		void relax( int* position ){
			for( int i = 0; i < 4; i++ ){
				int next_node[2] = { position[0] + neighbor[i][0], position[1] + neighbor[i][1] };  
				if( next_node[0] < 0 || next_node[1] < 0 || next_node[0] > size - 1 || next_node[1] > size - 1 )
					continue;

				double new_weight = vertex[ position[0] ][ position[1] ].distance + getweight( vertex[ position[0] ][ position[1] ], i );
				if( vertex[ next_node[0] ][ next_node[1] ].distance > new_weight ){
					
					vertex[ next_node[0] ][ next_node[1] ].distance = new_weight;
					vertex[ next_node[0] ][ next_node[1] ].precessor = i;  
				}
				if(vertex[ next_node[0] ][ next_node[1] ].relaxed == false)  
					min_map.insert( pair< double, int >( new_weight, hash_position( next_node[0], next_node[1] ) ) ) ;
			}
			vertex[ position[0] ][ position[1] ].relaxed = true;  
		}

		double getweight( node &v, int i ){
		
			return (0.1/(1+exp(-100*(v.edges[i] - capa))) + 1);
		}
	
		int* unhash_position( int &hashed ){
			int* unhashed = new int[2];
			unhashed[0] = floor( hashed / size );
			unhashed[1] = hashed - unhashed[0] * size;
			return unhashed;
		}
		int* extract_min(){

			int *ans = new int[2];
			ans[0] = -1;
			ans[1] = -1;
			if( min_map.begin() == min_map.end() ){
				cout << "empty map\n";
				exit(0);
			}
			do{
				ans = unhash_position( min_map.begin() -> second );
				min_map.erase( min_map.begin() );
			}while( vertex[ ans[0] ][ ans[1] ].relaxed );

			if( ans[0] == -1 || ans[1] == -1){
				cout << "extractMin error" << endl;
				exit(3);
			}
			return ans;
		}

		void initialize( int x, int y ){
			min_map.insert( pair<double, int>( 0, hash_position(x, y) ) ); 
			for( int i = 0; i < size; i++){
				for( int j = 0; j < size; j++){
					vertex[i][j].distance = numeric_limits<double>::max();
					vertex[i][j].precessor = -1;
					vertex[i][j].relaxed = false;
				}
			}
			vertex[x][y].distance = 0;
		}
		void delete_path( stack<int*>* path ){
			int* current_node = path->top();
			path->pop();
			while( !path->empty() ){
				int* next_node = path->top();
				path->pop();
				int type;
				if(next_node[1] > current_node[1])
					type = 0;
				else if(next_node[1] < current_node[1])
					type = 1;
				else if(next_node[0] < current_node[0])
					type = 2;
				else if(next_node[0] > current_node[0])
					type = 3;
				else{
					cout << "delete path error" << endl;
					exit(0);
				}
				vertex[ current_node[0] ][ current_node[1] ].edges[reverse_index[type]] -= 1;
				vertex[ next_node[0] ][ next_node[1] ].edges[type] -= 1;
				current_node = next_node;
			}	
		}
		stack<int*>* get_path( int* net ){
			unordered_map<int, bool> cycle;		
			stack<int*> *path = new stack<int*>();
			int position[2] = { net[2], net[3] };
			int* push = new int[2]{ net[2], net[3] };
			path -> push(push);
			while( position[0] != net[0] || position[1] != net[1] ){
				if( vertex[ position[0] ][ position[1] ].precessor == -1 || vertex[ position[0] ][ position[1] ].relaxed == false){
					cout << "get_path error: not relaxed" << endl;	
					exit(2);
				}
				if( cycle[hash_position(position[0], position[1])] ){
					cout << "cycle\n";
					exit(0);
				} 
				cycle[hash_position(position[0], position[1])] = true;

				short precessor = vertex[ position[0] ][ position[1] ].precessor;
				vertex[ position[0] ][ position[1] ].edges[ precessor ] += 1;
				position[0] -= neighbor[ precessor ][0];
				position[1] -= neighbor[ precessor ][1];
				vertex[ position[0] ][ position[1] ].edges[ reverse_index[precessor] ] += 1;
				int* push = new int[2]{ position[0], position[1] };
				path -> push(push);
			}
			return path;
		}
};
