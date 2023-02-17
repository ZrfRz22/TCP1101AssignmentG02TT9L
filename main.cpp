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

void DotRandomiser (vector<vector<char>> &Board, int Row, int Column)
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

bool HitRock(vector<vector<char>> &Board, int NextRow, int NextColumn)
{
    if (Board[NextRow][NextColumn] == 'R')
    {   
        cout << "Alien hits a rock!" << endl;
        Board[NextRow][NextColumn] = GameObjects[rand() % 7];
        return true;
    }

    else 
    {   
        return false;
    }
}

bool HitZombie(vector<vector<char>> &Board, int NextRow, int NextColumn)
{
    if (48 < Board[NextRow][NextColumn] && Board[NextRow][NextColumn] < 58)
    {   
        cout << "A zombie is blocking your path!" << endl;
        return true;
    }

    else 
    {   
        return false;
    }
}

void HitHealthPod()
{

}

bool HitBorder(vector<vector<char>> &Board, int Row, int Column, int NextMove)
{
    if (NextMove >= Column)
    {
        cout << "The Alien has hit the border" << endl;
        cout << "Move: " << NextMove << endl;
        return true;
    }

    else if (NextMove <= -1)
    {
        cout << "The Alien has hit the border" << endl;
        cout << "Move: " << NextMove << endl;
        return true;
    }

    else if (NextMove >= Row)
    {
        cout << "The Alien has hit the border" << endl;
        cout << "Move: " << NextMove << endl;
        return true;
    }

    else
    {
        return false;
    }
}


void AlienRight (vector<vector<char>> &Board, int Row, int Column)
{
    int ARow, AColumn;
    AlienFind (Board, ARow, AColumn, Row, Column);

    int Counter = 0;
    while (true)
    {
        if (HitBorder(Board, Row, Column, AColumn+Counter+1) ||
            HitRock(Board, ARow, AColumn+Counter+1) ||
            HitZombie(Board, ARow, AColumn+Counter+1))
        {   
            DotRandomiser (Board, Row, Column);
            DisplayBoard (Board, Row, Column);
            break;
        }

        else
        {
            char Temp = Board[ARow][AColumn+Counter+1];
            Board[ARow][AColumn+Counter] = '.';
            Board[ARow][AColumn+Counter+1] = 'A';
            DisplayBoard (Board, Row, Column);

            Counter += 1;

            if (Temp == '<' || Temp == '>' || Temp == 'V' || Temp == '^')
            {
                ArrowMovement (Board, Row, Column, Temp);
                break;
            }
            
        }
    }
}

void AlienLeft (vector<vector<char>> &Board, int Row, int Column)
{
    int ARow, AColumn;
    AlienFind (Board, ARow, AColumn, Row, Column);

    int Counter = 0;
    while (true)
    {
        if (HitBorder(Board, Row, Column, AColumn-Counter-1) ||
            HitRock(Board, ARow, AColumn-Counter-1) ||
            HitZombie(Board, ARow, AColumn-Counter-1))
        {   
            DotRandomiser (Board, Row, Column);
            DisplayBoard (Board, Row, Column);
            break;
        }

        else
        {
            char Temp = Board[ARow][AColumn-Counter-1];
            Board[ARow][AColumn-Counter] = '.';
            Board[ARow][AColumn-Counter-1] = 'A';
            DisplayBoard (Board, Row, Column);

            Counter += 1;

            if (Temp == '<' || Temp == '>' || Temp == 'V' || Temp == '^')
            {
                ArrowMovement (Board, Row, Column, Temp);
                break;
            }
            
        }
    }
}

void AlienDown (vector<vector<char>> &Board, int Row, int Column)
{
    int ARow, AColumn;
    AlienFind (Board, ARow, AColumn, Row, Column);

    int Counter = 0;
    while (true)
    {
        if (HitBorder(Board, Row, Column, ARow+Counter+1) ||
            HitRock(Board, ARow+Counter+1, AColumn) ||
            HitZombie(Board, ARow+Counter+1, AColumn))
        {   
            DotRandomiser (Board, Row, Column);
            DisplayBoard (Board, Row, Column);
            break;
        }

        else
        {
            char Temp = Board[ARow+Counter+1][AColumn];
            Board[ARow+Counter][AColumn] = '.';
            Board[ARow+Counter+1][AColumn] = 'A';
            DisplayBoard (Board, Row, Column);

            Counter += 1;

            if (Temp == '<' || Temp == '>' || Temp == 'V' || Temp == '^')
            {
                ArrowMovement (Board, Row, Column, Temp);
                break;
            }
            
        }
    }
}

void AlienUp (vector<vector<char>> &Board, int Row, int Column)
{
    int ARow, AColumn;
    AlienFind (Board, ARow, AColumn, Row, Column);

    int Counter = 0;
    while (true)
    {
        if (HitBorder(Board, Row, Column, ARow-Counter-1) ||
            HitRock(Board, ARow-Counter-1, AColumn) ||
            HitZombie(Board, ARow-Counter-1, AColumn))
        {   
            DotRandomiser (Board, Row, Column);
            DisplayBoard (Board, Row, Column);
            break;
        }

        else
        {
            char Temp = Board[ARow-Counter-1][AColumn];
            Board[ARow-Counter][AColumn] = '.';
            Board[ARow-Counter-1][AColumn] = 'A';
            DisplayBoard (Board, Row, Column);

            Counter += 1;

            if (Temp == '<' || Temp == '>' || Temp == 'V' || Temp == '^')
            {
                ArrowMovement (Board, Row, Column, Temp);
                break;
            }
            
        }
    }
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

void DisplayStatOnZombieTurn(int AlienHP_DMG[], int ZombieStats[][3], int Zombies, int ZombieNum)
{
    cout << endl;
    cout << "   Alien    | Health ";
    cout.width(3);
    cout << AlienHP_DMG[0];
    cout.width(0);
    cout << ", Attack ";
    cout.width(3);
    cout << AlienHP_DMG[1] << endl;

    for (int x=0; x<Zombies; ++x)
    {
        string ZombieName;
        if (ZombieNum == x+1)
        {
            ZombieName = "-> Zombie ";
        }

        else
        {
            ZombieName = "   Zombie ";
        }
        cout << ZombieName << x+1 << " | Health ";
        cout.width(3);
        cout << ZombieStats[x][0];
        cout.width(0);
        cout << ", Attack ";
        cout.width(3);
        cout << ZombieStats[x][1];
        cout.width(0);
        cout << ", Range ";
        cout << ZombieStats[x][2] << endl;
    }
    cout << endl;

}

void Find(vector<vector<char>> Board, int Row, int Column, char Wanted, int &FoundRow, int &FoundColumn)
{
    for (int i=0; i<Row; ++i)
    {
        for (int j=0; j<Column; ++j)
        {
            if (Board[i][j] == Wanted)
            {
                FoundRow = i;
                FoundColumn = j;
                break;
            } 
        }
    }
}

void ZombieMovement(vector<vector<char>> &Board, int Row, int Column, int ZombieNum)
{
    int TempZombieNum = ZombieNum + 48;
    char ZombieChar = TempZombieNum;

    int ZRow, ZColumn;
    Find(Board, Row, Column, ZombieChar, ZRow, ZColumn);

    //cout << Board[ZRow][ZColumn] << endl;

    while (true)
    {
        int MoveRow;
        int MoveColumn;
        int RandomDirection = rand() % 4;

        switch (RandomDirection)
        {
            case 0: //right
                MoveRow = ZRow;
                MoveColumn = ZColumn + 1;
                break;

            case 1: //left
                MoveRow = ZRow;
                MoveColumn = ZColumn - 1;
                break;

            case 2: //down
                MoveRow = ZRow + 1;
                MoveColumn = ZColumn;
                break;

            case 3: //up
                MoveRow = ZRow - 1;
                MoveColumn = ZColumn;
                break;
        }

        if (MoveColumn == Column || MoveRow == Row || MoveColumn == -1 || MoveRow == -1)
        {
            continue;
        }

        else if ((Board[MoveRow][MoveColumn] == 'A') || 
                (48 < Board[MoveRow][MoveColumn] && Board[MoveRow][MoveColumn] < 58))
        {
            continue;
        }

        else
        {
            Board[ZRow][ZColumn] = ' ';
            Board[MoveRow][MoveColumn] = ZombieChar;
            break;
        }
    }
}

void DisplayStatOnAlienTurn(int AlienHP_DMG[], int ZombieStats[][3], int Zombies)
{
    //"   Alien    "
    cout << endl;
    cout << "-> Alien    | Health ";
    cout.width(3);
    cout << AlienHP_DMG[0];
    cout.width(0);
    cout << ", Attack ";
    cout.width(3);
    cout << AlienHP_DMG[1] << endl;

    for (int x=0; x<Zombies; ++x)
    {
        cout << "   Zombie " << x+1 << " | Health ";
        cout.width(3);
        cout << ZombieStats[x][0];
        cout.width(0);
        cout << ", Attack ";
        cout.width(3);
        cout << ZombieStats[x][1];
        cout.width(0);
        cout << ", Range ";
        cout << ZombieStats[x][2] << endl;
    }
    cout << endl;

}

void AlienTurn(vector<vector<char>> &Board, int Row, int Column, string Direction)
{
    if (Direction == "right")
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

void ZombieAttack(vector<vector<char>> Board, int Row, int Column, 
                  int ZombieNum, int ZombieStats[][3], int AlienHP_DMG[])
{
    int TempZombieNum = ZombieNum + 48;
    char ZombieChar = TempZombieNum;

    int ZRow, ZColumn;
    Find(Board, Row, Column, ZombieChar, ZRow, ZColumn);

    int ZombieRange = ZombieStats[ZombieNum-1][2];
    int ZombieDMG = ZombieStats[ZombieNum-1][1];

    int RightAttack;
    int LeftAttack;
    int DownAttack;
    int UpAttack;
    int OrginalAlienHealth = AlienHP_DMG[0];

    for (int x=1; x<=ZombieRange; ++x)
    {
        RightAttack = ZColumn + x;
        LeftAttack = ZColumn - x;
        DownAttack = ZRow + x;
        UpAttack = ZRow - x;

        if (!(RightAttack >= Column))
        {
            if (Board[ZRow][RightAttack] == 'A')
            {
                cout << "The Zombie hits the Alien and does " << ZombieDMG << " damage to the Alien!" << endl;
                AlienHP_DMG[0] = AlienHP_DMG[0] - ZombieDMG;
            }
        }

        if (!(LeftAttack <= -1))
        {
            if (Board[ZRow][LeftAttack] == 'A')
            {
                cout << "The Zombie hits the Alien and does " << ZombieDMG << " damage to the Alien!" << endl;
                AlienHP_DMG[0] = AlienHP_DMG[0] - ZombieDMG;
            }
        }

        if (!(DownAttack >= Row))
        {
            if (Board[DownAttack][ZColumn] == 'A')
            {
                cout << "The Zombie hits the Alien and does " << ZombieDMG << " damage to the Alien!" << endl;
                AlienHP_DMG[0] = AlienHP_DMG[0] - ZombieDMG;
            }
        }

        if (!(UpAttack <= -1))
        {
            if (Board[UpAttack][ZColumn] == 'A')
            {
                cout << "The Zombie hits the Alien and does " << ZombieDMG << " damage to the Alien!" << endl;
                AlienHP_DMG[0] = AlienHP_DMG[0] - ZombieDMG;
            }
        }
    }

    if (OrginalAlienHealth == AlienHP_DMG[0])
    {
        cout << "The Alien was not within range of the Zombie. It missed its attack!" << endl;
    }
    

    

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

    //int AlienHP = 100;
    //int AlienDMG = 0;

    int AlienHP_DMG[2] = {100,0};
    //HP - index 0
    //DMG - index 1

    

    int ZombieStats[Zombies][3];

    for (int x=0; x<Zombies; ++x)
    {
        ZombieStats[x][0] = {((rand() % 21)*10) + 50}; //Multiples of 10, 50 < x < 250
        ZombieStats[x][1] = {((rand() % 8)*5) + 5}; //Multiples of 5, 5 < x < 40
        ZombieStats[x][2] =  {(rand() % 3) + 1}; //Range, 1 < x < 4
    } 

    DisplayBoard (Board, Row, Column);
    DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);
    
    string Input;
    while (true)
    {
        cout <<"which direction do you want the Alien to move in?";
        cin >> Input;
        
        if (Input == "arrow")
        {
            ChangeArrow (Board, Row, Column);
            continue;
        }

        else if (Input == "right" || Input == "left" || Input == "down" || Input == "up")
        {   
           AlienTurn (Board, Row, Column, Input);
        }
        
        for (int x=1; x<=Zombies; ++x)
        {
            cout << "Zombie " << x << "'s turn!" << endl;
            ZombieMovement(Board, Row, Column, x);
            DisplayBoard (Board, Row, Column);
            DisplayStatOnZombieTurn(AlienHP_DMG, ZombieStats, Zombies, x);

            //Attack
            ZombieAttack(Board, Row, Column, x, ZombieStats, AlienHP_DMG);
        }
    }
    DotRandomiser(Board, Row, Column);
    DisplayBoard (Board, Row, Column);
}
