#include <iostream>
#include <vector>

using namespace std;

int n, m, k;
const int MAX = 100000;
vector<vector<int>> adj(MAX);
vector<bool> visited(MAX, false);
vector<int> parent(MAX, -1);
int cycle_start, cycle_end;

bool dfs(int v, int par)
{
    visited[v] = true;
    for (int u : adj[v])
    {
        if(u == par) continue; // ignoramos os vértices predecessores
        if (visited[u])
        {
            cycle_start = u;
            cycle_end = v;
            k++;
            return true;
        }
        parent[u] = v; // predecessores
        if (dfs(u, parent[u]))
        {
            k++;
            return true;
        }
    }
    return false;
}

void find_cycle()
{
    cycle_start = -1;

    for (size_t i = 1; i <= n; i++)
    {
        if (!visited[i] && dfs(i, parent[i]))
        {
            break;
        }
    }

    if (cycle_start == -1)
    {
        std::cout << "IMPOSSIBLE" << std::endl;
    } else {
        vector<int> tempCycle;
        tempCycle.push_back(cycle_start);
        for (size_t i = cycle_end; i != cycle_start; i = parent[i])
        {
            tempCycle.push_back(i);
        }
        tempCycle.push_back(cycle_start);
        
        std::cout << k << std::endl;
        for (int v : tempCycle)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;        
    }
}

int main(int argc, char const *argv[])
{
    cin >> n >> m; // quantidade de cidades e estradas, respectivamente

    for (size_t i = 0; i < m; i++) // m linhas descrevendo as estradas
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    find_cycle();

    return 0;
}