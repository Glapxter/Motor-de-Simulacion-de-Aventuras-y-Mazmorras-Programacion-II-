#ifndef BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__SIMULATIONENGINE_H
#define BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__SIMULATIONENGINE_H

#include "World.h"
#include "Link.h"
#include "Logger.h"
#include <string>

// Outcome of the simulation
enum class SimulationResult {
    VICTORY,
    DEFEAT,
    INCOMPLETE
};

// Orchestrates the entire simulation
class SimulationEngine {
private:
    World* world;
    Link* link;
    Logger* logger;
    int maxTurns;
    SimulationResult result;

    void phaseInteractObjects(Region* region);
    void phaseResolveCombat(Region* region);
    void phaseMove();

    void applyObjectEffect(WorldObject* obj);
    void tryUnlockDoors(Region* region);
    std::string chooseNextRegion() const;
    std::string bfsNextStep(const std::string& from, const std::string& goal) const;
    std::string buildSummary() const;

public:
    SimulationEngine(const std::string& regionsPath, const std::string& objectsPath, const std::string& enemiesPath,
                     const std::string& linkPath, const std::string& logPath, int maxTurns = 100);
    ~SimulationEngine();

    void run();

    SimulationResult getResult() const;
};

#endif //BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__SIMULATIONENGINE_H