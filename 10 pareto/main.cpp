#include <cmath>
#include <vector>
#include <random>
#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std;
using namespace std::chrono;


#define I 1.
#define sigma 58.
#define delta 1e-2

struct node {
    double H, R;
    bool flag = true;

    node(double a, double b, double S) {
        H = I/2*sqrt(M_PI/(4*S)) *(
                (b + delta)/sqrt(pow(a, 2)+pow(b + delta, 2))
                - delta/sqrt(pow(a, 2)+pow(delta, 2))
        );
        R = 2*M_PI*a*b*sqrt(M_PI/(4*S))/(S*sigma);
    }
};

bool isMarkedForDeletion(const node* n) {
    return !n->flag;
}


int main() {
//    auto start = high_resolution_clock::now();
    mt19937 gen(time(nullptr));
    uniform_real_distribution<> aGen(1e-2, 5e-2), bGen(.1, .4), SGen(0.5e-6, 3e-6);
    vector<node*> paretoOptimals, nonParetoOptimals;
    paretoOptimals.reserve(1e3);
    nonParetoOptimals.reserve(1e6);
    node* x;
    double a, b, S;
    cout << fixed << std::setprecision(12);
    int cnt = 0;
    for (int i = 0; i < 1e6; i++) {
        a = aGen(gen);
        b = bGen(gen);
        S = SGen(gen);
        x = new node(a, b, S);

        for (auto& po: paretoOptimals) if (po->flag) {
            bool c1 = (x->H >= po->H), c2 = (x->R <= po->R);
            // samo ako je jedan optimalniji od drugog
            if (c1 == c2) {
                if (c1) {
                    po->flag = false;
                    nonParetoOptimals.push_back(po);
                    cout << po->H << endl << po->R << endl;
                } else {
                    x->flag = false;
                }
            }
        }

        if (++cnt == 300) {
            cnt = 0;
            erase_if(paretoOptimals, isMarkedForDeletion);
        }

        if (x->flag) {
            paretoOptimals.push_back(x);
        } else {
            nonParetoOptimals.push_back(x);
            cout << x->H << endl << x->R << endl;
        }
    }
    cout << endl;
//    cout << paretoOptimals.size();
    for (auto& po: paretoOptimals){
        cout << po->H << endl << po->R << endl;
        delete po;
    }

    for (auto& npo: nonParetoOptimals)
        delete npo;

//    cout << (high_resolution_clock::now() - start).count();

}

