#ifndef BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__ENEMY_H
#define BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__ENEMY_H

#include "Character.h"
#include <string>

// Forward declaration
class Link;

// Abstract base for all enemies
class Enemy : public Character {
protected:
    int damage;
    int rupeeDrop;
    std::string regionId;

public:
    Enemy(const std::string& id, const std::string& name, const std::string& description, int maxHealth,
          int damage, int rupeeDrop, const std::string& regionId);
    virtual ~Enemy() = default;

    int getDamage() const;
    int getRupeeDrop() const;
    const std::string& getRegionId() const;

    // Pure virtual: each enemy type defines its own combat logic
    virtual std::string interact(Link& link) = 0;

    // Called each simulation turn
    virtual void update() {}

    virtual std::string toString() const override;
};

#endif //BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__ENEMY_H