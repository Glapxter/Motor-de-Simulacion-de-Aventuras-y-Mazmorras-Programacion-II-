#ifndef BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__INVENTORY_H
#define BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__INVENTORY_H

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

// Generic inventory — T must have getName() and getId() methods
template <typename T>
class Inventory {
private:
    std::vector<T*> items;
    int capacity;

public:
    explicit Inventory(int capacity = 20) : capacity(capacity) {}
    ~Inventory() = default;

    bool addItem(T* item) {
        if (static_cast<int>(items.size()) >= capacity) return false;

        items.push_back(item);
        return true;
    }

    T* findById(const std::string& id) const {
        for (T* item : items)
            if (item->getId() == id) return item;
        return nullptr;
    }

    T* removeById(const std::string& id) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if ((*it)->getId() == id) {
                T* item = *it;
                items.erase(it);
                return item;
            }
        }
        throw std::runtime_error("Item not found in inventory: " + id);
    }

    bool hasItem(const std::string& id) const
    {
        return findById(id) != nullptr;
    }
    int  size() const
    {
        return static_cast<int>(items.size());
    }
    bool isEmpty() const
    {
        return items.empty();
    }
    bool isFull() const
    {
        return static_cast<int>(items.size()) >= capacity;
    }
    const std::vector<T*>& getItems() const
    {
        return items;
    }

    T* operator[](int index) const
    {
        return items[index];
    }
};
#endif //BARRIOS_MARCHAN_ANTHONY__PROYECTO_2__INVENTORY_H