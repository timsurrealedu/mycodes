#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_WORD_LEN 100
#define MAX_DESC_LEN 500
#define MAX_RESULTS 1000

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
    char *description;
} TrieNode;

TrieNode *createNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->isEndOfWord = 0;
    node->description = NULL;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

void readLine(char *buf, int maxLen) {
    if (fgets(buf, maxLen, stdin) != NULL) {
        int len = strlen(buf);
        if (len > 0 && buf[len - 1] == '\n')
            buf[len - 1] = '\0';
    }
}

void toLowerStr(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = tolower((unsigned char)s[i]);
}

int hasSpace(const char *s) {
    for (int i = 0; s[i]; i++)
        if (s[i] == ' ')
            return 1;
    return 0;
}

int countWords(const char *s) {
    int count = 0, inWord = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] != ' ') {
            if (!inWord) {
                count++;
                inWord = 1;
            }
        } else {
            inWord = 0;
        }
    }
    return count;
}

void pressEnter() {
    printf("Press enter to continue...");
    fflush(stdout);
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int trieInsert(TrieNode *root, const char *word, const char *desc) {
    TrieNode *curr = root;
    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';
        if (curr->children[idx] == NULL)
            curr->children[idx] = createNode();
        curr = curr->children[idx];
    }

    int isNew = !curr->isEndOfWord;
    curr->isEndOfWord = 1;

    if (curr->description)
        free(curr->description);
    curr->description = (char *)malloc(strlen(desc) + 1);
    strcpy(curr->description, desc);

    return isNew;
}

TrieNode *trieSearch(TrieNode *root, const char *word) {
    TrieNode *curr = root;
    for (int i = 0; word[i]; i++) {
        int idx = word[i] - 'a';
        if (curr->children[idx] == NULL)
            return NULL;
        curr = curr->children[idx];
    }
    return (curr->isEndOfWord) ? curr : NULL;
}

TrieNode *trieGetPrefixNode(TrieNode *root, const char *prefix) {
    TrieNode *curr = root;
    for (int i = 0; prefix[i]; i++) {
        int idx = prefix[i] - 'a';
        if (curr->children[idx] == NULL)
            return NULL;
        curr = curr->children[idx];
    }
    return curr;
}

void collectWords(TrieNode *node, char *prefix, int depth,
                  char results[][MAX_WORD_LEN], int *cnt) {
    if (*cnt >= MAX_RESULTS)
        return;

    if (node->isEndOfWord) {
        prefix[depth] = '\0';
        strcpy(results[*cnt], prefix);
        (*cnt)++;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            prefix[depth] = 'a' + i;
            collectWords(node->children[i], prefix, depth + 1, results, cnt);
        }
    }
}

void menuReleaseWord(TrieNode *root) {
    char word[MAX_WORD_LEN];
    char desc[MAX_DESC_LEN];

    while (1) {
        printf("Input a new slang word [Must be more than 1 characters and "
               "contains no space]: ");
        readLine(word, MAX_WORD_LEN);
        toLowerStr(word);

        if (strlen(word) <= 1) {
            continue;
        }
        if (hasSpace(word)) {
            continue;
        }
        break;
    }

    while (1) {
        printf(
            "Input a new slang word description [Must be more than 2 words]: ");
        readLine(desc, MAX_DESC_LEN);

        if (countWords(desc) <= 1) {
            continue;
        }
        break;
    }

    int isNew = trieInsert(root, word, desc);
    if (isNew)
        printf("Successfully released new slang word.\n");
    else
        printf("Successfully updated a slang word.\n");

    pressEnter();
}

void menuSearchWord(TrieNode *root) {
    char word[MAX_WORD_LEN];

    while (1) {
        printf("Input a slang word to be searched [Must be more than 1 "
               "characters and contains no space]: ");
        readLine(word, MAX_WORD_LEN);
        toLowerStr(word);

        if (strlen(word) <= 1)
            continue;
        if (hasSpace(word))
            continue;
        break;
    }

    TrieNode *result = trieSearch(root, word);
    if (result == NULL) {
        printf("There is no word \"%s\" in the dictionary.\n", word);
    } else {
        printf("Slang word  : %s\n", word);
        printf("Description : %s\n", result->description);
    }

    pressEnter();
}

void menuPrefixSearch(TrieNode *root) {
    char prefix[MAX_WORD_LEN];
    char buf[MAX_WORD_LEN];

    printf("Input a prefix to be searched: ");
    readLine(prefix, MAX_WORD_LEN);
    toLowerStr(prefix);

    TrieNode *prefixNode = trieGetPrefixNode(root, prefix);
    if (prefixNode == NULL) {
        printf("There is no prefix \"%s\" in the dictionary.\n", prefix);
        pressEnter();
        return;
    }

    char results[MAX_RESULTS][MAX_WORD_LEN];
    int cnt = 0;

    strcpy(buf, prefix);
    collectWords(prefixNode, buf, strlen(prefix), results, &cnt);

    if (cnt == 0) {
        printf("There is no prefix \"%s\" in the dictionary.\n", prefix);
    } else {
        printf("Words starts with \"%s\":\n", prefix);
        for (int i = 0; i < cnt; i++)
            printf("%d. %s\n", i + 1, results[i]);
    }

    pressEnter();
}

void menuViewAll(TrieNode *root) {
    char results[MAX_RESULTS][MAX_WORD_LEN];
    char buf[MAX_WORD_LEN];
    int cnt = 0;

    buf[0] = '\0';
    collectWords(root, buf, 0, results, &cnt);

    if (cnt == 0) {
        printf("There is no slang word yet in the dictionary.\n");
    } else {
        printf("List of all slang words in the dictionary:\n");
        for (int i = 0; i < cnt; i++)
            printf("%d. %s\n", i + 1, results[i]);
    }

    pressEnter();
}

int main() {
    TrieNode *root = createNode();
    int choice;
    char inputBuf[16];

    while (1) {
        printf("\n===== BOOGLE SLANG DICTIONARY =====\n");
        printf("1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix word\n");
        printf("4. View all slang words\n");
        printf("5. Exit\n");
        printf("Choose menu: ");

        readLine(inputBuf, sizeof(inputBuf));
        choice = atoi(inputBuf);

        switch (choice) {
        case 1:
            menuReleaseWord(root);
            break;
        case 2:
            menuSearchWord(root);
            break;
        case 3:
            menuPrefixSearch(root);
            break;
        case 4:
            menuViewAll(root);
            break;
        case 5:
            printf("Thank you... Have a nice day :)\n");
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
