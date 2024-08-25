#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _conexao
{
    unsigned int timestamp;
    unsigned int cliente;
} Conexao;

typedef struct _hashTable
{
    int tam;
    Conexao *conexoes;
} HashTable;


int adicionarConexaoOrd(unsigned int timestamp, unsigned int cliente, HashTable *hashTable, int *hash){
    int pos = 0;
    //
    Conexao *conexoes;
    if(hashTable[*hash].conexoes == NULL){
        conexoes = (Conexao*)malloc(100000 * sizeof(Conexao)); 
        conexoes[0].timestamp = timestamp;
        conexoes[0].cliente = cliente;
        //
        hashTable[*hash].tam = 1;
        hashTable[*hash].conexoes = conexoes;
        
    }else{
        pos = hashTable[*hash].tam;
        conexoes = hashTable[*hash].conexoes;
        while (pos > 0 && conexoes[pos - 1].timestamp > timestamp)
        {
            conexoes[pos] = conexoes[pos - 1];
            pos--;
        }
        conexoes[pos].timestamp = timestamp;
        conexoes[pos].cliente = cliente;
        hashTable[*hash].tam = hashTable[*hash].tam + 1;
    }
    printf("%d %d\n", *hash, hashTable[*hash].tam);
    return pos;
}

int bSearch(Conexao *conexoes, int low, int high, unsigned int key)
{
    if (high < low)
        return -1;
    int mid = (low + high) / 2;
    if (key == conexoes[mid].timestamp)
        return mid;    
    if (key > conexoes[mid].timestamp)
        return bSearch(conexoes, (mid + 1), high, key);
    return bSearch(conexoes, low, (mid - 1), key);
}

int main()
{
    HashTable *hashTable;
    Conexao *conexoes;
    char input[30];
    char command[4]; 
    int tam = 0;
    int posCliente;
    unsigned int cliente;
    unsigned int timestamp;
    int continuar = 1;
    //
    int m;
    double Lmax;
    int hash;

    scanf("%d %f", &m, &Lmax);
    hashTable = (HashTable*)malloc(m * sizeof(HashTable)); 
    if (hashTable == NULL) {
        printf("memory cannot be allocated");
        exit(0);
    }

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
                hash = (timestamp % m);
                if(tam <= Lmax)
                    adicionarConexaoOrd(timestamp, cliente, hashTable, &hash);                    
                else    
                    printf("rehash\n");
            }
            else if (strcmp(command, "QRY") == 0)
            {
                /*sscanf(input, "%s %u", &command, &timestamp);
                posCliente = bSearch(conexoes, 0, tam, timestamp); 
                if (posCliente != -1)
                    printf("%u %d\n", conexoes[posCliente].cliente, posCliente);
                else
                    printf("-1 -1\n");*/
            }
        }
    };
    free(conexoes);
    
    return 0;
}
