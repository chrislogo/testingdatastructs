#include"MyDS.h"
#include<string>
#include<iostream>
#include<cstdlib>

using namespace std;


// constructor
MyDS::MyDS()
{
	root = new Node();
}


// destructor
MyDS::~MyDS()
{
	delete root;
}	


// push subtracts each char in the string with ascii value of 'a'
// since all lower case it will index 0 = 'a' to 25 = 'z'
// when index is met it becomes a parent to 26 new Node children
void MyDS::push(const string &s)
{
	int index = 0;			// finds which node out of s[i] - 'a'
	Node *temp = root;
	
	// Traverse levels of trie
	for(unsigned int i = 0; i < s.length(); i++)
	{
		index = int(s[i]) - 97;	//97 is ascii value of 'a'
	
		if(temp->children[index] == NULL)
			init_nodes(temp, index);
		
			temp = temp->children[index];
	}
	
}


// search does the same thing as push to find which path of the prefix trie to
// follow. If it makes it to a child that is pointing to NULL before the string
// legnth is reached then the word doesn't exist in the trie
bool MyDS::search(const string &s)
{
	int index;
	Node *temp = root;
	
	for(unsigned int i = 0; i < s.length(); i++)
	{
		// takes ascii value of 'a' and subtracts from char in word to
		// find which pointer to make a new subtree for
		index = int(s[i]) - 97;

		if(temp->children[index] == NULL)
			return false;
	
		temp = temp->children[index];
	}
			
	return true;
}



// initializes a new node as a parent pointing to 26 children
void MyDS::init_nodes(Node* temp, const int index)
{
	Node *t = new Node();
	temp->children[index] = t;
}

