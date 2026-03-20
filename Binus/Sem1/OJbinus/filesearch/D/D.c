#include <stdio.h>
#include <string.h>

// Define a structure to hold dictionary entries
// Constraints: Word length <= 50 [cite: 23]
struct Dictionary {
    char shortWord[55];
    char originalWord[55];
};

int main() {
    // 1. Open the file "testdata.in" for reading [cite: 3]
    FILE *fp = fopen("testdata.in", "r");
    
    if (fp == NULL) {
        printf("Error: Could not open testdata.in\n");
        return 1;
    }

    // 2. Read the number of data in the dictionary (T) [cite: 12]
    int T;
    fscanf(fp, "%d", &T);

    // Create array of structs based on constraint T <= 100 [cite: 20]
    struct Dictionary dict[105];

    // 3. Read the dictionary entries [cite: 13]
    for (int i = 0; i < T; i++) {
        // Format: short#original
        // %[^#] reads everything until the '#' character
        // The space before %[^#] consumes the newline from the previous line
        fscanf(fp, " %[^#]#%s", dict[i].shortWord, dict[i].originalWord);
    }

    // 4. Read the number of test cases (TC) [cite: 14]
    int TC;
    fscanf(fp, "%d", &TC);
    
    // Consume the newline character left in the buffer after reading the integer TC
    fgetc(fp); 

    // Buffer for reading sentences. Constraints say sentences in TC <= 100, 
    // but we use a safe buffer size to ensure we capture the whole line.
    char sentence[1005];

    // 5. Process each test case
    for (int i = 1; i <= TC; i++) {
        // Read the entire sentence line [cite: 14]
        if (fgets(sentence, sizeof(sentence), fp) == NULL) {
            break;
        }

        // Remove the trailing newline character added by fgets
        sentence[strcspn(sentence, "\n")] = 0;

        // Print the Case number format 
        printf("Case #%d:\n", i);

        // Tokenize the sentence by space to check individual words
        char *token = strtok(sentence, " ");
        
        int firstWord = 1;

        while (token != NULL) {
            // Print space between words (but not before the first word)
            if (!firstWord) {
                printf(" ");
            }

            // Search for the token in the dictionary
            int found = 0;
            for (int j = 0; j < T; j++) {
                // strcmp returns 0 if strings are identical
                if (strcmp(token, dict[j].shortWord) == 0) {
                    printf("%s", dict[j].originalWord); // Print translated word
                    found = 1;
                    break;
                }
            }

            // If word does not exist in dictionary, display inputted word unchanged 
            if (!found) {
                printf("%s", token);
            }
        
            // Move to the next word
            token = strtok(NULL, " ");
            firstWord = 0;
        }
        // Print newline at the end of the translated sentence
        printf("\n");
    }

    // Close the file
    fclose(fp);

    return 0;
}