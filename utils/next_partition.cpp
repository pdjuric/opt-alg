#include <iostream>


using namespace std;
void print_arr(int* p, int n){
    for (int i = 0; i < n && p[i] != 0; i++) cout << p[i] << " ";
    cout << endl;
}


bool next_partition(int* arr, int n) {
    int p, q;

    if (arr[0] == 0) {
        arr[0] = n;
        return true;
    }

    // find the last element which can be broken down
    for (p = -1; p + 1 < n && arr[p + 1] > 1; p++);

    // if no such element exists, then it's the end of partitioning
    if (p == -1) return false;

    // find the number of 1s
    // if they exist, the sequence will start from (p+1)th element
    for (q = 0; p + q + 1 < n && arr[p + q + 1] == 1; q++);

    // decrement the p-th element
    arr[p]--;
    //the remaining elements should sum up to q + 1
    q++;

    // if the sum of remaining elements is greater than the p-th element
    // the sum couldn't be put on (p+1)th place
    while (q > arr[p]) {
        // put the maximum possible value on p+1
        arr[p + 1] = arr[p];
        // reduce the remaining sum
        q -= arr[p];
        p++;
    }

    // the sum of remaining elements is less than the p-th element and
    // can be put on (p+1)th place
    arr[++p] = q;

    // delete old remaining elements
    for (p++; p < n && arr[p] != 0; p++) arr[p] = 0;

    return true;
}


bool next_partition_old(int* p, int n) {
    int k, i;
    int q = 0;

    if (p[0] == 0) {
        p[0] = n;
        return true;
    }


    for (i = 0; p[i] != 0 && i < n; k = i, i++);


    // k will be the last non-1, and q would be the number of 1s
    for(; k >= 0 && p[k] == 1; q++, k--);

    // if all elements are 1, end
    if (k < 0) return false;

    // decrement the last non-1 element
    p[k]--;
    q++;

    while (q > p[k]) {
        p[k + 1] = p[k];
        q -= p[k];
        k++;
    }

    p[k + 1] = q;
    k++;

    for (i = k + 1; i < n; i++)
        p[i] = 0;

    return true;
}


void driver_next_partition() {
    int n = 12;
    int* p = new int[n];

    for (int i = 0; i < n; i++)
        p[i] = 0;

    while (next_partition(p, n)) {
        print_arr(p, n);
    }
    delete [] p;

}