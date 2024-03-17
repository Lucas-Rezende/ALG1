#include <iostream>
#include <vector>

using namespace std;

const int MAX = 100000;
int n, m;
vector<vector<int>> adj(MAX);
vector<int> parent;
int children;
int timer;
vector<bool> visited;
vector<int> low, tin;

void DFS(int V, int pai = -1) {
    visited[V] = true;
    low[V] = tin[V] = timer++;
    children = 0;
    for (int to : adj[V])
    {
        if (to == pai) continue;
        if (visited[to])
        {
            low[V] = min(low[V], tin[to]);
        } else
        {
            low[V] = min(low[V], low[to]);
            if (low[to] >= tin[V] && pai != -1)
            {
                std::cout << "Ponto de articulação encontrado em " << V << std::endl;
            }
            children++;
        }
    }
    if (pai == -1 && children > 1)
    {
        std::cout << "Ponto de articulação encontrado em " << V << std::endl;
    }
    
}

void FindArticulationPoints() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (size_t i = 0; i < n; i++)
    {
        // chamar dfs para todos os vértices
        if (!visited[i])
            DFS(i);
    }
}

int main(int argc, char const *argv[])
{
    int num1, num2;
    scanf("%d %d", &n, &m);
    for (size_t i = 0; i < m; i++)
    {
        scanf("%d %d", &num1, &num2);
        adj[num1 - 1].push_back(num2 - 1);
        adj[num2 - 1].push_back(num1 - 1);
    }
    FindArticulationPoints();

    return 0;
}