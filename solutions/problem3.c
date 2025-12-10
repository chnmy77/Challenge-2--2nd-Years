// solutions/problem3.c
// Compile: gcc -std=c11 -O2 -o solutions/problem3 solutions/problem3.c
// Run:     ./solutions/problem3        (reads inputs/states.txt)
// Or:      ./solutions/problem3 path/to/states.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define OUT_PATH "solutions/problem3.out"
#define MAX_LINE 8192

/* Simple is_prime check for positive integers */
int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0) return 0;
    int r = (int) sqrt((double)n);
    for (int i = 3; i <= r; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char **argv) {
    const char *inpath = "inputs/states.txt";
    if (argc >= 2) inpath = argv[1];

    FILE *fin = fopen(inpath, "r");
    if (!fin) {
        perror("Failed to open states input file");
        return 1;
    }

    /* Read full file into buffer and parse integers separated by whitespace */
    char buf[MAX_LINE];
    size_t read = fread(buf, 1, sizeof(buf)-1, fin);
    fclose(fin);
    if (read == 0) {
        fprintf(stderr, "states.txt is empty or unreadable\n");
        return 1;
    }
    buf[read] = '\0';

    /* Tokenize and parse integers */
    int values[1024];
    size_t cnt = 0;
    char *tok = strtok(buf, " \t\r\n");
    while (tok && cnt < sizeof(values)/sizeof(values[0])) {
        /* allow negative? problem seems positive; we will parse ints nonetheless */
        int v = atoi(tok);
        values[cnt++] = v;
        tok = strtok(NULL, " \t\r\n");
    }

    /* State machine interpretation:
       states = {0,1,2,3} ; start=0 ; terminal=3
       - prime -> direct transition to terminal (0 -> 3)
       - even (non-prime) -> advance +1 state per step until terminal (so eventually reach 3)
       - odd composite -> do not advance (remain at 0)
    */
    size_t terminated_in_terminal = 0;
    for (size_t i = 0; i < cnt; ++i) {
        int x = values[i];
        /* classify */
        if (is_prime(x)) {
            /* prime: direct jump to terminal */
            int final_state = 3;
            if (final_state == 3) terminated_in_terminal++;
        } else if (x % 2 == 0) {
            /* even (and not prime): will advance step-by-step to the terminal */
            /* starting at state 0, it needs 3 steps to reach state 3 -> always reaches terminal */
            int final_state = 3;
            if (final_state == 3) terminated_in_terminal++;
        } else {
            /* odd composite or 1 or <=0: fallback rule -> does not advance */
            /* final_state remains 0; does not terminate */
        }
    }

    printf("%zu\n", terminated_in_terminal);

    FILE *fo = fopen(OUT_PATH, "w");
    if (fo) {
        fprintf(fo, "%zu\n", terminated_in_terminal);
        fclose(fo);
    } else {
        perror("Warning: could not write output file");
    }

    return 0;
}
