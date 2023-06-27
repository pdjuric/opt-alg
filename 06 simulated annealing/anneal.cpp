#include <random>
#include <queue>

#include "config.h"
#include "state.h"
#include "anneal_stats.h"

using namespace std;
typedef unsigned char byte;

// costROC => rate of change of cost function
inline double getProbabilityOfChange(int costROC, double T) {
    if (costROC < 0) return 1;
    else if (costROC == 0) return .5;
    else return exp(- costROC / T);
}

void randomSequence(int len, byte values[FILE_CNT], mt19937 &gen) {
    for (int i = 0; i < FILE_CNT; i++) values[i] = i;

    for (int i = 0; i < len; i++) {
        // generate a random int, but hit a number in array values which is not yet been generated
        uniform_int_distribution<> rand_int(i, FILE_CNT - 1);
        int idx = rand_int(gen);

        swap(values[i], values[idx]);

        // generated values are values[0..i-1], and remaining are values[i..MEMORY_CNT-1]
    }
}

AnnealStats* anneal(State &best, mt19937 &gen) {

    auto* stats = new AnnealStats();

    // random generator init
    uniform_real_distribution<double> rand_dbl(0, 1);
    uniform_int_distribution<> rand_int(0, 2);

    // array for storing chosen elements by random generator
    byte values[FILE_CNT];

    // info about newly generated state
    State curr;

    double T = START_TEMPERATURE;

#if defined ENABLE_DEBUG_OUTPUT && ( defined CUMULATIVE_BEST_BY_ANNEALING || defined CURRENT_BEST_BY_ANNEALING )
    outputStats(0, best.getCost(), "BEFORE");
#endif

    for (int iter = 0; iter < ITER_NUM; iter++) {
        curr = best;

        // find the Humming distance (how many of the )
        byte h = (h_min - h_max) * iter / (ITER_NUM - 1) + h_max;

        // determine which files will be [potentially] moved to another memory
        randomSequence(h, values, gen);

        // for each of the generated elements
        for (byte *file = values; file < values + h; file++) {
            // find its new memory
            int newMemory = rand_int(gen);
            // change its memory
            curr.changeMemoryForFile(*file, newMemory);
        }

        // calculate the optimization function
        curr.calculateCost();

        // determine whether the generated state should be kept and further explored
        if (rand_dbl(gen) <= getProbabilityOfChange(curr.getCost() - best.getCost(), T)) {
            best = curr;
#if defined ENABLE_DEBUG_OUTPUT && defined CURRENT_BEST_BY_ANNEALING
            outputDebugMessage("stavlja novi best na ");
            outputStats(iter, best.getCost());
#endif
            // save the current iteration and current cost, if the cost is optimal
            if (stats->isNewMinimum(best.getCost()))
                stats->addNewMinimum(iter, best.getCost());

        }
        // determine next T
        T *= a;

    }

    return stats;

}
