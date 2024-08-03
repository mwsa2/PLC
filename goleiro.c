#include <string.h>
#include <stdio.h>
#include <malloc.h>

#define max(a, b) (a > b ? a : b)

typedef struct
{
    int id;
    int wei;
} Dispositivo;

typedef struct _arvore
{
    Dispositivo *dispositivo;
    int height;
    int rnk;
    int tam;
    struct _arvore *right;
    struct _arvore *left;
} Arvore;

void in_ordem(Arvore *root)
{
    if (root != NULL)
    {
        in_ordem(root->left);
        printf("%d %d %d\n", root->dispositivo->id, root->dispositivo->wei, root->rnk);
        in_ordem(root->right);
    }
}

Arvore *AVLsearch(Arvore *root, int id, int* count)
{
    if (root == NULL)
        return NULL;

    else if (root->dispositivo->id == id)
        return root;

    else if (root->dispositivo->id > id)
    {
        *count = *count + 1;
        AVLsearch(root->left, id, count);
    }
    else
    {
        *count = *count + 1;
        AVLsearch(root->right, id, count);
    }
}

int height(Arvore *root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

int isLeaf(Arvore *root){
    if(root->left == NULL && root->right == NULL)
        return 1;
    else    
        return 0;
}

int getBalance(Arvore *root)
{
    if (root == NULL)
        return 0;
    return height(root->left) - height(root->right);
}

void updateHeight(Arvore* root) {
    if (root == NULL)
        return;
    root->height = 1 + max(height(root->left), height(root->right));
}

void updateRNK(Arvore* root) {
    if (root == NULL)
        return;
    root->rnk = root->dispositivo->wei + (root->left ? root->left->rnk : 0) + (root->right ? root->right->rnk : 0);
}

void updateTam(Arvore* root) {
    if (root == NULL)
        return;
    root->tam = 1 + (root->left ? root->left->tam : 0) + (root->right ? root->right->tam : 0);
}

Arvore *rotate_left(Arvore *root)
{
    Arvore *R = root->right;
    Arvore *RL = R->left;
    R->left = root;
    root->right = RL;
    //
    updateHeight(root);
    updateHeight(R);
    updateRNK(root);
    updateRNK(R);
    return R;
}

Arvore *rotate_right(Arvore *root)
{
    Arvore *L = root->left;
    Arvore *LR = L->right;
    L->right = root;
    root->left = LR;
    updateHeight(root);
    updateHeight(L);
    updateRNK(root);
    updateRNK(L);
    return L;
}


int getRNK(Arvore *root, int id, int *ranking)
{
    if(root == NULL){
        printf("is Null\n");
    	return 0;	
    }    
	
    if(root->dispositivo->id > id){
        return getRNK(root->left, id, ranking);
    }    
	else if(root->dispositivo->id < id){
        ranking += root->rnk + (root->left ? root->left->rnk : 0);
        printf("ranking: %d\n", ranking);
        return 1 + root->tam - (root->right ? root->right->tam : 0) + getRNK(root->right, id, ranking);
    }    
    else{
        ranking += (root->left ? root->left->rnk : 0);
        printf("ranking: %d\n", ranking);
        return root->tam - (root->right ? root->right->tam : 0);      
    }    
}

int RNK(Arvore *root, int id) {
    int ranking = 0;
    getRNK(root, id, &ranking);
    printf("RNK: %d\n", ranking);
    return ranking;
}

int getRNK2(Arvore *root, int id)
{
    if(root == NULL){
    	return 0;	
    }    
	if(root->dispositivo->id == id){
        return root->rnk;
    }    
	else if(root->dispositivo->id < id){
        return root->rnk + root->dispositivo->wei + getRNK2(root->right, id);
    }    
    else{
        return getRNK2(root->left, id);       
    }    
}

Arvore *inserir(Arvore *root, int id, int wei)
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
        no->tam = 1;
        no->rnk = wei;
        return no;
    }
    else if (root->dispositivo->id == id)
    {
        root->dispositivo->wei += wei;
        updateRNK(root);
        return root;
    }
    else if (root->dispositivo->id > id)
    {
    	root->left = inserir(root->left, id, wei);
        root->tam++; 
    }
    else if (root->dispositivo->id < id)
    {
        root->right = inserir(root->right, id, wei);
        root->tam++;
    }
    //
    updateHeight(root);
    updateRNK(root);

    int balance = getBalance(root);

    if (balance > 1 && id < root->left->dispositivo->id)
        return rotate_right(root);

    if (balance < -1 && id > root->right->dispositivo->id)
        return rotate_left(root);

    if (balance > 1 && id > root->left->dispositivo->id) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < -1 && id < root->right->dispositivo->id) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

int main()
{
    Arvore *root = NULL;
    printf("root: %i\n", root);
    // Inicio
    int id, wei, rnk;
    int globalWei = 0;
    char input[12];
    char command[4];
    int continuar = 1;
    //
    while (continuar)
    {
        scanf(" %11[^\n]s", &input);
        continuar = strcmp(input, "END");
        if (continuar)
        {
            sscanf(input, "%s %d %d", &command, &id, &wei);
            if (strcmp(command, "ADD") == 0)
            {
                root = inserir(root, id, wei);
                globalWei += wei;
                printf("%d\n", globalWei);
            }
            else if (strcmp(command, "WEI") == 0)
            {
                int count = 0;
                Arvore *search = AVLsearch(root, id, &count); 
                //cout << aux->qbytes << " " << contp << endl;
                if (search != NULL)
                    printf("%d %d\n", search->dispositivo->wei, count);
                else
                    printf("%d %d\n", 0, -1);
            }
            else if (strcmp(command, "RNK") == 0)
            {
            	printf("%d\n", RNK(root, id));
                /*if(root->dispositivo->id == id)
		            printf("%d\n", root->rnk);
            	else 
                    printf("%d\n", getRNK2(root, id));*/
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
