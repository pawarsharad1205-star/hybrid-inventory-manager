#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <string>
#include <vector>

extern "C" {
#include "inventory.h"
}

enum class SortOrder { BY_ID, BY_NAME };

class InventoryManager {
public:
    InventoryManager();
    ~InventoryManager();

    /* CRUD operations – return true on success, false on failure. */
    bool addItem(int id, const std::string &name, int quantity, float price);
    bool viewItem(int id);
    bool updateItem(int id, const std::string &name, int quantity, float price);
    bool deleteItem(int id);

    /* List all active items, sorted by id (default) or name. */
    void listItems(SortOrder order = SortOrder::BY_ID);

private:
    void printHeader() const;
    void printItem(const Item &item) const;
};

#endif /* INVENTORYMANAGER_H */
