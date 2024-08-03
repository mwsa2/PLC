#include <iostream>
#define endl '\n'
using namespace std;

struct Node {
    int height;
    int rnk;
    int tam;
    int qbytes;
    int id;
    Node* left;
    Node* right;
};

Node* rootprime = nullptr;

int getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void updateHeight(Node* node) {
    if (node == nullptr)
        return;
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

void updateSize(Node* node) {
    if (node == nullptr)
        return;
    node->tam = 1 + (node->left ? node->left->tam : 0) + (node->right ? node->right->tam : 0);
}

void updateRNK(Node* node) {
    if (node == nullptr)
        return;
    node->rnk = node->qbytes + (node->left ? node->left->rnk : 0) + (node->right ? node->right->rnk : 0);
}

Node* left_Rotate(Node* root) {
    Node* R = root->right;
    Node* RL = R->left;
    R->left = root;
    root->right = RL;
    updateHeight(root);
    updateHeight(R);
    updateRNK(root);
    updateRNK(R);
    return R;
}

Node* right_Rotate(Node* root) {
    Node* L = root->left;
    Node* LR = L->right;
    L->right = root;
    root->left = LR;
    updateHeight(root);
    updateHeight(L);
    updateRNK(root);
    updateRNK(L);
    return L;
}

Node* avl_insert(Node* root, int id, int qbytes) {
    if (root == nullptr) {
        Node* N = new Node;
        N->id = id;
        N->rnk = qbytes;
        N->qbytes = qbytes;
        N->left = nullptr;
        N->right = nullptr;
        N->height = 1;
        N->tam = 1;
        return N;
    }

    if (id < root->id) {
        root->left = avl_insert(root->left, id, qbytes);
        root->tam++;
    } else if (id > root->id) {
        root->right = avl_insert(root->right, id, qbytes);
        root->tam++;
    } else {
        root->qbytes += qbytes;
        updateRNK(root);
        return root;
    }

    updateHeight(root);
    updateRNK(root);

    int balance = getBalance(root);

    if (balance > 1 && id < root->left->id)
        return right_Rotate(root);

    if (balance < -1 && id > root->right->id)
        return left_Rotate(root);

    if (balance > 1 && id > root->left->id) {
        root->left = left_Rotate(root->left);
        return right_Rotate(root);
    }

    if (balance < -1 && id < root->right->id) {
        root->right = right_Rotate(root->right);
        return left_Rotate(root);
    }

    return root;
}

Node* binary_search(Node* root, int id, int* cont) {
    if (root == nullptr)
        return nullptr;

    if (root->id == id)
        return root;

    if (id < root->id) {
        *cont = *cont + 1;
        return binary_search(root->left, id, cont);
    } else {
        *cont = *cont + 1;
        return binary_search(root->right, id, cont);
    }
}

void ADD(int id, int qbytes, int* cont) {
    rootprime = avl_insert(rootprime, id, qbytes);
    *cont = *cont + qbytes;
    cout << *cont << endl;
}

void WEI(int id) {
    int contp = 0;
    Node* aux = binary_search(rootprime, id, &contp);
    if (aux == nullptr)
        cout << "0 -1" << endl;
    else
        cout << aux->qbytes << " " << contp << endl;
}

int Rank(Node* node, int id, int& ranking) {
    if (node == nullptr)
        return 0;

    if (id < node->id) {
        return Rank(node->left, id, ranking);
    } else if (id > node->id) {
        ranking += node->qbytes + (node->left ? node->left->rnk : 0);
        return 1 + node->tam - (node->right ? node->right->tam : 0) + Rank(node->right, id, ranking);
    } else {
        ranking += (node->left ? node->left->rnk : 0);
        return node->tam - (node->right ? node->right->tam : 0);
    }
}

int RNK(int id) {
    int ranking = 0;
    Rank(rootprime, id, ranking);
    return ranking;
}

int main() {
    string input;
    int cont = 0;
    while (input != "END") {
        cin >> input;
        if (input != "END") {
            if (input == "ADD") {
                int id, qbytes;
                cin >> id >> qbytes;
                ADD(id, qbytes, &cont);
            } else if (input == "WEI") {
                int id;
                cin >> id;
                WEI(id);
            } else if (input == "RNK") {
                int id;
                cin >> id;
                cout << RNK(id) << endl;
            }
        }
    }
    
    return 0;
}
