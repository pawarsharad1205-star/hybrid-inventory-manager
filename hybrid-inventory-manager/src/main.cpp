#include <iostream>
#include "InventoryManager.h"

int main() {
    InventoryManager inventoryManager;
    int choice;

    do {
        std::cout << "Inventory Manager Menu:\n";
        std::cout << "1. Add item\n";
        std::cout << "2. View item\n";
        std::cout << "3. Update item\n";
        std::cout << "4. Delete item\n";
        std::cout << "5. List all\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                inventoryManager.addItem();
                break;
            case 2:
                inventoryManager.viewItem();
                break;
            case 3:
                inventoryManager.updateItem();
                break;
            case 4:
                inventoryManager.deleteItem();
                break;
            case 5:
                inventoryManager.listItems();
                break;
            case 6:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}