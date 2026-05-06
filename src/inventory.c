#include "inventory.h"

#include <stdio.h>
#include <string.h>

/* Open the binary inventory file.
 * mode: "rb" / "wb" / "r+b" (standard fopen modes).
 * Returns NULL on failure. */
static FILE *open_file(const char *mode)
{
    return fopen(INVENTORY_FILE, mode);
}

/* Return the total number of records currently stored in the file
 * (including deleted ones). */
static long record_count(FILE *fp)
{
    if (fseek(fp, 0, SEEK_END) != 0)
        return -1;
    long size = ftell(fp);
    if (size < 0)
        return -1;
    return size / (long)sizeof(Item);
}

/* ------------------------------------------------------------------ */

int add_item(const Item *item)
{
    if (!item)
        return 0;

    /* First check for duplicate id.
     * Open in read mode; if the file does not exist yet that is fine –
     * no records means no duplicates. */
    FILE *fp = open_file("rb");
    if (fp) {
        Item tmp;
        while (fread(&tmp, sizeof(Item), 1, fp) == 1) {
            if (!tmp.is_deleted && tmp.id == item->id) {
                fclose(fp);
                return 0; /* duplicate */
            }
        }
        fclose(fp);
    }

    /* Append the new record. */
    fp = open_file("ab");
    if (!fp)
        return 0;

    int ok = (fwrite(item, sizeof(Item), 1, fp) == 1);
    fclose(fp);
    return ok;
}

/* ------------------------------------------------------------------ */

int get_item(int id, Item *out)
{
    if (!out)
        return 0;

    FILE *fp = open_file("rb");
    if (!fp)
        return 0;

    Item tmp;
    int found = 0;
    while (fread(&tmp, sizeof(Item), 1, fp) == 1) {
        if (!tmp.is_deleted && tmp.id == id) {
            *out = tmp;
            found = 1;
            break;
        }
    }
    fclose(fp);
    return found;
}

/* ------------------------------------------------------------------ */

int update_item(int id, const Item *updated)
{
    if (!updated)
        return 0;

    FILE *fp = open_file("r+b");
    if (!fp)
        return 0;

    long count = record_count(fp);
    if (count < 0) {
        fclose(fp);
        return 0;
    }

    rewind(fp);
    Item tmp;
    int found = 0;
    for (long i = 0; i < count; i++) {
        long offset = i * (long)sizeof(Item);
        if (fseek(fp, offset, SEEK_SET) != 0)
            break;
        if (fread(&tmp, sizeof(Item), 1, fp) != 1)
            break;
        if (!tmp.is_deleted && tmp.id == id) {
            /* Write the updated record at the same offset. */
            if (fseek(fp, offset, SEEK_SET) != 0)
                break;
            /* Preserve the original id so the caller cannot accidentally
             * change it to something else (optional safety measure). */
            Item to_write = *updated;
            to_write.id = id;
            to_write.is_deleted = 0;
            if (fwrite(&to_write, sizeof(Item), 1, fp) == 1)
                found = 1;
            break;
        }
    }
    fclose(fp);
    return found;
}

/* ------------------------------------------------------------------ */

int delete_item(int id)
{
    FILE *fp = open_file("r+b");
    if (!fp)
        return 0;

    long count = record_count(fp);
    if (count < 0) {
        fclose(fp);
        return 0;
    }

    rewind(fp);
    Item tmp;
    int found = 0;
    for (long i = 0; i < count; i++) {
        long offset = i * (long)sizeof(Item);
        if (fseek(fp, offset, SEEK_SET) != 0)
            break;
        if (fread(&tmp, sizeof(Item), 1, fp) != 1)
            break;
        if (!tmp.is_deleted && tmp.id == id) {
            tmp.is_deleted = 1;
            if (fseek(fp, offset, SEEK_SET) != 0)
                break;
            if (fwrite(&tmp, sizeof(Item), 1, fp) == 1)
                found = 1;
            break;
        }
    }
    fclose(fp);
    return found;
}

/* ------------------------------------------------------------------ */

int list_items(Item *buffer, int max_items)
{
    if (!buffer || max_items <= 0)
        return 0;

    FILE *fp = open_file("rb");
    if (!fp)
        return 0;

    int count = 0;
    Item tmp;
    while (count < max_items && fread(&tmp, sizeof(Item), 1, fp) == 1) {
        if (!tmp.is_deleted) {
            buffer[count++] = tmp;
        }
    }
    fclose(fp);
    return count;
}
