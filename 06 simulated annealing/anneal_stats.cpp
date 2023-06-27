
#include "anneal_stats.h"
#include "config.h"

using namespace std;


bool AnnealStats::hasNext() {
    return idx != vals.size() - 1;
}

void AnnealStats::toNext() {
    currCost = vals[++idx].second;
}

int AnnealStats::getNextIter() {
    return !vals.empty() && idx >= vals.size() - 1 ? ITER_NUM : vals[idx+1].first;
}


void AnnealStats::addNewMinimum(int iteration, int cost) {
    vals.emplace_back(iteration, cost);
#if defined ENABLE_DEBUG_OUTPUT && defined CUMULATIVE_BEST_BY_ANNEALING
    outputStats(iteration, cost, "NEW BEST");
#endif

}

bool AnnealStats::isNewMinimum(int cost) {
    return vals.empty()|| vals.back().second > cost;
}

int AnnealStats::getCurrentCost() {
    return currCost;
}

vector<pair<int, int>>& AnnealStats::getPoints() {
    return vals;
}
