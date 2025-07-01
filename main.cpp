#include <iostream>
#include <cstdlib>

using namespace std;

bool player1_turn = true;
bool game_running = true;

//game map
string map[10] = {
    "-","-","-",
    "-","-","-",
    "-","-","-"
};

void Clear()//clears the screen depending on the system being used
{
    #ifdef _WIN32//checks which system game is being run on to use correct clear command
        system("cls"); // Clear terminal on Windows
    #else
        system("clear"); // Clear terminal on Mac and Linux
    #endif
};

void print_map()//prints game map
{
    for(int i = 0; i < 9; i++)
    {
        if (map[i] == "X")
        {
            cout << "\033[31m";
        }
        else if (map[i] == "O")
        {
            cout << "\033[34m";
        }
        cout << map[i] << " ";
        cout << "\033[0m";
        if(i == 2 || i == 5 || i ==8)
        {
            cout << endl;
        }
    } 
};

bool OverWrite(int Spot)//prevents players from placing an "X" or an "O" on an occupied spot
{
    if(map[Spot] == "X" || map[Spot] == "O")
    {
        return true;
    }
    else
    {
        return false;
    }
};

int Start_of_Win()
{
    if(map[0] != "-" && map[0] == map[1] && map[1] == map[2]) return 0; // Horiz 1
    if(map[0] != "-" && map[0] == map[4] && map[4] == map[8]) return 0; // Diag 1
    if(map[0] != "-" && map[0] == map[3] && map[3] == map[6]) return 0; // Vert 1
    if(map[1] != "-" && map[1] == map[4] && map[4] == map[7]) return 1; // Vert 2
    if(map[2] != "-" && map[2] == map[5] && map[5] == map[8]) return 2; // Vert 3
    if(map[2] != "-" && map[2] == map[4] && map[4] == map[6]) return 2; // Diag 2
    if(map[3] != "-" && map[3] == map[4] && map[4] == map[5]) return 3; // Horiz 2
    if(map[6] != "-" && map[6] == map[7] && map[7] == map[8]) return 6; // Horiz 3

    return 10; // no win
};

bool CheckWin()//Checks if there is win
{
    // Horizontals
    if (map[0] != "-" && map[0] == map[1] && map[1] == map[2]) return true;
    if (map[3] != "-" && map[3] == map[4] && map[4] == map[5]) return true;
    if (map[6] != "-" && map[6] == map[7] && map[7] == map[8]) return true;

    // Verticals
    if (map[0] != "-" && map[0] == map[3] && map[3] == map[6]) return true;
    if (map[1] != "-" && map[1] == map[4] && map[4] == map[7]) return true;
    if (map[2] != "-" && map[2] == map[5] && map[5] == map[8]) return true;

    // Diagonals
    if (map[0] != "-" && map[0] == map[4] && map[4] == map[8]) return true;
    if (map[2] != "-" && map[2] == map[4] && map[4] == map[6]) return true;

    return false;

};

bool CheckDraw()
{
    int spots_occupied = 0;
    for(int i = 0; i < 9; i++)
    {
        if(map[i] != "-")
        {
            spots_occupied++;
        }
    }

    // Only return true if board is full AND there's no win
    return (spots_occupied == 9 && !CheckWin());
}

bool Player1_Won(int start)
{
    if(map[start] == "X")
    {
        return true;
    }
    else
    {
        return false;
    }
};

int main()
{
    int spot;

    while (game_running)
    {
        
        if(player1_turn)
        {   
            retry1:
            Clear();
            print_map();
            cout << "\033[41m"<< "Player 1(X) "<<"\033[0m"<<":" << endl;//red background
            cout << "0 1 2" << endl;
            cout << "3 4 5" << endl;
            cout << "6 7 8" << endl;
            cout << "Enter spot #: " << endl;
            cin >> spot;
            
            if(OverWrite(spot) || spot < 0 || spot > 8)
            {
                goto retry1;
            }
            else
            {
                Clear();
                map[spot] = "X";
            }

            
        }
        else
        {   
            retry2:
            Clear();
            print_map();
            
            cout << "\033[44m"<< "Player 2(O) "<<"\033[0m"<<":" << endl;//blue background
            cout << "0 1 2" << endl;
            cout << "3 4 5" << endl;
            cout << "6 7 8" << endl;
            cout << "Enter spot #: " << endl;
            cin >> spot;

            if(OverWrite(spot) || spot < 0 || spot > 8)
            {
                goto retry2;
            }
            else
            {
                Clear();
                map[spot] = "O";
            }
        }

        if(CheckWin())
        {
            
            game_running = false;
            break;
        }
        else if(CheckDraw())
        {
            game_running = false;
            break;
        }
        
        //switch turns
        player1_turn = !player1_turn;
    }

    if(CheckDraw())//check for draw
    {
        Clear();
        print_map();
        cout << endl;
        cout << "It's a Draw!";
    }
    else if(Player1_Won(Start_of_Win()))//check who won
    {
        Clear();
        print_map();
        cout << endl;
        cout << "\033[41m" << "Player 1 Wins!" << "\033[0m";
    }
    else
    {
        Clear();
        print_map();
        cout << endl;
        cout << "\033[44m" << "Player 2 Wins!" << "\033[0m";
    }
    return 0;
}