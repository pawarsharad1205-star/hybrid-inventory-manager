#ifndef INVENTORY_H
#define INVENTORY_H

#define INVENTORY_FILE "inventory.dat"
#define NAME_LEN 40
#define MAX_ITEMS 1024

typedef struct {
    int   id;
    char  name[NAME_LEN];
    int   quantity;
    float price;
    int   is_deleted; /* 0 = active, 1 = deleted */
} Item;

#ifdef __cplusplus
extern "C" {
#endif

/* Add a new item. Returns 1 on success, 0 on failure (e.g. duplicate id). */
int add_item(const Item *item);

/* Find item by id and copy it into *out. Returns 1 on success, 0 if not found. */
int get_item(int id, Item *out);

/* Overwrite the record with matching id. Returns 1 on success, 0 if not found. */
int update_item(int id, const Item *updated);

/* Soft-delete the record with matching id. Returns 1 on success, 0 if not found. */
int delete_item(int id);

/* Copy up to max_items non-deleted items into buffer[]. Returns count copied. */
int list_items(Item *buffer, int max_items);

#ifdef __cplusplus
}
#endif

#endif /* INVENTORY_H */
