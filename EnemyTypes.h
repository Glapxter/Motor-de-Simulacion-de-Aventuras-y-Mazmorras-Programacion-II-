#ifndef BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__ENEMYTYPES_H
#define BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__ENEMYTYPES_H

#include "Enemy.h"

// Forward declaration
class Link;

// ─── Moblin ───────────────────────────────────────────────────────────────────
// Standard enemy with straightforward combat behavior
class Moblin : public Enemy {
public:
    Moblin(const std::string& id, const std::string& name, const std::string& description, int maxHealth,
           int damage, int rupeeDrop, const std::string& regionId);

    std::string interact(Link& link) override;
    void update() override;

    std::string toString() const override;
};

// ─── Boss ─────────────────────────────────────────────────────────────────────
// Powerful enemy with two phases; gets stronger below 50% HP
class Boss : public Enemy {
private:
    int  phase;
    bool enraged;

public:
    Boss(const std::string& id, const std::string& name, const std::string& description, int maxHealth,
         int damage, int rupeeDrop, const std::string& regionId);

    std::string interact(Link& link) override;
    void update() override;

    int  getPhase() const;
    bool isEnraged() const;

    std::string toString() const override;
};

#endif //BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__ENEMYTYPES_H