# Hybrid Inventory Manager

## Project Overview
The Hybrid Inventory Manager is a console application designed to manage inventory items using a hybrid approach. The data layer is implemented in C, utilizing structs and binary file storage, while the user interface and menu system are developed in C++ using classes and the Standard Template Library (STL). This application allows users to perform basic CRUD (Create, Read, Update, Delete) operations on inventory items, ensuring data persistence through binary file storage.

## File Structure
```
hybrid-inventory-manager
├── include
│   └── inventory.h
├── src
│   ├── inventory.c
│   ├── InventoryManager.cpp
│   └── main.cpp
├── Makefile
└── README.md
```

## Build and Run Steps
1. **Clone the repository**:
   ```
   git clone <repository-url>
   cd hybrid-inventory-manager
   ```

2. **Build the project**:
   - Using Make:
     ```
     make
     ```
   - Using CMake:
     ```
     mkdir build
     cd build
     cmake ..
     make
     ```

3. **Run the application**:
   ```
   ./hybrid-inventory-manager
   ```

## Test Cases
- **Test Case 1**: Add three items and verify they persist after restarting the application.
- **Test Case 2**: Update an existing item and check that the changes are retained after restarting.
- **Test Case 3**: Attempt to add an item with a duplicate ID and ensure it is rejected.
- **Test Case 4**: Soft delete an item and confirm it does not appear in the list of items.
- **Test Case 5**: List all items and verify that only non-deleted items are displayed.

## Acceptance Criteria
- The application must allow adding, viewing, updating, and deleting inventory items.
- Data must persist across application restarts.
- Deleted items should not appear in any views or lists.
- Input validation must be implemented to ensure data integrity.