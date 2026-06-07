#ifndef BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__CHARACTER_H
#define BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__CHARACTER_H

#include "Entity.h"

// Represents any living character in the simulation (Link, enemies, NPCs)
class Character : public Entity {
protected:
    int health;
    int maxHealth;
    bool alive;

public:
    Character(const std::string& id, const std::string& name, const std::string& description, int maxHealth);
    virtual ~Character() = default;

    int getHealth() const;
    int getMaxHealth() const;
    bool isAlive() const;

    virtual int takeDamage(int amount);
    virtual void heal(int amount);

    virtual std::string toString() const override;
};

#endif //BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__CHARACTER_H