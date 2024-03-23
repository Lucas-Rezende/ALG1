#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<vector<int>> adj, rev;
vector<bool> visited;
vector<int> order, component;

void DFS1(int V)
{
    visited[V] = true;

    for (int to : adj[V])
    {
        if (!visited[to])
            DFS1(to);
    }
    order.push_back(V);
}

void DFS2(int v)
{
    visited[v] = true;
    component.push_back(v);

    for (int to : rev[v])
    {
        if (!visited[to])
            DFS2(to);
    }
}

int main(int argc, char const *argv[])
{
    int a, b;
    cin >> n >> m; // vertex and edges

    adj.resize(n);
    rev.resize(n);

    for (size_t i = 0; i < m; i++)
    {
        cin >> a >> b;
        adj[a - 1].push_back(b - 1);
        rev[b - 1].push_back(a - 1);
    }

    visited.assign(n, false);

    for (size_t i = 0; i < n; i++)
    {
        if (!visited[i])
            DFS1(i);
    }

    visited.assign(n, false);            // Isso proporciona a segunda visita
    reverse(order.begin(), order.end()); // Nos dá os tempos de término ao contrário

    vector<int> roots(n, 0);
    vector<int> root_nodes;
    vector<vector<int>> adj_scc(n); // Nosso grafo condensado

    for (size_t i = 0; i < n; i++)
    {
        if (!visited[i])
            DFS2(i);

        int root = component.front(); // O primeiro elemento da raíz é o começo da lista de término
        for (auto u : component)
            roots[u] = root;
        root_nodes.push_back(root);

        component.clear();
    }

    for (int v = 0; v < n; v++)
        for (auto u : adj[v])
        {
            int root_v = roots[v],
                root_u = roots[u];

            if (root_u != root_v)
                adj_scc[root_v].push_back(root_u);
        }

    sort(root_nodes.begin(), root_nodes.end());
    root_nodes.erase(unique(root_nodes.begin(), root_nodes.end()), root_nodes.end());

    for (size_t i = 0; i < root_nodes.size(); ++i)
    {
        printf("%d: ", i + 1);
        vector<int> component_vertices;
        for (size_t j = 0; j < n; ++j)
        {
            if (roots[j] == root_nodes[i])
                component_vertices.push_back(j);
        }
        reverse(component_vertices.begin(), component_vertices.end());
        for (size_t j = 0; j < component_vertices.size(); ++j)
        {
            printf("%d", component_vertices[j] + 1);
            if (j != component_vertices.size() - 1)
                printf(" -> ");
        }
        printf("\n");
    }

    return 0;
}