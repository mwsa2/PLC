#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _conexao
{
    unsigned int timestamp;
    unsigned int cliente;
} Conexao;

int adicionarConexaoOrd(unsigned int timestamp, unsigned int cliente, Conexao *conexoes, int *tam){
    int pos = 0;
    printf("count %d\n", *tam);
    
	if(*tam == 0){
		conexoes = (Conexao *)malloc(sizeof(Conexao));
		if (conexoes == NULL) {
			printf("memory cannot be allocated malloc");
			exit(0);
		}
	}else{
		printf(" novo tam %d\n", *tam);
		conexoes = (Conexao*)realloc(conexoes, 1 * sizeof(Conexao));
		if (conexoes == NULL) {
			printf("memory cannot be allocated realloc");
			exit(0);
		}
	}
	
	printf("OK\n");  
    
    //conexoes[*tam].timestamp = timestamp;
    //conexoes[*tam].cliente = cliente;
    *tam = *tam + 1;
    
    /*for(int i=0; i<*tam; i++){
		printf("i: %d\n", i);
		printf("%u %u\n", conexoes[i].timestamp, conexoes[i].cliente);
    }*/

    return pos;
}

int main()
{
    // Inicio
    char input[30];
    char command[4];
    unsigned int cliente;
    unsigned int timestamp;
    int continuar = 1;
    int tam = 0;
    int posConexao;
    //
    Conexao *conexoes;// = (Conexao *)malloc(sizeof(Conexao));
    while (continuar)
    {
        scanf(" %29[^\n]s", &input);
        //
        continuar = strcmp(input, "END");
        if (continuar)
        {
            sscanf(input, "%s ", &command);
            if (strcmp(command, "NEW") == 0)
            {   
                sscanf(input, "%s %u %u", &command, &timestamp, &cliente);
                adicionarConexaoOrd(timestamp, cliente, conexoes, &tam);
                
            }
            else if (strcmp(command, "QRY") == 0)
            {
                
            }
        }
    }

    /*for(int i=0; i<tam; i++){
        printf("tam: %d\n", tam);
        printf("i: %d\n", i);
        printf("%u %u\n", conexoes[i].timestamp, conexoes[i].cliente);
    }*/
    free(conexoes);
    return 0;
}
