#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _cordenada
{
    int x;
    int y;
} Cordenada;

Cordenada *setCord(Cordenada *c, int x, int y)
{
    c->x = x;
    c->y = y;
    //         
    return c;
}

typedef struct _pilha
{
    Cordenada *cordenada;  
    int distancia; 
	struct _pilha *next;
} Pilha;

// enfileirar
Pilha *enquee(Pilha *p, Cordenada *cordenada, int distancia)
{
    Pilha *pilha;
    pilha = (Pilha *)malloc(sizeof(Pilha));
    pilha->cordenada = cordenada;
    pilha->distancia = distancia;
    pilha->next = p->next;
    p->next = pilha;
    //         
    return p;
}

// desenfileirar
Pilha *dequee(Pilha *p)
{
    Pilha *cur = p;
    p = cur->next;
    cur->next = p->next;
    free(p);
    return cur;
}

int BFS(int *matriz, int *m, int *n, Cordenada *origem, Cordenada *destino){
	
    

	//sentinela
    Pilha *pilhas;
    pilhas = (Pilha *)malloc(sizeof(Pilha));
    pilhas->next = NULL;
    
    
    enquee(pilhas, origem, 0);

    int dist[*m][*n];
	dist[origem->x][origem->y] = 1;
    while(pilhas->next != NULL)
    {
        Pilha *curr = pilhas;
        Cordenada *cord = curr->next->cordenada;

        int i = cord->x;
        int j = cord->y;   
        
        dequee(pilhas);
        Cordenada *cordenada;
		cordenada = (Cordenada*)malloc(1 * sizeof(Cordenada)); 
		
        if( i-1 >= 0 && *((matriz+(i-1)**n) + j) != 1 && dist[i-1][j] == 0 ) dist[i-1][j] = dist[i][j] + 1, enquee(pilhas, setCord(cordenada, i-1, j), 0);
        if( i+1 <  m && *((matriz+(i+1)**n) + j) != 1 && dist[i+1][j] == 0 ) dist[i+1][j] = dist[i][j] + 1, enquee(pilhas, setCord(cordenada, i+1, j), 0);
        if( j-1 >= 0 && *((matriz+(i)**n) + (j-1)) != 1 && dist[i][j-1] == 0 ) dist[i][j-1] = dist[i][j] + 1, enquee(pilhas, setCord(cordenada, i, j-1), 0);
        if( j+1 <  n && *((matriz+(i)**n) + (j+1)) != 1 && dist[i][j+1] == 0 ) dist[i][j+1] = dist[i][j] + 1, enquee(pilhas, setCord(cordenada, i, j+1), 0);
    }

    
    //if(dist[destino->x][destino->y] == 0) printf("Labirinto Impossivel\n");
    //else 
    printf("%d\n", dist[destino->x][destino->y]);
	
    
    //if(dist[ed.first][ed.second] == 0) cout << "Labirinto Impossivel" << endl;
    //else cout << dist[ed.first][ed.second] - 1 << endl;
	
    


    

    /*for(int i = 0; i<*m; i++){
        for(int j = 0; j<*n; j++){
            printf("%d ", *((matriz+i**n) + j));
        }
        printf("\n");
    }
       
    printf("Origem %d %d\n", origem->x, origem->y);
    printf("Destino %d %d\n", destino->x, destino->y);*/
	
	
    return -1;
}

int main()
{
    int m, n;
    Cordenada *origem;
    Cordenada *destino;

    origem = (Cordenada*)malloc(1 * sizeof(Cordenada)); 
    destino = (Cordenada*)malloc(1 * sizeof(Cordenada)); 
    if ((origem == NULL) || (destino == NULL)) {
        printf("memory cannot be allocated");
        exit(0);
    }

    scanf("%d %d", &m, &n);
    int matriz[m][n];
    int val = 0;
    for(int i = 0; i<m; i++){
        for(int j = 0; j<n; j++){
            scanf("%d", &val);
            matriz[i][j] = val;
            if(val == 2){
                origem->x = i;
                origem->y = j;
            }    
            if(val == 3){
                destino->x = i;
                destino->y = j;
            }      
        }
    }

    int x = BFS((int *)matriz, &m, &n, origem, destino);   
	printf("%d\n", x);
    return 0;
}