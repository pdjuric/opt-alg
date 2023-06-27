#include "Permutation.h"

Permutation* Permutation::list = nullptr;
int Permutation::size = 0;
int Permutation::n = 0;


ostream &operator<<(ostream &os, const Permutation &p) {
    for (int i = 0; i < Permutation::n; i++) {
        os << p.arr[i] << " ";
    }
    os << endl;
    if (p.next) os << *p.next;
    return os;
}