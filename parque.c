#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int *knapSack_unbounded(int budget, int *S, int *B, int *C, int N) {

    int * dp = (int *) calloc(budget + 1, sizeof(int));

    for(int i = 0; i < N; i++){
        
        for(int j = budget; j >= C[i]; j--){
            
            int max = INT_MIN;
            int uses = 1;
            int F = S[i];
            
            while(uses * C[i] <= j){
                
                int aux = dp[j - uses*C[i]] + F;
                
                if (aux > max) max = aux;
                
                F += S[i] - (uses)*(uses)*B[i];
                if(F <= 0) F = 0;
                uses++;              
            }
        
            if (max > dp[j]) dp[j] = max;
        }
       
    }

    return dp;
}

int main() {
    int n; //brinquedos
    scanf("%d", &n);
	
	int v; //visitas
	int max = 0;

    

    int *S = (int *) malloc(N * sizeof(int));
    int *fator_aborrecimento = (int *) malloc(N * sizeof(int));
    int *custos = (int *) malloc(N * sizeof(int));

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &S[i], &B[i], &C[i]);
    }

    scanf("%d", &V);

    int *K = (int *) malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        scanf("%d", &K[i]);
        if (K[i] > max) max = K[i];
    }

    int * dp = NULL;

    dp = knapSack_unbounded(max, S, B, C, N);
	
	free(S);
    free(B);
    free(C);
    free(K);
	
    for (int i = 0; i < V; i++) {
        printf("%d: %d\n", i, dp[K[i]]);
    }

    
    free(dp);
    return 0;
}