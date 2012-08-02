//
//  ObjectSystemTest.c
//  ObjectSystemTest
//
//  Created by Hyun Hwang on 7/21/12.
//  Copyright (c) 2012 SI Cyrusian. All rights reserved.
//

#include "Library/ObjectSystem/ObjectSystem.h"
#include "Library/Seatest/Seatest.h"


typedef struct _TestObject {
	OSMethodSet OSObject;
	OSIvarSet *OSIvars;
	int Charles;
	float Marie;
} TestObject;

void OSObjectTestAll();
void OSObjectTestEnvReset();
void OSObjectTestDealloc(OSObject *);


TestObject *testObj=NULL;
int deallocTest=0;

int main(int argc, const char **argv) {
	run_tests(OSObjectTestAll);
	
	return 0;
}

void OSObjectTestAlloc() {
	testObj=(TestObject *)OSAlloc(sizeof(TestObject));
	assert_false(testObj==NULL);
	assert_true(OSIsValid(testObj)==YES);
	assert_int_equal(MSG(testObj, OSObject, retainCount), 1);
	
	// not an standard way.
	testObj->OSObject.dealloc=OSObjectTestDealloc;
}

void OSObjectTestDealloc(OSObject *self) {
	deallocTest=1205;
}

void OSObjectTestDestroy() {
	MSG(testObj, OSObject, release);
	assert_true(OSIsValid(testObj)==NO);
	assert_int_equal(MSG(testObj, OSObject, retainCount), 0);
	assert_int_equal(deallocTest, 1205);
}


void OSObjectTestEnvReset() {
	testObj=NULL;
	deallocTest=0;
}

void OSObjectTestNoDealloc() {
	testObj=(TestObject *)OSAlloc(sizeof(TestObject));
	MSG(testObj, OSObject, release);
	assert_int_equal(deallocTest, 0);
}

void OSObjectTestRelease() {
	MSG(testObj, OSObject, release);
	assert_int_equal(MSG(testObj, OSObject, retainCount), 1);
}

void OSObjectTestRetain() {
	MSG(testObj, OSObject, retain);
	assert_int_equal(MSG(testObj, OSObject, retainCount), 2);
}

void OSObjectTestZeroAlloc() {
	testObj=(TestObject *)OSAlloc(0);
	assert_true(testObj==NULL);
}

void OSObjectTestAll() {
	test_fixture_start();
	run_test(OSObjectTestZeroAlloc);
	test_fixture_end();
	
	OSObjectTestEnvReset();
	
	test_fixture_start();
	run_test(OSObjectTestAlloc);
	run_test(OSObjectTestRetain);
	run_test(OSObjectTestRelease);
	run_test(OSObjectTestDestroy);
	test_fixture_end();
	
	OSObjectTestEnvReset();
	
	test_fixture_start();
	run_test(OSObjectTestNoDealloc);
	test_fixture_end();
}