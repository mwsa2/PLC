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
    if(hashTable[*hash].conexoes == NULL){
        conexoes = (Conexao*)malloc(100000 * sizeof(Conexao)); 
        if (conexoes == NULL) {
            printf("memory cannot be allocated");
            exit(0);
        }
        conexoes[0].timestamp = timestamp;
        conexoes[0].cliente = cliente;
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
    *insersoesHash = *insersoesHash + 1;
    pos = *hash;
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
                if( fator <= Lmax){
                    posCliente = adicionarConexaoOrd(timestamp, cliente, hashTable, &hash, &insersoesHash);                    
                    printf("%d %d\n", posCliente, hashTable[posCliente].tam);
                }else{
                    int mLast = m;
                    m = (2*m) + 1;
                    HashTable *hashTableNew;
                    hashTableNew = (HashTable*)malloc(m * sizeof(HashTable)); 
                    if (hashTableNew == NULL) {
                        printf("memory cannot be allocated hashTableNew\n");
                        exit(0);
                    }
                    hashTableNew->conexoes = NULL;
                    insersoesHash = 0;
                    //reordena
                    for(int i = 0;(i < mLast) && (hashTable[i].conexoes != NULL); i++){
                        for(int j=0; j<hashTable[i].tam; j++ ){
                            hash = (hashTable[i].conexoes[j].timestamp % m);
                            adicionarConexaoOrd(hashTable[i].conexoes[j].timestamp, hashTable[i].conexoes[j].cliente, hashTableNew, &hash, &insersoesHash);          
                        }       
                    }
                    free(hashTable);
                    hashTable = hashTableNew;
                    hash = (timestamp % m);
                    posCliente = adicionarConexaoOrd(timestamp, cliente, hashTable, &hash, &insersoesHash);
                    printf("%d %d\n", posCliente, hashTable[posCliente].tam); 
                }    
                    
            }
            else if (strcmp(command, "QRY") == 0)
            {
                posCliente = -1;
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
