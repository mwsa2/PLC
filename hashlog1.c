#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _conexao
{
    unsigned int timestamp;
    unsigned int cliente;
} Conexao;


int adicionarConexaoOrd(unsigned int timestamp, unsigned int cliente, Conexao *conexoes, int *index){
    int pos = 1;
    //
    conexoes[*index].timestamp = timestamp;
    conexoes[*index].cliente = cliente;
    
    /*printf("would you like to add more(1/0): ");
    scanf("%d", &ans);
    if (ans == 1) {
        index++;
        conexoes = (Conexao*)realloc(conexoes, (index + 1) * sizeof(Conexao)); 
        if (conexoes == NULL) {
            printf("memory cannot be allocated");
            exit(0);
        }
    }*/
    return pos;
}

int main()
{
    Conexao *conexoes;
    char input[30];
    char command[4]; 
    int index = 0;
    int ans;
    unsigned int cliente;
    unsigned int timestamp;
    int continuar = 1;

    conexoes = (Conexao*)malloc(sizeof(Conexao)); 
    if (conexoes == NULL) {
        printf("memory cannot be allocated");
        exit(0);
    }
    else {
        while(continuar) {
            
            scanf(" %29[^\n]s", &input);
            //
            continuar = strcmp(input, "END");
            if (continuar)
            {
                sscanf(input, "%s ", &command);
                if (strcmp(command, "NEW") == 0)
                {   
                    sscanf(input, "%s %u %u", &command, &timestamp, &cliente);
                    adicionarConexaoOrd(timestamp, cliente, conexoes, &index);
                    /*conexoes[index].timestamp = timestamp;
                    conexoes[index].cliente = cliente;
                    
                    printf("would you like to add more(1/0): ");
                    scanf("%d", &ans);
                    if (ans == 1) {
                        index++;
                        conexoes = (Conexao*)realloc(conexoes, (index + 1) * sizeof(Conexao)); 
                        if (conexoes == NULL) {
                            printf("memory cannot be allocated");
                            exit(0);
                        }
                    }*/
                    
                }
                else if (strcmp(command, "QRY") == 0)
                {
                    
                }
            }
        };
        
        for (int i = 0; i <= index; i++) {
            printf("conexoes %d are: %u\n ", i, conexoes[i].cliente);
        }
        free(conexoes);
    }
    return 0;
}
