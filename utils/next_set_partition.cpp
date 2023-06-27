#include <iostream>
using namespace std;


bool next_set_partition(int* a, int n) {
    int *maxVal = new int[n];
    int i;
    for (i = 0; i < n; i++)
        maxVal[i] = i == 0 ? 0 : std::max(maxVal[i - 1], a[i - 1] + 1);

    for (i = n - 1; i >= 0 && a[i] == maxVal[i]; i--) a[i] = 0;
    if (i != -1) a[i]++;
    delete [] maxVal;
    return i != -1;
}

void driver() {
    int n = 4;
    int* a = new int[n];

    for (int i = 0; i < n; i++)
        a[i] = 0;

    do {
        for (int i = 0; i < n; i++)
            printf("%2d ", a[i]);
        printf("\n");
    } while (next_set_partition(a, n));

        delete [] a;


}