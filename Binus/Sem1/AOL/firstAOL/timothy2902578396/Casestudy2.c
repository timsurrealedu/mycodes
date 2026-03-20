//Timothy Sebastian Darmawan - 2902578396
//Case study 2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char name[100];
    char city[100];
    int cost;
    char currency[100];
    int priceRange;
    float rating;
    char ratingText[100];
    int votes;
}Restaurant;

Restaurant records[10000];
int totalRows = 0;

void readCSV(){
    FILE* fp = fopen("restaurant(in).csv", "r");
    if(fp==NULL){
        printf("Cannot access file\n");
        exit(1);
    }

    char line[1024];
    fgets(line, 1024, fp); 

    while (fgets(line, 1024, fp) && totalRows < 10000) {
        char* token = strtok(line, ",");
        if (token) strcpy(records[totalRows].name, token);
        
        token = strtok(NULL, ",");
        if (token) strcpy(records[totalRows].city, token);
        
        token = strtok(NULL, ",");
        if (token) records[totalRows].cost = atoi(token);
        
        token = strtok(NULL, ",");
        if (token) strcpy(records[totalRows].currency, token);
        
        token = strtok(NULL, ",");
        if (token) records[totalRows].priceRange = atoi(token);
        
        token = strtok(NULL, ",");
        if (token) records[totalRows].rating = atof(token);
        
        token = strtok(NULL, ",");
        if (token) strcpy(records[totalRows].ratingText, token);
        
        token = strtok(NULL, ",");
        if (token) records[totalRows].votes = atoi(token);

        totalRows++;
    }
    fclose(fp);
}

void printHeader() {
    printf("\n%-30s %-20s %-10s %-20s %-8s %-8s %-12s %-8s\n", 
           "Restaurant name", "City", "Cost", "Currency", "Price", "Rating", "Text", "Votes");
}

void printRow(Restaurant r) {
    printf("%-30.30s %-20.20s %-10d %-20.20s %-8d %-8.1f %-12s %-8d\n", 
           r.name, r.city, r.cost, r.currency, r.priceRange, r.rating, r.ratingText, r.votes);
}
void display(int n){
    if (n <= 0) return;
    int limit = (n > totalRows) ? totalRows : n;
    printHeader();
    for (int i = 0; i < limit; i++) {
        printRow(records[i]);
    }
}

void search(char* column, char* query) {
    int found = 0;
    for (int i = 0; i < totalRows; i++) {
        int match = 0;
        if (strcmp(column, "Restaurant name") == 0 && strcmp(records[i].name, query) == 0) match = 1;
        else if (strcmp(column, "City") == 0 && strcmp(records[i].city, query) == 0) match = 1;
        else if (strcmp(column, "Rating text") == 0 && strcmp(records[i].ratingText, query) == 0) match = 1;
        else if (strcmp(column, "Currency") == 0 && strcmp(records[i].currency, query) == 0) match = 1;

        if (match) {
            if (!found) printHeader();
            printRow(records[i]);
            found = 1;
        }
    }
    if (!found) printf("\nData not found!\n");
}

int compare(const void* a, const void* b, char* column, int desc) {
    Restaurant* r1 = (Restaurant*)a;
    Restaurant* r2 = (Restaurant*)b;
    int result = 0;

    if (strcmp(column, "Rating text") == 0) result = strcmp(r1->ratingText, r2->ratingText);
    else if (strcmp(column, "Rating") == 0) result = (r1->rating > r2->rating) - (r1->rating < r2->rating);

    return desc ? -result : result;
}

void sortData(char* column, char* order) {
    int desc = (strcasecmp(order, "desc") == 0);
    
    for (int i = 0; i < totalRows - 1; i++) {
        for (int j = 0; j < totalRows - i - 1; j++) {
            int shouldSwap = 0;
            
            if (strcmp(column, "Rating") == 0) {
                shouldSwap = desc ? (records[j].rating < records[j+1].rating) : (records[j].rating > records[j+1].rating);
            } else if (strcmp(column, "Votes") == 0) {
                shouldSwap = desc ? (records[j].votes < records[j+1].votes) : (records[j].votes > records[j+1].votes);
            } else if (strcmp(column, "Cost for two") == 0) {
                shouldSwap = desc ? (records[j].cost < records[j+1].cost) : (records[j].cost > records[j+1].cost);
            } 
            else if (strcmp(column, "Rating text") == 0) {
                int cmp = strcmp(records[j].ratingText, records[j+1].ratingText);
                shouldSwap = desc ? (cmp < 0) : (cmp > 0);
            } else if (strcmp(column, "Restaurant name") == 0) {
                int cmp = strcmp(records[j].name, records[j+1].name);
                shouldSwap = desc ? (cmp < 0) : (cmp > 0);
            }

            if (shouldSwap) {
                Restaurant temp = records[j];
                records[j] = records[j+1];
                records[j+1] = temp;
            }
        }
    }
    display(10);
}

void exportCSV(char* filename) {
    char fullFilename[100];
    sprintf(fullFilename, "%s.csv", filename);
    FILE* fp = fopen(fullFilename, "w");
    
    fprintf(fp, "Restaurant name,City,Cost for two,Currency,Price range,Rating,Rating text,Votes\n");
    for (int i = 0; i < totalRows; i++) {
        fprintf(fp, "%s,%s,%d,%s,%d,%.1f,%s,%d\n", 
                records[i].name, records[i].city, records[i].cost, records[i].currency, 
                records[i].priceRange, records[i].rating, records[i].ratingText, records[i].votes);
    }
    fclose(fp);
    printf("Data successfully written to file %s!\n", fullFilename);
}

int main(){
    readCSV();
    int choice;
    
    while(1){
        printf("What do you want to do?\n1. Display Data\n2. Search Data\n3. Sort Data\n4. Export Data\n5. Exit\nYour choice: ");
        scanf("%d", &choice);getchar();
        if(choice == 1){
            int n;
            printf("Number of rows: ");
            scanf("%d", &n);
            display(n);
        }
        else if(choice ==2){
            printf("Choose column: ");
            char col[100], query[100];
            fgets(col, 100, stdin); col[strcspn(col, "\n")] = 0;
            printf("What data do you want to find? ");
            fgets(query, 100, stdin); query[strcspn(query, "\n")] = 0;
            search(col, query);
        } else if (choice == 3) {
            char col[100], order[100];
            printf("Choose column: ");
            fgets(col, 100, stdin); col[strcspn(col, "\n")] = 0;
            printf("Sort ascending (asc) or descending (desc)? ");
            scanf("%s", order);
            sortData(col, order);
        } else if (choice == 4) {
            char filename[100];
            printf("File name: ");
            scanf("%s", filename);
            exportCSV(filename);
        } else if (choice == 5) {
            break;
        }
    }
    return 0;
}

