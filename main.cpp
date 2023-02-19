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
#include <cmath>

#include<fstream>
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

void ArrowMovement (vector<vector<char>> &Board, int Row, int Column, char Arrow, 
                    int AlienHP_DMG[], int ZombieStats[][3], int Zombies);
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

bool HitZombie(vector<vector<char>> &Board, int NextRow, int NextColumn,
               int AlienHP_DMG[], int ZombieStats[][3])
{
    if (48 < Board[NextRow][NextColumn] && Board[NextRow][NextColumn] < 58)
    {   
        int ZombieInteger = Board[NextRow][NextColumn]-49;
        int AlienDMG = AlienHP_DMG[1];

        ZombieStats[ZombieInteger][0] -= AlienDMG;
        cout << "Alien does " << AlienDMG << " damage to Zombie " << ZombieInteger+1 << endl;

        if (ZombieStats[ZombieInteger][0] <= 0)
        {
            ZombieStats[ZombieInteger][0] = 0;
            cout << "Alien has killed Zombie " << ZombieInteger+1 << endl;
            return false;
        }

        else 
        {
            return true;
        }
        
    }

    else 
    {   
        return false;
    }
}

void HitHealthPack(int AlienHP_DMG[])
{
    if (AlienHP_DMG[0] < 100)
    {
        AlienHP_DMG[0] += 20;
        cout << "Alien gained 20 health" << endl;

        if (AlienHP_DMG[0] >= 100)
        {
            AlienHP_DMG[0] = 100;
            cout << "Alien has gained full health" << endl;
        }
    }

    else
    {
        cout << "Alien health has reached maximum capacity" << endl;
    }
}

double pythagoras(double Length, double Height)
{
    double Hypo;
    Hypo = sqrt((Length*Length) + (Height*Height));
    return Hypo;
}

void ZombieDeath (vector<vector<char>> &Board, int ZombieRow, int ZombieColumn)
{
    Board[ZombieRow][ZombieColumn] = ' ';
}

void HitPod(vector<vector<char>> &Board, int Row, int Column, int ZombieStats[][3], int Zombies)
{
    int ARow, AColumn;
    Find(Board, Row, Column, 'A', ARow, AColumn);

    int ZRow[Zombies]; 
    int ZColumn[Zombies];

    for (int x=0; x<Zombies; ++x)
    {
        ZRow[x] = 100; 
        ZColumn[x] = 100;
    }

    int ZombieCounter = 49; 

    for (int x=0; x<Zombies; ++x)
    {
        for (int i=0; i<Row; ++i)
        {
            for (int j=0; j<Column; ++j)
            {
                if (ZombieCounter == Board[i][j])
                {
                    ZRow[x] = i;
                    ZColumn[x] = j;
                }
            }
        }

        cout << "Hello " << ZRow[x] << " " << ZColumn[x] << endl;                
        ZombieCounter += 1;
    }

    int RowDistance, ColumnDistance;
    double DistanceArray[Zombies];
    for (int x=0; x<Zombies; ++x)
    {
        RowDistance = ARow - ZRow[x];
        ColumnDistance = AColumn - ZColumn[x];
        cout << "Zombie " << x+1 << " : " << pythagoras(RowDistance,ColumnDistance) << endl;
        DistanceArray[x] = pythagoras(RowDistance,ColumnDistance);
    }

    double SmallestDistance[Zombies];
    int SmallestIndex[Zombies];

    for (int x=0; x<Zombies; ++x)
    {
        SmallestDistance[x] = 0.0;
        SmallestIndex[x] = -1;
    }

    SmallestDistance[0] = DistanceArray[0];
    SmallestIndex[0] = 0;
    for (int x=1; x<Zombies; ++x)
    {
        if (SmallestDistance[0] > DistanceArray[x])
        {
            SmallestDistance[0] = DistanceArray[x];
            SmallestIndex[0] = x;
        }
    }

    int Counter = 1;
    for (int x=1; x<Zombies; ++x)
    {
        if (SmallestDistance[0] == DistanceArray[x])
        {
            SmallestDistance[Counter] = DistanceArray[x];
            SmallestIndex[Counter] = x;
            Counter += 1;
        }
    }

    int SelectedZombie = rand() % Counter;

    cout << "Smallest distance = " << SmallestDistance[SelectedZombie] <<
            " from Zombie " << SmallestIndex[SelectedZombie]+1 << endl;
    cout << "Pod does 20 damage to Zombie " << SmallestIndex[SelectedZombie]+1 << endl;
    ZombieStats[SmallestIndex[SelectedZombie]][0] -= 20;

    if (ZombieStats[SmallestIndex[SelectedZombie]][0] <= 0)
        {
            ZombieStats[SmallestIndex[SelectedZombie]][0] = 0;
            ZombieDeath (Board, ZRow[SmallestIndex[SelectedZombie]], ZColumn[SmallestIndex[SelectedZombie]]);
            cout << "Alien has killed Zombie " << SmallestIndex[SelectedZombie]+1 << " via pod" << endl;
            
        }

    for (int x=0; x<Zombies; ++x)
    {
        cout << "Distance: " << SmallestDistance[x]
             << ", Zombie : " << SmallestIndex[x]+1 << endl;
    }

    cout << endl;

    


}

bool HitBorder(vector<vector<char>> &Board, int Row, int Column, int NextRow, int NextColumn)
{
    if (NextColumn >= Column)
    {
        cout << "The Alien has hit the border" << endl;
        return true;
    }

    else if (NextColumn <= -1 || NextRow <= -1)
    {
        cout << "The Alien has hit the border" << endl;
        return true;
    }

    else if (NextRow >= Row)
    {
        cout << "The Alien has hit the border" << endl;
        return true;
    }

    else
    {
        return false;
    }
}

void DisplayStatOnAlienTurn(int AlienHP_DMG[], int ZombieStats[][3], int Zombies);
void AlienRight (vector<vector<char>> &Board, int Row, int Column,
                 int AlienHP_DMG[], int ZombieStats[][3], int Zombies)
{
    int ARow, AColumn;
    AlienFind (Board, ARow, AColumn, Row, Column);

    int Counter = 0;
    while (true)
    {
        if (HitBorder(Board, Row, Column, ARow, AColumn+Counter+1) ||
            HitRock(Board, ARow, AColumn+Counter+1) ||
            HitZombie(Board, ARow, AColumn+Counter+1, AlienHP_DMG, ZombieStats))
        {   
            DotRandomiser (Board, Row, Column);
            DisplayBoard (Board, Row, Column);
            DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);
            break;
        }

        else
        {
            char Temp = Board[ARow][AColumn+Counter+1];
            Board[ARow][AColumn+Counter] = '.';
            Board[ARow][AColumn+Counter+1] = 'A';
            DisplayBoard (Board, Row, Column);
            DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);

            Counter += 1;

            if (Temp == '<' || Temp == '>' || Temp == 'V' || Temp == '^')
            {
                AlienHP_DMG[1] += 20;
                ArrowMovement(Board, Row, Column, Temp, AlienHP_DMG, ZombieStats, Zombies);
                break;
            }

            else if (Temp == 'P')
            {
                HitPod(Board, Row, Column, ZombieStats, Zombies);
            }

            else if (Temp == 'H')
            {
                HitHealthPack(AlienHP_DMG);
            }
            
        }
    }
}

void AlienLeft (vector<vector<char>> &Board, int Row, int Column, 
                int AlienHP_DMG[], int ZombieStats[][3], int Zombies)
{
    int ARow, AColumn;
    AlienFind (Board, ARow, AColumn, Row, Column);

    int Counter = 0;
    while (true)
    {
        if (HitBorder(Board, Row, Column, ARow, AColumn-Counter-1) ||
            HitRock(Board, ARow, AColumn-Counter-1) ||
            HitZombie(Board, ARow, AColumn-Counter-1, AlienHP_DMG, ZombieStats))
        {   
            DotRandomiser (Board, Row, Column);
            DisplayBoard (Board, Row, Column);
            DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);
            break;
        }

        else
        {
            char Temp = Board[ARow][AColumn-Counter-1];
            Board[ARow][AColumn-Counter] = '.';
            Board[ARow][AColumn-Counter-1] = 'A';
            DisplayBoard (Board, Row, Column);
            DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);
            Counter += 1;

            if (Temp == '<' || Temp == '>' || Temp == 'V' || Temp == '^')
            {
                AlienHP_DMG[1] += 20;
                ArrowMovement(Board, Row, Column, Temp, AlienHP_DMG, ZombieStats, Zombies);
                break;
            }

            else if (Temp == 'P')
            {
                HitPod(Board, Row, Column, ZombieStats, Zombies);
            }

            else if (Temp == 'H')
            {
                HitHealthPack(AlienHP_DMG);
            }
            
        }
    }
}

void AlienDown (vector<vector<char>> &Board, int Row, int Column, 
                int AlienHP_DMG[], int ZombieStats[][3], int Zombies)
{
    int ARow, AColumn;
    AlienFind (Board, ARow, AColumn, Row, Column);

    int Counter = 0;
    while (true)
    {
        if (HitBorder(Board, Row, Column, ARow+Counter+1, AColumn) ||
            HitRock(Board, ARow+Counter+1, AColumn) ||
            HitZombie(Board, ARow+Counter+1, AColumn, AlienHP_DMG, ZombieStats))
        {   
            DotRandomiser (Board, Row, Column);
            DisplayBoard (Board, Row, Column);
            DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);
            break;
        }

        else
        {
            char Temp = Board[ARow+Counter+1][AColumn];
            Board[ARow+Counter][AColumn] = '.';
            Board[ARow+Counter+1][AColumn] = 'A';
            DisplayBoard (Board, Row, Column);
            DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);

            Counter += 1;

            if (Temp == '<' || Temp == '>' || Temp == 'V' || Temp == '^')
            {
                AlienHP_DMG[1] += 20;
                ArrowMovement(Board, Row, Column, Temp, AlienHP_DMG, ZombieStats, Zombies);
                break;
            }

            else if (Temp == 'P')
            {
                HitPod(Board, Row, Column, ZombieStats, Zombies);
            }
            
            else if (Temp == 'H')
            {
                HitHealthPack(AlienHP_DMG);
            }
        }
    }
}

void AlienUp (vector<vector<char>> &Board, int Row, int Column,
              int AlienHP_DMG[], int ZombieStats[][3], int Zombies)
{
    int ARow, AColumn;
    AlienFind (Board, ARow, AColumn, Row, Column);

    int Counter = 0;
    while (true)
    {
        if (HitBorder(Board, Row, Column, ARow-Counter-1, AColumn) ||
            HitRock(Board, ARow-Counter-1, AColumn) ||
            HitZombie(Board, ARow-Counter-1, AColumn, AlienHP_DMG, ZombieStats))
        {   
            DotRandomiser (Board, Row, Column);
            DisplayBoard (Board, Row, Column);
            DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);
            break;
        }

        else
        {
            char Temp = Board[ARow-Counter-1][AColumn];
            Board[ARow-Counter][AColumn] = '.';
            Board[ARow-Counter-1][AColumn] = 'A';
            DisplayBoard (Board, Row, Column);
            DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);

            Counter += 1;

            if (Temp == '<' || Temp == '>' || Temp == 'V' || Temp == '^')
            {
                AlienHP_DMG[1] += 20;
                ArrowMovement(Board, Row, Column, Temp, AlienHP_DMG, ZombieStats, Zombies);
                break;
            }
            
            else if (Temp == 'P')
            {
                HitPod(Board, Row, Column, ZombieStats, Zombies);
            }

            else if (Temp == 'H')
            {
                HitHealthPack(AlienHP_DMG);
            }
        }
    }
}

void ArrowMovement (vector<vector<char>> &Board, int Row, int Column, char Arrow, 
                    int AlienHP_DMG[], int ZombieStats[][3], int Zombies)
{
    switch (Arrow)
    {
        case '>':
            AlienRight (Board, Row, Column, AlienHP_DMG, ZombieStats, Zombies);
            break;

        case '<':
            AlienLeft (Board, Row, Column, AlienHP_DMG, ZombieStats, Zombies);
            break;

        case 'V':
            AlienDown (Board, Row, Column, AlienHP_DMG, ZombieStats, Zombies);
            break;

        case '^':
            AlienUp (Board, Row, Column, AlienHP_DMG, ZombieStats, Zombies);
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
        if (Board[ArrowRow][ArrowColumn] == '>' || Board[ArrowRow][ArrowColumn] == '<' ||
            Board[ArrowRow][ArrowColumn] == '^' || Board[ArrowRow][ArrowColumn] == 'V')
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
            cout << "Please enter the coordinates for an Arrow only" << endl;
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

void ZombieMovement(vector<vector<char>> &Board, int Row, int Column, int ZombieNum)
{
    int TempZombieNum = ZombieNum + 48;
    char ZombieChar = TempZombieNum;

    int ZRow, ZColumn;
    Find(Board, Row, Column, ZombieChar, ZRow, ZColumn);

    //cout << Board[ZRow][ZColumn] << endl;

    vector<int> RandomArray = {0,1,2,3};
    int StuckCounter = 0;
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
        
        StuckCounter += 1;

        if (StuckCounter > 20)
        {
            cout << "The Zombie is stuck! It does not move" << endl;
            break;
        }

        else if (MoveColumn == Column || MoveRow == Row || MoveColumn == -1 || MoveRow == -1)
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

    else if (AlienHP_DMG[0] <= 0)
    {
        AlienHP_DMG[0] = 0;
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
        ZombieStats[x][0] = {((rand() % 21)*10) + 50}; //HP - Multiples of 10, 50 < x < 250 
        ZombieStats[x][1] = {((rand() % 8)*5) + 5}; //DMG - Multiples of 5, 5 < x < 40
        ZombieStats[x][2] =  {(rand() % 4) + 2}; //Range, 2 < x < 5
    } 

    DisplayBoard (Board, Row, Column);
    DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);
    
    string Input;
    while (true)
    {
        //Alien Turn
         
        cout <<"which direction do you want the Alien to move in?";
        cin >> Input;
        
        if (Input == "arrow")
        {
            ChangeArrow (Board, Row, Column);
            continue;
        }

        if (Input == "right")
        {   
           AlienRight (Board, Row, Column, AlienHP_DMG, ZombieStats, Zombies);
        }

        else if (Input == "left")
        {   
            AlienLeft (Board, Row, Column, AlienHP_DMG, ZombieStats, Zombies);
        }

        else if (Input == "down")
        {   
            AlienDown (Board, Row, Column, AlienHP_DMG, ZombieStats, Zombies);
        }

        else if (Input == "up")
        {   
            AlienUp (Board, Row, Column, AlienHP_DMG, ZombieStats, Zombies);
        }

        else
        {
            cout << "Please enter a valid command, try again." << endl;
            continue;
        }

        AlienHP_DMG[1] = 0;
        
        //Zombie turn
        int ZombieDeathCounter = 0;
        for (int x=1; x<=Zombies; ++x)
        {
            if (ZombieStats[x-1][0] <= 0)
            {
                ZombieDeathCounter += 1;
                continue;
            }

            else
            {
                cout << "Zombie " << x << "'s turn!" << endl;
                ZombieMovement(Board, Row, Column, x);
                DisplayBoard (Board, Row, Column);
                DisplayStatOnZombieTurn(AlienHP_DMG, ZombieStats, Zombies, x);

                //Attack
                ZombieAttack(Board, Row, Column, x, ZombieStats, AlienHP_DMG);
                DisplayBoard (Board, Row, Column);
                DisplayStatOnZombieTurn(AlienHP_DMG, ZombieStats, Zombies, x);
            }
            
        }

        if (ZombieDeathCounter == Zombies)
        {
            cout << "_____________________________________" << endl;
            cout << "|                                   |" << endl;
            cout << "|       ALL ZOMBIES HAVE DIED       |" << endl;
            cout << "|  YOU HAVE WON, CONGRATULATIONS!!  |" << endl;
            cout << "|___________________________________|" << endl;
            break;
        }

        if (AlienHP_DMG[0] <= 0)
        {
            cout << "_____________________________________" << endl;
            cout << "|                                   |" << endl;
            cout << "|         THE ALIEN HAS DIED        |" << endl;
            cout << "|  YOU HAVE LOST, MUHAHAHAHAHAHA!!  |" << endl;
            cout << "|___________________________________|" << endl;
            break;
        }
        
    }
}
