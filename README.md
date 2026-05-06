# Hybrid Inventory Manager

A console-based inventory management system that blends a **C data layer** (binary file storage using structs + `fread`/`fwrite`/`fseek`) with a **C++ UI layer** (class, `std::vector`, `std::sort`).

## Project Structure

```
hybrid-inventory-manager/
├── include/
│   ├── inventory.h          # C struct + function declarations (with C++ extern "C" guards)
│   └── InventoryManager.h   # C++ class declaration
├── src/
│   ├── inventory.c          # C backend: binary file CRUD
│   ├── InventoryManager.cpp # C++ wrapper using STL
│   └── main.cpp             # Console menu + input validation
├── Makefile
└── README.md
```

## Build & Run

**Prerequisites:** `gcc`, `g++`, `make`

```bash
# Build
make

# Run
./inventory_manager

# Clean build artifacts and data file
make clean
```

Data persists in `inventory.dat` (binary) in the working directory.

## Menu

```
=== Hybrid Inventory Manager ===
1. Add item
2. View item
3. Update item
4. Delete item
5. List all
6. Exit
```

## Test Cases

- **Add 3 items and list:** Added items with IDs 1, 2, 3 (Widget A, Gadget B, Tool C). Chose "List all" — all three appeared correctly sorted by ID.
- **Persistence after restart:** Exited the program, re-launched, chose "List all" — all three items were still present, confirming binary file persistence.
- **View by ID:** Chose "View item" with ID 2 — displayed only "Gadget B" with correct quantity and price.
- **Update then verify:** Updated item ID 1 to "Widget UPDATED" with new quantity and price. Viewed item 1 — reflected the new values both in-session and after restart.
- **Delete then list:** Deleted item ID 2. Chose "List all" — only items 1 and 3 appeared; item 2 was absent (soft-deleted). Attempting to view item 2 returned "Item not found."
- **Duplicate ID rejected:** Tried to add a new item with an already-existing ID — received "Failed to add item (duplicate ID or file error)" and no duplicate was written.
