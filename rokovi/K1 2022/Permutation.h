//
// Created by pavle on 4.11.22..
//

#ifndef IOA1_PERMUTATION_H
#define IOA1_PERMUTATION_H

#include <iostream>

using namespace std;

class Permutation;
extern ostream& operator<<(ostream& os, const Permutation& p);

// Linked list for saving optimal permutations
class Permutation {

    ~Permutation() {
        delete next;
        delete arr;
    }

public:
    static int size;
    static int n;
    int* arr;
    Permutation* next;

    static Permutation* list;
    Permutation(const int a[], int N) : arr(new int[N]) {
        for (int i = 0; i < N; i++)
            this->arr[i] = a[i];
        this->next = list;
        list = this;
        size++;
    }

    static void deleteList() {
        delete list;
        list = nullptr;
        size = 0;
    }
    friend ostream& operator<<(ostream& os, const Permutation& p);
};



#endif //IOA1_PERMUTATION_H
