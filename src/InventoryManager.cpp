#include "InventoryManager.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

extern "C" {
#include "inventory.h"
}

/* ------------------------------------------------------------------ */
/* Construction / destruction                                           */
/* ------------------------------------------------------------------ */

InventoryManager::InventoryManager() {}
InventoryManager::~InventoryManager() {}

/* ------------------------------------------------------------------ */
/* Private helper                                                       */
/* ------------------------------------------------------------------ */

/* Safely copy a std::string into a fixed-size C char array. */
static void copyName(const std::string &src, char *dest)
{
    src.copy(dest, NAME_LEN - 1);
    dest[NAME_LEN - 1] = '\0';
}

/* ------------------------------------------------------------------ */
/* Public operations                                                    */
/* ------------------------------------------------------------------ */

bool InventoryManager::addItem(int id, const std::string &name,
                               int quantity, float price)
{
    Item item{};
    item.id         = id;
    item.quantity   = quantity;
    item.price      = price;
    item.is_deleted = 0;
    copyName(name, item.name);

    return add_item(&item) == 1;
}

bool InventoryManager::viewItem(int id)
{
    Item item{};
    if (get_item(id, &item) != 1)
        return false;

    printHeader();
    printItem(item);
    return true;
}

bool InventoryManager::updateItem(int id, const std::string &name,
                                  int quantity, float price)
{
    Item updated{};
    updated.id         = id;
    updated.quantity   = quantity;
    updated.price      = price;
    updated.is_deleted = 0;
    copyName(name, updated.name);

    return update_item(id, &updated) == 1;
}

bool InventoryManager::deleteItem(int id)
{
    return delete_item(id) == 1;
}

void InventoryManager::listItems(SortOrder order)
{
    /* Use a heap-allocated vector to collect items from the C backend,
     * avoiding a large stack allocation. */
    std::vector<Item> buffer(MAX_ITEMS);
    int count = list_items(buffer.data(), MAX_ITEMS);

    if (count == 0) {
        std::cout << "No items in inventory.\n";
        return;
    }

    /* Trim to the actual number of active items, then sort. */
    buffer.resize(static_cast<std::size_t>(count));

    if (order == SortOrder::BY_NAME) {
        std::sort(buffer.begin(), buffer.end(), [](const Item &a, const Item &b) {
            return std::string(a.name) < std::string(b.name);
        });
    } else {
        std::sort(buffer.begin(), buffer.end(), [](const Item &a, const Item &b) {
            return a.id < b.id;
        });
    }

    printHeader();
    for (const auto &item : buffer)
        printItem(item);
}

/* ------------------------------------------------------------------ */
/* Private helpers                                                      */
/* ------------------------------------------------------------------ */

void InventoryManager::printHeader() const
{
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(42) << "Name"
              << std::setw(10) << "Qty"
              << std::setw(10) << "Price"
              << '\n';
    std::cout << std::string(68, '-') << '\n';
}

void InventoryManager::printItem(const Item &item) const
{
    std::cout << std::left
              << std::setw(6)  << item.id
              << std::setw(42) << item.name
              << std::setw(10) << item.quantity
              << std::fixed << std::setprecision(2)
              << std::setw(10) << item.price
              << '\n';
}
