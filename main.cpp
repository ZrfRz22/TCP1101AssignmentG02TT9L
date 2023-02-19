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
        ZombieCounter += 1;
    }

    int RowDistance, ColumnDistance;
    double DistanceArray[Zombies];
    for (int x=0; x<Zombies; ++x)
    {
        RowDistance = ARow - ZRow[x];
        ColumnDistance = AColumn - ZColumn[x];
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

    cout << "Pod does 20 damage to Zombie " << SmallestIndex[SelectedZombie]+1 << endl;
    ZombieStats[SmallestIndex[SelectedZombie]][0] -= 20;

    if (ZombieStats[SmallestIndex[SelectedZombie]][0] <= 0)
        {
            ZombieStats[SmallestIndex[SelectedZombie]][0] = 0;
            ZombieDeath (Board, ZRow[SmallestIndex[SelectedZombie]], ZColumn[SmallestIndex[SelectedZombie]]);
            cout << "Alien has killed Zombie " << SmallestIndex[SelectedZombie]+1 << " via pod" << endl;
            
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
        ClearScreen();
        if (HitBorder(Board, Row, Column, ARow, AColumn+Counter+1) ||
            HitRock(Board, ARow, AColumn+Counter+1) ||
            HitZombie(Board, ARow, AColumn+Counter+1, AlienHP_DMG, ZombieStats))
        {   
            DotRandomiser (Board, Row, Column);
            DisplayBoard (Board, Row, Column);
            DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);
            Pause();
            ClearScreen();
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
            Pause();
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
        ClearScreen();
        if (HitBorder(Board, Row, Column, ARow, AColumn-Counter-1) ||
            HitRock(Board, ARow, AColumn-Counter-1) ||
            HitZombie(Board, ARow, AColumn-Counter-1, AlienHP_DMG, ZombieStats))
        {   
            DotRandomiser (Board, Row, Column);
            DisplayBoard (Board, Row, Column);
            DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);
            Pause();
            ClearScreen();
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
            Pause();
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
        ClearScreen();
        if (HitBorder(Board, Row, Column, ARow+Counter+1, AColumn) ||
            HitRock(Board, ARow+Counter+1, AColumn) ||
            HitZombie(Board, ARow+Counter+1, AColumn, AlienHP_DMG, ZombieStats))
        {   
            DotRandomiser (Board, Row, Column);
            DisplayBoard (Board, Row, Column);
            DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);
            Pause();
            ClearScreen();
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
            Pause();
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
        ClearScreen();
        if (HitBorder(Board, Row, Column, ARow-Counter-1, AColumn) ||
            HitRock(Board, ARow-Counter-1, AColumn) ||
            HitZombie(Board, ARow-Counter-1, AColumn, AlienHP_DMG, ZombieStats))
        {   
            DotRandomiser (Board, Row, Column);
            DisplayBoard (Board, Row, Column);
            DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);
            Pause();
            ClearScreen();
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
            Pause();
        }
    }
}

void ArrowMovement (vector<vector<char>> &Board, int Row, int Column, char Arrow, 
                    int AlienHP_DMG[], int ZombieStats[][3], int Zombies)
{
    Pause();
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
    int ArrowRow;
    int ArrowColumn;
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
                ClearScreen();
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

    int StuckCounter = 0;
    while (true)
    {
        int MoveRow;
        int MoveColumn;
        int RandomDirection = rand() % 4;
        string ZombieMovementNotif;

        switch (RandomDirection)
        {
            case 0: //right
                MoveRow = ZRow;
                MoveColumn = ZColumn + 1;
                ZombieMovementNotif = " moved one space to the right";
                break;

            case 1: //left
                MoveRow = ZRow;
                MoveColumn = ZColumn - 1;
                ZombieMovementNotif = " moved one space to the left";
                break;

            case 2: //down
                MoveRow = ZRow + 1;
                MoveColumn = ZColumn;
                ZombieMovementNotif = " moved one space to downwards";
                break;

            case 3: //up
                MoveRow = ZRow - 1;
                MoveColumn = ZColumn;
                ZombieMovementNotif = " moved one space to the upwards";
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
            cout << "Zombie " << ZombieChar << ZombieMovementNotif << endl;
            break;
        }
    }
}

void DisplayStatOnAlienTurn(int AlienHP_DMG[], int ZombieStats[][3], int Zombies)
{
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

void SaveGameAgain(vector<vector<char>> Board, int Row, int Column,
              int AlienHP_DMG[], int ZombieStats[][3], int Zombies, string FileName)
{
    fstream File(FileName, ios::out);
        File << Row << "\n";
        File << Column << "\n";
        File << Zombies << "\n";
        File << AlienHP_DMG[0] <<  "\n";
        File << AlienHP_DMG[1] << "\n";
        
        for (int x=0; x<Zombies; ++x)
        {
            File << ZombieStats[x][0] << "\n";
            File << ZombieStats[x][1] << "\n";
            File << ZombieStats[x][2] << "\n";
        }

        for (int i=0; i<Row; ++i)
        {
            for (int j=0; j<Column; ++j)
            {
                File << Board [i][j] << "\n";
            }
        }
    File.close();
    cout << "Game successfully saved!" << endl;
}

string SaveGame(vector<vector<char>> Board, int Row, int Column,
              int AlienHP_DMG[], int ZombieStats[][3], int Zombies)
{   
    string FileName;
    cout << "Name for the save game file? : "; cin >> FileName;
    FileName += ".txt";

    ofstream File(FileName, ios::out);
        File << Row << "\n";
        File << Column << "\n";
        File << Zombies << "\n";
        File << AlienHP_DMG[0] <<  "\n";
        File << AlienHP_DMG[1] << "\n";
        
        for (int x=0; x<Zombies; ++x)
        {
            File << ZombieStats[x][0] << "\n";
            File << ZombieStats[x][1] << "\n";
            File << ZombieStats[x][2] << "\n";
        }

        for (int i=0; i<Row; ++i)
        {
            for (int j=0; j<Column; ++j)
            {
                File << Board [i][j] << "\n";
            }
        }
    File.close();
    cout << "Game successfully saved!" << endl;
    return FileName;
}

int main();
void LoadGame();
void StartGame();

void TryAgain()
{
    string Input;
    cout << "Want to play again? (yes/no)"; cin >> Input;

    while(true)
    {
        if (Input == "yes")
        {
            cout << "Starting a new game..." << endl;
            Pause();
            ClearScreen();
            StartGame();
            break;
        }

        else if (Input == "No")
        {
            cout << "Quitting to Main Menu..." << endl;
            Pause();
            ClearScreen();
            main();
            break;
        }

        else
        {
            cout << "Please enter a valid command" << endl;
            continue;
        }
    }
}

void TurnSystem(vector<vector<char>> &Board, int Row, int Column,
                int AlienHP_DMG[], int ZombieStats[][3], int Zombies) 
{
    string Input;
    int SaveCounter = 0;
    string SavedFileName;
    while (true)
    {
        DisplayBoard (Board, Row, Column);
        DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);

        //Alien Turn
        cout <<"which direction do you want the Alien to move in?" << endl;
        cout << "-> "; cin >> Input; cout << endl;
        
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

        else if (Input == "save")
        {   
            if (SaveCounter == 0)
            {
                SavedFileName = SaveGame(Board, Row, Column, AlienHP_DMG, ZombieStats, Zombies);
                SaveCounter += 1;
                Pause();
                ClearScreen();
            }
        
            else
            {
                SaveGameAgain(Board, Row, Column, AlienHP_DMG, ZombieStats, Zombies, SavedFileName);
                SaveCounter += 1;
                Pause();
                ClearScreen();
            }
            continue;
        }

        else if (Input == "load")
        {   
            LoadGame();
            break;
        }

        else if (Input == "quit")
        {
            string SaveOption;
            cout << "If you quit without saving, progress to this game will be lost! (type cancel to continue game)" << endl;
            cout << "Save current game? (yes/no)" << endl; cout << "-> "; cin >> SaveOption;

            if (SaveOption == "yes")
            {
                if (SaveCounter == 0)
                {
                    SavedFileName = SaveGame(Board, Row, Column, AlienHP_DMG, ZombieStats, Zombies);
                    SaveCounter += 1;
                    Pause();
                }
            
                else
                {
                    SaveGameAgain(Board, Row, Column, AlienHP_DMG, ZombieStats, Zombies, SavedFileName);
                    SaveCounter += 1;
                    Pause;
                }

                ClearScreen();
                cout << "Game exited, Thank you for playing!" << endl;
                cout << endl;
                Pause();
                ClearScreen();
                main();
                break;
            }

            else if (SaveOption == "no")
            {
                ClearScreen();
                cout << "Game was not saved" << endl;
                cout << "Game exited, Thank you for playing!" << endl;
                cout << endl;
                Pause();
                ClearScreen();
                main();
                break;
            }

            else if (SaveOption == "cancel")
            {
                ClearScreen();
                continue;
            }

            else
            {   
                ClearScreen();
                cout << "Please enter a valid command, try again." << endl;
                continue;
            }
        }

        else if (Input == "help")
        {
            cout << "List of commands" << endl;
            cout << "--------------------------------------------------" << endl;
            cout << "right : Move Alien to the right" << endl;
            cout << "left  : Move Alien to the left" << endl;
            cout << "up    : Move Alien upwards" << endl;
            cout << "down  : Move Alien downwards" << endl;
            cout << "arrow : Change the direction of a seclected arrow" << endl;
            cout << "quit  : Quit current game" << endl;
            cout << "save  : Save current game" << endl;
            cout << "load  : Load a previously saved game" << endl;
            cout << "help  : Shows a list of valid in-game commands" << endl;
            cout << endl;
            
            Pause();
            ClearScreen();
            continue;
        } 

        else
        {
            ClearScreen();
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
                DisplayBoard (Board, Row, Column);
                DisplayStatOnZombieTurn(AlienHP_DMG, ZombieStats, Zombies, x);
                Pause();
                ClearScreen();

                //Zombie Movement
                ZombieMovement(Board, Row, Column, x);
                DisplayBoard (Board, Row, Column);
                DisplayStatOnZombieTurn(AlienHP_DMG, ZombieStats, Zombies, x);
                Pause();
                ClearScreen();

                //Zombie Attack
                ZombieAttack(Board, Row, Column, x, ZombieStats, AlienHP_DMG);
                DisplayBoard (Board, Row, Column);
                DisplayStatOnZombieTurn(AlienHP_DMG, ZombieStats, Zombies, x);
                Pause();
                ClearScreen();
            }
            
        }

        if (ZombieDeathCounter == Zombies)
        {
            DisplayBoard (Board, Row, Column);
            DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);

            cout << "_____________________________________" << endl;
            cout << "|                                   |" << endl;
            cout << "|       ALL ZOMBIES HAVE DIED       |" << endl;
            cout << "|  YOU HAVE WON, CONGRATULATIONS!!  |" << endl;
            cout << "|___________________________________|" << endl;
            
            break;
        }

        if (AlienHP_DMG[0] <= 0)
        {
            DisplayBoard (Board, Row, Column);
            DisplayStatOnAlienTurn(AlienHP_DMG, ZombieStats, Zombies);

            cout << "_____________________________________" << endl;
            cout << "|                                   |" << endl;
            cout << "|         THE ALIEN HAS DIED        |" << endl;
            cout << "|  YOU HAVE LOST, MUHAHAHAHAHAHA!!  |" << endl;
            cout << "|___________________________________|" << endl;
            
            break;
        }
        
    }

    TryAgain();
}

void LoadGame()
{   
    string FileName;
    cout << "Name of the saved game file? : "; cin >> FileName;
    FileName += ".txt";

    int Row, Column, Zombies;
    int AlienHP_DMG[2];
    int ZombieStats[Zombies][3];

    ifstream File;
    int SizeCounter = 0;
    File.open(FileName,ios::in);
    if(File.is_open())
    { 
        ClearScreen();
        cout << "saved game file found, opening..." << endl;
        cout << endl;
        Pause();
        
        string Line;
        while(getline(File, Line))
        {
            cout << Line;
            SizeCounter += 1;
        }
        File.close();

        string txtArray[SizeCounter];
        int Counter = 0;

        File.open(FileName,ios::in);
        if(File.is_open())
        { 
            string Line;
            while(getline(File, Line))
            {
                txtArray[Counter] = Line;
                Counter += 1;
            }
            File.close();
        }

        //stoi converts const char* into int
        //.c_str() converts string into const char*

        Row = stoi(txtArray[0].c_str());
        Column = stoi(txtArray[1].c_str());
        Zombies = stoi(txtArray[2].c_str());
        AlienHP_DMG[0] = stoi(txtArray[3].c_str());
        AlienHP_DMG[1] = stoi(txtArray[4].c_str());

        int ArrayCounter = 5;
        for (int x=0; x<Zombies; ++x)
        {
            ZombieStats[x][0] = stoi(txtArray[ArrayCounter].c_str());
            ZombieStats[x][1] = stoi(txtArray[ArrayCounter+1].c_str());
            ZombieStats[x][2] = stoi(txtArray[ArrayCounter+2].c_str());
            ArrayCounter += 3;
        }

        vector<vector<char>> Board( Row , vector<char> (Column, 'L'));
        int ArrayCounter2 = 0;
        for (int i=0; i<Row; ++i)
        {
            for (int j=0; j<Column; ++j)
            {
                string Temp = txtArray[ArrayCounter+ArrayCounter2];
                char Temp2 = Temp[0];
                Board[i][j] = Temp2;
                ArrayCounter2 += 1;
            }
        }
        TurnSystem(Board, Row, Column, AlienHP_DMG, ZombieStats, Zombies);
    }

    else
    {
        cout << "The file name you searched does not exist or has been deleted." << endl;
        Pause();
        ClearScreen();
        main();
    }
}

void StartGame() 
{
    int Row, Column, Zombies;
    string UserInput;

    cout << "Game settings (Default)" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows      : 5" << endl;
    cout << "Board Columns   : 11" << endl;
    cout << "No. of Zombies  : 1" << endl;
    cout << endl;
    cout << "Do you want to proceed with the default settings? (yes/no)" << endl;
    cout << "-> "; cin >> UserInput; cout << endl;

    
    if (UserInput == "no")
    {
        cout << "Please enter the dimensions of your board! (Odd numbers ONLY)" << endl;

        cout << "Row(Horizontal) = "; cin >> Row;
        while (Row % 2 == 0)
        {
            cout << "Please enter an odd number for Rows" << endl;
            cout << "Row(Horizontal) = "; cin >> Row; cout << endl;
        }

        cout << "Column(Vertical) = "; cin >> Column; 
        while (Column % 2 == 0)
        {
            cout << "Please enter an odd number for Column" << endl;
            cout << "Column(Vertical) = "; cin >> Column; cout << endl;
        }

        cout << endl;
        cout << "Please enter the number of Zombies! (Not more than 10 and not less than 1!) " << endl;
        cout << "Zombies? = "; cin >> Zombies;  cout << endl;
        while (Zombies <= 0 || Zombies >= 10)
        {
            cout << "Please enter a value LESS than 10" << endl;
            cout << "Zombies? = "; cin >> Zombies; cout << endl;
        }
    }

    else if (UserInput == "yes")
    {
        Row = 5;
        Column = 11;
        Zombies = 1;
    }

    else
    {
        cout << "Please enter a valid command, try again." << endl;
        StartGame();
    }
    
    srand(time(0));

    vector<vector<char>> Board( Row , vector<char> (Column, 'L'));
    
    int MidpointRow = (Row/2);
    int MidpointColumn = (Column/2);
    Board[MidpointRow][MidpointColumn] = 'A';

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

    int AlienHP_DMG[2] = {100,0};
    //int AlienHP = 100;
    //int AlienDMG = 0;
    //HP - index 0
    //DMG - index 1

    int ZombieStats[Zombies][3];
    for (int x=0; x<Zombies; ++x)
    {
        ZombieStats[x][0] = {((rand() % 21)*10) + 50}; //HP - Multiples of 10, 50 < x < 250 
        ZombieStats[x][1] = {((rand() % 8)*5) + 5}; //DMG - Multiples of 5, 5 < x < 40
        ZombieStats[x][2] =  {(rand() % 4) + 2}; //Range, 2 < x < 5
    } 

    Pause();
    ClearScreen();
    TurnSystem(Board, Row, Column, AlienHP_DMG, ZombieStats, Zombies);
}

int main()
{
    string UserInput;

    while(true)
    {
        cout << "-------- ALIEN VS ZOMBIES --------" << endl;
        cout << endl;
        cout << "Game settings (Default)" << endl;
        cout << "-----------------------" << endl;
        cout << "Board Rows      : 5" << endl;
        cout << "Board Columns   : 11" << endl;
        cout << "No. of Zombies  : 1" << endl;
        cout << endl;
        cout << "Type start to begin a game! (Or quit to exit the game)" << endl;
        cout << "Type load to load up a previously saved game!" << endl;
        cout << "-> "; cin >> UserInput; cout << endl;

        if (UserInput == "start")
        {
            Pause();
            ClearScreen();
            StartGame();
            break;
        }

        else if (UserInput == "quit")
        {
            ClearScreen();
            cout << "Game exited. Thanks for playing!" << endl;
            break;
        }

        else if (UserInput == "load")
        {
            LoadGame();
            break;
        }

        else 
        {
            cout << "Please enter a valid command, try again." << endl;
            continue;
        }
    }
}
