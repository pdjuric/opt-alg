#include <cmath>
#include <iostream>
#include <cfloat>

using namespace std;

double coord[12][2] = {
    {62.0, 58.4},
    {57.5, 56.0},
    {51.7, 56.0},
    {67.9, 19.6},
    {57.7, 42.1},
    {54.2, 29.1},
    {46.0, 45.1},
    {34.7, 45.1},
    {45.7, 25.1},
    {34.7, 26.4},
    {28.4, 31.7},
    {33.4, 60.5},
};

double **memo, *currPrefixCost;
int *currPath, *minPath;
int pathLen, firstChanged;

inline bool nextPath() {
    // firstChanged will be last changed position
    int s;
    int *first = currPath, *last = &currPath[pathLen-1];
    int *k = last-1, *l = last;
    firstChanged = pathLen - 2;

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
}

inline double distance(int x, int y) {
    if (memo[x][y] != 0) return memo[x][y];
    return memo[x][y] = memo[y][x] = sqrt(pow(coord[x][0] - coord[y][0], 2) + pow(coord[x][1] - coord[y][1], 2));
}

inline double getCost() {
    double sum = firstChanged ? currPrefixCost[firstChanged-1] : 0;

    for (int i = firstChanged; i < pathLen; i++)
        if (i > 0) {
            currPrefixCost[i] = sum + distance(currPath[i-1], currPath[i]);
            sum = currPrefixCost[i];
        }
    return sum;
}

void findOptimal() {
    currPath = new int[pathLen];
    minPath = new int[pathLen];
    currPrefixCost = new double[pathLen];
    memo = new double*[pathLen];
    firstChanged = 0;

    for (int i = 0; i < pathLen; i++){
        currPath[i] = i;
        memo[i] = new double[pathLen] {};
    }

    double minCost = DBL_MAX, currCost;

    clock_t start = clock();

    do {
        currCost = getCost();

        if (currCost < minCost) {
            minCost = currCost;
            copy(currPath, currPath + pathLen, minPath);
        }

    } while (nextPath());

    clock_t duration = clock() - start;

    cout << "path length: " << pathLen << endl;
    cout << "paths: \t";
    for (int i = 0; i < pathLen; i++) cout << minPath[i] + 1 << " ";
    cout <<  "\n\t\t";
    for (int i = pathLen-1; i >= 0; i--) cout << minPath[i] + 1 << " ";
    cout << endl << "path distance: " << minCost << endl;
    cout << "time: " << duration * 1000 / CLOCKS_PER_SEC << "ms" << endl << endl;

    delete [] currPath;
    delete [] minPath;
    delete [] currPrefixCost;
    for (int i = 0; i < pathLen; i++) delete [] memo[i];
    delete [] memo;
 }

int main_1() {
    pathLen = 12;
    findOptimal();
    pathLen = 8;
    findOptimal();
}