#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

class node{
	public:
		node(){};
		short precessor;
		double distance;
		bool relaxed;
		double edges[4] = {0.0, 0.0, 0.0, 0.0};
};
