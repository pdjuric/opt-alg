//
// Created by pavle on 30.11.22..
//

#ifndef IOA1_ANNEAL_STATS_H
#define IOA1_ANNEAL_STATS_H

#include <iostream>
#include "config.h"
#include <vector>

using namespace std;

class AnnealStats {
private:
    vector<pair<int, int> > vals;
    int idx = -1;
    int currCost = MAX_COST;

public:
    AnnealStats(vector<pair<int, int> >& vect)
        : vals(vect) {
    }

    AnnealStats() = default;

    bool hasNext();

    void toNext();

    int getNextIter();


    void addNewMinimum(int iteration, int cost);

    bool isNewMinimum(int cost) ;

    int getCurrentCost();

    vector<pair<int, int>>& getPoints();

//    long long s[3] = {};
//    for (int file = 0; file < FILE_CNT; file++){
//        s[optimal->memory[file]] += size[file];
//    }
};


#endif //IOA1_ANNEAL_STATS_H
