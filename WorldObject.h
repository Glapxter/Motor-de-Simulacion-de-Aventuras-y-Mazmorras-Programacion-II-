#ifndef BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__WORLDOBJECT_H
#define BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__WORLDOBJECT_H

#include "Entity.h"
#include <string>

// Forward declaration to avoid circular includes
class Character;

// Abstract base for all interactive objects in a region
class WorldObject : public Entity {
protected:
    bool visible;
    bool active;

public:
    WorldObject(const std::string& id, const std::string& name, const std::string& description);
    virtual ~WorldObject() = default;

    bool isVisible() const;
    bool isActive()  const;

    void setVisible(bool value);
    void setActive(bool value);

    // Pure virtual: each object type defines its own interaction logic
    virtual std::string interact(Character& character) = 0;

    virtual std::string toString() const override;
};

#endif //BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__WORLDOBJECT_H