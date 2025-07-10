#include <stdio.h>
#include <stdlib.h>

#define HASHMAP_SIZE 100

typedef struct Entry {
    int key;
    int value;
    struct Entry* next;
} Entry; // tag name
// It lets you refer to this struct as struct Entry inside its own definition (which is needed for the next pointer).

typedef struct {
    Entry* buckets[HASHMAP_SIZE];
} Hashmap;

void hashmap_init(Hashmap* map) {
    for (int i = 0; i < HASHMAP_SIZE; ++i) {
        map->buckets[i] = NULL;
    }
}

unsigned int hash(int key) {
    return key % HASHMAP_SIZE;
}

void hashmap_insert(Hashmap* map, int key, int value) {
    unsigned int idx = hash(key);
    Entry* curr = map->buckets[idx];

    // Check if key already exists, update value if found
    while (curr != NULL) {
        if (curr->key == key) {
            curr->value = value;
            return;
        }
        curr = curr->next;
    }

    // Key not found, create new entry
    Entry* new_entry = (Entry*)malloc(sizeof(Entry));
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = map->buckets[idx];
    map->buckets[idx] = new_entry;
}

// Function to get value by key. Returns 1 if found, 0 otherwise. Value is stored in *out_value.
int hashmap_get(Hashmap* map, int key, int* out_value) {
    unsigned int idx = hash(key);
    Entry* curr = map->buckets[idx];
    while (curr != NULL) {
        if (curr->key == key) {
            *out_value = curr->value;
            return 1;
        }
        curr = curr->next;
    }
    return 0; // Not found
}

int main() {
    Hashmap map;
    hashmap_init(&map);

    // Insert some key-value pairs
    hashmap_insert(&map, 10, 100);
    hashmap_insert(&map, 20, 200);
    hashmap_insert(&map, 30, 300);
    hashmap_insert(&map, 10, 999); // Update value for key 10

    // Retrieve and print values
    int value;
    int keys[] = {10, 20, 30, 40};
    for (int i = 0; i < 4; ++i) {
        if (hashmap_get(&map, keys[i], &value)) {
            printf("Key %d => Value %d\n", keys[i], value);
        } else {
            printf("Key %d not found!\n", keys[i]);
        }
    }

    return 0;
}
