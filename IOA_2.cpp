#include <ctime>
#include <iostream>

#define node(i) (char)('A' + i)

using namespace std;
int costs[10][10] = {
        {0,374, 350, 223, 108, 178, 252, 285, 240, 356},
        {374, 0, 27, 166, 433, 199, 135, 95, 136, 17},
        {350, 27, 0, 41, 52, 821, 180, 201, 131, 247},
        {223, 166, 41, 0, 430, 47, 52, 84, 40, 155},
        {108, 433, 52, 430, 0, 453, 478, 344, 389, 423},
        {178, 199, 821, 47, 453, 0, 91, 37, 64, 181},
        {252, 135, 180, 52, 478, 91, 0, 25, 83, 117},
        {285, 95, 201, 84, 344, 37, 25, 0, 51, 42},
        {240, 136, 131, 40, 389, 64, 83, 51, 0, 118},
        {356, 17, 247, 155, 423, 181, 117, 42, 118, 0}
};

int* currCnt = nullptr;
int* totalCnt = nullptr;
int* paths[2] = {};
int* nodeCnt = nullptr;
int* P = nullptr;
int len, minCost;


void sequence_to_spanning_tree() {
    int q = 0, cost = 0, n = len + 2;
    int* potentialOptimal = paths[1];
    for (int i = 0; i < n; i++) currCnt[i] = nodeCnt[i] = 0;

    for (int i = 0; i < len && cost < minCost; i++) {
        for (int j = 0; j < n && cost < minCost; j++) {
            if (totalCnt[j] == currCnt[j]) {
                currCnt[j] = -1;
                potentialOptimal[q++] = j;
                potentialOptimal[q++] = P[i];
                currCnt[P[i]]++;

                cost += costs[j][P[i]];
                if (++nodeCnt[j] > 3) cost += 250;
                if (++nodeCnt[P[i]] > 3) cost += 250;
                break;
            }
        }
    }

    for (int i = 0; cost < minCost && i < n && q < 2*(n-1); i++)
        if (totalCnt[i] == currCnt[i]) {
            potentialOptimal[q++] = i;
            if (++nodeCnt[i] > 3) cost += 250;
        }

    if (cost < minCost) cost += costs[potentialOptimal[q - 2]][potentialOptimal[q - 1]];

    if (cost < minCost) {
        minCost = cost;
        paths[1] = paths[0];
        paths[0] = potentialOptimal;
    }
}



void variations_with_repetition(int n) {
    int curr;
    len = n - 2;
    minCost = INT_MAX;

    paths[0] = new int[(n - 1) * 2];
    paths[1] = new int[(n - 1) * 2];
    nodeCnt = new int[n];

    P = new int[len];
    for (int i = 0; i < len; i++) P[i] = 0;

    currCnt = new int[n];
    totalCnt = new int[n];
    for (int i = 0; i < n; i++) totalCnt[i] = 0;
    for (int i = 0; i < len; i++) totalCnt[P[i]]++;

    clock_t start = clock();

    do {
        sequence_to_spanning_tree();

        for (curr = len - 1; curr >= 0; curr--) {
            totalCnt[P[curr]]--;

            if (P[curr] == n - 1) P[curr] = 0;
            else P[curr]++;

            totalCnt[P[curr]]++;

            if (P[curr] != 0) break;
        }

    } while (curr >= 0);

    clock_t duration = (clock() - start) * 1000 / CLOCKS_PER_SEC;
    cout << "tree cost: " << minCost << endl;
    cout << "edges: \t";
    for (int i = 0; i < n-1; i++)
        cout << node(paths[0][i*2]) << " " << node(paths[0][i*2 + 1]) << (i != n-2 ? " - " : "");

    cout << endl << "time: " << duration << "ms" << endl;

    delete [] paths[0];
    delete [] paths[1];
    delete [] P;
    delete [] nodeCnt;
    delete [] currCnt;
    delete [] totalCnt;
}


int main_2() {
    variations_with_repetition(10);
    return 0;
}