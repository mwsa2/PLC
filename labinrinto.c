#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _cordenada
{
    int x;
    int y;
} Cordenada;


int BFS(int *matriz, int *m, int *n, Cordenada *origem, Cordenada *destino){

    /*for(int i = 0; i<*m; i++){
        for(int j = 0; j<*n; j++){
            printf("%d ", *((matriz+i**n) + j));
        }
        printf("\n");
    }

       
    printf("Origem %d %d\n", origem->x, origem->y);
    printf("Destino %d %d\n", destino->x, destino->y);*/
    return 0;
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

    BFS((int *)matriz, &m, &n, origem, destino);   

    return 0;
}