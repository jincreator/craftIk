/*!
 * @header Object System
 * @author Hyun Hwang
 *
 * Object System is a crucial member of craftIk's foundation. This library
 * provides convenience in managing objects in C programming language. Every
 * single object in craftIk probject should be manipulated using functions
 * provided by the library.
 *
 * @copyright SI Cyrusian
 * @encoding utf-8
 */

#ifndef _CRAFTIK_OBJECTSYSTEM_H_
#define _CRAFTIK_OBJECTSYSTEM_H_

#include "Library/CTTypes.h"
#include <stddef.h>

/*
 * Note: Prefixing ## to __VA_ARGS__ is not a standard way of getting rid of
 * unwanted additional comma at the end.
 */
#define MSG(receiver, class, method, ...) \
	(receiver)->class.method((class *)receiver, ## __VA_ARGS__)


/*!
 * @typedef OSObject
 * @discussion
 * This structure acts as a ``root'' template of objects in our object system.
 * Every single object that is designed to run inside craftIk should logically
 * inherit this object template; in other words, contain ``OSMethodSet OSObject;
 * '' as its first field.
 */
typedef struct _OSObject OSObject;

/*!
 * @typedef OSMethodSet
 * @discussion
 * This structure contains OSObject's methods.
 *
 * % dealloc() is called when the receiver gets deallocated(freed) by our
 *   system.
 * % hash() returns the receiver's unique identifier in integer form.
 * % isEqual() measures sameness of the receiver with another object and returns
 *   the result in boolean form.
 * % release() decreases the receiver's internal reference count by one(1) and
 *   deallocates the object if the count reaches zero(0).
 * % retain() increases receiver's internal reference count by one(1).
 * % retainCount() returns receiver's current internal reference count, only for
 *   referential purpose; you should not rely on the result, as it is highly
 *   variable.
 */
typedef struct _OSMethodSet {
	void (*dealloc)(OSObject *self);
	CTUInteger (*hash)(OSObject *self);
	BOOL (*isEqual)(OSObject *self, OSObject *theOther);
	void (*release)(OSObject *self);
	void (*retain)(OSObject *self);
	CTUShort (*retainCount)(OSObject *self);
} OSMethodSet;

// This structure is a privatized data container. Defined here as a placeholder.
typedef struct _OSIvarSet OSIvarSet;

// Public interface of OSObject.
struct _OSObject {
	OSMethodSet OSObject;
	OSIvarSet *OSIvars;
	char privateData[];
};


/*!
 * @function OSAlloc
 *
 * @abstract
 * Allocates necessary memory space for an object.
 * @discussion
 * Every single object MUST use this function for its allocation. The only
 * exception is OSObject itself; OSObject should NEVER be instantiated.
 *
 * @param objectSize Required memory amount.
 * @return
 * A pointer pointing to newly allocated, uninitialized object.
 */
OSObject *OSAlloc(size_t objectSize);

/*!
 * @function OSIsValid
 *
 * @abstract
 * Figures out whether given pointer IS genuine object or not.
 *
 * @param object A pointer pointing to possibly-an-object target.
 * @return
 * YES if given pointer points to genuine object. Otherwise, NO is returned.
 */
BOOL OSIsValid(void *object);

#endif