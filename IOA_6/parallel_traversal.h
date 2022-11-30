//
// Created by pavle on 30.11.22..
//

#ifndef IOA1_PARALLEL_TRAVERSAL_H
#define IOA1_PARALLEL_TRAVERSAL_H

#include <iostream>
#include "anneal_stats.h"

using namespace std;

class Callback {
protected:
    vector<pair<int, int> > result;
public:
    virtual void operator()(AnnealStats* arr[REANNEAL_NUM], int curr_iter,AnnealStats* pStats) = 0;
    vector<pair<int, int> > getResult();
};


class FindBest: public Callback {
public:
    void operator()(AnnealStats* arr[REANNEAL_NUM], int curr_iter,AnnealStats* pStats) override;
};

class FindAverage: public Callback {
public:
    void operator()(AnnealStats *arr[REANNEAL_NUM], int curr_iter, AnnealStats *pStats) override;
};

void parallel_traversal(AnnealStats* stats[REANNEAL_NUM],  Callback& callback );


#endif //IOA1_PARALLEL_TRAVERSAL_H
