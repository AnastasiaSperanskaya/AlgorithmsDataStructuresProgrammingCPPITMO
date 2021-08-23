#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define mapsize (1 << 20)
#define setsize (1 << 8)
#define strsize 22

typedef struct  set_node
{
    set_node * prev = NULL;
    set_node * next = NULL;
    char val[strsize];
} set_node;

typedef struct set
{
    set_node * first = NULL;
    int size;
} set;

typedef struct map_node
{
    map_node * prev = NULL;
    map_node * next = NULL;
    set * set = NULL;
    char key[strsize];
} map_node;

typedef struct multimap
{
    map_node * first = NULL;
} multimap;

int hash_func(char * arg);
int map_hash(char * key);
int set_hash(char * val);
void insert_val(map_node * mapnode, char * val);
void delete_val(map_node * mapnode, char * val);
map_node * make_map_node(char * key);
set * make_set(char * val);
void set_print(set * set, FILE * file);
void put(multimap * multimap, char * key, char * val);
void delete_set_node(multimap * multimap, char * key, char * val);
void delete_map_node(multimap * multimap, char * key);
set * get_map_node_set(multimap * multimap, char * key);

int multimapsize = 0;

int main()
{
    FILE * in, *out;
    in = fopen("multimap.in", "r");
    out = fopen("multimap.out", "w");

    multimap map[mapsize];
    char command[strsize];
    char key[strsize];
    char val[strsize];

    fscanf(in, "%s", command);
    fscanf(in, "%s", key);
    while (true)
    {
        if (strcmp(command, "put") == 0)
        {
            fscanf(in, "%s", val);
            put(&map[0], key, val);
        }

        else if (strcmp(command, "delete") == 0)
        {
            fscanf(in, "%s", val);
            delete_set_node(&map[0], key, val);
        }

        else if (strcmp(command, "deleteall") == 0)
            delete_map_node(&map[0], key);

        else if (strcmp(command, "get") == 0)
        {
            set * findset = get_map_node_set(&map[0], key);
            if (findset == NULL)
                fprintf(out, "0\n");
            else set_print(findset, out);
        }

        if (feof(in))
            break;

        strcpy(command, "");
        fscanf(in, "%s", command);
        fscanf(in, "%s", key);
    }

    fclose(in);
    fclose(out);
    return 0;
}

int hash_func(char * arg)
{
    int result = 0;
    for (int i = 0; i < strlen(arg); i++)
    {
        result *= 31;
        result += arg[i];
    }
    return abs(result);
}

int map_hash(char * key)
{
    return hash_func(key) % mapsize;
}

int set_hash(char * val)
{
    return hash_func(val) % setsize;
}

map_node * make_map_node(char * key)
{
    map_node * new_map_node = new map_node;
    strcpy(new_map_node->key, key);
    return new_map_node;
}

set * make_set(char * val)
{
    set * new_set = new set[setsize];
    int hash = set_hash(val);
    new_set[hash].first = new set_node;
    strcpy(new_set[hash].first->val, val);
    return new_set;
}

void put(multimap * multimap, char * key, char * val)
{
    int hash = map_hash(key);
    map_node *mapnode = multimap[hash].first;

    if (mapnode == NULL)
    {
        multimap[hash].first = make_map_node(key);
        multimap[hash].first->set = make_set(val);
        multimap[hash].first->set->size = 1;
        multimapsize++;
        return;
    }

    while (true)
    {
        if (strcmp(mapnode->key, key) == 0)
        {
            insert_val(mapnode, val);
            return;
        }
        else if (mapnode->next == NULL)
        {
            mapnode->next = make_map_node(key);
            mapnode->next->set = make_set(val);
            mapnode->next->set->size = 1;
            mapnode->next->prev = mapnode;
            multimapsize++;
            return;
        }
        else mapnode = mapnode->next;
    }
}

void insert_val(map_node * mapnode, char * val)
{
    int hash = set_hash(val);
    set_node * setnode = mapnode->set[hash].first;

    if (setnode == NULL)
    {
        mapnode->set[hash].first = new set_node;
        strcpy(mapnode->set[hash].first->val, val);
        mapnode->set->size++;
    }

    else
    {
        while (true)
        {
            if (strcmp(setnode->val, val) == 0)
                return;
            if (setnode->next == NULL)
            {
                setnode->next = new set_node;
                strcpy(setnode->next->val, val);
                setnode->next->prev = setnode;
                mapnode->set->size++;
                break;
            }
            else setnode = setnode->next;
        }

    }
}

set * get_map_node_set(multimap * multimap, char * key)
{
    if (multimapsize == 0)
        return NULL;

    int hash = map_hash(key);
    map_node * mapnode = multimap[hash].first;

    while (mapnode != NULL)
    {
        if (strcmp(mapnode->key, key) == 0)
        {
            if (mapnode->set->size > 0)
                return mapnode->set;
            else return NULL;
        }
        mapnode = mapnode->next;
    }

    return NULL;
}

void set_print(set * set, FILE * file)
{
    fprintf(file, "%d ", set->size);

    for (int i = 0; i < setsize; i++)
    {
        set_node * setnode = set[i].first;
        while (setnode != NULL)
        {
            fprintf(file, "%s ", setnode->val);
            setnode = setnode->next;
        }
    }
    fprintf(file, "\n");
}

void delete_val(map_node * mapnode, char * val)
{
    int hash = set_hash(val);
    set_node * setnode = mapnode->set[hash].first;

    while (setnode != NULL)
    {
        if (strcmp(setnode->val, val) == 0)
        {
            if (setnode->prev == NULL && setnode->next == NULL)
                mapnode->set[hash].first = NULL;
            else if (setnode->prev == NULL)
            {
                mapnode->set[hash].first = setnode->next;
                setnode->next->prev = NULL;
            }
            else if (setnode->next == NULL)
                setnode->prev->next = NULL;
            else
            {
                setnode->prev->next = setnode->next;
                setnode->next->prev = setnode->prev;
            }
            mapnode->set->size--;
            delete setnode;
            return;
        }
        else setnode = setnode->next;
    }
}

void delete_map_node(multimap * multimap, char * key)
{
    int hash = map_hash(key);
    map_node * mapnode = multimap[hash].first;

    while (mapnode != NULL)
    {
        if (strcmp(mapnode->key, key) == 0)
        {
            if (mapnode->prev == NULL && mapnode->next == NULL)
                multimap[hash].first = NULL;
            else if (mapnode->prev == NULL)
            {
                multimap[hash].first = mapnode->next;
                mapnode->next->prev = NULL;
            }
            else if (mapnode->next == NULL)
                mapnode->prev->next = NULL;
            else
            {
                mapnode->prev->next = mapnode->next;
                mapnode->next->prev = mapnode->prev;
            }
            multimapsize--;
            delete mapnode;
            return;
        }
        else mapnode = mapnode->next;
    }
}

void delete_set_node(multimap * multimap, char * key, char * val)
{
    int hash = map_hash(key);
    map_node * mapnode = multimap[hash].first;

    while (mapnode != NULL)
    {
        if (strcmp(mapnode->key, key) == 0)
        {
            delete_val(mapnode, val);
            if (mapnode->set->size == 0)
                delete_map_node(multimap, key);
            return;
        }
        else mapnode = mapnode->next;
    }
}