#include <iostream>
#include "SimulationEngine.h"
using namespace std;

int main() {
    cout << "=== Hyrule Adventure Simulation Engine ===" << endl;
    try {
        SimulationEngine engine(
            "data/regions.txt",
            "data/objects.txt",
            "data/enemies.txt",
            "data/link.txt",
            "output/log.txt",
            150
        );
        engine.run();
    } catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    }
    return 0;
}