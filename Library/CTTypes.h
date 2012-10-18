//
//  CTTypes.h
//  craftIk
//
//  Created by Hyun Hwang on 7/14/12.
//  Copyright (c) 2012 SI Cyrusian. All rights reserved.
//

#ifndef _CRAFTIK_CTTYPES_H_
#define _CRAFTIK_CTTYPES_H_

#include <stdint.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

typedef signed char BOOL;
#define YES ((BOOL)1)
#define NO ((BOOL)0)

typedef int16_t CTShort;
typedef uint16_t CTUShort;
typedef int32_t CTInteger;
typedef uint32_t CTUInteger;

typedef char CTChar;
typedef uint16_t CTUniChar;

#endif
