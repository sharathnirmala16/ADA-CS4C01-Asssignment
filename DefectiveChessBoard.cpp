//Program: Defective Chess Board Problem
//Author: Sharath Chandra Nirmala
//USN: 4NI20CS093
#include<iostream>
#include<chrono>
#include<vector>
#include<algorithm>
using namespace std;
#include "exec_time.h"

#define forl(i, a, n) for (int i = a; i < n; i++)
#define VI vector<int>
#define VVI vector<VI>

void Print2D(VVI arr)
{
    forl(i, 0, (int)arr.size())
    {
        forl(j, 0, (int)arr[i].size()) cout << arr[i][j] << " ";
        cout << "\n";
    }
}

class DefectiveChessBoard
{
private:
    int N, color;
    VVI board;
    VI defect;
public:
    void Initialize()
    {
        int pX, pY;
        cout << "Enter the size of the board: ";
        cin >> N;
        board.resize(N, VI(N, 0));
        defect.resize(2, 0);
        cout << "(0 based indexing), enter the position of the defect: ";
        cin >> pX >> pY;
        board[pX][pY] = -1;
        defect[0] = pX;
        defect[1] = pY;
        color = ((N * N) - 1) / 3;
    }

    void PrintBoard()
    {
        cout << "Board:\n";
        Print2D(board);
    }

    void PlaceTile(VI coord1, VI coord2, VI coord3)
    {
        board[coord1[0]][coord1[1]] = color;
        board[coord2[0]][coord2[1]] = color;
        board[coord3[0]][coord3[1]] = color--;
    }

    void Tile(VI coord, int n = -1)
    { 
        if (n == -1) return Tile({ 0, 0 }, N);
        if (n == 2)
        {
            forl(i, 0, n)
            {
                forl(j, 0, n)
                {
                    if (board[coord[0] + i][coord[1] + j] == 0) board[coord[0] + i][coord[1] + j] = color;
                }
            }
            color--;
            return;
        }

        /*
        Quadrants
        1 2
        3 4
        */

        //Defective tile in 1st Quadrant
        if (defect[0] < coord[0] + n / 2 && defect[1] < coord[1] + n / 2)
        {
            VI coord1{ coord[0] + n / 2, coord[1] + (n / 2) - 1 };
            VI coord2{ coord[0] + n / 2, coord[1] + n / 2 };
            VI coord3{ coord[0] + (n / 2) - 1, coord[1] + n / 2 };
            PlaceTile(coord1, coord2, coord3);
        }

        //Defective tile in 2nd Quadrant
        else if (defect[0] < coord[0] + n / 2 && defect[1] >= coord[1] + n / 2)
        {
            VI coord1{ coord[0] + n / 2, coord[1] + (n / 2) - 1 };
            VI coord2{ coord[0] + n / 2, coord[1] + n / 2 };
            VI coord3{ coord[0] + (n / 2) - 1, coord[1] + (n / 2) - 1 };
            PlaceTile(coord1, coord2, coord3);
        }

        //Defective tile in 3rd Quadrant
        else if (defect[0] >= coord[0] + n / 2 && defect[1] < coord[1] + n / 2)
        {
            VI coord1{ coord[0] + (n / 2) - 1, coord[1] + n / 2 };
            VI coord2{ coord[0] + n / 2, coord[1] + n / 2 };
            VI coord3{ coord[0] + (n / 2) - 1, coord[1] + (n / 2) - 1 };
            PlaceTile(coord1, coord2, coord3);
        }

        //Defective tile in 4th Quadrant
        else if (defect[0] >= coord[0] + n / 2 && defect[1] >= coord[1] + n / 2)
        {
            VI coord1{ coord[0] + (n / 2) - 1, coord[1] + n / 2 };
            VI coord2{ coord[0] + n / 2, coord[1] + (n / 2) - 1 };
            VI coord3{ coord[0] + (n / 2) - 1, coord[1] + (n / 2) - 1 };
            PlaceTile(coord1, coord2, coord3);
        }

        //Recursive division into 4 quarters again
        VI tcoord = coord;
        tcoord[1] += n / 2;
        Tile(tcoord, n / 2);
        tcoord = coord;
        Tile(tcoord, n / 2);
        tcoord[0] += n / 2;
        Tile(tcoord, n / 2);
        tcoord[1] += n / 2;
        Tile(tcoord, n / 2);
    }
};

int main()
{
    DefectiveChessBoard dcb;
    ExecTime et;
    dcb.Initialize();
    cout << "Inital ";
    dcb.PrintBoard();
    et.GetT1();
    VI temp{ 0, 0 };
    dcb.Tile(temp);
    et.GetT2();
    cout << "Tiled ";
    dcb.PrintBoard();
    et.PrintExecTime();

    return 0;
}