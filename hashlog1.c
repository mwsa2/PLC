#include <string.h>
#include <stdio.h>
#include <malloc.h>

typedef struct _conexao
{
    unsigned int timestamp;
    unsigned int cliente;
} Conexao;

void adicionarConexao(unsigned int timestamp, unsigned int cliente){
    Conexao *con = (Conexao *)malloc(sizeof(Conexao));
    con->timestamp = timestamp;
    con->cliente = cliente;
    
}

int main()
{
    // Inicio
    char input[30];
    char command[4];
    unsigned int client;
    int continuar = 1;
    //
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
                sscanf(input, "%s %s %d", &command, &nome, &pontuacao);

                Nome *searchNome = AVLsearchNome(rootNome, nomeAux);
                if (searchNome != NULL)
                    printf("%s ja esta no sistema.\n", nome);
                else{
                    rootNome = inserirNome(rootNome, nomeAux);
                    rootJogador = inserirJogador(rootJogador, nomeAux, pontuacao);
                    printf("%s inserido com sucesso!\n", nome);
                }
            }
            else if (strcmp(command, "QRY") == 0)
            {
                sscanf(input, "%s %d", &command, &pontuacao);
            }
        }
    }
            
    return 0;
}
