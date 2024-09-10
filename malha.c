#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct _aresta
{
    int v;
    int w;
} Aresta;

typedef struct _grafo {
    Aresta* arestas[MAX_VERTICES];
    int count[MAX_VERTICES];
} Grafo;

void addAresta(Grafo* grafo, int u, int v, int w) {
    grafo->arestas[u][grafo->count[u]].v = v;
    grafo->arestas[u][grafo->count[u]].w = w;
    grafo->count[u]++;
    //
    grafo->arestas[v][grafo->count[v]].v = u;
    grafo->arestas[v][grafo->count[v]].w = w;
    grafo->count[v]++;
}

void mostraGrafo(Grafo* grafo, int v) {
    for (int u = 0; u < v; u++) {
        printf("Node %d makes an edge with \n", u);
        for (int i = 0; i < grafo->count[u]; i++) {
            int v = grafo->arestas[u][i].v;
            int w = grafo->arestas[u][i].w;
            printf("\tNode %d with edge weight = %d\n", v, w);
        }
        printf("\n");
    }
}

// Driver code
int main() {
    Grafo *grafo;
    int m, n;
    int a, b, p; 
    scanf("%d %d", &m, &n);

    grafo = (Grafo*)malloc(sizeof(Grafo)); 
     if (grafo == NULL) {
        printf("memory cannot be allocated");
        exit(0);
    }
    for (int i = 0; i < m; i++) {
        grafo->count[i] = 0;
        grafo->arestas[i] = (Aresta*)malloc(MAX_VERTICES * sizeof(Aresta));
    }

    for(int i = 0; i<n; i++){
        scanf("%d %d %d", &a, &b, &p);
        addAresta(grafo, a, b, p);
    }
    
    mostraGrafo(grafo, m);
    
    for (int i = 0; i < m; i++) {
        free(grafo->arestas[i]);
    }

    return 0;
}

