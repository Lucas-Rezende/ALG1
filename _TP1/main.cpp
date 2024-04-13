#include <vector>
#include <iostream>
#include <set>
#include <stack>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

struct Forest
{
    map<int, set<int>> tree;
};

class graph
{
private:
    // GRAFO

    /**
     * @param adj Armazenamento do grafo.
     */
    vector<vector<int>> adj;
    /**
     * @param parent Pais de cada vértice.
     */
    vector<int> parent;
    /**
     * @param timer Variável auxiliar para descobrir tin e low.
     */
    int timer = 0;
    /**
     * @param visited Indica se um vértice já foi visitado ou não
     */
    vector<bool> visited;
    /**
     * @param low, tin Tempo de início e tempo de tpermino
     */
    vector<int> low, tin;
    /**
     * @param saveArticulationPoints Armazenamento dos pontos de articulação.
     */
    set<int> saveArticulationPoints;

    // CLUSTERS
    int n, m;
    
    /**
     * @param timerAux Auxiliar para setar low em DFS2
     */
    vector<int> tinAux;
    /**
     * @param timerAux Auxiliar para estabelecer valores de tin e low no DFS2
     */
    int timerAux = 0;
    /**
     * @param S Pilha auxiliar pra armazenar componentes.
     */
    stack<int> S;
    /**
     * @param components Armazenamento dos clusters/componentes biconexos.
     */
    vector<vector<int>> components;

    /**
     * @param forest Armazenamento das florestas.
     */
    set<set<int>> forest;
    /**
     * @param forestEdges Auxiliar que armazena temporariamente as arestas da floresta.
     */
    set<pair<int, int>> forestEdges;
    /**
     * @param countEdges Contabiliza arestas na floresta.
     */
    int countEdges = 0;

public:
    graph(int n);
    ~graph();
    void buildGraph(int n, int m);

    void DFS(int V, int pai);
    void DFS2(int V);
    void FindArticulationPoints();
    void FindClusters();

    void OutputPrint();
    int N_vertex, M_edges = 0;
    int quantidadeArticulationPoints = 0;

    void buildForest();
    void printForest();
    void buildForestAndPrint();
};

graph::graph(int n_vertex) : N_vertex(n_vertex), adj(n_vertex) {}

graph::~graph() {}

void graph::buildGraph(int n, int m)
{
    N_vertex = n;
    M_edges = m;

    for (size_t i = 0; i < M_edges; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        adj[a - 1].push_back(b - 1);
        adj[b - 1].push_back(a - 1);
    }
}

void graph::DFS(int V, int pai = -1)
{
    visited[V] = 1;
    tin[V] = low[V] = ++timer;
    int children = 0;

    for (int to : adj[V])
    {
        if (to == pai)
            continue;
        if (visited[to])
        {
            low[V] = min(low[V], tin[to]);
        }
        else
        {
            DFS(to, V);

            low[V] = min(low[V], low[to]);

            if (low[to] >= tin[V] && pai != -1)
            {
                saveArticulationPoints.insert(V + 1);
                quantidadeArticulationPoints++;
            }
            children++;
        }
    }
    if (pai == -1 && children > 1)
    {
        quantidadeArticulationPoints++;
        saveArticulationPoints.insert(V + 1);
    }
}

void graph::DFS2(int u)
{
    tinAux[u] = low[u] = timerAux++;
    S.push(u);

    for (int v : adj[u])
    {
        if (tinAux[v] == -1)
        {
            parent[v] = u;
            DFS2(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= tinAux[u])
            {
                vector<int> component;
                int w;
                do
                {
                    w = S.top();
                    S.pop();
                    component.push_back(w);
                } while (w != v);
                component.push_back(u);

                sort(component.begin(), component.end());

                components.push_back(component);
            }
        }
        else if (v != parent[u])
        {
            low[u] = min(low[u], tinAux[v]);
        }
    }
}

void graph::FindArticulationPoints()
{
    parent.assign(N_vertex, -1);
    timer = 0;
    visited.assign(N_vertex, false);
    tin.assign(N_vertex, -1);
    low.assign(N_vertex, -1);

    for (size_t i = 1; i < N_vertex; i++)
    {
        if (!visited[i])
            DFS(i);
    }
}

void graph::buildForest()
{
    int vertexCount = components.size();
    int componentID = N_vertex + 1;

    for (const auto &component : components)
    {
        for (int value : component)
        {
            for (int articulationPoint : saveArticulationPoints)
            {
                if (value == articulationPoint - 1)
                {
                    forestEdges.insert({articulationPoint, componentID});
                    countEdges++;
                }
            }
        }
        componentID++;
    }
}

void graph::printForest()
{
    for (const auto &edge : forestEdges)
    {
        printf("%d %d\n", edge.first, edge.second);
    }
}

void graph::buildForestAndPrint()
{
    buildForest();
    printf("%lu %d\n", components.size() + saveArticulationPoints.size(), countEdges);
    printForest();
}

void graph::OutputPrint()
{
    // Listando os links da borda

    printf("%lu", saveArticulationPoints.size());
    for (int element : saveArticulationPoints)
    {
        printf("\n%d", element);
    }
    
    // Reiniciando variáveis

    parent.assign(N_vertex, -1);
    timer = 0;
    visited.assign(N_vertex, false);
    tin.assign(N_vertex, -1);
    low.assign(N_vertex, -1);
    tinAux.assign(N_vertex, -1);

    // Listando os clusters

    for (size_t i = 0; i < N_vertex; i++)
    {
        if (!visited[i])
            DFS2(i);
    }

    sort(components.begin(), components.end());

    printf("\n%lu\n", components.size());
    for (size_t j = 0; j < components.size(); j++)
    {
        int aux = j + 1;
        const auto &component = components[j];
        printf("%d %lu ", N_vertex + aux, component.size());

        for (int v : component)
        {
            printf("%d ", v + 1);
        }
        printf("\n");
    }

    // Listando a floresta

    buildForestAndPrint();
}

int main(int argc, char const *argv[])
{
    int vertex, edges = 0;
    scanf("%d %d", &vertex, &edges);

    graph myCluster(vertex);

    myCluster.buildGraph(vertex, edges);
    myCluster.FindArticulationPoints();
    myCluster.OutputPrint();

    return 0;
}