#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n, m; // n computers and m connections
vector<vector<int>> graph;
vector<int> parent, myPath;
vector<bool> visited;

void BFS(int S)
{
    queue<int> q; // Lista
    q.push(S);
    parent[S] = S;
    visited[S] = 1;

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (auto to : graph[v])
        {
            if (!visited[to])
            {
                q.push(to);
                visited[to] = 1;
                parent[to] = v;
            }
        }
    }
}

bool path(int v)
{
    vector<int> temp;

    if (!visited[v])
        return true;

    temp.push_back(v);
    while (parent[v] != v)
    {
        v = parent[v];
        temp.push_back(v);
    }

    myPath = temp;
    reverse(myPath.begin(), myPath.end());

    return true;
}

void startBFS()
{
    visited.assign(n, 0);
    parent.assign(n, -1);
    myPath.assign(n, 1);
}

void printAns() {
    path(n - 1);

    if (myPath.size() == 0)
    {
        printf("IMPOSSIBLE");
    }
    else
    {
        cout << myPath.size() << endl;
        for (int to : myPath)
            printf("%d ", to + 1);
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    cin >> n >> m;
    graph.resize(n);

    for (int i = 0; i < m; i++)
    {
        // Inserindo arestas
        int a, b;
        cin >> a >> b;

        // Grafo não direcionado
        graph[a - 1].push_back(b - 1);
        graph[b - 1].push_back(a - 1);
    }

    // Uolevi's computer is 1 and Maija's computer is n. Devemos verificar se existe conexão entre esses dois computadores.
    startBFS();
    BFS(0);
    printAns();

    return 0;
}
