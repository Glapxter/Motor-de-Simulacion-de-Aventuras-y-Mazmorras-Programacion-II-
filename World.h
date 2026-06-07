#ifndef BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__WORLD_H
#define BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__WORLD_H

#include "Region.h"
#include <map>
#include <string>
#include <vector>
#include <stdexcept>

// Holds all regions and loads them from data files
class World {
private:
    std::map<std::string, Region*> regions;

    void loadRegions(const std::string& path);
    void loadObjects(const std::string& path);
    void loadEnemies(const std::string& path);

    static std::string trim(const std::string& s);
    static std::vector<std::string> split(const std::string& s, char delimiter);

public:
    World();
    ~World();

    void load(const std::string& regionsPath, const std::string& objectsPath, const std::string& enemiesPath);

    Region* getRegion(const std::string& id) const;
    bool hasRegion(const std::string& id) const;

    const std::map<std::string, Region*>& getAllRegions() const;

    std::string toString() const;
};

#endif //BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__WORLD_H