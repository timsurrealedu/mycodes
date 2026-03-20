#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Structure to keep track of products
struct Product {
    char name[55]; // Max length 50 based on constraints [cite: 28]
    long long stock; // Using long long to ensure it fits [cite: 29]
};

int main() {
    // Open the file testdata.in for reading 
    FILE *fp = fopen("testdata.in", "r");
    
    if (fp == NULL) {
        printf("Error: testdata.in not found.\n");
        return 1;
    }

    int T;
    // Read number of test cases [cite: 15]
    fscanf(fp, "%d", &T);

    for (int t = 1; t <= T; t++) {
        int N;
        // Read number of transactions for this case [cite: 16]
        fscanf(fp, "%d\n", &N); // \n consumes the newline after the number

        struct Product products[105];
        int productCount = 0;

        // Process transactions
        for (int i = 0; i < N; i++) {
            char type[10];
            char tempName[55];
            int qty;

            // Parse format: type#name#quantity [cite: 11]
            // %[^#] reads string until '#' is encountered
            fscanf(fp, "%[^#]#%[^#]#%d\n", type, tempName, &qty);

            // Check if product already exists in our array
            int foundIndex = -1;
            for (int j = 0; j < productCount; j++) {
                if (strcmp(products[j].name, tempName) == 0) {
                    foundIndex = j;
                    break;
                }
            }

            // If not found, add it to the array
            if (foundIndex == -1) {
                strcpy(products[productCount].name, tempName);
                products[productCount].stock = 0;
                foundIndex = productCount;
                productCount++;
            }

            // Update stock based on type (buy/sell) 
            if (strcmp(type, "buy") == 0) {
                products[foundIndex].stock += qty;
            } else if (strcmp(type, "sell") == 0) {
                products[foundIndex].stock -= qty;
            }
        }

        printf("Case #%d:\n", t);

        // Validation Phase
        // Check if ANY product has negative stock
        int isAllValid = 1;
        for (int i = 0; i < productCount; i++) {
            if (products[i].stock < 0) {
                isAllValid = 0;
                break;
            }
        }

        // Output Phase
        if (isAllValid) {
            // Scenario A: All stocks are valid. Print all products. 
            for (int i = 0; i < productCount; i++) {
                printf("%s - %lld\n", products[i].name, products[i].stock);
            }
        } else {
            // Scenario B: Some stocks are invalid. 
            // ONLY print error messages for invalid products. 
            for (int i = 0; i < productCount; i++) {
                if (products[i].stock < 0) {
                    printf("stock is not enough for product %s\n", products[i].name);
                }
            }
        }
    }

    fclose(fp);
    return 0;
}