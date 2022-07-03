//Program: Matrix Chain Multiplication
//Author: Sharath Chandra Nirmala
//USN: 4NI20CS093
//#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<chrono>
using namespace std;
#include "exec_time.h"

#define forl(i, a, n) for (int i = a; i < n; i++)
#define VI vector<int>
#define VVI vector<VI>
#define MAX 99999

void Print2D(VVI arr)
{
    forl(i, 0, (int)arr.size())
    {
        forl(j, 0, (int)arr[i].size()) cout << arr[i][j] << " ";
        cout << "\n";
    }
}

class MCM
{
private:
    int numMatrices;
    VI dimensions;
    VVI tableMain;
    VVI tableS;
    char matrixName;
public:
    void Initialize()
    {
        matrixName = 'A';
        cout << "Enter the number of matrices: ";
        cin >> numMatrices;
        cout << "Enter the matrix dimensions:\n";
        forl(i, 0, numMatrices)
        {
            int m, n;
            cin >> m >> n;
            if (i < numMatrices - 1) dimensions.push_back(m);
            else if (i == numMatrices - 1)
            {
                dimensions.push_back(m);
                dimensions.push_back(n);
            }
        }
        tableMain.resize(numMatrices + 1, VI(numMatrices + 1, 0));
        tableS.resize(numMatrices + 1, VI(numMatrices + 1, 0));
        forl(i, 0, numMatrices + 1)
        {
            tableMain[i][i] = 0;
            tableS[i][i] = 0;
        }
    }

    void CalcTable()
    {
        forl(diagonal, 1, numMatrices + 1)
        {
            forl(i, 1, numMatrices + 1 - diagonal)
            {
                int j = i + diagonal;
                int minimum = MAX;
                forl(k, i, j)
                {
                    int q = tableMain[i][k] + tableMain[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
                    if (q < minimum)
                    {
                        minimum = q;
                        tableS[i][j] = k;
                    }
                }
                tableMain[i][j] = minimum;
            }
        }
    }

    int GetNumOps() { return *((*(tableMain.begin() + 1)).end() - 1); }

    VVI GetTableMain() { return tableMain; }
    VVI GetTableS() { return tableS; }

    int GetMaxLen(VVI table)
    {
        int maxLen = table[0].size();
        forl(i, 1, (int)table.size()) maxLen = table[i].size();
        return maxLen;
    }

    VI GetSArr(VVI table, int s)
    {
        forl(i, 0, (int)table.size())
        {
            if (table[i].size() > s) return table[i];
        }
    }

    void PrintMultiplication(int n = -1, int i = 1, int j = -1)
    {
        if (n == -1) n = numMatrices;
        if (j == -1) j = numMatrices;

        if (i == j)
        {
            cout << matrixName++;
            return;
        }

        cout << "(";
        PrintMultiplication(n, i, tableS[i][j]);
        PrintMultiplication(n, tableS[i][j] + 1, j);
        cout << ")";
    }
};

int main()
{
    MCM mcm;
    ExecTime et;
    mcm.Initialize();
    et.GetT1();
    mcm.CalcTable();
    et.GetT2();
    cout << "Minimum Number of Operations: " << mcm.GetNumOps() << "\n";
    et.PrintExecTime();
    cout << "Multiplication Order: ";
    mcm.PrintMultiplication();
    cout << "\nMain Table:\n";
    Print2D(mcm.GetTableMain());
    cout << "Table S:\n";
    Print2D(mcm.GetTableS());
    return 0;
}
