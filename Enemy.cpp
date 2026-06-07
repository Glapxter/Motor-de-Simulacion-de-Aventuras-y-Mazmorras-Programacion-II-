#include "Enemy.h"

using namespace std;

Enemy::Enemy(const string& id, const string& name, const string& description, int maxHealth,
             int dmg, int rupeeDrop, const string& regionId) : Character(id, name, description,
             maxHealth), damage(dmg), rupeeDrop(rupeeDrop), regionId(regionId) {}

int Enemy::getDamage() const
{
    return damage;
}
int Enemy::getRupeeDrop() const
{
    return rupeeDrop;
}
const string& Enemy::getRegionId()  const
{
    return regionId;
}

string Enemy::toString() const {
    return Character::toString() +
           " | DMG: " + to_string(damage) +
           " | Drop: " + to_string(rupeeDrop) + " rupees";
}