#ifndef BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__ENTITY_H
#define BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__ENTITY_H

#include <string>

// Base class for all named elements in the simulation world
class Entity {
protected:
    std::string id;
    std::string name;
    std::string description;

public:
    Entity(const std::string& id, const std::string& name, const std::string& description);
    virtual ~Entity() = default;

    const std::string& getId() const;
    const std::string& getName() const;
    const std::string& getDescription() const;

    virtual std::string toString() const;

    bool operator==(const Entity& other) const;
    bool operator!=(const Entity& other) const;
};


#endif //BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__ENTITY_H