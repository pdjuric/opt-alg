#include <cstdio>


void variations_with_repetition(int n, int k) {
    int q;
    int *P = new int[k];
    for (int i = 0; i < k; i++)
        P[i] = 0;

    do {
        for (int i = 0; i < k; i++)
            printf("%5d ", P[i]+1);
        printf("\n");

        q = k - 1;
        while (q >= 0) {
            P[q]++;
            if (P[q] == n) {
                P[q] = 0;
                q--;
            } else break;

        }

    } while (q >= 0);

    delete [] P;
}