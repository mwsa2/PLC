#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _cordenada
{
    int x;
    int y;
} Cordenada;

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
	/*if (!matriz[origem->x][origem->y] || !matriz[destino->x][destino->y])
        return -1;*/
	
	int visited[*m][*n];
	visited[origem->x][origem->y] = 1;
    
	
	//sentinela
    Pilha *pilhas;
    pilhas = (Pilha *)malloc(sizeof(Pilha));
    pilhas->next = NULL;
	
	enquee(pilhas, origem, 0);
	
	int rowNum[] = {-1, 0, 0, 1};
	int colNum[] = {0, -1, 1, 0};
	
	while (pilhas->next != NULL)
    {
        //Pilha *curr = pilhas->next;
		Pilha *curr = pilhas;
        Cordenada *cord = curr->cordenada;
 
        if (cord->x == destino->x && cord->y == destino->y)
            return curr->distancia;
 
        dequee(pilhas);
 
        for (int i = 0; i < *m; i++)
        {
            int row = cord->x + rowNum[i];
            int col = cord->y + colNum[i];
             
            if (!(*((matriz+i*row) + col)) && !visited[row][col])
            {
                visited[row][col] = 1;
                //
				Cordenada *cordenada;
				cordenada = (Cordenada*)malloc(1 * sizeof(Cordenada)); 
				cordenada->x = row;
				cordenada->y = col;
				enquee(pilhas, cordenada, curr->distancia + 1);
				
            }
        }
    }
 
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
