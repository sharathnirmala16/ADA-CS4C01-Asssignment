//Program: Travelling Salesman Problem, the algorithm produces an approximate solution by:
//Obtaining a minimum spanning tree, then it performs a preorder walk on the minimum spanning tree,
//after which it calculates the cost of this preorder walk. The preorder walk is performed on edges
//sorted by their weight.
//Author: Sharath Chandra Nirmala
//USN: 4NI20CS093
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<chrono>
#include<unordered_map>
#include<unordered_set>
using namespace std;
#include "exec_time.h"

#define forl(i, a, n) for (int i = a; i < n; i++)
#define VI vector<int>
#define VVI vector<VI>
#define umap unordered_map
#define uset unordered_set

bool Comparator(const VI& a, const VI& b)
{
    return a[1] < b[1];
}

class Prim
{
protected:
    umap<int, VVI> adjList;
    int vertices;
    int edges;
public:
    Prim(VVI edgeList, int v)
    {
        vertices = v;
        edges = (v * (v - 1)) / 2;
        adjList.clear();

        forl(i, 0, edges)
        {
            VI temp(3);
            temp[0] = edgeList[i][0]; temp[1] = edgeList[i][1]; temp[2] = edgeList[i][2];
            adjList[temp[0]].push_back(temp);
            reverse(temp.begin(), temp.end());
            adjList[temp[0]].push_back(temp);
        }
    }

    umap<int, VVI> GetAdjList()
    {
        return adjList;
    }

    int GetVertexCount()
    {
        return vertices;
    }

    int GetEdgeCount()
    {
        return edges;
    }

    int MinEdge(VVI edges)
    {
        int minWeight = INT32_MAX;
        int minIndex = -1;
        for (int i = 0; i < (int)edges.size(); i++)
        {
            if (edges[i][1] < minWeight)
            {
                minWeight = edges[i][1];
                minIndex = i;
            }
        }
        return minIndex;
    }

    int FindEdge(VVI edges, VI edge)
    {
        forl(i, 0, (int)edges.size()) if (edges[i] == edge) return i;
        return -1;
    }

    void DeleteEdge(umap<int, VVI>& edgeList, VI minEdge)
    {
        edgeList[minEdge[0]].erase(edgeList[minEdge[0]].begin() + FindEdge(edgeList[minEdge[0]], minEdge));
        swap(minEdge[0], minEdge[2]);
        edgeList[minEdge[0]].erase(edgeList[minEdge[0]].begin() + FindEdge(edgeList[minEdge[0]], minEdge));
    }

    bool NotInSet(uset<int> intree, VI edge)
    {
        if (intree.find(edge[0]) == intree.end() || intree.find(edge[2]) == intree.end()) return true;
        return false;
    }

    VVI GetMST()
    {
        VVI res;
        uset<int> intree;
        umap<int, VVI> edgeList = adjList;

        intree.insert(0);
        while (intree.size() != vertices)
        {
            VVI possibleEdges;
            for (auto i = intree.begin(); i != intree.end(); i++)
            {
                possibleEdges.insert(possibleEdges.begin(), edgeList[*i].begin(), edgeList[*i].end());
            }
            int minInd = MinEdge(possibleEdges);
            VI minEdge = possibleEdges[minInd];
            if (NotInSet(intree, minEdge))
            {
                if (minInd != -1)
                {
                    intree.insert(minEdge[0]);
                    intree.insert(minEdge[2]);
                    res.push_back(minEdge);
                    DeleteEdge(edgeList, minEdge);
                }
                else break;
            }
            else DeleteEdge(edgeList, minEdge);
        }
        return res;
    }
};

class TravellingSalesman : public Prim
{
private:
    VVI MST;
    umap<int, bool> visited;
    VI route;
public:
    TravellingSalesman(VVI eList, int v) : Prim(eList, v) 
    {
        MST = GetMST(); 
        sort(MST.begin(), MST.end(), &Comparator);
        edges = MST.size();
    }

    void PreorderWalk(int vertex = 0)
    {
        if (!visited[vertex])
        {
            visited[vertex] = true;
            route.push_back(vertex);
        }

        forl(i, 0, edges)
        {
            if (!visited[MST[i][0]]) PreorderWalk(MST[i][0]);
            if (!visited[MST[i][2]]) PreorderWalk(MST[i][2]);
        }
    }

    int GetWeight(VVI edges, int destination)
    {
        forl(i, 0, (int)edges.size())
        {
            if (edges[i][2] == destination) return edges[i][1];
        }
        return -1;
    }

    pair<VI, int> GetRouteAndCost()
    {
        //Gets the route
        PreorderWalk();
        if (*(route.begin()) != *(route.end() - 1)) route.push_back(*route.begin());

        //Cost calculation for the route
        int cost = 0;
        forl(i, 0, (int)route.size() - 1) cost += GetWeight(adjList[route[i]], route[i + 1]);
        
        return make_pair(route, cost);
    }
};

int main()
{
    int vertices, edges;
    cout << "Enter the number of vertices: ";
    cin >> vertices;

    cout << "Enter the source, weight, destination (0 based indexing, undirected edges):\n";
    edges = (vertices * (vertices - 1)) / 2;
    VVI edgeList(edges, VI(3, 0));
    forl(i, 0, edges) cin >> edgeList[i][0] >> edgeList[i][1] >> edgeList[i][2];

    TravellingSalesman tsp(edgeList, vertices);
    ExecTime et;
    et.GetT1();
    pair<VI, int> sol = tsp.GetRouteAndCost();
    et.GetT2();
    cout << "Route: ";
    forl(i, 0, (int)sol.first.size() - 1) cout << sol.first[i] << "->";
    cout << sol.first[*(sol.first.end() - 1)] << "\n";
    cout << "Route Cost: " << sol.second << "\n";
    et.PrintExecTime();

    return 0;
}
