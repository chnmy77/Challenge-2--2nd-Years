// solutions/problem1.c  (Fully Optimized Version)
// Compile: gcc -std=c11 -O2 -o solutions/problem1 solutions/problem1.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 4096
#define OUT_PATH "solutions/problem1.out"

// Trim newline and trailing spaces
static void rtrim(char *s) {
    int len = (int)strlen(s);
    while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r' ||
           isspace((unsigned char)s[len-1])))
    {
        s[--len] = '\0';
    }
}

// portable strdup
static char *my_strdup(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s) + 1;
    char *p = malloc(len);
    if (p) memcpy(p, s, len);
    return p;
}

int main(int argc, char **argv) {
    const char *grid_path = "inputs/grid.txt";
    const char *dir_path  = "inputs/directions.txt";

    if (argc >= 3) {
        grid_path = argv[1];
        dir_path = argv[2];
    }

    // First, read all directions so we know the instruction for the central row.
    FILE *fd = fopen(dir_path, "r");
    if (!fd) {
        perror("Failed to open directions file");
        return 1;
    }

    char dirline[MAX_LINE];
    if (!fgets(dirline, sizeof(dirline), fd)) {
        fprintf(stderr, "Directions file empty.\n");
        fclose(fd);
        return 1;
    }
    fclose(fd);
    rtrim(dirline);

    // Tokenize directions
    char *tokens[MAX_LINE/2];
    size_t tcnt = 0;

    char *copy = my_strdup(dirline);
    char *p = strtok(copy, " \t");
    while (p && tcnt < (MAX_LINE/2)) {
        tokens[tcnt++] = p;
        p = strtok(NULL, " \t");
    }

    // Stream grid file and capture only the central row.
    FILE *fg = fopen(grid_path, "r");
    if (!fg) {
        perror("Failed to open grid file");
        free(copy);
        return 1;
    }

    // Count rows first (we must find central index)
    size_t total_rows = 0;
    char buf[MAX_LINE];

    while (fgets(buf, sizeof(buf), fg)) {
        rtrim(buf);
        if (buf[0] != '\0')
            total_rows++;
    }

    if (total_rows == 0) {
        fprintf(stderr, "Grid is empty.\n");
        free(copy);
        fclose(fg);
        return 1;
    }

    size_t central_index = total_rows / 2;

    // Now read again and extract only the central row
    rewind(fg);

    char *central = NULL;
    size_t current = 0;

    while (fgets(buf, sizeof(buf), fg)) {
        rtrim(buf);
        if (buf[0] == '\0') continue;

        if (current == central_index) {
            central = my_strdup(buf);
            break;
        }
        current++;
    }
    fclose(fg);

    if (!central) {
        fprintf(stderr, "Failed to load central row.\n");
        free(copy);
        return 1;
    }

    size_t clen = strlen(central);

    // Apply rotation ONLY to central row if a direction exists
    if (central_index < tcnt) {
        char d = tokens[central_index][0];
        if (d >= 'a' && d <= 'z') d = d - 'a' + 'A';

        if (clen > 1) {
            if (d == 'R') {
                char last = central[clen-1];
                memmove(central+1, central, clen-1);
                central[0] = last;
            } else if (d == 'L') {
                char first = central[0];
                memmove(central, central+1, clen-1);
                central[clen-1] = first;
            }
        }
    }

    // Compute ASCII sum
    long long sum = 0;
    for (size_t i = 0; i < clen; i++)
        sum += (unsigned char)central[i];

    printf("%lld\n", sum);

    FILE *fo = fopen(OUT_PATH, "w");
    if (fo) {
        fprintf(fo, "%lld\n", sum);
        fclose(fo);
    }

    free(copy);
    free(central);

    return 0;
}
