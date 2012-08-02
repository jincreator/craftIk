//
//  CoreString.c
//  CoreString
//
//  Created by Hyun Hwang on 7/20/12.
//  Copyright (c) 2012 SI Cyrusian. All rights reserved.
//

#include "Library/CoreString/CoreString.h"
#include "Library/CTTypes.h"
#include <stddef.h>


struct _CSIvarSet {
	CTUniChar *str;
	CTUShort length;
};