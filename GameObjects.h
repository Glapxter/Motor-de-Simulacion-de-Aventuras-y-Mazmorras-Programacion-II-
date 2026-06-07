
#ifndef BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__GAMEOBJECTS_H
#define BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__GAMEOBJECTS_H

#include "WorldObject.h"
#include "Character.h"
#include <string>

// ─── HeartContainer ──────────────────────────────────────────────────────────
class HeartContainer : public WorldObject {
private:
    int healAmount;
public:
    HeartContainer(const std::string& id, const std::string& name, const std::string& description, int healAmount);
    std::string interact(Character& character) override;
    int getHealAmount() const;
};

// ─── RupeePickup ──────────────────────────────────────────────────────────────
class RupeePickup : public WorldObject {
private:
    int amount;
public:
    RupeePickup(const std::string& id, const std::string& name, const std::string& description, int amount);
    std::string interact(Character& character) override;
    int getAmount() const;
};

// ─── Weapon ───────────────────────────────────────────────────────────────────
class Weapon : public WorldObject {
private:
    int attackBonus;
public:
    Weapon(const std::string& id, const std::string& name, const std::string& description, int attackBonus);
    std::string interact(Character& character) override;
    int getAttackBonus() const;
};

// ─── Key ──────────────────────────────────────────────────────────────────────
class Key : public WorldObject {
private:
    std::string unlocksDoorId;
public:
    Key(const std::string& id, const std::string& name, const std::string& description, const std::string& unlocksDoorId);
    std::string interact(Character& character) override;
    const std::string& getUnlocksDoorId() const;
};

// ─── Door ─────────────────────────────────────────────────────────────────────
class Door : public WorldObject {
private:
    std::string requiredKeyId;
    bool locked;
public:
    Door(const std::string& id, const std::string& name, const std::string& description, const std::string& requiredKeyId);
    std::string interact(Character& character) override;
    bool isLocked() const;
    void unlock();
    const std::string& getRequiredKeyId() const;
};

// ─── Chest ────────────────────────────────────────────────────────────────────
class Chest : public WorldObject {
private:
    std::string containsItemId;
public:
    Chest(const std::string& id, const std::string& name, const std::string& description, const std::string& containsItemId);
    std::string interact(Character& character) override;
    const std::string& getContainsItemId() const;
};

#endif //BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__GAMEOBJECTS_H