#include <iostream>
#include <vector>
#include <algorithm>
#include "inventory.h"

class InventoryManager {
public:
    void addItem() {
        Item item;
        std::cout << "Enter item ID: ";
        std::cin >> item.id;
        if (item.id <= 0) {
            std::cout << "Invalid ID. Must be positive." << std::endl;
            return;
        }
        std::cout << "Enter item name: ";
        std::cin.ignore();
        std::cin.getline(item.name, 40);
        if (strlen(item.name) == 0) {
            std::cout << "Invalid name. Cannot be empty." << std::endl;
            return;
        }
        std::cout << "Enter item quantity: ";
        std::cin >> item.quantity;
        if (item.quantity < 0) {
            std::cout << "Invalid quantity. Must be 0 or more." << std::endl;
            return;
        }
        std::cout << "Enter item price: ";
        std::cin >> item.price;
        if (item.price < 0) {
            std::cout << "Invalid price. Must be 0 or more." << std::endl;
            return;
        }
        item.is_deleted = 0;

        if (add_item(item) == 0) {
            std::cout << "Failed to add item. ID may already exist." << std::endl;
        } else {
            std::cout << "Item added successfully." << std::endl;
        }
    }

    void viewItem() {
        int id;
        std::cout << "Enter item ID to view: ";
        std::cin >> id;
        Item item;
        if (get_item(id, item) == 1) {
            if (item.is_deleted == 0) {
                std::cout << "ID: " << item.id << ", Name: " << item.name 
                          << ", Quantity: " << item.quantity 
                          << ", Price: " << item.price << std::endl;
            } else {
                std::cout << "Item is deleted." << std::endl;
            }
        } else {
            std::cout << "Item not found." << std::endl;
        }
    }

    void updateItem() {
        int id;
        std::cout << "Enter item ID to update: ";
        std::cin >> id;
        Item updatedItem;
        if (get_item(id, updatedItem) == 1 && updatedItem.is_deleted == 0) {
            std::cout << "Updating item ID: " << updatedItem.id << std::endl;
            std::cout << "Enter new name: ";
            std::cin.ignore();
            std::cin.getline(updatedItem.name, 40);
            std::cout << "Enter new quantity: ";
            std::cin >> updatedItem.quantity;
            std::cout << "Enter new price: ";
            std::cin >> updatedItem.price;

            if (update_item(id, updatedItem) == 1) {
                std::cout << "Item updated successfully." << std::endl;
            } else {
                std::cout << "Failed to update item." << std::endl;
            }
        } else {
            std::cout << "Item not found or is deleted." << std::endl;
        }
    }

    void deleteItem() {
        int id;
        std::cout << "Enter item ID to delete: ";
        std::cin >> id;
        if (delete_item(id) == 1) {
            std::cout << "Item deleted successfully." << std::endl;
        } else {
            std::cout << "Failed to delete item. Item may not exist." << std::endl;
        }
    }

    void listItems() {
        std::vector<Item> items;
        Item buffer[100];
        int count = list_items(buffer, 100);
        for (int i = 0; i < count; ++i) {
            items.push_back(buffer[i]);
        }

        std::sort(items.begin(), items.end(), [](const Item &a, const Item &b) {
            return a.id < b.id; // Sort by ID
        });

        std::cout << "Listing all items:" << std::endl;
        for (const auto &item : items) {
            if (item.is_deleted == 0) {
                std::cout << "ID: " << item.id << ", Name: " << item.name 
                          << ", Quantity: " << item.quantity 
                          << ", Price: " << item.price << std::endl;
            }
        }
    }
};