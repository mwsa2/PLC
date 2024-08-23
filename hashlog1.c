#include <string.h>
#include <stdio.h>
#include <malloc.h>

typedef struct _conexao
{
    unsigned int timestamp;
    unsigned int cliente;
} Conexao;

int adicionarConexaoOrd(unsigned int timestamp, unsigned int cliente, Conexao *conexoes, int *tam){
    int pos = 0;
    printf("%d\n", *tam);
    conexoes = (Conexao*)realloc(conexoes, (*tam) * sizeof(Conexao));
    printf("OK\n");  
    if (conexoes == NULL) {
        printf("Reallocation Failed\n");
        exit(0);
    }
    
    conexoes[*tam]->timestamp = timestamp;
    conexoes[*tam]->cliente = cliente;
    //*tam = *tam + 1;
    
    for(int i=0; i<*tam; i++){
        printf("%u %u\n", conexoes[i]->timestamp, conexoes[i]->cliente);
    }

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
    int tam = 1;
    int posConexao;
    //
    Conexao *conexoes; //= (Conexao *)malloc(1 * sizeof(Conexao));
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
