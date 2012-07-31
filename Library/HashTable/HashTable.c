#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "HashTable.h"

HashTable* CreateHashTable(int TableSize, int(*HashFunc)(void* Key)){
	HashTable* Temp= (HashTable*)malloc(sizeof(HashTable));
	Temp->TableSize= TableSize;
	Temp->HashFunc= HashFunc;
	Temp->Using= 0;
	Temp->TableHead= (ElementType*) malloc(sizeof(ElementType)* TableSize);
	memset(Temp->TableHead, 0, sizeof(ElementType)* TableSize);

	Temp->HT_Set= HT_Set;
	Temp->HT_Get= HT_Get;
	Temp->HT_Del= HT_Del;

	return Temp;
}

int DestroyHashTable(HashTable* HT){
	free(HT->TableHead);
	free(HT);
	return 0;
}

void HT_Set(HashTable* HT, void* Key, void* Value){
	int reservingslot= HT->HashFunc(Key)%HT->TableSize;
	while(HT->TableHead[reservingslot].Status== OCCUPIED){
		reservingslot++;
	}
	HT->TableHead[reservingslot].Value= Value;
	HT->TableHead[reservingslot].Key= Key;
	HT->TableHead[reservingslot].Status= OCCUPIED;

	HT->Using++;

	if((float)HT->Using/HT->TableSize> 0.75){
		HT_Refresh(HT);
	}
}

void* HT_Get(HashTable* HT, void* Key){
	int HashVal= HT->HashFunc(Key)%HT->TableSize;

	while(HT->TableHead[HashVal].Status== EMPTY|| HT->TableHead[HashVal].Key!= Key){
		HashVal++;
	}
	return HT->TableHead[HashVal].Value;
}

int HT_Del(HashTable* HT, void* Key){
	int HashVal= HT->HashFunc(Key)%HT->TableSize;

	while(HT->TableHead[HashVal].Status== EMPTY|| HT->TableHead[HashVal].Key!= Key){
		HashVal++;
	}

	if(HT->TableHead[HashVal].Status== OCCUPIED){
		HT->TableHead[HashVal].Key= NULL;
		HT->TableHead[HashVal].Value= NULL;
		HT->TableHead[HashVal].Status= EMPTY;
		return 0;
	}
	return 1;
}

void HT_Refresh(HashTable* HT){
}