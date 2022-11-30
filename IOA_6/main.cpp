

#include <random>
#include <iostream>
#include <thread>
#include <queue>
#include <fstream>

using namespace std;
#include "anneal_stats.h"
#include "state.h"
#include "parallel_traversal.h"
#include "config.h"
extern AnnealStats* anneal(State &best, mt19937 &gen);


vector<pair<int, int> > plot_points[20];
State* best[20];

 int ITER_NUM  = 100000;
 int REANNEAL_NUM = 10;
 int THREAD_NUM = 20;
 const double a = .95;


 int size[] = {173669, 275487, 1197613, 1549805, 502334, 217684, 1796841, 274708,
 631252, 148665, 150254, 4784408,344759,440109, 4198037, 329673,
 28602, 144173, 1461469, 187895, 369313, 959307, 1482335, 2772513,
 1313997,254845,486167, 2667146, 264004, 297223, 94694, 1757457,
 576203, 8577828, 498382, 8478177, 123575, 4062389,3001419,196884,
 617991, 421056, 3017627, 131936, 1152730, 2676649, 656678, 4519834,
 201919, 56080, 2142553,326263,8172117, 2304253, 4761871, 205387,
 6148422, 414559, 2893305, 2158562, 465972, 304078, 1841018, 1915571};



 void writeToFile(string filename, vector<pair<int, int>> arr) {
    ofstream file(filename, ios::out | ios::binary);
    for (auto & p: arr)  {
        file.write((char *) &p.first, sizeof(int));
        file.write((char *) &p.second, sizeof(int));
    }
    file.close();
}

thread_local int threadId;
thread_local ofstream* debug_output = nullptr;

void openDebugOutput() {
    debug_output = new ofstream ("thread_debug_output_" + to_string(threadId));
}

void closeDebugOutput() {
    debug_output->close();
    delete debug_output;
    debug_output = nullptr;
}

 void outputThreadInfo(int annealNo) {
#ifdef DEBUG_OUTPUT_TO_FILE
     ostream& out = *debug_output;
#else
     ostream& out = cout;
#endif
     out << endl << "_______________________________________________________" << endl << "THREAD " << threadId;
     if (annealNo != -1){
         out << "\t\t"<< (annealNo == 0 ? "INITIAL ANNEAL" : "REANNEAL " + to_string(annealNo)) ;
     }
      out << endl;
 }


void outputStats(int iteration, int cost, string message){
#ifdef DEBUG_OUTPUT_TO_FILE
     ostream& out = *debug_output;
#else
    ostream& out = cout;
#endif
    if (message != "") out << message << "  ";
    out << "iteration: " << left << setw(10) <<  (iteration)
            << " min value: " << left << setw(10) << (cost) << endl;
 }

extern void outputDebugMessage(string message) {
#ifdef DEBUG_OUTPUT_TO_FILE
    ostream& out = *debug_output;
#else
    ostream& out = cout;
#endif
    out << message;
}


void run(time_t seed, int id, const string& output_dir) {

    threadId = id;
#if defined ENABLE_DEBUG_OUTPUT && defined DEBUG_OUTPUT_TO_FILE
    openDebugOutput();
#endif

    mt19937 gen(seed);
    State *threadBest = new State();
    AnnealStats* stats[REANNEAL_NUM];

    for (int i = 0; i < REANNEAL_NUM; i++){
#if defined ENABLE_DEBUG_OUTPUT && (defined CUMULATIVE_BEST_BY_ANNEALING || defined CURRENT_BEST_BY_ANNEALING)
        outputThreadInfo(i);
#endif
        stats[i] = anneal(*threadBest, gen);
    }

    FindBest callback;
    parallel_traversal(stats, callback);

    plot_points[threadId] = callback.getResult();
    best[threadId] = threadBest;

    // write points to file
    writeToFile(output_dir + "/plot_points_" + to_string(threadId) + ".dat", plot_points[threadId]);

#if defined ENABLE_DEBUG_OUTPUT and defined BEST_BY_THREAD
    outputThreadInfo();
    for (auto & p: plot_points[threadId]) {
        outputStats(p.first, p.second);
    }
#endif

    for (int i = 0; i < REANNEAL_NUM; i++) delete stats[i];

#if defined ENABLE_DEBUG_OUTPUT && defined DEBUG_OUTPUT_TO_FILE
        closeDebugOutput();
#endif

}


int main(int argC, const char* argV[]) {
    time_t seed = time(nullptr);

    string output_dir = argV[0];
    output_dir = output_dir.substr(0, output_dir.find_last_of('/')) + "/output";

    system(("mkdir \"" + output_dir + "\"").c_str());

    if (argC > 1) seed = stoi(argV[1]);
    if (argC > 2) ITER_NUM = stoi(argV[2]);
    if (argC > 3) REANNEAL_NUM = stoi(argV[3]);
    if (argC > 4) THREAD_NUM = stoi(argV[4]);

    vector<thread> t;
    for (int id = 0; id < THREAD_NUM; id++, seed += 111) t.emplace_back(thread(&run, seed, id, output_dir));

#ifdef ENABLE_PYTHON_ARGS
    ofstream pyargs(output_dir +"/pyargs");
    pyargs  << output_dir << endl << ITER_NUM << endl << REANNEAL_NUM << endl << THREAD_NUM ;
    pyargs.close();
#endif

    for (auto &th: t) th.join();

    State* optimal = nullptr;
    for (int i = 0; i < THREAD_NUM; i++)
        if (optimal == nullptr || best[i]->getCost() < optimal->getCost())
            optimal = best[i];

    cout << "Seed: " << seed << endl;
    cout << *optimal << endl << flush;
    cin.get();


//    AnnealStats* arr[THREAD_NUM];
//    for (int i = 0; i < THREAD_NUM; i++) arr[i] = new AnnealStats(plot_points[i]);
//
//    FindAverage callback;
//    parallel_traversal(arr, callback);
//    writeToFile("./output/plot_points_avg.dat", callback.getResult());

    for (int i = 0; i < THREAD_NUM; i++) delete best[i];

    return 0;
}
