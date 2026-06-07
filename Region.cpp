#include "Region.h"
#include <algorithm>
using namespace std;

Region::Region(const string& id, const string& name, const string& description)
              : Entity(id, name, description), visited(false) {}

Region::~Region() {
    for (WorldObject* obj : objects) delete obj;
    for (Enemy* e : enemies) delete e;
}

void Region::addConnectionId(const string& id) {
    connectionIds.push_back(id);
}

const vector<string>& Region::getConnectionIds() const {
    return connectionIds;
}

bool Region::isConnectedTo(const string& regionId) const {
    return find(connectionIds.begin(), connectionIds.end(), regionId) != connectionIds.end();
}

void Region::addObject(WorldObject* obj) { objects.push_back(obj); }

WorldObject* Region::findObject(const string& id) const {
    for (WorldObject* obj : objects)
        if (obj->getId() == id) return obj;
    return nullptr;
}

const vector<WorldObject*>& Region::getObjects() const
{
    return objects;
}

void Region::addEnemy(Enemy* enemy)
{
    enemies.push_back(enemy);
}

Enemy* Region::findEnemy(const string& id) const {
    for (Enemy* e : enemies)
        if (e->getId() == id) return e;
    return nullptr;
}

bool Region::hasAliveEnemies() const {
    for (Enemy* e : enemies)
        if (e->isAlive()) return true;
    return false;
}

const vector<Enemy*>& Region::getEnemies() const
{
    return enemies;
}

bool Region::isVisited() const
{
    return visited;
}
void Region::markVisited()
{
    visited = true;
}

string Region::toString() const {
    string result = Entity::toString();
    result += " | Connections: ";
    for (const auto& c : connectionIds) result += c + " ";
    result += "| Enemies: " + to_string(enemies.size());
    result += " | Objects: " + to_string(objects.size());
    return result;
}