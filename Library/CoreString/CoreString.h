/*!
 * @header Core String
 * @author Hyun Hwang
 *
 * Core String is a general string container. Not yet fully implemented.
 *
 * @copyright SI Cyrusian
 * @encoding utf-8
 */

#ifndef _CRAFTIK_CORESTRING_H_
#define _CRAFTIK_CORESTRING_H_

#include "Library/ObjectSystem/ObjectSystem.h"


/*!
 * @typedef CSString
 * @discussion
 * CSString overrides OSObject.hash() and OSObject.isEqual(). Internally, each
 * method will be connected with CSString.hash() and CSString.isEqualToString().
 */
typedef struct _CSString CSString;

/*!
 * @typedef CSMethodSet
 * @discussion
 * This structure contains CSString's methods.
 *
 * % hash() returns an identifier in integer form, which is unique to the
 *   ``content'' of the receiver.
 * % isEqualToString() measures sameness of the ``content'' of the receiver with
 *   another string's ``content'' and returns the result in boolean form.
 * % length() returns the count of Unicode characters that the receiver
 *   contains.
 */
typedef struct _CSMethodSet {
	CTUInteger (*hash)(CSString *self);
	BOOL (*isEqualToString)(CSString *self, CSString *theOther);
	CTUShort (*length)(CSString *self);
} CSMethodSet;

// This structure is a privatized data container. Defined here as a placeholder.
typedef struct _CSIvarSet CSIvarSet;

// Public interface of CSString.
struct _CSString {
	OSMethodSet OSObject;
	OSIvarSet *OSIvars;
	CSMethodSet CSString;
	CSIvarSet *CSIvars;
};

#endif