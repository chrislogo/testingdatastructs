#ifndef MYHASH_H
#define MYHASH_H


#include<string>


using namespace std;


class MyHash
{
 public:
	

	size_t operator()(const string& s) const
	{
		size_t index = s[0];
		unsigned int i;
		
		for(i = 1; i < s.length(); i++)
			index = ((index ^ 370261) * 101) + (index >> 20) + s[i];
			
		index = ((index & 370261) * 101) + (index >> 20);
		
		return index; 
	}
};

#endif
