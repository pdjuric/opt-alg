// Created by pavle on 30.11.22..
//

#ifndef IOA1_STATE_H
#define IOA1_STATE_H

#include "config.h"
#include <iostream>

using namespace std;
typedef unsigned char byte;


class State {
private:
    byte memory[FILE_CNT] = {};
    int space_left[MEMORY_CNT];
    int cost = 2 * MAX_MEMORY_CAPACITY;

public:
    State();

    void calculateCost();

    void changeMemoryForFile(int file, byte newMemory);

    int getCost() const;

    friend ostream& operator<<(ostream& out, const State& state);

};






#endif //IOA1_STATE_H
