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
	CTUniChar *string;
	CTUInteger length;
	CTUInteger hash;
};


CTUInteger CSHash(CSString *self);
BOOL CSIsEqualToString(CSString *self, CSString *theOther);
CTUInteger CSLength(CSString *self);


CTUInteger CSHash(CSString *self) {
	CTUInteger h=self->CSIvars->hash;
	CTUInteger l=MSG(self, CSString, length); // This assures: length!=0
	CTUniChar *s=self->CSIvars->string;
	
	if(h==0) {
		for(CTUInteger i=0; i<l; ++i)
			h=31*h+s[i];
		self->CSIvars->hash=h;
	}
	
	return h;
}

BOOL CSIsEqualToString(CSString *self, CSString *theOther) {
	CTUInteger i=0, l=MSG(self, CSString, length);
	
	if(l==MSG(theOther, CSString, length)) {
		CTUniChar *s1=self->CSIvars->string;
		CTUniChar *s2=theOther->CSIvars->string;
		
		for(; i<l && s1[i]==s2[i]; ++i);
		
		if(i==l)
			return YES;
		else
			return NO;
	}
	
	return NO;
}

CTUInteger CSLength(CSString *self) {
	CTUInteger l=self->CSIvars->length;
	
	if(l==0) {
		CTUniChar *s=self->CSIvars->string;
		
		for(; s[l]!='\0'; ++l);
		self->CSIvars->length=l;
	}
	
	return l;
}

// TODO
// 1. Validate UTF-8
CSString *CSStringFromUTF8String(const char *UTF8CStr) {
	
	
	return NULL;
}