#include <string.h>
#include <stdio.h>
#include <malloc.h>

#define max(a, b) (a > b ? a : b)


typedef struct _jogador
{
    char nome[8];
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

Jogador *AVLsearchPontuacao(Jogador *root, int pontuacao)
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


Jogador *AVLsearchNome(Jogador *root, char nome)
{
    if (root == NULL)
        return NULL;

    else if  if (strcmp(root->nome, nome) == 0)
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
    Jogador *y = root->right;
    Jogador *T2 = y->left;
    y->left = root;
    root->right = T2;
    // BF
    root->height = max(height(root->left), height(root->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

Jogador *rotate_right(Jogador *root)
{
    Jogador *x = root->left;
    Jogador *T2 = x->right;
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
        Jogador *no = (Jogador *)malloc(sizeof(Jogador));
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
    Jogador *root = NULL;
    // Inicio
    int pontuacao = 0;
    char nome[8];
    char input[30];
    char command[4];
    int continuar = 1;
    //
    int cases = 0;

    scanf("%d", &cases);
    for (int i = 0; i < cases; i++)
    {
        scanf(" %29[^\n]s", &input);
        //
        sscanf(input, "%s ", &command);
        if (strcmp(command, "ADD") == 0)
        {   
            sscanf(input, "%s %s %d", &command, &nome, &pontuacao);

            Jogador *search = AVLsearch(root, id);
            if (search != NULL)
                printf("%d %d\n", search->dispositivo->wei, findDepth(root, id));
            else
                printf("%d %d\n", 0, -1);

            root = inserir(root, nome, pontuacao);
            printf("%d\n", globalWei);
        }
        else if (strcmp(command, "WEI") == 0)
        {
            
        }
        
    }
    return 0;
}
