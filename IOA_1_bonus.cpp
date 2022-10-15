#include <iostream>
#include <cmath>

using namespace std;

typedef unsigned long long ullong;

class PowArr {
private:
    ullong *arr, *a, *b, *c;
    int len, currPower = 0;

public:
    explicit PowArr(int maxValue) : len(maxValue), arr(new ullong[maxValue]), a(arr), b(arr), c(arr+maxValue-1) {
        for (int i = 0; i < len; i++) arr[i] = 1;
    }

    void powerUp() {
        for (int i = 0; i < len; i++) arr[i] *= i + 1;
        currPower++;
    }

    ullong getMinSum() const { return *a + *b + *b; }
    ullong getMaxSum() const { return *a + *c + *c; }
    ullong getSum() const { return *a + *b + *c; }

    void printCurrent() const {
        long ints[3] = {a-arr+1, b-arr+1, c-arr+1};
        do {
            cout << "n=" << currPower+1 << " a=" << ints[0] << " b=" << ints[1] << " c=" << ints[2] << endl;
        } while (next_permutation(ints,ints+3));
    }

    void reset() {
        a = b = arr;
        c = arr + len - 1;
    }

    bool hasMoreIterations() const { return a < arr + len - 1; }

    void nextIteration() {
        b = ++a;
        c = arr + len - 1;
    }

    bool isIterationEnd() const { return b <= c; }

    void nextHigherSum() { b++; }
    void nextLowerSum() { c--; }

};

int main(){

    // determine the greatest factorial that fits into 64-bit location
    ullong prevFact = 1, currFact = 2;
    int maxN = 1;
    for (; prevFact == currFact / (maxN + 1); maxN++, prevFact = currFact, currFact *= (maxN + 1));

    // determine the biggest number whose power to the maxN-1 fits into 64-bit location
    int maxABC = floor(pow(~0ULL, 1./(maxN-1)));

    cout << "n! = a^(n-1) + b^(n-1) + c^(n-1)" << endl;

    clock_t start = clock();

    PowArr arr(maxABC);
    ullong fact = 1;
    int n = 1;

    for (; n <= maxN; fact *= ++n, arr.powerUp())
        for (arr.reset(); arr.hasMoreIterations(); arr.nextIteration()) {
            if (arr.getMinSum() > fact || arr.getMaxSum() < fact) continue;

            while (arr.isIterationEnd())
                if (arr.getSum() > fact) arr.nextLowerSum();
                else if (arr.getSum() < fact) arr.nextHigherSum();
                else {
                    arr.printCurrent();
                    break;
                }

        }

    cout << clock() - start;
}
