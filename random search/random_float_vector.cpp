
void driver_random_vector() {
    srand((unsigned) time(NULL));

    double xmin = -1.0;
    double xmax = +1.0;
    int k = 4;  // length of a sequence
    int s = 15;  // number of sequences to generate

    double *r = new double [k];

    for (int i = 0; i < s; i++) {
        for (int j = 0; j < k; j++) {
            r[j] = random_float(xmin, xmax);
            printf("% 2.3f ", r[j]);
        }
        printf("\n");
    }

    delete [] r;
}