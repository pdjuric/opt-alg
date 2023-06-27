//
// Created by pavle on 30.11.22..
//

#ifndef IOA1_CONFIG_H
#define IOA1_CONFIG_H

#define FILE_CNT 64
#define MEMORY_CNT 3
#define MAX_MEMORY_CAPACITY (1 << 25)
#define MAX_COST (1 << 26)
#define START_TEMPERATURE (1 << 26)

#define h_max 5
#define h_min 1

//#define ENABLE_DEBUG_OUTPUT
//#define BEST_BY_THREAD
//#define CUMULATIVE_BEST_BY_ANNEALING
#define CURRENT_BEST_BY_ANNEALING
//#define DEBUG_OUTPUT_TO_FILE
#define ENABLE_PYTHON_ARGS


extern int ITER_NUM;
extern int REANNEAL_NUM;
extern int THREAD_NUM;
extern const double a;

extern int size[];


#include <iostream>
#include <iomanip>
using namespace std;

extern void outputThreadInfo(int annealNo = -1);
extern void outputStats(int iteration, int cost, string message = "");
extern void outputDebugMessage(string message);

#endif //IOA1_CONFIG_H
