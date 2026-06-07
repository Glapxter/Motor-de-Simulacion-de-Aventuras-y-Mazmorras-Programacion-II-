#include "World.h"
#include "GameObjects.h"
#include "EnemyTypes.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

// ─── Helpers ──────────────────────────────────────────────────────────────────
string World::trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

vector<string> World::split(const string& s, char delimiter) {
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter))
        tokens.push_back(trim(token));
    return tokens;
}

// ─── Constructor / Destructor ─────────────────────────────────────────────────
World::World() {}
World::~World() {
    for (auto& pair : regions) delete pair.second;
}

// ─── Load ─────────────────────────────────────────────────────────────────────
void World::load(const string& regionsPath, const string& objectsPath, const string& enemiesPath) {
    loadRegions(regionsPath);
    loadObjects(objectsPath);
    loadEnemies(enemiesPath);
}

void World::loadRegions(const string& path) {
    ifstream file(path);
    if (!file.is_open())
        throw runtime_error("Cannot open regions file: " + path);

    string line;
    while (getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;

        auto parts = split(line, '|');
        if (parts.size() < 4) continue;

        auto firstParts = split(parts[0], ' ');
        if (firstParts.size() < 2) continue;

        string id   = firstParts[1];
        string name = parts[1];
        string desc = parts[2];

        Region* region = new Region(id, name, desc);

        auto connections = split(parts[3], ',');
        for (const auto& conn : connections)
            if (!conn.empty()) region->addConnectionId(conn);

        regions[id] = region;
    }
}

void World::loadObjects(const string& path) {
    ifstream file(path);
    if (!file.is_open())
        throw runtime_error("Cannot open objects file: " + path);

    string line;
    while (getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;

        auto parts = split(line, '|');
        if (parts.size() < 5) continue;

        auto firstParts = split(parts[0], ' ');
        if (firstParts.size() < 2) continue;

        string type= firstParts[0];
        string id= firstParts[1];
        string name= parts[1];
        string desc= parts[2];
        string regionId= parts[3];
        string extra= parts[4];

        Region* region = getRegion(regionId);
        if (!region) {
            cerr << "Warning: region '" << regionId
                 << "' not found for object '" << id << "'\n";
            continue;
        }

        WorldObject* obj = nullptr;

        if (type == "HEART") {
            obj = new HeartContainer(id, name, desc, stoi(extra));
        } else if (type == "RUPEES") {
            obj = new RupeePickup(id, name, desc, stoi(extra));
        } else if (type == "WEAPON") {
            obj = new Weapon(id, name, desc, stoi(extra));
        } else if (type == "KEY") {
            obj = new Key(id, name, desc, extra);
        } else if (type == "DOOR") {
            obj = new Door(id, name, desc, extra);
        } else if (type == "CHEST") {
            obj = new Chest(id, name, desc, extra);
        } else {
            cerr << "Warning: unknown object type '" << type << "'\n";
            continue;
        }

        region->addObject(obj);
    }
}

void World::loadEnemies(const string& path) {
    ifstream file(path);
    if (!file.is_open())
        throw runtime_error("Cannot open enemies file: " + path);

    string line;
    while (getline(file, line)) {
        line = trim(line);
        if (line.empty() || line[0] == '#') continue;

        auto parts = split(line, '|');
        if (parts.size() < 7) continue;

        auto firstParts = split(parts[0], ' ');
        if (firstParts.size() < 2) continue;

        string type = firstParts[0];
        string id= firstParts[1];
        string name= parts[1];
        string desc = parts[2];
        int hp = stoi(parts[3]);
        int dmg = stoi(parts[4]);
        int drop = stoi(parts[5]);
        string regionId = parts[6];

        Region* region = getRegion(regionId);
        if (!region) {
            cerr << "Warning: region '" << regionId
                 << "' not found for enemy '" << id << "'\n";
            continue;
        }

        Enemy* enemy = nullptr;
        if (type == "MOBLIN") {
            enemy = new Moblin(id, name, desc, hp, dmg, drop, regionId);
        } else if (type == "BOSS") {
            enemy = new Boss(id, name, desc, hp, dmg, drop, regionId);
        } else {
            cerr << "Warning: unknown enemy type '" << type << "'\n";
            continue;
        }

        region->addEnemy(enemy);
    }
}

// ─── Accessors ────────────────────────────────────────────────────────────────
Region* World::getRegion(const string& id) const {
    auto it = regions.find(id);
    return (it != regions.end()) ? it->second : nullptr;
}

bool World::hasRegion(const string& id) const {
    return regions.find(id) != regions.end();
}

const map<string, Region*>& World::getAllRegions() const {
    return regions;
}

string World::toString() const {
    string result = "=== World Map ===\n";
    for (const auto& pair : regions)
        result += pair.second->toString() + "\n";
    return result;
}