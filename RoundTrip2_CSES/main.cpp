#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Globais
const int MAX = 100000;
vector<vector<int>> adj(MAX);
int n, m; // n cities and m flight connections
vector<int> parent(MAX, -1);
vector<int> color(MAX, 0);
int cycle_start, cycle_end;

bool dfs(int v) {
    color[v] = 1; // gray, ou seja, visitado
    for (int u : adj[v])
    {
        if (color[u] == 0) // white, ou seja, não visitado
        {
            parent[u] = v;
            if (dfs(u))
            {
                return true;
            }
        } else if (color[u] == 1)
        {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
    }
    color[v] = 2; // black, ou seja, Revisitado
    return false;
}

void find_cycle()
{
    cycle_start = -1;
    color.assign(n, 0);
    parent.assign(n, -1);

    for (size_t i = 1; i <= n; i++)
    {
        if (color[i] == 0 && dfs(i))
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
        for (int v = cycle_end; v != cycle_start; v = parent[v])
        {
            tempCycle.push_back(v);
        }
        tempCycle.push_back(cycle_start);
        reverse(tempCycle.begin(), tempCycle.end());
        
        std::cout << tempCycle.size() << std::endl;
        for (int v : tempCycle)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;        
    }
}

int main(int argc, char const *argv[])
{
    int a, b;
    cin >> n >> m;
    for (size_t i = 0; i < m; i++)
    {
        cin >> a >> b;
        adj[a].push_back(b); // Como é um grafo direcionado, não necessariamente b é adjacente com a
    }

    find_cycle();
    
    return 0;
}