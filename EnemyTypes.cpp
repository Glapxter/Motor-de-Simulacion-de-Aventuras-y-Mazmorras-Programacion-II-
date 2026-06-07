#include "EnemyTypes.h"
#include "Link.h"
using namespace std;

// ─── Moblin ───────────────────────────────────────────────────────────────────
Moblin::Moblin(const string& id, const string& name, const string& description, int maxHealth,
               int dmg, int rupeeDrop, const string& regionId) : Enemy(id, name, description, maxHealth, dmg, rupeeDrop, regionId) {}

string Moblin::interact(Link& link) {
    if (!isAlive()) return name + " is already defeated.";

    int dmgToLink = link.takeDamage(damage);
    int dmgToMob  = takeDamage(link.getAttack());

    string result = name + " attacks " + link.getName() +
                    " for " + to_string(dmgToLink) + " damage! " +
                    link.getName() + " strikes back for " +
                    to_string(dmgToMob) + " damage!";

    if (!isAlive()) {
        link.addRupees(rupeeDrop);
        result += " " + name + " is defeated! +" +
                  to_string(rupeeDrop) + " rupees.";
    }
    return result;
}

void Moblin::update() {}

string Moblin::toString() const {
    return "[Moblin] " + Enemy::toString();
}

// ─── Boss ─────────────────────────────────────────────────────────────────────
Boss::Boss(const string& id, const string& name, const string& description, int maxHealth,
           int dmg, int rupeeDrop, const string& regionId) : Enemy(id, name, description, maxHealth, dmg, rupeeDrop, regionId),
           phase(1), enraged(false) {}

string Boss::interact(Link& link) {
    if (!isAlive()) return name + " is already defeated.";

    string phaseMsg = "";
    if (!enraged && health <= maxHealth / 2) {
        enraged = true;
        phase = 2;
        damage = static_cast<int>(damage * 1.5);
        phaseMsg = " ** " + name + " enters ENRAGED phase! Damage increased! **";
    }

    int dmgToLink = link.takeDamage(damage);
    int dmgToBoss = takeDamage(link.getAttack());

    string result = name + " [Phase " + to_string(phase) + "] " +
                    "attacks " + link.getName() +
                    " for " + to_string(dmgToLink) + " damage! " +
                    link.getName() + " deals " +
                    to_string(dmgToBoss) + " damage!" + phaseMsg;

    if (!isAlive()) {
        link.addRupees(rupeeDrop);
        result += " " + name + " has been DEFEATED! The darkness fades!";
    }
    return result;
}

void Boss::update() {}

int  Boss::getPhase()  const
{
    return phase;
}
bool Boss::isEnraged() const
{
    return enraged;
}

string Boss::toString() const {
    return "[BOSS Ph." + to_string(phase) + "] " + Enemy::toString();
}