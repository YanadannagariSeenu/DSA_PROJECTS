#include <stdio.h>
#include <stdlib.h>

void printSolution(int *pos, int N) {
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            if (pos[r] == c) putchar('Q');
            else putchar('.');
            if (c < N-1) putchar(' ');
        }
        putchar('\n');
    }
    putchar('\n');
}

void solve(int row, int N, int *col, int *diag1, int *diag2, int *pos, long *count) {
    if (row == N) {
        printSolution(pos, N);
        (*count)++;
        return;
    }

    for (int c = 0; c < N; ++c) {
        int d1 = row + c;            // '\' diagonal index (0 .. 2N-2)
        int d2 = row - c + (N - 1);  // '/' diagonal index (0 .. 2N-2)

        if (!col[c] && !diag1[d1] && !diag2[d2]) {
            pos[row] = c;
            col[c] = diag1[d1] = diag2[d2] = 1;

            solve(row + 1, N, col, diag1, diag2, pos, count);

            // backtrack
            col[c] = diag1[d1] = diag2[d2] = 0;
        }
    }
}

int main(void) {
    int N;
    printf("Enter N (board size): ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    // allocate supporting arrays
    int *col   = (int*)calloc(N, sizeof(int));           // columns
    int *diag1 = (int*)calloc(2*N - 1, sizeof(int));     // row+col
    int *diag2 = (int*)calloc(2*N - 1, sizeof(int));     // row-col+(N-1)
    int *pos   = (int*)malloc(N * sizeof(int));          // pos[row] = column of queen in that row
    long count = 0;

    if (!col || !diag1 || !diag2 || !pos) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    solve(0, N, col, diag1, diag2, pos, &count);

    printf("Total solutions for N=%d : %ld\n", N, count);

    free(col);
    free(diag1);
    free(diag2);
    free(pos);
    return 0;
}