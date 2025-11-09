#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_generator.c"  // your function to generate Forth code

#define MAX_LINES 1
#define MAX_LINE_LEN 200

// get mine og get correct funktioner er skrevet af GPT

char ** get_correct(){

    FILE *fp = _popen("runforth.exe < input.txt", "r");

    char **lines = malloc(MAX_LINES * sizeof(char*));
    if (!lines) return NULL;

    for (int i = 0; i < MAX_LINES; i++) {
        lines[i] = malloc(MAX_LINE_LEN);
        lines[i][0] = '\0'; // initialize as empty string
    }

    char buffer[256];
    int lineIndex = 0;
    while (fgets(buffer, sizeof(buffer), fp) && lineIndex < MAX_LINES) {
        // copy first 15 chars to avoid overflow (+1 for null terminator)
        strncpy(lines[lineIndex], buffer, MAX_LINE_LEN - 1);
        lines[lineIndex][MAX_LINE_LEN - 1] = '\0'; // ensure null terminator
        lineIndex++;
    }

    _pclose(fp);
    // free memory
    // for (int i = 0; i < MAX_LINES; i++) free(lines[i]);
    // free(lines);

    return lines;
}   

char ** get_mine(){
    FILE *fp = _popen("main.exe", "r");

    char **lines = malloc(MAX_LINES * sizeof(char*));
    if (!lines) return NULL;

    for (int i = 0; i < MAX_LINES; i++) {
        lines[i] = malloc(MAX_LINE_LEN);
        lines[i][0] = '\0'; // initialize as empty string
    }

    char buffer[256];
    int lineIndex = 0;
    while (fgets(buffer, sizeof(buffer), fp) && lineIndex < MAX_LINES) {
        // copy first 15 chars to avoid overflow (+1 for null terminator)
        strncpy(lines[lineIndex], buffer, MAX_LINE_LEN - 1);
        lines[lineIndex][MAX_LINE_LEN - 1] = '\0'; // ensure null terminator
        lineIndex++;
    }

    _pclose(fp);

    // Example: print captured lines
    // for (int i = 0; i < lineIndex; i++) {
    //     printf("%s", lines[i]);
    // }

    // // free memory
    // for (int i = 0; i < MAX_LINES; i++) free(lines[i]);
    // free(lines);

    return lines;
}



int main(void) {
    node *forthCode = generate_test(1); // e.g., "10 . 20 30 * ."

    char * test = ll_to_string(forthCode);

    // skriv string til læsefil
    FILE * fptr = fopen("input.txt", "w");
    fputs(test, fptr);
    fclose(fptr);

    // kør læsefil på begge 
    char * res_correct = *get_correct();
    char * res_mine = *get_mine();

    printf("%s", (strcmp(res_mine, res_correct) == 0) ? "Equal" : "Not equal");
}
