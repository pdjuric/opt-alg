
#include "state.h"

using namespace std;
typedef unsigned char byte;


State::State() {
    for (int &space: space_left) space = MAX_MEMORY_CAPACITY;
}

void State::calculateCost() {
    cost = (space_left[1] < 0 || space_left[2] < 0 || space_left[1] == MAX_MEMORY_CAPACITY || space_left[2]  == MAX_MEMORY_CAPACITY)
                ? MAX_COST
                : space_left[1] + space_left[2];
}

void State::changeMemoryForFile(int file, byte newMemory){
    if (file < 0 || file >= FILE_CNT || newMemory < 0 || newMemory >= MEMORY_CNT)
        throw "Invalid file index or memory";
    // adjust the remaining space in both old and new memory
    space_left[memory[file]] += size[file];
    space_left[newMemory] -= size[file];

    // set the new memory flag
    memory[file] = newMemory;
}

int State::getCost() const {
    return cost;
}

ostream& operator<<(ostream& out, const State& state){
    out << "Optimal solution: ";
    for (int file = 0; file < FILE_CNT; file++)
        out << (file != 0 ? ", " : "") << to_string(state.memory[file]);
    cout << endl << "Cost: " << state.getCost() << endl;
    return out;
}
