// ---------------------------------------------------------------------
// Name:	Joseph Ly
//			Phong Vu
// Course:	CPSC 323
// Date:	October 29, 2015
// Project:	7
//
// Purpose: This program determines whether the strings that are stored 
// in a text file are accepted or rejected
//               
// ---------------------------------------------------------------------
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <iterator>
#include <fstream>
using namespace std;

// Function prototypes
void copyData(string frame);
void check(string &w);
void display(stack<char> &s); // Recursive function to display stack after match
void insert(stack<char> &, vector<char> &, int &a, int &b, string table[][8]); // Add to stack

int main()
{
	copyData("data.txt"); // Input file

	cout << endl;
	system("Pause");
	return 0;
} // End of main

  //----copyData----------------------------------------------------------
  //
  // This function reads strings from text file and determines whether 
  // that words are accepted or rejected by the language 
  //
  //----------------------------------------------------------------------
void copyData(string frame)
{
	fstream infile;
	string w;
	infile.open(frame, ios::in);
	if (infile.is_open())
	{
		while (infile >> w)
		{
			check(w);
		}
		infile.close();
	}
	else
	{
		cout << "Error on file read!\n";
	}
} // End of copyData

void check(string &w)
{
	stack<char> cha;
	vector<char> v;
	int i = 0;
	int a, b;
	bool stack = 0, pass = 0, rem = 0;

	/* ! is used for empty space. ^ is used for lambda */
	/* Table needs to be changed for other artifical languages */
	string table[5][8] = { "TQ", "!", "!", "!", "!", "TQ", "!", "!",
		"!", "+TQ", "-TQ", "!", "!", "!", "^", "^",
		"FR", "!", "!", "!", "!", "FR", "!", "!",
		"!", "^", "^", "*FR", "/FR", "!", "^", "^",
		"i", "!", "!", "!", "!", "(E)", "!", "!" };

	cout << "Testing: " << w << endl;
	cha.push('$');
	cha.push('E');

	for (auto i = w.begin(); i != w.end(); i++)
	{
		rem = 0; // Reset break pass
		b = *i; // Read input

		/* ASCII Table Conversion */
		/* Table needs to be changed for other artifical languages */
		switch (b)
		{
		case 105: b = 0; break;	// i
		case 43: b = 1; break;	// +
		case 45: b = 2; break;	// -
		case 42: b = 3; break;	// *
		case 47: b = 4; break;	// /
		case 40: b = 5; break;	// (
		case 41: b = 6; break;	// )
		case 36: b = 7; break;	// $
		default:
		{
			cout << "REJECT" << endl;
			system("pause");
			exit(0);
		}
		}

		while (rem == 0) 
		{
			pass = 0; // Reset break pass
			a = cha.top();

			/* ASCII Table Conversion */
			switch (a)
			{
			case 69: a = 0; break;	// E
			case 81: a = 1; break;	// Q
			case 84: a = 2; break;	// T
			case 82: a = 3; break;	// R
			case 70: a = 4; break;	// F
			default:
			{
				if (a == 94) // ^ used for lambda
				{
					cha.pop();
					pass = 1;
					break;
				}
				else if (a == 33) // ! used for null space
				{
					cout << "REJECT" << endl;
					system("pause");
					exit(0);
				}
				else
				{
					cha.pop();
					if (cha.empty())
					{
						cout << "Match: " << endl;
						cout << "\nACCEPT" << endl;
						system("pause");
						exit(0);
					}
					cout << "Match: ";
					display(cha); // Recursive function to display stack after match
					i++; // Read next input
					while (cha.top() == *i)
					{
						cha.pop();
						cout << "\nMatch: ";
						display(cha);
						i++;
					}
					cout << endl;
					rem = 1;
				}
			}
			}
			if (rem == 1) {
				i--; // Jump equivalent to counter
				break;
			}
			if (pass == 0) { insert(cha, v, a, b, table); }
		}
	}
	system("pause");
	exit(0);
}

void display(stack<char> &s) // Recursive function to display stack after match
{
	if (s.empty())
	{
		return;
	}
	char top = s.top();
	s.pop();
	display(s);
	s.push(top);
	cout << top;
}

void insert(stack<char> &i, vector<char> &v, int &a, int &b, string table[][8]) {
	bool vector = 0;
	string buffer;
	i.pop();
	buffer = table[a][b];
	copy(buffer.begin(), buffer.end(), back_inserter(v));
	vector = 0;
	while (vector == 0)
	{
		i.push(v.back());
		v.pop_back();
		vector = v.empty(); // Break loop
	}
}

