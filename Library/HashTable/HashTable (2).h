typedef struct HashTable{
	int TableSize;
	void** TableHead;
	int (*HashFunc)(void* Key);

	void(*HT_Set)(struct HashTable* HT, void* Key, void* Value);
} HashTable;

HashTable* CreateHashTable(int TableSize, int(*HashFunc)(void* Key));
int DestroyHashTable(HashTable* HT);

void HT_Set(HashTable* HT, void* Key, void* Value);