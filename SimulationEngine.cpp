#include "SimulationEngine.h"
#include "GameObjects.h"
#include "EnemyTypes.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <map>
using namespace std;

// ─── Constructor ──────────────────────────────────────────────────────────────
SimulationEngine::SimulationEngine(const string& regionsPath, const string& objectsPath, const string& enemiesPath,
                                   const string& linkPath, const string& logPath, int maxTurns) : world(nullptr),
                                   link(nullptr), logger(nullptr), maxTurns(maxTurns), result(SimulationResult::INCOMPLETE)
{
    logger = new Logger(logPath);
    *logger << "Loading world data...";

    world = new World();
    world->load(regionsPath, objectsPath, enemiesPath);
    *logger << "World loaded: " + to_string(world->getAllRegions().size()) + " regions.";

    ifstream linkFile(linkPath);
    if (!linkFile.is_open())
        throw runtime_error("Cannot open link file: " + linkPath);

    string name = "Link";
    int hp = 500, attack = 35;
    string startRegion = "kokiri_forest";
    string goalRegion = "ganons_tower";
    string goalEnemy = "boss003";

    string line;
    while (getline(linkFile, line)) {
        if (line.empty() || line[0] == '#') continue;
        istringstream iss(line);
        string key, value;
        iss >> key >> value;

        if (key == "NAME")
            name = value;
        else if (key == "HP")
            hp = stoi(value);
        else if (key == "MAX_HP")
            hp = stoi(value);
        else if (key == "ATTACK")
            attack = stoi(value);
        else if (key == "START_REGION")
            startRegion = value;
        else if (key == "GOAL_REGION")
            goalRegion = value;
        else if (key == "GOAL_ENEMY")
            goalEnemy = value;
    }

    link = new Link(name, hp, attack, startRegion, goalRegion, goalEnemy);
    *logger << name + " created. HP:" + to_string(hp) + " ATK:" + to_string(attack) + " Start:" + startRegion;
}

// ─── Destructor ───────────────────────────────────────────────────────────────
SimulationEngine::~SimulationEngine() {
    delete world;
    delete link;
    delete logger;
}

// ─── Run ──────────────────────────────────────────────────────────────────────
void SimulationEngine::run() {
    *logger << "\n=== SIMULATION START ===\n";

    while (logger->getTurn() <= maxTurns) {
        Region* current = world->getRegion(link->getCurrentRegionId());
        if (!current) {
            *logger << "ERROR: current region not found. Aborting.";
            break;
        }

        if (!current->isVisited()) {
            current->markVisited();
            logger->logTurn("Link enters: " + current->getName() +
                            " — " + current->getDescription());
        } else {
            logger->logTurn("Link is in: " + current->getName());
        }

        phaseInteractObjects(current);
        phaseResolveCombat(current);

        if (!link->isAlive()) {
            result = SimulationResult::DEFEAT;
            logger->logTurn("Link has fallen... The darkness wins.");
            break;
        }

        if (link->getCurrentRegionId() == link->getGoalRegionId()) {
            Enemy* finalBoss = current->findEnemy(link->getGoalEnemyId());
            if (!finalBoss || !finalBoss->isAlive()) {
                result = SimulationResult::VICTORY;
                logger->logTurn(" VICTORY! " + link->getName() + " has defeated Ganondorf and saved Hyrule!");
                break;
            }
        }

        phaseMove();
        logger->nextTurn();
    }

    if (result == SimulationResult::INCOMPLETE)
        logger->logTurn("Simulation reached max turns without conclusion.");

    logger->writeReport("output/report.txt", buildSummary());
    cout << "\nSimulation finished. Check output/log.txt and output/report.txt\n";
}

// ─── Phase: Interact with objects ─────────────────────────────────────────────
void SimulationEngine::phaseInteractObjects(Region* region) {
    tryUnlockDoors(region);

    for (WorldObject* obj : region->getObjects()) {
        if (!obj->isActive()) continue;

        if (Chest* chest = dynamic_cast<Chest*>(obj)) {
            string itemId = chest->getContainsItemId();
            string msg = chest->interact(*link);
            logger->logTurn(msg);
            for (auto& pair : world->getAllRegions()) {
                WorldObject* item = pair.second->findObject(itemId);
                if (item && item->isActive()) {
                    string itemMsg = item->interact(*link);
                    logger->logTurn(itemMsg);
                    applyObjectEffect(item);
                    break;
                }
            }
            continue;
        }

        string msg = obj->interact(*link);
        logger->logTurn(msg);
        applyObjectEffect(obj);
    }
}

// ─── Apply effect of object on Link
void SimulationEngine::applyObjectEffect(WorldObject* obj) {
    if (!obj || obj->isActive()) return;

    if (RupeePickup* r = dynamic_cast<RupeePickup*>(obj)) {
        link->addRupees(r->getAmount());
    } else if (Weapon* w = dynamic_cast<Weapon*>(obj)) {
        link->addAttack(w->getAttackBonus());
        logger->logTurn("  -> " + link->getName() + " attack is now " + to_string(link->getAttack()) + ".");
    } else if (Key* k = dynamic_cast<Key*>(obj)) {
        link->addItem(k);
        logger->logTurn("  -> Key added to inventory.");
    }
}

// ─── Phase: Resolve combat ────────────────────────────────────────────────────
void SimulationEngine::phaseResolveCombat(Region* region) {
    for (Enemy* enemy : region->getEnemies()) {
        if (!enemy->isAlive()) continue;
        if (!link->isAlive()) break;

        int rounds = 0;
        while (enemy->isAlive() && link->isAlive() && rounds < 20) {
            string msg = enemy->interact(*link);
            logger->logTurn("  [Combat] " + msg);
            logger->logTurn("  [Status] " + link->getName() + " HP:" + to_string(link->getHealth()) +
                            " | " + enemy->getName() + " HP:" + to_string(enemy->getHealth()));
            rounds++;
        }
    }
}

// ─── Try to unlock doors ──────────────────────────────────────────────────────
void SimulationEngine::tryUnlockDoors(Region* region) {
    for (WorldObject* obj : region->getObjects()) {
        Door* door = dynamic_cast<Door*>(obj);
        if (!door || !door->isLocked()) continue;

        WorldObject* keyItem = link->findItem(door->getRequiredKeyId());
        if (keyItem) {
            door->unlock();
            link->removeItem(door->getRequiredKeyId());
            logger->logTurn(link->getName() + " used a key to unlock: " + door->getName() + "!");
        }
    }
}

// ─── Phase: Move ──────────────────────────────────────────────────────────────
void SimulationEngine::phaseMove() {
    Region* current = world->getRegion(link->getCurrentRegionId());
    if (!current) return;

    if (current->hasAliveEnemies()) {
        logger->logTurn("Enemies remain in " + current->getName() + ". Link holds position.");
        return;
    }

    string next = chooseNextRegion();
    if (next.empty() || next == link->getCurrentRegionId()) {
        logger->logTurn("No path forward. Link explores the area.");
        return;
    }

    link->moveTo(next);
    logger->logTurn(link->getName() + " moves to: " +
                    world->getRegion(next)->getName() + ".");
}

// ─── Choose next region ───────────────────────────────────────────────────────
string SimulationEngine::chooseNextRegion() const {
    const string& from = link->getCurrentRegionId();
    const string& goal = link->getGoalRegionId();

    if (link->hasItem("key002"))
        return bfsNextStep(from, goal);

    map<string, string> parent;
    queue<string> q;
    q.push(from);
    parent[from] = "";

    while (!q.empty()) {
        string current = q.front(); q.pop();
        Region* region = world->getRegion(current);
        if (!region) continue;

        for (const string& neighborId : region->getConnectionIds()) {
            if (parent.find(neighborId) != parent.end()) continue;
            if (neighborId == "ganons_tower" && !link->hasItem("key002")) continue;

            parent[neighborId] = current;
            Region* neighbor = world->getRegion(neighborId);
            if (neighbor && !neighbor->isVisited()) {
                string step = neighborId;
                while (parent[step] != from) step = parent[step];
                return step;
            }
            q.push(neighborId);
        }
    }

    return bfsNextStep(from, goal);
}

// ─── BFS next step ────────────────────────────────────────────────────────────
string SimulationEngine::bfsNextStep(const string& from,
                                      const string& goal) const {
    if (from == goal) return from;

    map<string, string> parent;
    queue<string> q;
    q.push(from);
    parent[from] = "";

    while (!q.empty()) {
        string current = q.front(); q.pop();
        Region* region = world->getRegion(current);
        if (!region) continue;

        for (const string& neighborId : region->getConnectionIds()) {
            if (parent.find(neighborId) != parent.end()) continue;

            parent[neighborId] = current;
            if (neighborId == goal) {
                string step = goal;
                while (parent[step] != from) step = parent[step];
                return step;
            }
            q.push(neighborId);
        }
    }

    Region* r = world->getRegion(from);
    if (r && !r->getConnectionIds().empty())
        return r->getConnectionIds()[0];
    return from;
}

// ─── Build summary ────────────────────────────────────────────────────────────
string SimulationEngine::buildSummary() const {
    string outcome;
    switch (result) {
        case SimulationResult::VICTORY: outcome = "VICTORY"; break;
        case SimulationResult::DEFEAT: outcome = "DEFEAT"; break;
        case SimulationResult::INCOMPLETE: outcome = "INCOMPLETE"; break;
    }

    string s;
    s += "Outcome      : " + outcome + "\n";
    s += "Hero         : " + link->getName() + "\n";
    s += "Final HP     : " + to_string(link->getHealth()) +
         "/" + to_string(link->getMaxHealth()) + "\n";
    s += "Attack power : " + to_string(link->getAttack()) + "\n";
    s += "Rupees       : " + to_string(link->getRupees()) + "\n";
    s += "Final region : " + link->getCurrentRegionId() + "\n";
    s += "Total turns  : " + to_string(logger->getTurn()) + "\n";
    s += "\nRegions visited:\n";
    for (const auto& pair : world->getAllRegions())
        if (pair.second->isVisited())
            s += "  - " + pair.second->getName() + "\n";
    return s;
}

SimulationResult SimulationEngine::getResult() const
{
    return result;
}