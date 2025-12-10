// solutions/problem1.c
// Compile: gcc -std=c11 -O2 -o solutions/problem1 solutions/problem1.c
// Usage:
//   ./solutions/problem1               (reads inputs/grid.txt and inputs/directions.txt)
// OR
//   ./solutions/problem1 grid.txt dirs.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 4096
#define OUT_PATH "solutions/problem1.out"

// trim newline and trailing spaces
static void rtrim(char *s) {
    int len = strlen(s);
    while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r' || isspace((unsigned char)s[len-1])))
        s[--len] = '\0';
}

int main(int argc, char **argv) {
    const char *grid_path = "inputs/grid.txt";
    const char *dir_path  = "inputs/directions.txt";
    if (argc >= 3) {
        grid_path = argv[1];
        dir_path = argv[2];
    }

    // Read grid lines into dynamic array
    FILE *fg = fopen(grid_path, "r");
    if (!fg) {
        perror("Failed to open grid file");
        return 1;
    }

    char **rows = NULL;
    size_t rows_cap = 0, rows_cnt = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fg)) {
        rtrim(line);
        // skip empty lines
        if (line[0] == '\0') continue;
        if (rows_cnt + 1 > rows_cap) {
            size_t newcap = rows_cap == 0 ? 8 : rows_cap * 2;
            char **tmp = realloc(rows, newcap * sizeof(char*));
            if (!tmp) { perror("realloc"); fclose(fg); return 1; }
            rows = tmp; rows_cap = newcap;
        }
        rows[rows_cnt] = strdup(line);
        if (!rows[rows_cnt]) { perror("strdup"); fclose(fg); return 1; }
        rows_cnt++;
    }
    fclose(fg);

    if (rows_cnt == 0) {
        fprintf(stderr, "Grid file empty or no rows found.\n");
        return 1;
    }

    // ensure all rows have same length (we'll accept differing lengths but handle safely)
    size_t cols = strlen(rows[0]);
    for (size_t i = 1; i < rows_cnt; ++i)
        if (strlen(rows[i]) != cols) {
            // Allow different lengths but proceed with min length for operations
            // (You can choose to error out instead.)
            // Here we choose min length across rows:
            if (strlen(rows[i]) < cols) cols = strlen(rows[i]);
        }

    // Read directions file (single line, tokens separated by spaces)
    FILE *fd = fopen(dir_path, "r");
    if (!fd) {
        perror("Failed to open directions file");
        // free memory
        for (size_t i=0;i<rows_cnt;++i) free(rows[i]);
        free(rows);
        return 1;
    }
    char dirs_line[MAX_LINE];
    if (!fgets(dirs_line, sizeof(dirs_line), fd)) {
        fprintf(stderr, "Directions file empty.\n");
        fclose(fd);
        for (size_t i=0;i<rows_cnt;++i) free(rows[i]);
        free(rows);
        return 1;
    }
    fclose(fd);
    rtrim(dirs_line);

    // Tokenize directions
    char *tokens[MAX_LINE/2];
    size_t tcnt = 0;
    char *p = strtok(dirs_line, " \t");
    while (p && tcnt < (MAX_LINE/2)) {
        tokens[tcnt++] = p;
        p = strtok(NULL, " \t");
    }

    // For each row i, apply tokens[i] if exists. If tokens fewer than rows, ignore remaining rows.
    for (size_t i = 0; i < rows_cnt; ++i) {
        if (i >= tcnt) break; // no instruction
        char dir = tokens[i][0]; // first char e.g., 'R' or 'L' (case-insensitive)
        if (dir >= 'a' && dir <= 'z') dir = dir - 'a' + 'A';

        size_t len = strlen(rows[i]);
        if (len == 0) continue;

        // rotate by 1
        if (dir == 'R') {
            // right rotation by 1: last char moves to front
            char last = rows[i][len-1];
            memmove(rows[i] + 1, rows[i], len-1);
            rows[i][0] = last;
        } else if (dir == 'L') {
            // left rotation by 1: first char moves to end
            char first = rows[i][0];
            memmove(rows[i], rows[i] + 1, len-1);
            rows[i][len-1] = first;
        } else {
            // unknown token: ignore
        }
    }

    // central row index floor(n/2)
    size_t cidx = rows_cnt / 2; // integer division does floor
    char *central = rows[cidx];

    // compute sum of integer representations (ASCII codes) of characters in the central row
    long long sum = 0;
    for (size_t j = 0; j < strlen(central); ++j) {
        unsigned char ch = central[j];
        sum += (int)ch;
    }

    // Print result and write to file
    printf("%lld\n", sum);

    FILE *fo = fopen(OUT_PATH, "w");
    if (fo) {
        fprintf(fo, "%lld\n", sum);
        fclose(fo);
    } else {
        // non-fatal
        perror("Warning: couldn't write output file");
    }

    // free memory
    for (size_t i=0;i<rows_cnt;++i) free(rows[i]);
    free(rows);

    return 0;
}
