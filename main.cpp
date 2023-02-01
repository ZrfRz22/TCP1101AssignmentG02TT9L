// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT9L
// Names: MUHAMMAD ZARIF BIN ROZAINI | KHIRTISHEN A/L THAMBI RAJA | MUHAMMAD HELMI BIN RAZALI 
// IDs: 1211103806 | 1211103676 | 1211307659 
// Emails: 1211103806@student.mmu.edu.my | 1211103676@student.mmu.edu.my | 1211307659@student.mmu.edu.my 
// Phones: 0123123142 | 0182975417 | 0176295760 
// ********************************************************* 

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;

char GameObjects[8] = {'H', ' ', 'P', '>', '<', 'V', '^', 'R'};

int ClearScreen()
    {
        #if defined(_WIN32)
            return std::system("cls");
        #elif defined(__linux__) || defined(__APPLE__)
            return std::system("clear");
        #endif
    }

    int Pause()
    {
        #if defined(_WIN32)
            return std::system("pause");
        #elif defined(__linux__) || defined(__APPLE__)
            return std::system(R"(read -p "Press any key to continue . . . " dummy)");
        #endif
    }

void PrintMultipleTimes (int x, string print)
{
    for (int i=0; i<x; ++i)
    {
         cout << print ;
    }

    cout << endl;
}

void DisplayBoard (const vector<vector<char>> &Board, int Row, int Column)
{
    cout << " ";
    PrintMultipleTimes(Column,"_____ ");
    
    for (int i=0; i<Row; ++i)
    { 
        cout << "|";
        PrintMultipleTimes(Column,"     |");
        cout << "|";
        for (int j=0; j<Column; ++j)
        {  
            cout<<"  "<< Board[i][j] <<"  |";
        }
        cout << endl;
        cout << "|";
        PrintMultipleTimes(Column,"_____|");
    }
}

bool Stopper (vector<vector<char>> &Board, int Row, int Column)
{
    if (Board[Row][Column] == 'R')
    {   
        cout << "Alien hits a rock!" << endl;
        Board[Row][Column] = GameObjects[rand() % 7];
        return false;
    }

    else if (48 < Board[Row][Column] && Board[Row][Column] < 58)
    {   
        cout << "A zombie is blocking your path!" << endl;
        return false;
    }

    else 
    {   
        return true;
    }
}

void ArrowMovement (vector<vector<char>> &Board, int Row, int Column, char Arrow);
void AlienFind (vector<vector<char>> &Board, int &ARow, int &AColumn, int Row, int Column)
{
    for (int i=0; i<Row; ++i)
    {
        for (int j=0; j<Column; ++j)
        {
            if (Board[i][j] == 'A')
            {
                ARow = i;
                AColumn = j;
                //cout << ARow << AColumn << endl;
                break;
                
            }
        }
    }
}

void DotRandomiser (vector<vector<char>> &Board, const char GameObjects[], int Row, int Column);
void AlienRight (vector<vector<char>> &Board, int Row, int Column)
{
    int ARow, AColumn;
    AlienFind (Board, ARow, AColumn, Row, Column);
    int Counter = 0;
    int ColCounter = AColumn;

    while (ColCounter < Column-1)
    {
        if (Stopper(Board, ARow, AColumn+Counter+1))
        {   
            char Temp = Board[ARow][AColumn+Counter+1];
            Board[ARow][AColumn+Counter] = '.';
            Board[ARow][AColumn+Counter+1] = 'A';
            DisplayBoard (Board, Row, Column);

            ColCounter += 1;
            Counter += 1;

            if (Temp == '<' || Temp == '>' || Temp == 'V' || Temp == '^')
            {
                ArrowMovement (Board, Row, Column, Temp);
                break;

            }
        }

        else
        {
            DotRandomiser (Board, GameObjects, Row, Column);
            DisplayBoard (Board, Row, Column);
            break;
        }
    }
    DotRandomiser (Board, GameObjects, Row, Column);
}

void AlienLeft (vector<vector<char>> &Board, int Row, int Column)
{
    int ARow, AColumn;
    AlienFind (Board, ARow, AColumn, Row, Column);
    int Counter = 0;
    int ColCounter = AColumn;

    while (ColCounter > 0)
    {
        if (Stopper(Board, ARow, AColumn-Counter-1))
        {   
            char Temp = Board[ARow][AColumn-Counter-1];
            Board[ARow][AColumn-Counter] = '.';
            Board[ARow][AColumn-Counter-1] = 'A';
            DisplayBoard (Board, Row, Column);

            ColCounter -= 1;
            Counter += 1;

            if (Temp == '<' || Temp == '>' || Temp == 'V' || Temp == '^')
            {
                ArrowMovement (Board, Row, Column, Temp);
                break;

            }
        }

        else
        {
            DotRandomiser (Board, GameObjects, Row, Column);
            DisplayBoard (Board, Row, Column);
            break;
        }
    }
    
    DotRandomiser (Board, GameObjects, Row, Column);
}

void AlienDown (vector<vector<char>> &Board, int Row, int Column)
{
    int ARow, AColumn;
    AlienFind (Board, ARow, AColumn, Row, Column);
    int Counter = 0;
    int RowCounter = ARow;

    while (RowCounter < Row-1)
    {
        if (Stopper(Board, ARow+Counter+1, AColumn))
        {   
            char Temp = Board[ARow+Counter+1][AColumn];
            Board[ARow+Counter][AColumn] = '.';
            Board[ARow+Counter+1][AColumn] = 'A';
            DisplayBoard (Board, Row, Column);

            RowCounter += 1;
            Counter += 1;

            if (Temp == '<' || Temp == '>' || Temp == 'V' || Temp == '^')
            {
                ArrowMovement (Board, Row, Column, Temp);
                break;

            }
        }
        else
        {
            DotRandomiser (Board, GameObjects, Row, Column);
            DisplayBoard (Board, Row, Column);
            break;
        }
    }

    DotRandomiser (Board, GameObjects, Row, Column);
}

void AlienUp (vector<vector<char>> &Board, int Row, int Column)
{
    int ARow, AColumn;
    AlienFind (Board, ARow, AColumn, Row, Column);
    int Counter = 0;
    int RowCounter = ARow;

    while (RowCounter > 0)
    {
        if (Stopper(Board, ARow-Counter-1, AColumn))
        {   
            char Temp = Board[ARow-Counter-1][AColumn];
            Board[ARow-Counter][AColumn] = '.';
            Board[ARow-Counter-1][AColumn] = 'A';
            DisplayBoard (Board, Row, Column);

            RowCounter -= 1;
            Counter += 1;

            if (Temp == '<' || Temp == '>' || Temp == 'V' || Temp == '^')
            {
                ArrowMovement (Board, Row, Column, Temp);
                break;

            }
        }

        else
        {
            DotRandomiser (Board, GameObjects, Row, Column);
            DisplayBoard (Board, Row, Column);
            break;
        }
    }

    DotRandomiser (Board, GameObjects, Row, Column);

}

void ArrowMovement (vector<vector<char>> &Board, int Row, int Column, char Arrow)
{
    switch (Arrow)
    {
        case '>':
            AlienRight (Board, Row, Column);
            break;

        case '<':
            AlienLeft (Board, Row, Column);
            break;

        case 'V':
            AlienDown (Board, Row, Column);
            break;

        case '^':
            AlienUp (Board, Row, Column);
            break;
    }
}

void DotRandomiser (vector<vector<char>> &Board, const char GameObjects[], int Row, int Column)
{
    srand(time(0));
    for (int i=0; i<Row; ++i)
    {
        for (int j=0; j<Column; ++j)
        {
            if (Board[i][j] == '.')
            {
                Board[i][j] = GameObjects[rand() % 8];      
            }
        }
    }
}

void ChangeArrow (vector<vector<char>> &Board, const int Row, const int Column)
{
    int ArrowRow, ArrowColumn;
    char NewArrow;
    cout <<"which arrow do you want to change" << endl;
    cout <<"Arrow Row position = "; cin >> ArrowRow; 
    cout <<"Arrow Column position = "; cin >> ArrowColumn;

    if ((0 <= ArrowColumn && ArrowColumn < Column) && (0 <= ArrowRow && ArrowRow < Row))
    {   
        cout <<"Enter the new arrow direction = "; cin >> NewArrow; 
        if (NewArrow == '>' || NewArrow == '<' || NewArrow == 'V' || NewArrow == '^')
        {
            Board[ArrowRow][ArrowColumn] = NewArrow;
        }

        else
        {
            cout << "Please enter a valid direction, try again." << endl;
        }
    }

    else
    {
        cout << "The Column or Row number entered was out of range, please try again." << endl;
    }

    DisplayBoard (Board, Row, Column);
}

int main() 
{
    int Row, Column;
    srand(time(0));

    cout << "Please enter the dimensions of your board!" << endl;
    cout << "Row(Horizontal) = "; cin >> Row;
    cout << "Column(Vertical) = "; cin >> Column;
    cout << endl;

    vector<vector<char>> Board( Row , vector<char> (Column, 'L'));
    
    int MidpointRow = (Row/2);
    int MidpointColumn = (Column/2);
    Board[MidpointRow][MidpointColumn] = 'A';
    
    int Zombies;
    cout << "Please enter the number of Zombies!" << endl;
    cout << "Zombies? = "; cin >> Zombies;

    int Counter = 0;
    while (Counter < Zombies)
    {
        int RandRow = rand() % Row;
        int RandColumn = rand() % Column;

        if (!(48 < Board[RandRow][RandColumn] && Board[RandRow][RandColumn] < 58) && 
            Board[RandRow][RandColumn] != 'A')
        {
            Board[RandRow][RandColumn] ='1'+ Counter;
        }

        else {continue;}

        Counter += 1;
    }

    for (int i=0; i<Row; ++i)
    {
        for (int j=0; j<Column; ++j)
        {
            if (!(48 < Board[i][j] && Board[i][j] < 58) && Board[i][j] != 'A')
            Board[i][j] = GameObjects[rand() % 8];

            else {continue;}
        }
    }

    DisplayBoard (Board, Row, Column);

    string Direction;
    while (Direction != "stop")
    {
        cout <<"which direction do you want the Alien to move in?";
        cin >> Direction;
        
        if (Direction == "arrow")
        {
            ChangeArrow (Board, Row, Column);
        }

        else if (Direction == "right")
        {   
           AlienRight (Board, Row, Column);
        }

        else if (Direction == "left")
        {   
            AlienLeft (Board, Row, Column);
        }

        else if (Direction == "down")
        {   
            AlienDown (Board, Row, Column);
        }

        else if (Direction == "up")
        {   
            AlienUp (Board, Row, Column);
        }
    }
    DotRandomiser(Board, GameObjects, Row, Column);
    DisplayBoard (Board, Row, Column);
}
