#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <iomanip>

#define R0 15
#define N 20
#define F 0.8
#define CR 0.9
#define POPULATION_SIZE 20

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> randCoord(-15, 15);
uniform_int_distribution<> randIdx(0, POPULATION_SIZE - 1);
uniform_real_distribution<> randR(0, 1);
uniform_int_distribution<> randRIdx(0, 5);




class Coord {
public:
    double x = 0, y = 0;

    Coord()
        :Coord(0, 0){
    }

    Coord(double x, double y)
        : x(x), y(y) {
    }

    double getDistance(Coord& source) const {
        return sqrt(pow(x - source.x, 2) + pow(y - source.y, 2));
    }

    bool isInsideArea() const {
        return pow(x, 2) + pow(y, 2) < pow(R0, 2);
    }

    Coord operator-(const Coord& c) const {
        return {x-c.x, y-c.y};
    }

    Coord operator+(const Coord& c) const {
        return {x+c.x, y+c.y};
    }

    Coord operator*(double d) const {
        return {x*d, y*d};
    }

    friend ostream& operator<<(ostream& out, Coord& c);

};

ostream& operator<<(ostream& out, Coord& c) {
    return out << c.x << " " << c.y;
}


class Measurement{
private:
    static int currIdx;
public:
    Coord c = {R0 * cos(2*M_PI*currIdx/N), R0 * sin(2*M_PI*currIdx/N)};
    double value = 0;
public:
    Measurement(double val)
            : value(val) {
        currIdx++;
    }

};

int Measurement::currIdx = 0;

class Source{
public:
    Coord c;
    double A;

    Source(Coord c, double A)
            : c(c), A(A) {
    }

    double getStrength(Coord& c2) const {
        return A/c.getDistance(c2);
    }

    Source operator-(const Source& s) const {
        return {c-s.c, A-s.A};
    }

    Source operator+(const Source& s) const {
        return {c+s.c, A+s.A};
    }

    Source operator*(double d) const {
        return {c*d, A*d};
    }

    double& operator[](int idx) {
        switch (idx) {
            case 0:
                return c.x;
            case 1:
                return c.y;
            case 2:
                return A;
        }
    }

    friend ostream& operator<<(ostream& out, Source& s);


};


ostream& operator<<(ostream& out, Source& s) {
    return out << s.c << " " << s.A;
}





Measurement measurements[N] = {2.424595205726587e-01, 1.737226395065819e-01, 1.315612759386036e-01,
                               1.022985539042393e-01, 7.905975891960761e-02, 5.717509542148174e-02,
                               3.155886625106896e-02, -6.242228581847679e-03, -6.565183775481365e-02,
                               -8.482380513926287e-02, -1.828677714588237e-02, 3.632382803076845e-02,
                               7.654845872485493e-02, 1.152250132891757e-01, 1.631742367154961e-01,
                               2.358469152696193e-01, 3.650430801728451e-01, 5.816044173713664e-01,
                               5.827732223753571e-01, 3.686942505423780e-01 };


class Solution {
public:
    Source sources[2];

    Solution(Source s0, Source s1)
        : sources{s0, s1} {
    }

     Solution()
        : sources{{{randCoord(gen), randCoord(gen)}, randCoord(gen)}, {{randCoord(gen), randCoord(gen)}, randCoord(gen)}} {
    }

    double getCost() {
        for (auto& s: sources)
            if (!s.c.isInsideArea())
                return 100;

        double sum = 0;
        for (auto& m: measurements)
            sum += pow(sources[0].getStrength(m.c) + sources[1].getStrength(m.c) - m.value, 2);

        return sum;
    }

    void variate(Solution& x) {
        int idx = randRIdx(gen);
        for (int i = 0; i < 6; i++)
            if (i != idx && randR(gen) >= CR) {
                sources[i/3][i%3] = x.sources[i/3][i%3];
            }
    }

    Solution operator-(const Solution& sol) const {
        return {sources[0]-sol.sources[0], sources[1]-sol.sources[1]};
    }

    Solution operator+(const Solution& sol) const {
        return {sources[0]+sol.sources[0], sources[1]+sol.sources[1]};
    }

    Solution operator*(double d) const {
        return {sources[0]*d, sources[1]*d};
    }

    friend ostream& operator<<(ostream& out, Solution& sol);

};

ostream& operator<<(ostream& out, Solution& sol) {
    return out << sol.sources[0].c << " " << sol.sources[1].c << " "
        << sol.sources[0].A << " " << sol.sources[1].A;
}



class Population {
    Solution arr[POPULATION_SIZE];

public:
    Solution& operator[](int i) {
        return arr[i];
    }

    void variate(Population& x) {
        for (int i = 0; i < POPULATION_SIZE; i++)
            arr[i].variate(x[i]);
    }

    void checkForBetterSolutions(Population& x){
        for (int i = 0; i < POPULATION_SIZE; i++)
            if (arr[i].getCost() >= x[i].getCost())
                arr[i] = x[i];
    }

    double getCost() {
        double res = 100;
        for (auto& t: arr)
            res = min(res, t.getCost());
        return res;
    }

    friend ostream& operator<<(ostream& out, Population& p);

};

ostream& operator<<(ostream& out, Population& p) {
    double min = 100, curr;
    vector<Solution*> v;
    for (auto& t: p.arr) {
        curr = t.getCost();
        if (curr < min) {
            v.clear();
            min = curr;
        }
        if (curr == min) {
            v.push_back(&t);
        }
    }

    for (Solution* t: v)
        out << *t << endl;

    return out;
}

void differentialEvolution(Population& p) {
    Population q = p;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        int generated = 0;
        Solution* x[3];
        bool generatedIndices[POPULATION_SIZE] = {};
        generatedIndices[i] = true;

        do {
            int next = randIdx(gen);
            if (!generatedIndices[next]) {
                x[generated++] = &p[next];
            }
            generatedIndices[next] = true;
        } while (generated < 3);

        q[i] = *x[0] + (*x[1] - *x[2]) * F;
    }

    q.variate(p);
    p.checkForBetterSolutions(q);

}

int main() {

    Population p;
    do {
        differentialEvolution(p);
    } while (p.getCost() > 1e-14);

    cout << p.getCost() << endl << setprecision(15) << fixed << p;
    return 0;
}
