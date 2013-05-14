#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 9
int cell[MAX][MAX];
void enterSudoku(FILE * file, char *filename)
{
    int i, j;
    char *str;
    str = (char *) calloc(4, sizeof(char));
    file = fopen(filename, "r");
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            fscanf(file, "%d", &cell[i][j]);
        }
    }
    fclose(file);
}

void displaySudoku(FILE * file, char *filename)
{
    int i, j;
    file = fopen(filename, "w+");
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            if (j == 2 || j == 5 || j == 8) {
                printf("%3d ", cell[i][j]);
            }

            else {
                printf("%3d", cell[i][j]);
            }
        }
        puts("");
        if (i == 2 || i == 5 || i == 8) {
            puts("");
        }
    }
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            fprintf(file, "%d ", cell[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int chck_sdk()
{
    int fail = 0;
    int i;
    for (i = 0; i < 9 && !fail; ++i) {
        int p[9] = { 0, };
        int j;
        for (j = 0; j < 9 && !fail; ++j) {
            if (cell[i][j] == 0) {
                continue;
            }
            if (p[cell[i][j] - 1] == 0)
                p[cell[i][j] - 1] = 1;

            else
                fail = 1;
        }
    }
    int j;
    for (j = 0; j < 9 && !fail; ++j) {
        int p[9] = { 0, };
        for (i = 0; i < 9 && !fail; ++i) {
            if (cell[i][j] == 0) {
                continue;
            }
            if (p[cell[i][j] - 1] == 0)
                p[cell[i][j] - 1] = 1;

            else
                fail = 1;
        }
    }
    for (i = 0; i < 9 && !fail; i += 3) {
        int j;
        for (j = 0; j < 9 && !fail; j += 3) {
            int p[9] = { 0, };
            int ik;
            for (ik = i; ik < i + 3 && !fail; ++ik) {
                int jk;
                for (jk = j; jk < j + 3 && !fail; ++jk) {
                    if (cell[ik][jk] == 0) {
                        continue;
                    }
                    if (p[cell[ik][jk] - 1] == 0)
                        p[cell[ik][jk] - 1] = 1;
                    else
                        fail = 1;
                }
            }
        }
    }
    if (!fail) {
        return 0;
    }
    else {
        return 1;
    }
}

int solveSudoku(FILE * file, int i, int j)
{
    int n = 1;
    while (1) {
        if (cell[i][j] != 0) {
            if ((i + 1) >= MAX && (j + 1) >= MAX) {
                return 0;
            }
            if ((j + 1) >= MAX) {
                i++;
                j = 0;
            }

            else {
                j++;
            }
        }
        else {
            break;
        }
    }
    while (1) {
        while (1) {
            cell[i][j] = n;
            n++;
            if (chck_sdk() == 0) {
                break;
            }
            if (n >= 10) {
                cell[i][j] = 0;
                return 1;
            }
        }
        if (solveSudoku(file, i, (j + 1)) == 0) {
            return 0;
        }
    }
}

int main()
{
    FILE *file;
    int n;
    file = NULL;
    enterSudoku(file, "input.txt");
    n = solveSudoku(file, 0, 0);
    if (n == 1) {
        puts("Bad sudoku");
        return 0;
    }
    else {
        displaySudoku(file, "output.txt");
    }
    return 0;
}
