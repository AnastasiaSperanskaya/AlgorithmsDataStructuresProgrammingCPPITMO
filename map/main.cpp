#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define hsize 10000

typedef struct chain
{
	chain* prev;
	chain* next;
	char key[30];
	char val[30];
} chain;

int hash_func(char key[30]);
chain * make_chain(char key[30], char val[30]);
void put(chain ** htable, char key[30], char val[30]);
void key_delete(chain ** htable, char key[30]);
void key_get(chain ** htable, char key[30], FILE * file);

long size = 0;

int main()
{
	FILE * in, *out;
	in = fopen("map.in", "r");
	out = fopen("map.out", "w");

	chain * hash[hsize];
	for (int i = 0; i < hsize; i++)
		hash[i] = NULL;

	char command[30];
	char key[30];
	char val[30];

	fscanf(in, "%s", command);
	fscanf(in, "%s", key);
	while (true)
	{
		if (strcmp(command, "put") == 0)
		{
			fscanf(in, "%s", val);
			put(&hash[0], key, val);
		}

		else if (strcmp(command, "delete") == 0)
			key_delete(&hash[0], key);

		else if (strcmp(command, "get") == 0)
			key_get(&hash[0], key, out);

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

int hash_func(char key[30])
{
	int result = 0;
	for (int i = 0; i < strlen(key); i++)
	{
		result *= 31;
		result += key[i];
	}

	result = abs(result);
	result = result % hsize;
	return result;
}

chain * make_chain(char key[30], char val[30])
{
	chain * new_chain = (chain *)malloc(sizeof(chain));
	new_chain->next = NULL;
	new_chain->prev = NULL;
	strcpy(new_chain->key, key);
	strcpy(new_chain->val, val);
	return new_chain;
}

void put(chain ** htable, char key[30], char val[30])
{
	int key_hash = hash_func(key);
	chain * check = htable[key_hash];

	if (check == NULL)
	{
		htable[key_hash] = make_chain(key, val);
		size++;
		return;
	}
	
	while (true)
	{
		if (strcmp(check->key, key) == 0)
		{
			strcpy(check->val, val);
			return;
		}

		else if (check->next == NULL)
		{
			check->next = make_chain(key, val);
			check->next->prev = check;
			size++;
			return;
		}
		else check = check->next;
	}
}

void key_delete(chain ** htable, char key[30])
{
	if (size <= 0)
		return;

	int key_hash = hash_func(key);
	chain * check = htable[key_hash];

	while (check != NULL)
	{
		if (strcmp(check->key, key) == 0)
		{
			if (check->prev == NULL & check->next == NULL)
			{
				htable[key_hash] = NULL;
			}

			else if (check->prev == NULL)
			{
				htable[key_hash] = check->next;
				check->next->prev = NULL;
			}

			else if (check->next == NULL)
				check->prev->next = NULL;

			else
            {
				check->prev->next = check->next;
				check->next->prev = check->prev;
			}

			free(check);
			size--;
			return;
		}

		else check = check->next;
	}
}

void key_get(chain ** htable, char key[30], FILE * file)
{
	if (size <= 0)
	{
		fprintf(file, "none\n");
		return;
	}

	int key_hash = hash_func(key);
	chain * check = htable[key_hash];

	while (check != NULL)
	{
		if (strcmp(check->key, key) == 0)
		{
			fprintf(file, "%s\n", check->val);
			return;
		}
		check = check->next;
	}

	fprintf(file, "none\n");
}
