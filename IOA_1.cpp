#include <cmath>
#include <iostream>

using namespace std;

int coord[12][2] = {
    {620, 584},
    {575, 560},
    {517, 560},
    {679, 196},
    {577, 421},
    {542, 291},
    {460, 451},
    {347, 451},
    {457, 251},
    {347, 264},
    {284, 317},
    {334, 605},
};

int **memo;
int *currPath, *minPath, *currPrefixCost;
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

inline int distance(int x, int y) {
    if (memo[x][y]) return memo[x][y];
    return memo[x][y] = memo[y][x] = (coord[x][0] - coord[y][0]) * (coord[x][0] - coord[y][0]) + (coord[x][1] - coord[y][1])*(coord[x][1] - coord[y][1]);
}

inline int getCost() {
    int sum = firstChanged ? currPrefixCost[firstChanged-1] : 0;

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
    currPrefixCost = new int[pathLen];
    memo = new int*[pathLen];
    firstChanged = 0;

    for (int i = 0; i < pathLen; i++){
        currPath[i] = i;
        memo[i] = new int[pathLen] {};
    }

    int minCost = ~0U >> 1, currCost;

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
    cout <<  "paths: \t";
    for (int i = 0; i < pathLen; i++) cout << minPath[i] + 1 << " ";
    cout <<  "\n\t\t";
    for (int i = pathLen-1; i >= 0; i--) cout << minPath[i] + 1 << " ";
    cout << endl << "path distance: " << sqrt(minCost / 100.)  << endl;
    cout << "time: " << duration * 1000 / CLOCKS_PER_SEC << "ms" << endl << endl;

    delete [] currPath;
    delete [] minPath;
    delete [] currPrefixCost;
    for (int i = 0; i < pathLen; i++) delete [] memo[i];
    delete [] memo;
 }

void main_1() {
    pathLen = 12;
    findOptimal();
    pathLen = 8;
    findOptimal();
}