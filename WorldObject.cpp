#include "WorldObject.h"
using namespace std;

WorldObject::WorldObject(const string& id, const string& name, const string& description)
    : Entity(id, name, description), visible(true), active(true) {}

bool WorldObject::isVisible() const
{
    return visible;
}
bool WorldObject::isActive()  const
{
    return active;
}

void WorldObject::setVisible(bool value)
{
    visible = value;
}
void WorldObject::setActive(bool value)
{
    active  = value;
}

string WorldObject::toString() const {
    string status = active ? "active" : "used";
    return Entity::toString() + " [" + status + "]";
}