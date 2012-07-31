enum ElementStatus{
	EMPTY= 0,
	OCCUPIED= 1
};

typedef struct ElementType{
	void* Key;
	void* Value;

	enum ElementStatus Status;
} ElementType;


typedef struct HashTable{
	int TableSize;
	int Using;
	ElementType* TableHead;
	int (*HashFunc)(void* Key);

	void (*HT_Set)(struct HashTable* HT, void* Key, void* Value);
	void* (*HT_Get)(struct HashTable* HT, void* Key);
	int (*HT_Del)(struct HashTable* HT, void* Key);
} HashTable;

HashTable* CreateHashTable(int TableSize, int(*HashFunc)(void* Key));
int DestroyHashTable(HashTable* HT);

void HT_Set(HashTable* HT, void* Key, void* Value);

void* HT_Get(HashTable* HT, void* Key);

int HT_Del(HashTable* HT, void* Key);

void HT_Refresh(HashTable* HT);