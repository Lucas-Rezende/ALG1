
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> G; // Graph
vector<bool> visited;
vector<int> parent, myPath;
int n, m;                   // Vertex and edges
int startVertex, endVertex; // Found a path between this vertices.

void starter()
{
    visited.assign(n, false);
    parent.assign(n, -1);
    myPath.assign(n, 1);
}

void BFS(int s)
{
    queue<int> fila;
    parent[s] = s;
    visited[s] = 1;
    fila.push(s);

    while (!fila.empty())
    {
        int aux = fila.front();
        fila.pop();
        for (auto adjTemp : G[aux])
        {
            if (!visited[adjTemp])
            {
                parent[adjTemp] = aux;
                visited[adjTemp] = 1;
                fila.push(adjTemp);
                if (adjTemp == endVertex)
                    return; // Parar BFS se o vértice de destino for alcançado
            }
        }
    }
}

vector<int> path(int start, int end)
{
    vector<int> path;
    for (int v = end; v != -1; v = parent[v])
    {
        path.push_back(v);
        if (v == start)
            break;
    }
    reverse(path.begin(), path.end());
    myPath = path;
    return path;
}

void printAns()
{
    if (myPath.empty())
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        cout << myPath.size() << endl;
        for (int to : myPath)
            cout << to + 1 << " ";
        cout << endl;
    }
}

int main(int argc, char const *argv[])
{
    cin >> n >> m;

    G.resize(n);

    for (size_t i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        G[a - 1].push_back(b - 1);
        G[b - 1].push_back(a - 1);
    }

    cin >> startVertex >> endVertex;

    starter();
    BFS(startVertex - 1);
    path(startVertex - 1, endVertex - 1);

    printAns();

    return 0;
}
