#include <string.h>
#include <stdio.h>
#include <malloc.h>

#define max(a, b) (a > b ? a : b)


typedef struct _jogador
{
    string nome;
    int pontuacao;
    int height;
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

int height(Jogador *root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

Jogador *AVLsearch(Jogador *root, int pontuacao)
{
    if (root == NULL)
        return NULL;

    else if (root->pontuacao == pontuacao)
        return root;

    else if (root->pontuacao > pontuacao)
    {
        AVLsearch(root->left, pontuacao);
    }
    else
    {
        AVLsearch(root->right, pontuacao);
    }
}


Jogador *rotate_left(Jogador *root)
{
    Arvore *y = root->right;
    Arvore *T2 = y->left;
    y->left = root;
    root->right = T2;
    // BF
    root->height = max(height(root->left), height(root->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

Jogador *rotate_right(Jogador *root)
{
    Arvore *x = root->left;
    Arvore *T2 = x->right;
    x->right = root;
    root->left = T2;
    // BF
    root->height = max(height(root->left), height(root->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

int getBalance(Jogador *root)
{
    if (root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}

Jogador *inserir(Jogador *root, string nome, int pontuacao)
{
    //
    if (root == NULL)
    {
        Arvore *no = (Arvore *)malloc(sizeof(Arvore));
        no->left = NULL;
        no->right = NULL;
        no->nome = nome;
        no->pontuacao = pontuacao;
	no->height = 1;
        return no;
    }
    else if (root->pontuacao == pontuacao)
    {
        root->pontuacao = pontuacao;
        return root;
    }
    else if (root->pontuacao > pontuacao)
    {
    	root->left = inserir(root->left, nome, pontuacao);
    }
    else if (root->pontuacao < pontuacao)
    {
        root->right = inserir(root->right, nome, pontuacao);
    }
    
    int bf = getBalance(root);
    if (bf > 1 && pontuacao < root->pontuacao)
        return rotate_right(root);
    if (bf < -1 && pontuacao > root->pontuacao)
        return rotate_left(root);
    if (bf > 1 && pontuacao > root->pontuacao)
    {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    if (bf < -1 && pontuacao < root->pontuacao)
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
    int pontuacao = 0;
    char nome[60];
    char input[12];
    char command[4];
    int continuar = 1;
    //
	aqui
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
