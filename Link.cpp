#include "Link.h"
using namespace std;

Link::Link(const string& name, int maxHealth, int attack, const string& startRegionId,
           const string& goalRegionId, const string& goalEnemyId) : Character("link", name, "The Hero of Time.", maxHealth),
           rupees(0), attack(attack), currentRegionId(startRegionId), goalRegionId(goalRegionId), goalEnemyId(goalEnemyId),
           inventory(20) {}

const string& Link::getCurrentRegionId() const
{
    return currentRegionId;
}
void Link::moveTo(const string& regionId)
{
    currentRegionId = regionId;
}

const string& Link::getGoalRegionId() const
{
    return goalRegionId;
}
const string& Link::getGoalEnemyId()  const
{
    return goalEnemyId;
}

int  Link::getAttack() const
{
    return attack;
}
void Link::addAttack(int bonus)
{
    attack += bonus;
}

int  Link::getRupees() const
{
    return rupees;
}
void Link::addRupees(int amount)
{
    rupees += amount;
}

bool Link::addItem(WorldObject* item)
{
    return inventory.addItem(item);
}
bool Link::hasItem(const string& id) const
{
    return inventory.hasItem(id);
}
WorldObject* Link::findItem(const string& id) const
{
    return inventory.findById(id);
}
WorldObject* Link::removeItem(const string& id) {
    try { return inventory.removeById(id); }
    catch (...) { return nullptr; }
}
const Inventory<WorldObject>& Link::getInventory() const
{
    return inventory;
}

string Link::toString() const {
    return Character::toString() +
           " | ATK: "    + to_string(attack)        +
           " | Rupees: " + to_string(rupees)        +
           " | Region: " + currentRegionId          +
           " | Items: "  + to_string(inventory.size());
}