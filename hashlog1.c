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
                            printf("hash calculado\n");
                            //verifica se o novo hash ja tem arquivo;
                            if(hashTable[hash].conexoes == NULL){
                               printf("nova posicao livre\n");     
                               hashTable[hash].conexoes = hashTable[i].conexoes;
                               free(hashTable[i].conexoes);
                               printf("reordernar OK\n");      
                            }else{
                                printf("nova posicao ocupada\n");
                                if(hashTable[hash].hashing == 0 ){ 
                                    //inserir os elementos 1 a 1
                                    for(int j=0; j<hashTable[i].tam; j++){
                                        adicionarConexaoOrd(hashTable[i].conexoes[j].timestamp, hashTable[i].conexoes[j].cliente, hashTable, &hash, &insersoesHash);  
                                    }   
                                    free(hashTable[i].conexoes);
                                }else{
                                    Conexao *conexoesTemp;
                                    conexoesTemp = hashTable[hash].conexoes;
                                    printf("tem = hash\n");
                                    hashTable[hash].conexoes = hashTable[i].conexoes;
                                    hashTable[hash].hashing = 0;
                                    printf("hash = i\n");
                                    //
                                    printf("reordernar a temp\n");
                                    hash = (conexoesTemp[0].timestamp % m);
                                    printf("hash calculado 2\n");
                                    hashTable[hash].conexoes = conexoesTemp;
                                    hashTable[hash].hashing = 0;
                                    printf("reordernar temp ok\n");
                                    free(conexoesTemp);
                                }
                            }
                            
                        }
                    }
                    //adiciona
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
