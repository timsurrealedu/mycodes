#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define TABLE_SIZE 10

// 1. The Entry (The "Node")
typedef struct Entry {
    char *key;           // The "Label" (e.g., "Alice")
    char *value;         // The "Data" (e.g., "555-0101")
    struct Entry *next;  // Pointer for collisions (The "Chain")
} Entry;

// 2. The Hash Table Structure
typedef struct {
    Entry *buckets[TABLE_SIZE]; // Array of pointers to Entries
} HashTable;

// 3. The "Scrambler" (djb2 Hash Function)
unsigned long hash(unsigned char *str) {
    unsigned long running_total = 5381;
    int c;
    while ((c = *str++)) {
        // (running_total * 33) + ASCII value of char
        running_total = ((running_total << 5) + running_total) + c;
    }
    return running_total;
}

// 4. Create and Initialize Table
HashTable* create_table() {
    HashTable *table = malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL; // Start with empty buckets
    }
    return table;
}

// 5. Insert a Key-Value Pair
void insert(HashTable *table, char *key, char *value) {
    // Stage A: Get the Index (Shrink-Ray)
    unsigned int index = hash((unsigned char*)key) % TABLE_SIZE;

    // Stage B: Create the new Entry
    Entry *new_entry = malloc(sizeof(Entry));
    new_entry->key = strdup(key);     // Copy string to heap
    new_entry->value = strdup(value); // Copy string to heap

    // Stage C: Handle Collision (Insert at the Head of the list)
    new_entry->next = table->buckets[index];
    table->buckets[index] = new_entry;

    printf("Inserted: [%s : %s] at Index: %d\n", key, value, index);
}

// 6. Search for a Value by Key
char* search(HashTable *table, char *key) {
    unsigned int index = hash((unsigned char*)key) % TABLE_SIZE;
    Entry *temp = table->buckets[index];

    // Walk the linked list in the bucket
    while (temp != NULL) {
        if (strcmp(temp->key, key) == 0) {
            return temp->value; // Found it!
        }
        temp = temp->next;
    }
    return NULL; // Not found
}

// 7. Cleanup Memory (Crucial in C!)
void free_table(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry *entry = table->buckets[i];
        while (entry != NULL) {
            Entry *prev = entry;
            entry = entry->next;
            free(prev->key);
            free(prev->value);
            free(prev);
        }
    }
    free(table);
}

// --- Main Execution ---
int main() {
    HashTable *my_phonebook = create_table();

    // Adding data
    insert(my_phonebook, "Alice", "555-0101");
    insert(my_phonebook, "Bob", "555-0202");
    insert(my_phonebook, "Charlie", "555-0303");

    // Looking up data
    printf("\nSearching for Bob's number...\n");
    char *bobs_num = search(my_phonebook, "Bob");
    
    if (bobs_num) {
        printf("Result: %s\n", bobs_num);
    } else {
        printf("Not found.\n");
    }

    // Cleanup
    free_table(my_phonebook);
    return 0;
}