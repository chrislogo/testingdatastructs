#include<iostream>
#include<cstdlib>
#include<fstream>
#include"cputime.h"
#include"MyHash.h"
#include"MyDS.h"
#include<set>
#include<unordered_set>


using namespace std;


void Load_Dictionary(string, MyDS&, set<string>&, unordered_set<string>&, 
			unordered_set<string, MyHash>&, unsigned long long[], const int); 
void Load_File(string&, string);	
static string Dict_Next_Word(string&,string::size_type&,string::size_type&);
static string Text_Next_Word(string&,string::size_type&,string::size_type&);

int main(int argc, char *argv[])
{
	// Check if user entered a file name with executable
	// If not warn and exit
	if(argc != 3)
	{
		cout << "USAGE: " << argv[0] << " DictionaryName InputFileName." << endl;
		exit(1);
	}

	MyDS A;
	set<string> B;
	unordered_set<string> C;
	unordered_set<string, MyHash> D;	
		
	string dict_name = argv[1];
	string file_name = argv[2];
	string word; 
	string file_content;
	string::size_type pos1 = 0;
 	string::size_type pos2 = 0; 
	
	unsigned long long num_words = 0.0;		// for calc mean

	set<string>::iterator B_itr;
	unordered_set<string>::iterator C_itr;
	unordered_set<string, MyHash>::iterator D_itr;
	
	unsigned long long t[28],
			   searchA, searchB, searchC, searchD,
			   meanA, meanB, meanC, meanD,
			   maxA, maxB, maxC, maxD,
			   minA, minB, minC, minD;

	bool exists;
	bool first_time = true;		//used to initialize the mean

	meanA = meanB = meanC = meanD = maxA = maxB = maxC = maxD = 0;
	minA = minB = minC = minD = 0;

	for(int i = 8; i < 28; i++)
		t[i] = 0;
 
	// set the load factor to be < 1 for less collisions
	// faster storing of MyHash
	float z = D.max_load_factor();
	D.max_load_factor(z*0.7);


 	Load_Dictionary(dict_name, A, B, C, D, t, 28);
	
	// Gets time for storing dictionary
	searchA = t[8];
	searchB = t[9];
	searchC = t[10];
	searchD = t[11];

	// reset for calculating means
	for(int i = 8; i < 12; i++)
		t[i] = 0;

	
	Load_File(file_content, file_name);
	
	
	while(pos1 != string::npos)
	{
		word = Text_Next_Word(file_content, pos1, pos2);
	
		if(pos1 == string::npos)
			break; 
		
		t[2] = cputime();
		B_itr = B.find(word);
		t[3] = cputime();
		
		t[17] = t[13];
		t[13] = t[3] - t[2];
		
		
		if(first_time)
			t[25] = t[13];

		// for maxB
		if(t[17] < t[13])
		{
			if(t[21] < t[13])
				t[21] = t[13];
		}

		
		// for minB
		if(t[25] > t[13])
			t[25] = t[13];
		
	
		// for meanB
		t[9] = t[9] + t[13];
		
		if(B_itr != B.end())
			cout << "Y set" << endl;
		else
			cout << "N set" << endl;



		t[4] = cputime();
		C_itr = C.find(word);
		t[5] = cputime();
		
		t[18] = t[14];
		t[14] = t[5] - t[4];
		
		if(first_time)
			t[26] = t[14];

		// for maxC
		if(t[18] < t[14])
		{
			if(t[22] < t[14])
				t[22] = t[14];
		}
		
		// for minC
		if(t[26] > t[14])
			t[26] = t[14];

		// for meanC
		t[10] = t[10] + t[14];

		if(C_itr != C.end())
			cout << "Y hash" << endl;
		else
			cout << "N hash" << endl;



		t[6] = cputime();
		D_itr = D.find(word);
		t[7] = cputime();
		
		t[7] = cputime();
		t[19]= t[15];
		t[15] = t[7] - t[6];
		
		if(first_time)
			t[27] = t[15];

		// for maxD
		if(t[19] < t[15])
		{	
			if(t[23] < t[15])
				t[23] = t[15];
		}	

		// for minD
		if(t[27] > t[15])
			t[27] = t[15];

		// for meanD
		t[11] = t[11] + t[15];

		if(D_itr != D.end())
			cout << "Y myhash" << endl;
		else
			cout << "N myhash" << endl;



		t[0] = cputime();
		exists = A.search(word);
		t[1] = cputime();
		
		t[16] = t[12];
		t[12] = t[1] - t[0];
		
		if(first_time)
			t[24] = t[12];

		// for maxA
		if(t[16] < t[12])
		{
			if(t[20] < t[12])
			{		
				t[0] = t[20];
				t[20] = t[12];
			}
		}

		// for minA
		if(t[24] > t[12])
			t[24] = t[12];
		
		// for meanA
		t[8] = t[8] + t[12];

		if(exists)
			cout << "Y myds" << endl;
		else
			cout << "N myds" << endl;

	
		pos1 = pos2;
	
		num_words++;
		first_time = false;
	}
	
	num_words = num_words * 1.0;
	
	meanA = t[8]/num_words;
	meanB = t[9]/num_words;
	meanC = t[10]/num_words;
	meanD = t[11]/num_words;
	
	maxA = t[20];
	maxB = t[21];
	maxC = t[22];
	maxD = t[23];
		
	minA = t[24];
	minB = t[25];
	minC = t[26];
	minD = t[27];

	cout << endl << "set: store dictionary " << searchB*iCPS 
	     << " s, search: min " << minB*iCPS << " s, max " << maxB*iCPS
	     << " s, mean " <<  meanB*iCPS << " s" << endl;
	cout << endl << "hash: store dictionary " << searchC*iCPS 
	     << " s, search: min " <<  minC*iCPS << " s, max " << maxC*iCPS
	     << " s, mean " << meanC*iCPS << " s" << endl;
	cout << endl << "myhash: store dictionary " << searchD*iCPS 
	     << " s, search: min " << minD*iCPS << " s, max " << maxD*iCPS
	     << " s, mean " << meanD*iCPS << " s" << endl;
	cout << endl << "myds: store dictionary " << searchA*iCPS  
	     << " s, search: min " << minA*iCPS << " s, max " << maxA*iCPS
	     << " s, mean " << meanA*iCPS << " s" << endl << endl;

	return 0;
}



void Load_Dictionary(string file_name, MyDS &A, set<string> &B, 
			unordered_set<string> &C, unordered_set<string, MyHash> &D
			, unsigned long long t[], const int z)
{

	ifstream in_file(file_name.data(), ifstream::in);

	string::size_type pos1 = 0;
	string::size_type pos2 = 0;
	string word;
	streampos size;
	
	if(!in_file)
        {
                cout << "ERROR: Cannot open input file: " << file_name << endl
                     << "Terminating..." << endl << endl;

                exit(1);
        }

        in_file.seekg (0,in_file.end);


	size = in_file.tellg();

	in_file.seekg(0, in_file.beg);

	char *buffer = new char[size];

	in_file.read(buffer, size);
	
	string s(buffer);

	delete[] buffer;

	in_file.close();
	
	

	while(pos1 != string::npos)
	{
		word = Dict_Next_Word(s, pos1, pos2);
	
		if(pos1 == string::npos)
			break;

		pos1 = pos2;
		
		if(islower(word[0]))
		{
			t[0] = cputime();
			A.push(word);
			t[1] = cputime();
	
			t[2] = cputime();
			B.insert(word);
			t[3] = cputime();

			t[4] = cputime();
			C.insert(word);
			t[5] = cputime();
	
			t[6] = cputime();
			D.insert(word);
			t[7] = cputime();

			// Calculate total time for search on each DS
			t[8] = (t[1] - t[0]) + t[8];
			t[9] = (t[3] - t[2]) + t[9];
			t[10] = (t[5] - t[4]) + t[10];
			t[11] = (t[7] - t[6]) + t[11];	
		}
	}
}




void Load_File(string &file_content, string file_name)
{ 
	ifstream in_file(file_name.data(), ifstream::in);
	
	streampos size;

	if(!in_file)
	{
		cout << "ERROR: Cannot open input file: " << file_name << endl
		     << "Terminating..." << endl << endl;

		exit(1);
	}

	in_file.seekg (0,in_file.end);

	size = in_file.tellg();

	in_file.seekg(0, in_file.beg);

	char *buffer = new char[size];

	in_file.read(buffer, size);

	string s(buffer);

	file_content = s;

	delete[] buffer;

	in_file.close();
}


static string Dict_Next_Word(string &S, string::size_type &start, string::size_type &end)
{
	string delimiters = " \n\t!*^():;\",.?/";
	string temp;
	
        start = S.find_first_not_of(delimiters, start);
	
	if(start == string::npos)
                return string("");

        end = S.find_first_of(delimiters, start);

        temp = S.substr(start, (end-1) - start);

	// gets rid of hyphenated, apostrophe  words also gets rid of upper and numeric
	for(unsigned int i = 0; i < temp.size(); i++)
	{
		if(temp[i] == '-' || temp[i] == '\'' 
			|| isdigit(temp[i]) || isupper(temp[i]))
			return string("");
	}

	return temp;
}


// Another problem I noticed was my functions were reading the dictionary
// and input file words in different ways I noticed and storing extra space that 
// wasn't there but separating the 2 fuctions in this way and the only difference
// is that Dict_Next_Word separates the word at (end-1) - start instead.
static string Text_Next_Word(string &S, string::size_type &start, string::size_type &end)
{
        string delimiters = " \n\t!*^():;\",.?/";
        string temp;

        start = S.find_first_not_of(delimiters, start);
        
        if(start == string::npos)
                return string("");

        end = S.find_first_of(delimiters, start);
       
	temp = S.substr(start, end - start);
       
        // gets rid of hyphenated, apostrophe  words also gets rid of upper and numeric
        for(unsigned int i = 0; i < temp.size(); i++)
        {
                if(temp[i] == '-' || temp[i] == '\''
                        || isdigit(temp[i]) || isupper(temp[i]))
                        return string("");
        }

        return temp;
}

