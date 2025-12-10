// solutions/problem2.c
// Compile: gcc -std=c11 -O2 -o solutions/problem2 solutions/problem2.c
// Run:     ./solutions/problem2            (reads inputs/input2.txt)
// Or:      ./solutions/problem2 path/to/input2.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 8192
#define OUT_PATH "solutions/problem2.out"
#define K_REMOVE 3

/* Portable strdup replacement */
static char *my_strdup(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char *r = malloc(len);
    if (r) memcpy(r, s, len);
    return r;
}

/* Reverse a null-terminated string in-place */
static void reverse_str(char *s) {
    if (!s) return;
    size_t i = 0, j = strlen(s);
    if (j == 0) return;
    j--; // last index
    while (i < j) {
        char t = s[i];
        s[i] = s[j];
        s[j] = t;
        i++; j--;
    }
}

/* Determine whether a character is a vowel (lowercase) */
static int is_vowel_lower(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

/* We will treat uppercase by converting to lowercase before checking,
   so both 'A' and 'a' count as vowels. */
int main(int argc, char **argv) {
    const char *inpath = "inputs/input2.txt";
    if (argc >= 2) inpath = argv[1];

    FILE *fin = fopen(inpath, "r");
    if (!fin) {
        perror("Failed to open input file");
        return 1;
    }

    char buf[MAX_LINE];
    if (!fgets(buf, sizeof(buf), fin)) {
        fprintf(stderr, "Input file empty or read error.\n");
        fclose(fin);
        return 1;
    }
    fclose(fin);

    /* Trim trailing newline and carriage return */
    size_t L = strlen(buf);
    while (L > 0 && (buf[L-1] == '\n' || buf[L-1] == '\r')) {
        buf[--L] = '\0';
    }

    /* For safety, copy into dynamically allocated string */
    char *s = my_strdup(buf);
    if (!s) {
        perror("malloc");
        return 1;
    }

    /* Step 1: Reverse the string (in-place) */
    reverse_str(s);

    /* Step 2: Remove every k-th character (k = K_REMOVE)
       Counting positions starting from 1 in the reversed string:
       remove characters at positions K_REMOVE, 2*K_REMOVE, 3*K_REMOVE, ...
    */
    size_t n = strlen(s);
    char *tmp = malloc(n + 1);
    if (!tmp) { perror("malloc"); free(s); return 1; }

    size_t write = 0;
    for (size_t i = 0; i < n; ++i) {
        size_t pos1 = i + 1; /* 1-based index */
        if (pos1 % K_REMOVE == 0) {
            /* skip this character */
            continue;
        } else {
            tmp[write++] = s[i];
        }
    }
    tmp[write] = '\0';

    /* Step 3: Shift each character by +2 (ordinal)
       We'll shift all characters, including non-letters, by adding 2 to their ASCII code.
       If you prefer letter wrap-around (e.g., 'z'->'b'), tell me and I will change.
    */
    for (size_t i = 0; i < write; ++i) {
        unsigned char ch = (unsigned char) tmp[i];
        ch = (unsigned char)(ch + 2);
        tmp[i] = (char) ch;
    }

    /* Step 4: Count vowel-class characters in the resulting sequence.
       We'll treat vowels case-insensitively by converting to lowercase.
    */
    int vowel_count = 0;
    for (size_t i = 0; i < write; ++i) {
        char c = tmp[i];
        char lc = (char) tolower((unsigned char)c);
        if (is_vowel_lower(lc)) vowel_count++;
    }

    /* Output the clue number */
    printf("%d\n", vowel_count);

    /* Also write to output file */
    FILE *fo = fopen(OUT_PATH, "w");
    if (fo) {
        fprintf(fo, "%d\n", vowel_count);
        fclose(fo);
    } else {
        perror("Warning: couldn't write output file");
    }

    free(s);
    free(tmp);
    return 0;
}
