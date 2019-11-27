#include "AsmIncludes.h"
#include "ProcessingTests.h"



TEST(ProcessingTest, DefinesARepAsProcessed) {
	Ref* ref = newRef();
	ref->list = newList();

	fprintf(stdout,"\nRef is unprocessed? %d\n",ref->unprocessed);

	EXPECT_EQ(1, ref->unprocessed);
	defineAsProcessed(ref);
	fprintf(stdout,"\nRef is unprocessed? %d\n",ref->unprocessed);

	EXPECT_EQ(0, ref->unprocessed);




}

TEST(ProcessingTest, GetsBaseRef) {
	Ref* ref = newRef();
	ref->list = newList();
	Ref* ref2 = newRef();
	newLastItem(ref->list, ref2);



	fprintf(stdout,"\nRef1: %d\n",(_int64)ref);
	fprintf(stdout,"\nRef2: %d\n",(_int64)ref2);
	Ref* baseRef = getBaseRefAtIndex(ref,0);

	fprintf(stdout,"\nRef at index: %d\n",(_int64)baseRef);
	EXPECT_EQ(ref, baseRef);

}

TEST(ProcessingTest, GetsParamBaseRef) {
	Ref* ref = newRef();
	ref->list = newList();
	Ref* ref2 = newRef();
	newLastItem(ref->list, ref2);



	fprintf(stdout,"\nRef1: %d\n",(_int64)ref);
	fprintf(stdout,"\nRef2: %d\n",(_int64)ref2);
	Ref* baseRef = getBaseRefAtIndex(ref,1);

	fprintf(stdout,"\nRef at index: %d\n",(_int64)baseRef);
	EXPECT_EQ(ref2, baseRef);

}



TEST(ProcessingTest, GetsBaseRefFromFlags) {
	Ref* ref = newRef();
	ref->list = newList();
	Ref* ref2 = newRef();
	newLastItem(ref->list, ref2);



	fprintf(stdout,"\nRef1: %d\n",(_int64)ref);
	fprintf(stdout,"\nRef2: %d\n",(_int64)ref2);
	Ref* baseRef = getBaseRefUsingFlags(ref,REF_BASE_ITEM_DEFINED_REF);

	fprintf(stdout,"\nRef at index: %d\n",(_int64)baseRef);
	EXPECT_EQ(ref, baseRef);

}

TEST(ProcessingTest, GetsParamBaseRefFromFlags) {
	Ref* ref = newRef();
	ref->list = newList();
	Ref* ref2 = newRef();
	newLastItem(ref->list, ref2);



	fprintf(stdout,"\nRef1: %d\n",(_int64)ref);
	fprintf(stdout,"\nRef2: %d\n",(_int64)ref2);
	Ref* baseRef = getBaseRefUsingFlags(ref,REF_BASE_DEFINED_REF_FIRST_PARAM);

	fprintf(stdout,"\nRef at index: %d\n",(_int64)baseRef);
	EXPECT_EQ(ref2, baseRef);

}

TEST(ProcessingTest, GetsBaseRefNotFirstSecondFromFlags) {
	Ref* ref = newRef();
	ref->list = newList();
	Ref* ref2 = newRef();
	newLastItem(ref->list, ref2);



	fprintf(stdout,"\nRef1: %d\n",(_int64)ref);
	fprintf(stdout,"\nRef2: %d\n",(_int64)ref2);
	Ref* baseRef = getBaseRefUsingFlags(ref,REF_BASE_DEFINED_REF_NOT_FIRST_SECOND_PARAM);

	fprintf(stdout,"\nRef at index: %d\n",(_int64)baseRef);
	EXPECT_EQ(ref, baseRef);

}