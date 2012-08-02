//
//  ObjectSystem.c
//  ObjectSystem
//
//  Created by Hyun Hwang on 7/14/12.
//  Copyright (c) 2012 SI Cyrusian. All rights reserved.
//

#include "Library/ObjectSystem/ObjectSystem.h"
#include <stdlib.h>
#include <string.h>

#define OSOBJECT_SIGNATURE "OSOb"


struct _OSIvarSet {
	CTUShort retainCount;
};

struct _OSObjectHeader {
	CTChar objSign[4]; // Should be always "OSOb".
};

struct _OSRawObject {
	struct _OSObjectHeader header;
	OSMethodSet OSObject;
	OSIvarSet *OSIvars;
};

#define OSOBJECTHEADER_SIZE \
	(sizeof(struct _OSRawObject)-sizeof(struct _OSObject))


CTUInteger OSHash(OSObject *);
BOOL OSIsEqual(OSObject *, OSObject *);
void OSRelease(OSObject *);
void OSRetain(OSObject *);
CTUShort OSRetainCount(OSObject *);


OSObject *OSAlloc(size_t objectSize) {
	if(objectSize==0)
		return NULL;
	
	struct _OSRawObject *rawObject=(struct _OSRawObject *)
		malloc(OSOBJECTHEADER_SIZE+objectSize);
	if(rawObject==NULL) // Frankly, this is near impossible to happen. :p
		return NULL;
	memset(rawObject, 0, OSOBJECTHEADER_SIZE+objectSize);
	
	OSIvarSet *ivars=(OSIvarSet *)malloc(sizeof(OSIvarSet));
	if(ivars==NULL) {
		free(rawObject);
		
		return NULL;
	}
	memset(ivars, 0, sizeof(OSIvarSet));
	
	memcpy(rawObject->header.objSign, OSOBJECT_SIGNATURE, 4);
	rawObject->OSIvars=ivars;
	
	rawObject->OSIvars->retainCount=1;
	rawObject->OSObject.dealloc=NULL;
	rawObject->OSObject.hash=OSHash;
	rawObject->OSObject.isEqual=OSIsEqual;
	rawObject->OSObject.release=OSRelease;
	rawObject->OSObject.retain=OSRetain;
	rawObject->OSObject.retainCount=OSRetainCount;
	
	return (OSObject *)
		(((uintptr_t)rawObject)+OSOBJECTHEADER_SIZE);
}

CTUInteger OSHash(OSObject *self) {
	if(OSIsValid(self)==NO)
		return 0;
	
	return (CTUInteger)((((uintptr_t)self)-OSOBJECTHEADER_SIZE)>>4);
}

BOOL OSIsEqual(OSObject *self, OSObject *theOther) {
	return ((BOOL)(((uintptr_t)self)==((uintptr_t)theOther)) &&
		OSIsValid(self) &&
		OSIsValid(theOther));
}

void OSRelease(OSObject *self) {
	if(OSIsValid(self)==NO)
		return;
	
	struct _OSRawObject *rawObject=(struct _OSRawObject *)
		(((uintptr_t)self)-OSOBJECTHEADER_SIZE);
	
	if(rawObject->OSIvars->retainCount==1) {
		if(rawObject->OSObject.dealloc!=NULL)
			rawObject->OSObject.dealloc(self);
		memset(rawObject->header.objSign, '\0', 4);
		rawObject->OSIvars->retainCount=0;
		
		free(rawObject);
	} else
		--(rawObject->OSIvars->retainCount);
}

void OSRetain(OSObject *self) {
	if(OSIsValid(self)==NO)
		return;
	
	++(self->OSIvars->retainCount);
}

CTUShort OSRetainCount(OSObject *self) {
	if(OSIsValid(self)==NO)
		return 0;
	
	return self->OSIvars->retainCount;
}

BOOL OSIsValid(void *anObject) {
	if(anObject==NULL)
		return NO;
	
	struct _OSRawObject *rawObject=(struct _OSRawObject *)
		(((uintptr_t)anObject)-OSOBJECTHEADER_SIZE);
	
	return (strncmp(rawObject->header.objSign, OSOBJECT_SIGNATURE, 4)==0 &&
		rawObject->OSIvars->retainCount>0 &&
		rawObject->OSObject.hash!=NULL &&
		rawObject->OSObject.isEqual!=NULL &&
		rawObject->OSObject.release!=NULL &&
		rawObject->OSObject.retain!=NULL &&
		rawObject->OSObject.retainCount!=NULL);
}