#include <iostream>
using namespace std;


void sequence_to_spanning_tree(int* P, int len, int* T) {
    int i, j, q = 0;

    int n = len + 2;
    int* V = new int[n];

    // countingsort
    for (i = 0; i < n; i++) V[i] = 0;
    for (i = 0; i < len; i++) V[P[i]-1]++;

    for (i = 0; i < len; i++) {
        for (j = 0; j < n; j++) {
            if (V[j] == 0) {
                V[j] = -1;
                T[q++] = j + 1;
                T[q++] = P[i];
                V[P[i]-1]--;
                break;
            }
        }
    }

    for (i = 0; i < n; i++) if (V[i] == 0) {
        T[q++] = i + 1;
        if (q == 2 * (len + 1)) break;
    }

    delete [] V;
}


void sptree() {
    //indeksiranje od 0
    int P[] = {3, 3, 4, 5, 4, 6 };

    int len = sizeof(P) / sizeof(P[0]);

    int* T = new int[2 * (len + 1)];
    sequence_to_spanning_tree(P, len, T);
    for (int i = 0;  i < 2 * (len + 1); i++) {
        cout << T[i];
        if ((i + 1) % 2 == 0 && i < 2 * len)
            cout << "   -  ";

    }
    cout << endl;
    delete [] T;
}


