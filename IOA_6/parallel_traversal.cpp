
#include "parallel_traversal.h"
#include <queue>


vector<pair<int, int> > Callback::getResult() {
    return result;
}


void FindBest::operator()(AnnealStats *arr[REANNEAL_NUM], int curr_iter, AnnealStats *pStats) {
    if (result.empty() || result.back().second > pStats->getCurrentCost()) {
        result.emplace_back(curr_iter, pStats->getCurrentCost());
    }
}

void FindAverage::operator()(AnnealStats *arr[REANNEAL_NUM], int curr_iter, AnnealStats *pStats) {
    long long sum = 0;
    for (int i = 0; i < REANNEAL_NUM; i++) sum += arr[i]->getCurrentCost();
    auto avg = (int) sum / REANNEAL_NUM;

    if (result.empty() || avg != result.back().second)
        result.emplace_back(curr_iter, avg);
}


void parallel_traversal(AnnealStats *stats[REANNEAL_NUM], Callback &callback) {
    AnnealStats *pStats;
    int currVal, min_iter;
    priority_queue<pair<int, AnnealStats *>> pqval, pqiter;

    // insert all the stats in the queue
    for (int i = 0; i < REANNEAL_NUM; i++)
        pqiter.push({0, stats[i]});

    while (!pqiter.empty() || !pqval.empty()) {
        // take the stats which are currently at the lowest iteration
        min_iter = -pqiter.top().first;
        while (!pqiter.empty() && min_iter == -pqiter.top().first) {
            pStats = pqiter.top().second;
            pqiter.pop();

            // advance through the list,  get the next cost
            pStats->toNext();

            // add the value to the pqval queue
            pqval.push({-pStats->getCurrentCost(), pStats});
            // if there is another, lower cost
            if (pStats->hasNext()) pqiter.push({-pStats->getNextIter(), pStats});
        }

        // discard all the old values, which aren't valid anymore because their iteration has already been processed
        do {
            currVal = -pqval.top().first;
            pStats = pqval.top().second;
            pqval.pop();
        } while (!pqval.empty() && pStats->getCurrentCost() != currVal);

        callback(stats, min_iter, pStats);

    }

}