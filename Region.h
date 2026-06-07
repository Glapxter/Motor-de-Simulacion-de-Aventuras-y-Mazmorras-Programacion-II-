#ifndef BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__REGION_H
#define BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__REGION_H

#include "Entity.h"
#include "WorldObject.h"
#include "Enemy.h"
#include <vector>
#include <string>

// Represents a location in the world (forest, castle, dungeon, etc.)
class Region : public Entity {
private:
    std::vector<std::string> connectionIds;
    std::vector<WorldObject*> objects;
    std::vector<Enemy*> enemies;
    bool visited;

public:
    Region(const std::string& id, const std::string& name, const std::string& description);
    ~Region();

    // Connections
    void addConnectionId(const std::string& id);
    const std::vector<std::string>& getConnectionIds() const;
    bool isConnectedTo(const std::string& regionId) const;

    // Objects
    void addObject(WorldObject* obj);
    WorldObject* findObject(const std::string& id) const;
    const std::vector<WorldObject*>& getObjects() const;

    // Enemies
    void addEnemy(Enemy* enemy);
    Enemy* findEnemy(const std::string& id) const;
    bool hasAliveEnemies() const;
    const std::vector<Enemy*>& getEnemies() const;

    bool isVisited() const;
    void markVisited();

    virtual std::string toString() const override;
};

#endif //BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__REGION_H