
// A person bought four products. If the prices are expressed in dollars, then the sum and
// product of all prices (numerically) are the same and amount to $ 7.77. Prices are rounded
// to $ 0.01 (1 cent).
//
// (a) Write a program that performs a complete search by all four prices, and determine the
// number of calls to the optimization function.
//
// (b) Express one price over the others and write a program that performs a complete search
// by (remaining) three prices. Calculate the maximum number of calls to the optimization
// function and compare the speed of the program with respect to the program from (a).
//
// (c) Which of these two programs is faster?

#include <iostream>
#include <ctime>

using namespace std;

class Stats {
public:
    double solution[4] = {0};
    long cnt = 0;
    clock_t dur = 0;

    friend ostream& operator<<(ostream& os, const Stats& s);

};

ostream &operator<<(ostream &os, const Stats &s) {
    return os << "Prices of four products: " << s.solution[0] << " " << s.solution[1] << " " << s.solution[2] << " " << s.solution[3] << endl
        << "Number of invocations of the optimization function: " << s.cnt << endl
        << "Total duration in milliseconds: " << s.dur << endl;

}

class Opt {
public:
    Stats stats;
    virtual bool f(const int* prices) = 0;
    virtual void loop() = 0;

    void run(){
        clock_t start = clock();
        loop();
        stats.dur = (clock() - start)*1000/CLOCKS_PER_SEC;
        for (int i = 0; i < 4; i++) stats.solution[i] /= 100;
    }
};


class OptA: public Opt {
public:
    bool f(const int* prices) override {
        return prices[0] + prices[1] + prices[2] + prices[3] == 777 &&
               prices[0] * prices[1] * prices[2] * prices[3] == 777000000; //< 777500000 &&
        //prices[0] * prices[1] * prices[2] * prices[3] > 776500000;
    }

    void loop() override {
        int prices[4];

        for (prices[0] = 1; prices[0] <= 774; prices[0]++)
            for (prices[1] = prices[0]; prices[0] + prices[1] <= 775; prices[1]++)
                for (prices[2] = prices[1]; prices[0] + prices[1] + prices[2] <= 776; prices[2]++)
                    for (prices[3] = prices[2]; prices[0] + prices[1] + prices[2] + prices[3] <= 777; prices[3]++) {
                        stats.cnt++;
                        if (f(prices))
                            copy(begin(prices), end(prices), begin(stats.solution));
                    }

    }
};


class OptB: public Opt {
public:
    bool f(const int* prices) override {
        return (777 - (prices[0] + prices[1] + prices[2])) * prices[0] * prices[1] * prices[2] == 777000000;
    }

    void loop() override {
        int prices[3];

        for (prices[0] = 1; prices[0] <= 774; prices[0]++)
            for (prices[1] = prices[0]; prices[0] + prices[1] <= 775; prices[1]++)

                // prices[0] + prices[1] + prices[2] <= 776 would result in having (4 choose 3) more combinations
                // instead, we want the sequence to be non-decreasing; first three elements will always be increasingly
                // chosen, and additionally prices[2] <= prices[3], where prices[3] = 777 - (prices[0] + prices[1] + prices[2])
                for (prices[2] = prices[1]; prices[0] + prices[1] + 2 * prices[2] <= 777; prices[2]++){
                    stats.cnt++;
                    if (f(prices))
                        copy(begin(prices), end(prices), begin(stats.solution));
                }

        stats.solution[3] = 777 - (stats.solution[0] + stats.solution[1] + stats.solution[2]);
    }
};



int main() {
    Opt* opts[2] = {new OptA(), new OptB()};

    for (Opt* opt: opts) opt->run();
    for (Opt* opt: opts) cout << opt->stats << endl;

    cout << "The second optimization is faster " << opts[0]->stats.dur / opts[1]->stats.dur << " times." << endl;
}