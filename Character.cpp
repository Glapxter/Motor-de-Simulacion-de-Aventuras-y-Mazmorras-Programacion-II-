#include "Character.h"
#include <algorithm>
using namespace std;

Character::Character(const string& id, const string& name,
                     const string& description, int maxHealth)
    : Entity(id, name, description),
      health(maxHealth), maxHealth(maxHealth), alive(true) {}

int  Character::getHealth()    const { return health; }
int  Character::getMaxHealth() const { return maxHealth; }
bool Character::isAlive()      const { return alive; }

int Character::takeDamage(int amount) {
    if (!alive) return 0;
    int actual = min(amount, health);
    health -= actual;
    if (health <= 0) {
        health = 0;
        alive  = false;
    }
    return actual;
}

void Character::heal(int amount) {
    if (!alive) return;
    health = min(health + amount, maxHealth);
}

string Character::toString() const {
    return Entity::toString() +
           " | HP: " + to_string(health) +
           "/" + to_string(maxHealth);
}