#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<time.h>

using namespace std;

int main()
{
	bool usr_attitude = true,usr_guess_right=false;
	char seq_index,usr_exist=0,wrong_times=0,usr_answer;
	const char max_seq = 6;
	string usr_name,temp_name;
	int usr_tries=0, usr_rights=0,nt,nc,usr_guess;
	vector<int> *current_vec = 0;
	int elem_seq[]={
		1,2,3,// Fibonacci
		3,4,7,// Lucas
		2,5,12,// Pell
		3,6,10,// Triangular
		4,9,16,// Square
		5,12,22// Pentagonal
	};
	vector<int> Fibonacci, Lucas, Pell, Triangular, Square, Pentagonal;
	vector<int> *seq_addrs[] = { &Fibonacci, &Lucas, &Pell, &Triangular, &Square, &Pentagonal };
	for(char j=0;j<6;j++)
		for (char i = 0; i < 3; i++)
			(*seq_addrs[j]).push_back(elem_seq[j*3+i]);
	cout << "Welcome to this game" << endl;
	cout << "Please input your name:" << endl;
	cin >> usr_name;
	ifstream infile("usr_data.text");
	if (!infile)
		cerr << "Unable to access the data file" << endl;
	else
		while (infile >> temp_name)
		{
			infile >> nc >> nt;
			if (temp_name == usr_name)
			{
				usr_exist = 1;
				usr_rights = nc;
				usr_tries = nt;
			}
		}
	if (usr_exist == 0)
	{		
		cout << "Welcome,new player:" << usr_name << endl;
		usr_rights = 0;
		usr_tries = 0;
	}
	else if (usr_exist == 1)
	{
		cout << "Welcome,player:" << usr_name<<endl;
		cout << "Your data: right times are " << usr_rights << endl;
		cout<< "try times are " << usr_tries << endl;
	}
	cout << "computer will give you first two numbers of a sequence,\nthen you input the third number that you guess,if you get the right guess,\nthe next sequence will appear" << endl;
	cout << "input 0 into guess or input n/N into answer can quit the game." << endl;
	while (usr_attitude)
	{
		srand(time(NULL));
		seq_index = rand() % max_seq;
		current_vec = seq_addrs[seq_index];

		cout << "The first two element of this sequence are:" << (*current_vec)[0] << " and " << (*current_vec)[1] << endl;
		cout << "Please enter the value of the third element:";
		cin >> usr_guess;
		usr_guess_right = false;
		while (!usr_guess_right)
		{
			if ((*current_vec)[2] == usr_guess)
			{
				cout << "congratulate! you get the right answer" << endl;
				usr_rights++;
				usr_tries++;
				usr_guess_right = true;
				wrong_times = 0;
			}
			else if(usr_guess==0)
			{
				usr_guess_right = true;
				usr_attitude = false;
			}
			else
			{
				usr_tries++;
				wrong_times++;
				switch (wrong_times)
				{
				case 1:
					cout << "Oops! Nice guess but not quite it.\n";
					break;
				case 2:
					cout << "Hmm. Sorry. Wrong a second time.\n";
					break;
				case 3:
					cout << "Ah, this is harder than it looks, isn't it?\n";
					break;
				default:
					cout << "It must be getting pretty frustrating by now!\n";
					break;
				}
				cout << "Would you like to guess again(answer y/n)?\n";
				cin >> usr_answer;
				if (usr_answer == 'n' || usr_answer == 'N')
				{
					usr_attitude = false;
					usr_guess_right = true;
				}
				else if (usr_answer == 'y' || usr_answer == 'Y')
				{
					cout << "guess again: \n";
					cin >> usr_guess;
					cout << endl;
				}
				else
				{
					cout << "answer again" << endl;
					cin >> usr_answer;
					while (1)
					{
						if (usr_answer == 'n' || usr_answer == 'N')
						{
							usr_attitude = false;
							break;
						}
						else if (usr_answer == 'y' || usr_answer == 'Y')
						{
							cout << "guess again: \n";
							cin >> usr_guess;
							cout << endl;
							break;
						}
						else
						{
							cout << "answer again" << endl;
							cin >> usr_answer;
						}
					}
				}
			}
		}
	}
	ofstream outfile("usr_data.text", ios_base::app);
	if (!outfile)
	{
		cerr << "Oops! Unable to save data!" << endl;
	}
	else
	{
		outfile << usr_name << ' '
			<< usr_rights << ' '
			<< usr_tries << endl;
	}
	return 0;
}