#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int temp;
const int MAX = 100000;
int qnt, qntArestas; // quantidade de vertices
vector<vector<int>> adj(MAX);
vector<bool> visited;
vector<int> tin, low;

void teste()
{
    std::cout << "dor" << std::endl;
}

void dfs(int verticeVigente, int paiDoVertice = -1)
{
    visited[verticeVigente] = 1;
    tin[verticeVigente] = low[verticeVigente] = temp++;
    for (int tempVertice : adj[verticeVigente])
    {
        if (tempVertice == paiDoVertice)
            continue;
        if (visited[tempVertice])
        {
            low[verticeVigente] = min(low[verticeVigente], tin[tempVertice]);
        }
        else
        {
            // Aqui tratamos os vértices não visitados
            dfs(tempVertice, verticeVigente);
            std::cout << low[tempVertice] << " " << tin[tempVertice] << std::endl;
            //std::cout << low[verticeVigente] << " " << tin[verticeVigente] << std::endl;
            //low[verticeVigente] = min(low[verticeVigente], low[tempVertice]);
            if (low[tempVertice] > tin[verticeVigente])
            {
                std::cout << "Aresta entre " << verticeVigente + 1 << " e " << tempVertice + 1 << std::endl;
            }
        }
    }
}

void findBridge()
{
    temp = 0;
    visited.assign(qnt, false);
    tin.assign(qnt, -1);
    low.assign(qnt, -1);
    for (size_t i = 0; i < qnt; i++)
    {
        // chamar dfs para todos os vértices
        if (!visited[i])
            dfs(i);
    }
}

int main(int argc, char const *argv[])
{
    int num1, num2;
    scanf("%d %d", &qnt, &qntArestas);
    for (size_t i = 0; i < qntArestas; i++)
    {
        scanf("%d %d", &num1, &num2);
        adj[num1 - 1].push_back(num2 - 1);
        adj[num2 - 1].push_back(num1 - 1);
    }
    findBridge();

    return 0;
}
