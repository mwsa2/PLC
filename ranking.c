#include <string.h>
#include <stdio.h>
#include <malloc.h>

#define max(a, b) (a > b ? a : b)


typedef struct _jogador
{
    string nome;
    int pontuacao;
    struct _arvore *right;
    struct _arvore *left;
} Jogador;

void in_ordem(Jogador *root)
{
    if (root != NULL)
    {
        in_ordem(root->left);
        printf("%s %d\n", root->nome, root->pontuacao);
        in_ordem(root->right);
    }
}
aqui
Jogador *AVLsearch(Jogador *root, int id)
{
    if (root == NULL)
        return NULL;

    else if (root->dispositivo->id == id)
        return root;

    else if (root->dispositivo->id > id)
    {
        AVLsearch(root->left, id);
    }
    else
    {
        AVLsearch(root->right, id);
    }
}

int height(Arvore *root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

Arvore *rotate_left(Arvore *root)
{
    Arvore *y = root->right;
    Arvore *T2 = y->left;
    y->left = root;
    root->right = T2;
    // BF
    root->height = max(height(root->left), height(root->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    //RNK
	/*int somador = 0;
	while(T2 != NULL){
		somador += T2->rnk + T2->dispositivo->wei;
		T2 = T2->right;
	}
    y->rnk = root->rnk + root->dispositivo->wei + somador;*/
    updateRNK(root);
    updateRNK(y);
    return y;
}

Arvore *rotate_right(Arvore *root)
{
    Arvore *x = root->left;
    Arvore *T2 = x->right;
    x->right = root;
    root->left = T2;
    // BF
    root->height = max(height(root->left), height(root->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    //RNK
	updateRNK(root);
    updateRNK(x);
    return x;
}

int getBalance(Arvore *root)
{
    if (root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}
int getRNK(Arvore *root, int id)
{
    //printf("ENTER\n");
    if(root == NULL){
    	//printf("ROOT NULL\n");
        return 0;	
    }    
	if(root->dispositivo->id == id){
        //printf("IS NODE\n");
	    return root->rnk;
    }    
	else if(root->dispositivo->id < id){
        //printf("%d IS MENOR QUE %d\n", root->dispositivo->id, id);
	    //printf("ACUMULE %d %d\n", root->rnk, root->dispositivo->wei);
        return root->rnk + root->dispositivo->wei + getRNK(root->right, id);
    }    
    else{
        //printf("%d IS MAIOR QUE %d\n", root->dispositivo->id, id);
	    return getRNK(root->left, id);       
    }    
}

Arvore *inserir(Arvore *root, int *globalWei, int id, int wei)
{
    //
    if (root == NULL)
    {
        Dispositivo *dispositivo = (Dispositivo *)malloc(sizeof(Dispositivo));
        dispositivo->id = id;
        dispositivo->wei = wei;
        Arvore *no = (Arvore *)malloc(sizeof(Arvore));
        no->left = NULL;
        no->right = NULL;
        no->dispositivo = dispositivo;
        no->height = 1;
        no->rnk = 0;
        *globalWei += wei;
        return no;
    }
    else if (root->dispositivo->id == id)
    {
        root->dispositivo->wei += wei;
        *globalWei += wei;
        return root;
    }
    else if (root->dispositivo->id > id)
    {
    	root->left = inserir(root->left, globalWei, id, wei);
        root->rnk = root->rnk + wei; 
    }
    else if (root->dispositivo->id < id)
    {
        root->right = inserir(root->right, globalWei, id, wei);
    }
    //
    root->height = 1 + max(height(root->left), height(root->right));

    int bf = getBalance(root);
    if (bf > 1 && id < root->left->dispositivo->id)
        return rotate_right(root);
    if (bf < -1 && id > root->right->dispositivo->id)
        return rotate_left(root);
    if (bf > 1 && id > root->left->dispositivo->id)
    {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    if (bf < -1 && id < root->right->dispositivo->id)
    {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    return root;
}

int main()
{
    Arvore *root = NULL;
    // Inicio
    int id, wei, rnk, globalWei;
    char input[12];
    char command[4];
    int continuar = 1;
    //
    globalWei = 0;
    while (continuar)
    {
        scanf(" %11[^\n]s", &input);
        continuar = strcmp(input, "END");
        if (continuar)
        {
            sscanf(input, "%s %d %d", &command, &id, &wei);
            if (strcmp(command, "ADD") == 0)
            {
                root = inserir(root, &globalWei, id, wei);
                printf("%d\n", globalWei);
            }
            else if (strcmp(command, "WEI") == 0)
            {
                Arvore *search = AVLsearch(root, id);
                if (search != NULL)
                    printf("%d %d\n", search->dispositivo->wei, findDepth(root, id));
                else
                    printf("%d %d\n", 0, -1);
            }
            else if (strcmp(command, "RNK") == 0)
            {
            	if(root->dispositivo->id == id)
		            printf("%d\n", root->rnk);
            	else 
                    printf("%d\n", getRNK(root, id));
            }
            else if (strcmp(command, "DEB") == 0)
            {
                printf("Altura: %d\n", height(root));
                printf("Bytes: %d\n", globalWei);
                printf("Raiz: %d\n", root->dispositivo->id);
                in_ordem(root);
            }
        }
    }
    return 0;
}
