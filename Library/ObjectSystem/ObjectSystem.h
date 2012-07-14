//
//  ObjectSystem.h
//  ObjectSystem
//
//  Created by Hyun Hwang on 7/14/12.
//  Copyright (c) 2012 SI Cyrusian. All rights reserved.
//

#ifndef _CRAFTIK_OBJECTSYSTEM_H_
#define _CRAFTIK_OBJECTSYSTEM_H_

#include "Library/CTTypes.h"
#include <stddef.h>


typedef void OSObject; // syntactic sugar for dummies :p

OSObject *OSAlloc(size_t objectSize, void (*optionalObjectDeallocCallback)(OSObject *));
void OSRelease(OSObject *object);
void OSRetain(OSObject *object);
CTUShort OSRetainCount(OSObject *object);

#endif