#include "GameObjects.h"
using namespace std;

// ─── HeartContainer ───────────────────────────────────────────────────────────
HeartContainer::HeartContainer(const string& id, const string& name, const string& description, int healAmount)
    : WorldObject(id, name, description), healAmount(healAmount) {}

string HeartContainer::interact(Character& character) {
    if (!active) return name + " has already been collected.";
    character.heal(healAmount);
    setActive(false);
    return character.getName() + " collected " + name +
           " and restored " + to_string(healAmount) + " HP!";
}

int HeartContainer::getHealAmount() const { return healAmount; }

// ─── RupeePickup ──────────────────────────────────────────────────────────────
RupeePickup::RupeePickup(const string& id, const string& name, const string& description, int amount)
    : WorldObject(id, name, description), amount(amount) {}

string RupeePickup::interact(Character& character) {
    if (!active) return name + " has already been collected.";
    setActive(false);
    return character.getName() + " picked up " + name +
           " (" + to_string(amount) + " rupees)!";
}

int RupeePickup::getAmount() const { return amount; }

// ─── Weapon ───────────────────────────────────────────────────────────────────
Weapon::Weapon(const string& id, const string& name, const string& description, int attackBonus)
    : WorldObject(id, name, description), attackBonus(attackBonus) {}

string Weapon::interact(Character& character) {
    if (!active) return name + " has already been taken.";
    setActive(false);
    return character.getName() + " equipped " + name +
           "! Attack +" + to_string(attackBonus) + ".";
}

int Weapon::getAttackBonus() const { return attackBonus; }

// ─── Key ──────────────────────────────────────────────────────────────────────
Key::Key(const string& id, const string& name, const string& description, const string& unlocksDoorId)
    : WorldObject(id, name, description), unlocksDoorId(unlocksDoorId) {}

string Key::interact(Character& character) {
    if (!active) return name + " has already been taken.";
    setActive(false);
    return character.getName() + " picked up " + name + "!";
}

const string& Key::getUnlocksDoorId() const { return unlocksDoorId; }

// ─── Door ─────────────────────────────────────────────────────────────────────
Door::Door(const string& id, const string& name, const string& description, const string& requiredKeyId)
    : WorldObject(id, name, description), requiredKeyId(requiredKeyId), locked(true) {}

string Door::interact(Character& character) {
    if (!locked) return name + " is already open.";
    return name + " is locked. " + character.getName() +
           " needs key: " + requiredKeyId + ".";
}

bool Door::isLocked() const
{
    return locked;
}
void Door::unlock()
{
    locked = false; setActive(false);
}
const string& Door::getRequiredKeyId() const
{
    return requiredKeyId;
}

// ─── Chest ────────────────────────────────────────────────────────────────────
Chest::Chest(const string& id, const string& name, const string& description, const string& containsItemId)
    : WorldObject(id, name, description), containsItemId(containsItemId) {}

string Chest::interact(Character& character) {
    if (!active) return name + " is already open and empty.";
    setActive(false);
    return character.getName() + " opened " + name +
           " and found item: " + containsItemId + "!";
}

const string& Chest::getContainsItemId() const { return containsItemId; }