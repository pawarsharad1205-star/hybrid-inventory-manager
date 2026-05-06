#include "InventoryManager.h"

#include <iostream>
#include <limits>
#include <string>

/* ------------------------------------------------------------------ */
/* Input helpers                                                        */
/* ------------------------------------------------------------------ */

static int readPositiveInt(const char *prompt)
{
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value > 0)
            break;
        std::cout << "Invalid input – must be a positive integer. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

static int readNonNegativeInt(const char *prompt)
{
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= 0)
            break;
        std::cout << "Invalid input – must be 0 or greater. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

static float readNonNegativeFloat(const char *prompt)
{
    float value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= 0.0f)
            break;
        std::cout << "Invalid input – must be 0 or greater. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

static std::string readNonEmptyString(const char *prompt)
{
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (!value.empty())
            break;
        std::cout << "Name must not be empty. Try again.\n";
    }
    return value;
}

/* ------------------------------------------------------------------ */
/* Menu handlers                                                        */
/* ------------------------------------------------------------------ */

static void handleAdd(InventoryManager &mgr)
{
    int         id       = readPositiveInt("Enter ID: ");
    std::string name     = readNonEmptyString("Enter name: ");
    int         quantity = readNonNegativeInt("Enter quantity: ");
    float       price    = readNonNegativeFloat("Enter price: ");

    if (mgr.addItem(id, name, quantity, price))
        std::cout << "Item added successfully.\n";
    else
        std::cout << "Failed to add item (duplicate ID or file error).\n";
}

static void handleView(InventoryManager &mgr)
{
    int id = readPositiveInt("Enter ID to view: ");
    if (!mgr.viewItem(id))
        std::cout << "Item not found.\n";
}

static void handleUpdate(InventoryManager &mgr)
{
    int         id       = readPositiveInt("Enter ID to update: ");
    std::string name     = readNonEmptyString("Enter new name: ");
    int         quantity = readNonNegativeInt("Enter new quantity: ");
    float       price    = readNonNegativeFloat("Enter new price: ");

    if (mgr.updateItem(id, name, quantity, price))
        std::cout << "Item updated successfully.\n";
    else
        std::cout << "Item not found or update failed.\n";
}

static void handleDelete(InventoryManager &mgr)
{
    int id = readPositiveInt("Enter ID to delete: ");
    if (mgr.deleteItem(id))
        std::cout << "Item deleted.\n";
    else
        std::cout << "Item not found.\n";
}

static void handleList(InventoryManager &mgr)
{
    std::cout << "Sort by: (1) ID  (2) Name  [default: 1]: ";
    std::string choice;
    std::getline(std::cin, choice);
    SortOrder order = (choice == "2") ? SortOrder::BY_NAME : SortOrder::BY_ID;
    mgr.listItems(order);
}

/* ------------------------------------------------------------------ */
/* Main                                                                 */
/* ------------------------------------------------------------------ */

int main()
{
    InventoryManager mgr;

    while (true) {
        std::cout << "\n=== Hybrid Inventory Manager ===\n"
                     "1. Add item\n"
                     "2. View item\n"
                     "3. Update item\n"
                     "4. Delete item\n"
                     "5. List all\n"
                     "6. Exit\n"
                     "Choice: ";

        std::string line;
        std::getline(std::cin, line);

        if (line.empty())
            continue;

        char choice = line[0];

        switch (choice) {
        case '1': handleAdd(mgr);    break;
        case '2': handleView(mgr);   break;
        case '3': handleUpdate(mgr); break;
        case '4': handleDelete(mgr); break;
        case '5': handleList(mgr);   break;
        case '6':
            std::cout << "Goodbye.\n";
            return 0;
        default:
            std::cout << "Unknown option. Please enter 1-6.\n";
        }
    }
}
