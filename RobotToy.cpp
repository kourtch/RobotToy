// RobotToy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

vector<string> directions = {"NORTH", "SOUTH", "EAST", "WEST"};

//int N = 5; // dimension of the board

class RobotToy
{
    string directionStr = "UNDEFINED";
    int directionInt = -1;
public:
    int X = 0;
    int Y = 0;
    bool setDirection(string newDirection)
    {
        auto it = find(directions.begin(), directions.end(), newDirection);
        if (it == directions.end())
            return false;
        directionInt = it - directions.begin();
        directionStr = directions[directionInt];
        return true;
    }
    bool setDirection(int newDirection)
    {
        if (newDirection < 0|| directions.size() <= newDirection)
        {
            return false;
        }
        directionInt = newDirection;
        directionStr = directions[directionInt];
        return true;
    }
    string getDirectionStr() { return directionStr; }
    int getDirectionInt() { return directionInt; };
    
    pair<int,int> getMove()
    {
        switch (directionInt)
        {
        case 0: /* NORTH */ return make_pair<int, int>(0, 1);
        case 1: /* SOUTH*/  return make_pair<int, int>(0, -1);
        case 2: /* EAST */  return make_pair<int, int>(1, 0);
        case 3: /* WEST */  return make_pair<int, int>(-1, 0);
        default: ;
        }
        return make_pair<int, int>(0, 0);
    }

    void Right()
    {
        // "NORTH" -> "EAST" -> "SOUTH" -> "WEST"
        switch (directionInt)
        {
        case 0: /* NORTH */ setDirection(2); break;
        case 1: /* SOUTH*/  setDirection(3); break;
        case 2: /* EAST */  setDirection(1); break;
        case 3: /* WEST */  setDirection(0); break;
        default: /* do nothing*/ ;
        }
    }
    void Left()
    {
        // "NORTH" -> "WEST" -> "SOUTH" -> "EAST"
        switch (directionInt)
        {
        case 0: /* NORTH */ setDirection(3); break;
        case 1: /* SOUTH*/  setDirection(2); break;
        case 2: /* EAST */  setDirection(0); break;
        case 3: /* WEST */  setDirection(1); break;
        default: /* do nothing*/ ;
        }
    }
} toy;

class Board
{;
public:
    int N = 5; // dimension of the square board
public:
    bool testXY(int X, int Y)
    {
        if (X < 0) return false;
        if (Y < 0) return false;
        if (X >= N) return false;
        if (Y >= N) return false;
        return true;
    }
} board;


int main()
{

    while (not cin.eof())
    {
        string command; 
        cout << "command>"; getline(cin, command); 
        if (command.empty())
            continue;

        // uppercase "command" strung
        for (auto& c : command)
        {
            c = toupper(c);
        }

        if (strncmp(command.c_str(), "REPORT", 6) == 0)
        {
            cout << "Output: "
                << toy.X << ","
                << toy.Y << ","
                << toy.getDirectionStr() << endl;

            // better report
            //cout << " ";
            //for (int X = 0; X < board.N; ++X)
            //    cout << " " << X;
            //cout << endl;
            //for (int Y = board.N - 1; Y >= 0; --Y)
            //{
            //    cout << Y;
            //    for (int X = 0; X < board.N; ++X)
            //    {
            //        cout << " ";
            //        if (X == toy.X && Y == toy.Y)
            //        {
            //            switch (toy.getDirectionInt())
            //            {
            //            case 0: /* NORTH */ cout << "^"; break;
            //            case 1: /* SOUTH*/  cout << "v"; break;
            //            case 2: /* EAST */  cout << ">"; break;
            //            case 3: /* WEST */  cout << "<"; break;
            //            default: cout << "o";
            //            }
            //        }
            //        else
            //        {
            //            cout << ".";
            //        }
            //    }
            //    cout << endl;
            //}

            continue;
        }

        if (strncmp(command.c_str(), "PLACE", 5) == 0)
        {
            auto parseString = [](string input, char delimiter)
            {
                stringstream ss(input);
                vector <string> items;
                string field;
                while (!ss.eof())
                {
                    getline(ss, field, delimiter);
                    if (field.empty())
                        continue;
                    items.push_back(field);
                }
                return items;
            };

            vector<string> fields = parseString(command, ' ');
            //cout << fields.size() << endl;

            if (fields.size() == 2)
            {
                vector<string> params = parseString(fields[1], ',');
                //cout << params.size() << endl;
                //for (auto p : params)
                //{
                //     cout << "   " << p << endl;
                //}
                 
                int newX = -1;
                if (sscanf_s(params[0].c_str(), "%d", &newX) != 1)
                {
                    cerr << "*** wrong X ***" << endl;
                    cerr << command << endl;
                    for (int i = 0; i <= fields[0].length(); ++i)
                        cerr << " ";
                    cerr << "^" << endl;
                    continue;
                }
                if (board.testXY(newX, toy.Y))
                {
                    toy.X = newX;
                }
                else
                {
                    cerr << "*** Invalid place outside the board: (" << newX << "," << toy.Y << ") ***" << endl;
                }

                int newY = -1;
                if (sscanf_s(params[1].c_str(), "%d", &newY) != 1)
                {
                    cerr << "*** wrong Y ***" << endl;
                    cerr << command << endl;
                    for (int i = 0; i <= fields[0].length() + 1 + params[0].length(); ++i)
                        cerr << " ";
                    cerr << "^" << endl;
                    continue;
                }
                if (board.testXY(toy.X, newY))
                {
                    toy.Y = newY;
                }
                else
                {
                    cerr << "*** Invalid place outside the board: (" << toy.X << "," << newY << ") ***" << endl;
                }

                string newDirection = params[2].c_str();
                if (!toy.setDirection(newDirection))
                {
                    cerr << "*** unknown direction; expected: ";
                    cerr << directions[0] << ", ";
                    cerr << directions[1] << ", ";
                    cerr << directions[2] << " or ";
                    cerr << directions[3] << " ***" << endl;
                    cerr << command << endl;
                    for (int i = 0; i <= fields[0].length() + params[0].length() + 1 + params[1].length() + 1; ++i)
                        cerr << " ";
                    cerr << "^" << endl;
                    continue;
                }

             }

             continue;
        }
        if (toy.getDirectionInt() == -1)
        {
            cerr << "*** Robot is not placed yet ***" << endl;
            cerr << "*** Use PLACE command ***" << endl;
            continue;
        }
        if (strncmp(command.c_str(), "MOVE", 4) == 0)
        {
            pair<int, int> p = toy.getMove();
            
            int dX = p.first;
            int dY = p.second;
            if (dX == 0 && dY == 0)
            {
                cerr << "*** unknown current direction:   " << toy.getDirectionStr() << " ***" << endl;
                continue;
            }
            int newX = toy.X + dX;
            int newY = toy.Y + dY;
            if (board.testXY(newX, newY))
            {
                toy.X = newX;
                toy.Y = newY;
            }
            else
            {
                cerr << "*** Invalid move outside the board: (" << newX << "," << newY << ") ***" << endl;
            }
            continue;
        }
        if (strncmp(command.c_str(), "RIGHT", 5) == 0)
        {
            toy.Right();
            continue;
        }
        if (strncmp(command.c_str(), "LEFT", 4) == 0)
        {
            toy.Left();
            continue;
        }

        cerr << "*** Unknown command ignored ***" << endl;
        cerr << command << endl;
        cerr << "^" << endl;
    }
}
