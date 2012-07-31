#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "HashTable.h"

HashTable* CreateHashTable(int TableSize, int(*HashFunc)(void* Key)){
	HashTable* Temp= (HashTable*)malloc(sizeof(HashTable));
	Temp->TableSize= TableSize;
	Temp->TableHead= (void**)malloc(sizeof(void*)*TableSize);
	Temp->HashFunc= HashFunc;
	Temp->HT_Set= HT_Set;
	memset(Temp->TableHead, 0, sizeof(sizeof(void*))*Temp->TableSize);

	return Temp;
}

int DestroyHashTable(HashTable* HT){
	free(HT->TableHead);
	free(HT);
	return 0;
}

void HT_Set(HashTable* HT, void* Key, void* Value){
	HT->TableHead[HT->HashFunc(Key)%HT->TableSize]= Value;
}
