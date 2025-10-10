/*
 CCCP - The C Create Coding Project

 Copyright (C) 2025 George Watson

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "cccp.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static unsigned long hash_string(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash;
}

CCCP_HashTable* CCCP_NewHashTable(size_t capacity) {
    if (capacity == 0)
        capacity = 16;
    CCCP_HashTable* table = malloc(sizeof(CCCP_HashTable));
    if (!table)
        return NULL;
    table->buckets = (CCCP_HashEntry**)calloc(capacity, sizeof(CCCP_HashEntry*));
    if (!table->buckets) {
        free(table);
        return NULL;
    }
    table->capacity = capacity;
    table->size = 0;
    return table;
}

void CCCP_DestroyHashTable(CCCP_HashTable* table) {
    if (!table) return;
    for (size_t i = 0; i < table->capacity; i++) {
        CCCP_HashEntry* entry = table->buckets[i];
        while (entry) {
            CCCP_HashEntry* next = entry->next;
            if (table->free_callback)
                table->free_callback(entry->value);
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(table->buckets);
    free(table);
}

int CCCP_HashTableInsert(CCCP_HashTable* table, const char* key, void* value) {
    if (!table || !key)
        return -1;
    unsigned long hash = hash_string(key);
    size_t index = hash % table->capacity;
    CCCP_HashEntry* entry = table->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value; // update
            return 0;
        }
        entry = entry->next;
    }
    // new entry
    CCCP_HashEntry* new_entry = malloc(sizeof(CCCP_HashEntry));
    if (!new_entry)
        return -1;
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = table->buckets[index];
    table->buckets[index] = new_entry;
    table->size++;
    return 0;
}

void* CCCP_HashTableGet(CCCP_HashTable* table, const char* key) {
    if (!table || !key)
        return NULL;
    unsigned long hash = hash_string(key);
    size_t index = hash % table->capacity;
    CCCP_HashEntry* entry = table->buckets[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

int CCCP_HashTableRemove(CCCP_HashTable* table, const char* key) {
    if (!table || !key)
        return -1;
    unsigned long hash = hash_string(key);
    size_t index = hash % table->capacity;
    CCCP_HashEntry* entry = table->buckets[index];
    CCCP_HashEntry* prev = NULL;
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                table->buckets[index] = entry->next;
            }
            if (table->free_callback)
                table->free_callback(entry->value);
            free(entry->key);
            free(entry);
            table->size--;
            return 0;
        }
        prev = entry;
        entry = entry->next;
    }
    return -1; // not found
}

size_t CCCP_HashTableSize(CCCP_HashTable* table) {
    return table ? table->size : 0;
}

void CCCP_HashTableClear(CCCP_HashTable* table) {
    if (!table)
        return;
    for (size_t i = 0; i < table->capacity; i++) {
        CCCP_HashEntry* entry = table->buckets[i];
        while (entry) {
            CCCP_HashEntry* next = entry->next;
            if (table->free_callback)
                table->free_callback(entry->value);
            free(entry->key);
            free(entry);
            entry = next;
        }
        table->buckets[i] = NULL;
    }
    table->size = 0;
}