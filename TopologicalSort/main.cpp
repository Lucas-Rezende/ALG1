#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> d;
vector<int> f;
vector<int> parent;
vector<int> color;
vector<int> topoSort;
int timer;

void DFS(int V, int pai = -1) {
    color[V] = 1;
    d[V] = timer++;
    parent[V] = pai;

    for (int to : adj[V])
    {
        if(V == pai) continue;
        if (color[to] == 0)
        {
            parent[to] = V;
            DFS(to, V);
        } else if (color[to] == 1)
        {   
            printf("Grafo Cíclico! Para usar Topological Sort, insira um grafo do tipo GAD");
            break;
        }
    }
    f[V] = timer++;
    color[V] = 2; // preto, ou seja, revisitado pela última vez
    topoSort.push_back(V);
}

void TopologicalSort() {
    timer = 0;
    parent.assign(n, -1);
    d.assign(n, 0);
    f.assign(n, 0);
    color.assign(n, 0); // todas as cores começam brancas = não visitado

    for (size_t i = 0; i < n; i++)
    {
        if (color[i] == 0) // se o vértice ainda não foi visitado
        {
            DFS(i);
        }
    }

    reverse(topoSort.begin(), topoSort.end());
    for (int i : topoSort)
    {
        printf("%d ", i);
    }
    printf("\n");
    
}

int main(int argc, char const *argv[])
{
    int a, b;
    cin >> n >> m;
    adj.resize(n);
    for (size_t i = 0; i < m; i++)
    {
        cin >> a >> b;
        adj[a].push_back(b);
    }

    TopologicalSort();
    
    return 0;
}