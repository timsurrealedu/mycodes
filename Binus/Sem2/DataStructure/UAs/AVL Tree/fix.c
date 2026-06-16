#include <stdio.h>
#include <stdlib.h>

// ==========================================
// 1. STRUKTUR NODE & FUNGSI BANTUAN
// ==========================================
typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

int maxValue(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(Node* n) {
    if (n == NULL) return 0;
    return n->height;
}

int getBalance(Node* n) {
    if (n == NULL) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // Node baru selalu jadi leaf (tinggi 1)

    return newNode; // Jangan sampai lupa return!
}

// Fungsi cari nilai terkecil (untuk Kasus 3 Delete)
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// ==========================================
// 2. FUNGSI ROTASI (OPERASI PENYEMBUHAN)
// ==========================================
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right; // T2 adalah "Anak Titipan"

    // Proses rotasi
    x->right = y;
    y->left = T2; // Aturan Emas: Titipkan anak

    // Update tinggi node
    y->height = maxValue(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = maxValue(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // x menjadi root baru dari subtree ini
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left; // T2 adalah "Anak Titipan"

    // Proses rotasi
    y->left = x;
    x->right = T2; // Aturan Emas: Titipkan anak

    // Update tinggi node
    x->height = maxValue(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = maxValue(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // y menjadi root baru dari subtree ini
}

// ==========================================
// 3. FUNGSI INSERT (MEMASUKKAN DATA)
// ==========================================
Node* insert(Node* n, int key) {
    // 1. Insert BST Biasa
    if (n == NULL) {
        return createNode(key);
    }

    if (key < n->key) {
        n->left = insert(n->left, key);
    } else if (key > n->key) {
        n->right = insert(n->right, key);
    } else {
        return n; // AVL tidak menerima duplikat
    }

    // 2. Update Tinggi
    n->height = 1 + maxValue(getHeight(n->left), getHeight(n->right));

    // 3. Cek Balance Factor
    int balance = getBalance(n);

    // 4. Rotasi jika sakit (Deteksi via KEY)
    // LL Case
    if (balance > 1 && key < n->left->key) {
        return rightRotate(n);
    }
    // RR Case
    if (balance < -1 && key > n->right->key) {
        return leftRotate(n);
    }
    // LR Case
    if (balance > 1 && key > n->left->key) {
        n->left = leftRotate(n->left);
        return rightRotate(n);
    }
    // RL Case
    if (balance < -1 && key < n->right->key) {
        n->right = rightRotate(n->right);
        return leftRotate(n);
    }

    return n;
}

// ==========================================
// 4. FUNGSI DELETE (MENGHAPUS DATA)
// ==========================================
Node* deleteNode(Node* root, int key) {
    // 1. Delete BST Biasa
    if (root == NULL) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node ditemukan! Eksekusi penghapusan
        if ((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                // Kasus 0 Anak
                temp = root;
                root = NULL;
            } else {
                // Kasus 1 Anak
                *root = *temp;
            }
            free(temp);
        } else {
            // Kasus 2 Anak
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // Jika setelah dihapus pohon kosong
    if (root == NULL) return root;

    // 2. Update Tinggi
    root->height = 1 + maxValue(getHeight(root->left), getHeight(root->right));

    // 3. Cek Balance Factor
    int balance = getBalance(root);

    // 4. Rotasi jika sakit (Deteksi via BALANCE ANAK)
    // LL Case (Perhatikan >= 0)
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    // LR Case (Perhatikan < 0)
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // RR Case (Perhatikan <= 0)
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    // RL Case (Perhatikan > 0)
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// ==========================================
// 5. FUNGSI UTILITY (UNTUK TESTING)
// ==========================================
// Print Pre-Order (Root -> Kiri -> Kanan)
// Memudahkan melihat struktur pohon secara hierarki
void preOrder(Node *root) {
    if (root != NULL) {
        printf("%d(H:%d BF:%d) ", root->key, root->height, getBalance(root));
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node *root = NULL;

    printf("--- Simulasi AVL Tree ---\n\n");

    // Simulasi Insert: Memicu LL, RR, LR, RL
    int arr[] = {50, 30, 20, 40, 70, 60, 80};
    int n = sizeof(arr)/sizeof(arr[0]);

    for(int i = 0; i < n; i++) {
        root = insert(root, arr[i]);
        printf("Insert %d selesai.\n", arr[i]);
    }

    printf("\nPohon setelah semua insert (Pre-Order):\n");
    preOrder(root);
    printf("\n");

    // Simulasi Delete
    printf("\nMenghapus node 20...\n");
    root = deleteNode(root, 20);

    printf("Pohon setelah 20 dihapus (Pre-Order):\n");
    preOrder(root);
    printf("\n");

    return 0;
}
