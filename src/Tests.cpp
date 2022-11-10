// Tests.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>

using namespace std;

bool test_commands(vector<string> commands)
{
	ofstream f_input("input.txt");
	if (f_input.is_open())
	{
		for (string s : commands)
			f_input << s << endl;
		f_input.close();
	}

	filesystem::path cwd = filesystem::current_path();
	//cout << "my directory is " << cwd.string() << endl;

	//cwd /= "x64";
	//cwd /= "Debug";
	cwd /= "RobotToy.exe";
	//cout << "my directory is " << cwd.string() << endl;
	string cmd = cwd.string() + " < input.txt > output.txt 2> error.txt";

	int res = system(cmd.c_str());
	if (res != 0)
		return false;

	ifstream f_output("output.txt");
	vector<string> lines;
	while (!f_output.eof())
	{
		string line;
		getline(f_output, line);
		if (line.empty())
			continue;
		lines.push_back(line);
	}

	//cout << "output: " << lines.size() << endl;
	//for (auto s : lines)
	//{
	//	cout << s << endl;
	//}

	ifstream f_error("error.txt");
	lines.clear();
	while (!f_error.eof())
	{
		string line;
		getline(f_error, line);
		if (line.empty())
			continue;
		lines.push_back(line);
	}

	if (lines.size() != 0)
	{
		//cout << X << "," << Y << "," << direction << " errors " << lines.size() << endl;
		//for (auto s : lines)
		//{
		//	cout << "   " << s << endl;
		//}
	}
	return lines.size() == 0;
}

int main()
{
	int N = 5; 
	
	cout << "test PLACE - wrong direction" << endl;

	vector<string> commands = { "place 0,0,NORT", "report" };
	bool res = test_commands(commands);
	cout << (res ? "Ok" : "error") << endl;
	
	//return 0;

	cout << "test PLACE - direction" << endl;
	for (auto direction : { "NORTH", "SOUTH", "EAST", "WEST" , "WES", "AAA"})
	{
		vector<string> commands;
		commands.push_back(string("place 0,0,") + string(direction));
		commands.push_back("report");

		bool res = test_commands(commands);
		cout << direction << "    " << (res ? "Ok" : "error") << endl;
	}

	//return 0;

	cout << endl << "test PLACE - X,Y" << endl;
	// test complexity is N * N
	// but as long as N is as small as 5 - it is Ok
	int error_count = 0; 
	//cout << "Y" << endl;
	cout << " ";
	for (int X = 0; X <= N; ++X)
		cout << " " << X;
	cout << endl;
	for (int Y = N ; Y >= 0; --Y)
	{
		cout << Y;
		for (int X = 0; X <= N; ++X)
		{
			vector<string> commands;
			stringstream ss;
			ss << "place " << X << "," << Y <<  ",NORTH"; 
			commands.push_back(ss.str());
			commands.push_back("report");

			bool res = test_commands(commands);

			cout << " " << (res ? "." : "x");
		}
		cout << endl;
	}
	if (error_count == 0)
		cout << "Ok" << endl;

	//return 0;

	cout << endl << "test MOVE" << endl;
	
	// test complexity is N * N * 4
	// but as log as N is as small as 5 - it is Ok
	//for (int X = 0; X < N; ++X)
	//	for (int Y = 0; Y < N; ++Y)
	for (auto direction : { "NORTH", "SOUTH", "EAST", "WEST" }) // only valid directions
	{
		cout << "move " << direction << endl;
		//cout << "Y" << endl;
		cout << " ";
		for (int X = 0; X < N; ++X) // only valid positions
			cout << " " << X;
		cout << endl;
		for (int Y = N - 1; Y >= 0; --Y) // only valid positions
		{
			cout << Y;
			for (int X = 0; X < N; ++X)
			{
				vector<string> commands;
				stringstream ss;
				ss << "place " << X << "," << Y << "," << direction;
				commands.push_back(ss.str());
				commands.push_back("move");
				commands.push_back("report");

				bool res = test_commands(commands);
				cout << " " << (res ? "." : "x");
			}
			cout << endl;
		}
	}
}
