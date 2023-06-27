void random_combination(int n, int k, int* P) {

    if (k > n) return;

    int j, r;
    int* Q = new int[n];

    for (int i = 0; i < n; i++) Q[i] = 0;

    for (int i = 0; i < k; i++) {
        int  r = random_int(0, n-1-i);
        for (j = 0; j < n && (r > 0 || Q[j] != 0); j++) if (Q[j] == 0) r--;
        Q[j]++;
    }

    for (int i = 0; i < n; i++)
        if (Q[i] == 1)
            P[j++] = i + 1;

    delete [] Q;
}

void driver() {
    int n = 5, k = 3;
    int* P = new int[k];

    for (int i = 0; i <100; i++) {
        random_combination(n, k, P);
        for (int i = 0; i < k; i++)
            printf("%2d ", P[i]);
        printf("\n");
    }

    delete [] P;
}