
#include "Permutation.h"
#include <cstdlib>
#include <ctime>

int getCost (const int* P, int N, const int *minCost = nullptr) {
    int cost = 0;
    // if the current cost exceeds minimal cost, we don't need to finish calculating it
    for (int i = 0; i < N && (!minCost || *minCost >= cost); i++)
        cost += P[i] / (i + 1);
    return cost;
}

bool next_permutation(const int N, int* P) {
    int s;
    int* first = &P[0];
    int* last = &P[N-1];
    int* k = last - 1;
    int* l = last;

    while (k > first) {
        if (*k < *(k+1)) break;
        k--;
    }

    if (*k > *(k+1)) return false;

    while (l > k){
        if (*l > *k) break;
        l--;
    }

    s = *k;
    *k = *l;
    *l = s;

    first = k +1;


    while (first < last) {
        s = *first;
        *first = *last;
        *last = s;

        first++;
        last--;
    }
    return true;

}

int random_int(int low, int high) {
    return low + (rand() % (high + 1 - low));
}

void random_next_permutation(int n, int* p) {
    int i, j, s;
    for (i = n - 1; i > 0; i--) {
        j = random_int(0, i);
        if (i != j) {
            s = p[i];
            p[i] = p[j];
            p[j] = s;
        }
    }
}

/* bool next_permutation_dp_optimized(const int N, int* P, int &firstChanged) {
    // firstChanged will be last changed position
    int s;
    int *first = P, *last = &P[N-1];
    int *k = last-1, *l = last;
    firstChanged = N - 2;

    // find largest k so that P[k] < P[k+1]
    while (k>first && *k >= *(k+1)) k--, firstChanged--;

    // if no P[k] < P[k+1], P is the last permutation in lexicographic order
    if (*k > *(k+1)) return false;

    //find largest l so that P[k] < P[l]
    while (l > k && *l <= *k) l--;

    // swap P[k] and P[l]
    s = *k;
    *k = *l;
    *l = s;

    // reverse the remaining P[k+1] .. P[N-1]
    first = k+1;
    while (first < last) {
        s = *first;
        *first = *last;
        *last = s;

        first++;
        last--;
    }

    return true;
}*/


// Zadatak 4
void findOptimal(int n) {
    Permutation::n = n;
    int* p = new int[n];
    int currCost, minCost = INT_MAX;

    for (int i = 0; i < n; i++) p[i] = i + 1;

    do {
        currCost = getCost(p, n, &minCost);

        if (minCost > currCost) {
            minCost = currCost;
            Permutation::deleteList();
        }

        if (minCost == currCost)
            new Permutation(p, n);

    } while (next_permutation(n, p));

    cout << "N = " << n << endl;
    cout << "min cost: " << minCost << endl;
    cout << "permutations: " << endl;
    cout << *Permutation::list;
    cout << endl;

    Permutation::deleteList();
    delete [] p;
}


//  ZADATAK 5
void findOptimalRandom(int n) {
    int* p = new int[n];
    int* best = new int[n];
    int T = 1e8,
        currCost,
        minCost = INT_MAX;

    for (int i = 0; i < n; i++) p[i] = i + 1;

    srand((unsigned)time(nullptr));

    for (int i = 0; i < T; i++) {
        random_next_permutation(n, p);

        currCost = getCost(p, n, &minCost);

        if (minCost > currCost) {
            minCost = currCost;
            for (int t = 0; t < n; t++)
                best[t] = p[t];
        }

    }

    cout << "N = " << n << endl;
    cout << "min cost: " << minCost << endl;
    cout << "permutation: ";
    for (int t = 0; t < n; t++)
        cout << best[t] << " ";

    delete [] p;
    delete [] best;
}


int main() {

    // zadatak 4a
    findOptimal(10);

    // zadatak 4b
    findOptimal(13);

    // zadatak 5
    findOptimalRandom(23);

    // zadatak 6 - provera
    int c = INT_MAX;
    int t[] = {1, 2, 5, 3 ,4 ,11, 6, 7, 8, 9, 10, 23, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};
    cout << endl << endl << " cost permutacije u zadatku 6: " << getCost(t, 23, &c);
    return 0;
}







