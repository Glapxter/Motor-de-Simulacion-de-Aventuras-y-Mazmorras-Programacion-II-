//
// Created by antho on 6/6/2026.
//

#ifndef BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__LINK_H
#define BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__LINK_H

#include "Character.h"
#include "Inventory.h"
#include "WorldObject.h"
#include <string>

// The hero. Extends Character with rupees, attack power, and an inventory.
class Link : public Character {
private:
    int rupees;  // The money in Zelda world are rupees
    int attack;
    std::string currentRegionId;
    std::string goalRegionId;
    std::string goalEnemyId;
    Inventory<WorldObject> inventory;

public:
    Link(const std::string& name, int maxHealth, int attack, const std::string& startRegionId,
         const std::string& goalRegionId, const std::string& goalEnemyId);

    const std::string& getCurrentRegionId() const;
    void moveTo(const std::string& regionId);

    const std::string& getGoalRegionId() const;
    const std::string& getGoalEnemyId() const;

    int  getAttack() const;
    void addAttack(int bonus);

    int  getRupees() const;
    void addRupees(int amount);

    bool addItem(WorldObject* item);
    bool hasItem(const std::string& id) const;
    WorldObject* findItem(const std::string& id) const;
    WorldObject* removeItem(const std::string& id);
    const Inventory<WorldObject>& getInventory() const;

    virtual std::string toString() const override;
};


#endif //BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__LINK_H