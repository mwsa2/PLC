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
    int hashing;
    int tam;
    Conexao *conexoes;
} HashTable;


int adicionarConexaoOrd(unsigned int timestamp, unsigned int cliente, HashTable *hashTable, int *hash, int *insersoesHash){
    int pos = 0;
    //
    Conexao *conexoes;
    //printf("add....\n");
    if(hashTable[*hash].conexoes == NULL){
        conexoes = (Conexao*)malloc(100000 * sizeof(Conexao)); 
        if (conexoes == NULL) {
            printf("memory cannot be allocated");
            exit(0);
        }
        //printf("primeiro....\n");
        conexoes[0].timestamp = timestamp;
        conexoes[0].cliente = cliente;
        //
        //printf("Ok1\n");
        hashTable[*hash].tam = 1;
        hashTable[*hash].conexoes = conexoes;
        //printf("Ok2\n");
    }else{
        //printf("ja tem....\n");
        pos = hashTable[*hash].tam;
        conexoes = hashTable[*hash].conexoes;
        while (pos > 0 && conexoes[pos - 1].timestamp > timestamp)
        {
            conexoes[pos] = conexoes[pos - 1];
            pos--;
        }
        //printf("OK3\n");
        conexoes[pos].timestamp = timestamp;
        conexoes[pos].cliente = cliente;
        hashTable[*hash].tam = hashTable[*hash].tam + 1;
        //printf("OK4\n");
    }
    *insersoesHash = *insersoesHash + 1;
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
    int posCliente = -1;
    unsigned int cliente;
    unsigned int timestamp;
    int insersoesHash = 0;
    int continuar = 1;
    //
    int m;
    float Lmax, fator;
    int hash;

    scanf("%d %f", &m, &Lmax);
    hashTable = (HashTable*)malloc(m * sizeof(HashTable)); 
    if (hashTable == NULL) {
        printf("memory cannot be allocated");
        exit(0);
    }
    hashTable->conexoes = NULL;
    for(int i = 0; i < m; i++){
        hashTable[i].hashing = 0;
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
                fator = ((float)insersoesHash / (float)m);
                if( fator <= Lmax)
                    adicionarConexaoOrd(timestamp, cliente, hashTable, &hash, &insersoesHash);                    
                else{
                    m = (2*m) + 1;
                    hashTable = (HashTable*)realloc(hashTable, m * sizeof(HashTable));
                    if (hashTable == NULL) {
                        printf("realloc error");
                        exit(0);
                    }
                    for(int i = 0; i < m; i++){
                        hashTable[i].hashing = 1;
                    }
                    //reordena
                    printf("reordernar\n");
                    for(int i = 0;i < m; i++){
                        if(hashTable[i].conexoes != NULL){
                            hash = (hashTable[i].conexoes[0].timestamp % m);
                            printf("inserindo fila: %d na posicao: %d\n", i, hash);
                            //verifica se o novo hash ja tem arquivo;
                            if(hashTable[hash].conexoes == NULL){
                               printf("%d livre\n", hash);     
                               hashTable[hash].conexoes = hashTable[i].conexoes;
                               free(hashTable[i].conexoes);
                               printf("reordernar OK e conexoes %d free\n", i);      
                            }else{
                                printf("%d ocupada com %d\n", hash, hashTable[hash].conexoes[0].cliente);
                                if(hashTable[hash].hashing == 0 ){ 
                                    printf("%d jah foi atualizada, inserindo os elemnetos de %d\n", hash, i);
                                    for(int j=0; j<hashTable[i].tam; j++){
                                        adicionarConexaoOrd(hashTable[i].conexoes[j].timestamp, hashTable[i].conexoes[j].cliente, hashTable, &hash, &insersoesHash);  
                                    }   
                                    free(hashTable[i].conexoes);
                                }else{
                                    printf("%d nao foi atualizada\n", hash);
                                    printf("copiando hash %d para temp\n", hash);
                                    Conexao *conexoesTemp;
                                    conexoesTemp = hashTable[hash].conexoes;
                                    printf("copiando i:%d para hash %d\n", i, hash);
                                    hashTable[hash].conexoes = hashTable[i].conexoes;
                                    hashTable[hash].hashing = 0;
                                    printf("copias OK\n");
                                    //
                                    hash = (conexoesTemp[0].timestamp % m);
                                    printf("inserindo temp na hash:%d\n", hash);
                                    hashTable[hash].conexoes = conexoesTemp;
                                    hashTable[hash].hashing = 0;
                                    printf("inserindo temp OK\n");
                                    free(conexoesTemp);
                                    printf("free temp\n");
                                }
                            }
                            
                        }
                    }
                    //adiciona
                    printf("tentando adicionar o %u\n", timestamp);
                    adicionarConexaoOrd(timestamp, cliente, hashTable, &hash, &insersoesHash); 
                }    
                    
            }
            else if (strcmp(command, "QRY") == 0)
            {
                sscanf(input, "%s %u", &command, &timestamp);
                hash = (timestamp % m);
                if(hashTable[hash].tam > 0)
                    posCliente = bSearch(hashTable[hash].conexoes, 0, hashTable[hash].tam, timestamp); 
                if (posCliente != -1)
                    printf("%u %d\n", hashTable[hash].conexoes[posCliente].cliente, posCliente);
                else
                    printf("-1 -1\n");
            }
        }
    };
    free(hashTable);
    
    return 0;
}
