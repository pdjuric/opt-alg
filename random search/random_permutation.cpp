srand(unsigned int seed_value)

int random_int(int low, int high) {
    random()
}

void random_permutation(int n, int* p) {
    int i, j, s;
    for (i = n - 1; i > 0; i--) {
        j = ranodm_int(0, i + 1);
        if (i != j) {
            s = p[i];
            p[i] = p[j];
            p[j] = s;
        }
    }
}
void driver() {
    int n = 3;
    int* p = new int[n];
    int* s = new int[n];
    int T = 1000;
    for (int i = 0; i < n; i++) {
        p[i] = i + 1;
        s[i] = 0;
    }

    for (int i = 0; i < T; i++) {
        random_permutation(n, p);

        for (int i = 0; i < n; i++)
            printf("%2d ", p[i]);
        printf("\n");

        s[p[0] - 1]++;
    }

    for (int i = 0; i < n; i++)
        printf("%2.5f\n", s[i]*1./T);

    delete [] p;
    delete [] s;
}

