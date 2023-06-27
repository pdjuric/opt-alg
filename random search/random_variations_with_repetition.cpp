#include <stdio.h>

using namespace std;

void driver_random_variation() {
    srand((unsigned) time(NULL));

    int n = 7;  // number of elements to choose from
    int k = 8;  // length of a sequence
    int s = 1;  // number of sequences to generate

    int *r = new int[k];

    for (int i = 0; i < s; i++) {
        for (int j = 0; j < k; j++) {
            r[j] = random_int(0, n - 1);
            printf("%2d ", r[j]);
        }
        printf("\n");
    }

    delete [] r;
}

