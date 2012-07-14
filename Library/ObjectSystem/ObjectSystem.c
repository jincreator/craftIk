//
//  ObjectSystem.c
//  ObjectSystem
//
//  Created by Hyun Hwang on 7/14/12.
//  Copyright (c) 2012 SI Cyrusian. All rights reserved.
//

#include "Library/ObjectSystem/ObjectSystem.h"
#include <stdlib.h>


// Typedefing is just for error-detouring.
// This suppresses LLVM's weird error regarding flexible array member in struct _OSRawObject.
typedef struct _OSObjectHeader {
	void (*deallocCallback)(OSObject *);
	CTUShort referenceCount;
} OSObjectHeader;

struct _OSRawObject {
	OSObjectHeader header;
	char wormhole[];
};


OSObject *OSAlloc(size_t objectSize, void (*optionalObjectDeallocCallback)(OSObject *)) {
	struct _OSRawObject *rawObject=(struct _OSRawObject *)malloc(sizeof(OSObjectHeader)+objectSize);
	if(rawObject==NULL)
		return NULL;
	
	if(optionalObjectDeallocCallback!=NULL)
		rawObject->header.deallocCallback=optionalObjectDeallocCallback;
	rawObject->header.referenceCount=1;
	
	return (OSObject *)(rawObject+sizeof(OSObjectHeader));
}

void OSRelease(OSObject *object) {
	struct _OSRawObject *rawObject=(struct _OSRawObject *)(object-sizeof(OSObjectHeader));
	
	if(rawObject->header.referenceCount==1) {
		if(rawObject->header.deallocCallback!=NULL)
			(rawObject->header.deallocCallback)(object);
		
		free(object);
	} else
		--(rawObject->header.referenceCount);
}

void OSRetain(OSObject *object) {
	struct _OSRawObject *rawObject=(struct _OSRawObject *)(object-sizeof(OSObjectHeader));
	
	++(rawObject->header.referenceCount);
}

CTUShort OSRetainCount(OSObject *object) {
	struct _OSRawObject *rawObject=(struct _OSRawObject *)(object-sizeof(OSObjectHeader));
	
	return rawObject->header.referenceCount;
}