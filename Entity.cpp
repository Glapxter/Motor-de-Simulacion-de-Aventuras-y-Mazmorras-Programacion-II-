//
// Created by antho on 6/6/2026.
//

#include "Entity.h"
using namespace std;

Entity::Entity(const string& id, const string& name, const string& description)
    : id(id), name(name), description(description) {}

const string& Entity::getId() const
{
    return id;
}
const string& Entity::getName() const
{
    return name;
}
const string& Entity::getDescription() const
{
    return description;
}

string Entity::toString() const {
    return "[" + id + "] " + name + ": " + description;
}

bool Entity::operator==(const Entity& other) const
{
    return id == other.id;
}
bool Entity::operator!=(const Entity& other) const
{
    return id != other.id;
}