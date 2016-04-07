#ifndef MYDS_H
#define MYDS_H

#include<string>
#include<iostream>

using namespace std;


class Node
{
 public:
	
	Node *children[26];
	
	Node()
	{
		for(int i = 0; i < 26; i++)
			children[i] = NULL;		
	}

	~Node()
	{
		for(int i = 0; i < 26; i++)
			delete children[i];
	}
};

class MyDS
{
 public:

	MyDS();
	~MyDS();
	void push(const string &s);
	bool search(const string &s);
	void init_nodes(Node*, const int);

 private:

	Node *root;
};

#endif
