#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

#define FILENAME "inventory.dat"

int add_item(const Item item) {
    FILE *file = fopen(FILENAME, "ab");
    if (!file) return 0;

    fwrite(&item, sizeof(Item), 1, file);
    fclose(file);
    return 1;
}

int get_item(int id, Item *out) {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) return 0;

    Item item;
    while (fread(&item, sizeof(Item), 1, file)) {
        if (item.id == id && item.is_deleted == 0) {
            *out = item;
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int update_item(int id, const Item updated) {
    FILE *file = fopen(FILENAME, "r+b");
    if (!file) return 0;

    Item item;
    long pos;
    while ((pos = ftell(file)), fread(&item, sizeof(Item), 1, file)) {
        if (item.id == id && item.is_deleted == 0) {
            fseek(file, pos, SEEK_SET);
            fwrite(&updated, sizeof(Item), 1, file);
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int delete_item(int id) {
    FILE *file = fopen(FILENAME, "r+b");
    if (!file) return 0;

    Item item;
    long pos;
    while ((pos = ftell(file)), fread(&item, sizeof(Item), 1, file)) {
        if (item.id == id && item.is_deleted == 0) {
            item.is_deleted = 1;
            fseek(file, pos, SEEK_SET);
            fwrite(&item, sizeof(Item), 1, file);
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int list_items(Item *buffer, int max_items) {
    FILE *file = fopen(FILENAME, "rb");
    if (!file) return 0;

    int count = 0;
    Item item;
    while (fread(&item, sizeof(Item), 1, file) && count < max_items) {
        if (item.is_deleted == 0) {
            buffer[count++] = item;
        }
    }
    fclose(file);
    return count;
}