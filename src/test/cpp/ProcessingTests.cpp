#include "AsmIncludes.h"
#include "ProcessingTests.h"



TEST(ProcessingTest, ProcessesLetters) {
	Ref* ref = newRef();
	ref->flags = REF_VALUE;
	ref->definedRefFlags = DEFINED_REF_LETTERS;
	char* refLetters = "adf12";
	
	Ref* ref2 = newRef();
	ref2->flags = REF_DEFINED;
	
	Ref* ref3 = newRef();
	ref3->ref = refLetters;

	newLastItem(ref->list, ref2);
	newLastItem(ref->list, ref3);

	Parsing* parsing = newParsing();
	RefRegistry* refRegistry = newRefRegistry();

	processLetters(parsing, ref, refRegistry,DEFINED_REF_LETTERS);

	fprintf(stdout, "\nRef1 letters: %s\n", (char*)ref->valueAlloc);



	EXPECT_STREQ("adf12", (char*)ref->valueAlloc);

}

TEST(ProcessingTest, ProcessesAppending) {
	Ref* ref = newRef();
	ref->flags = REF_VALUE;
	ref->definedRefFlags = 0;
	char* refLetters = "adf12";
	char* refLetters2 = "9zdf77";
	
	Ref* ref2 = newRef();
	ref2->ref = (char*)"ref2";
	ref2->flags = REF_VALUE;
	ref2->valueAlloc = refLetters;
	ref2->unprocessed = 0;

	Ref* ref3 = newRef();
	ref3->ref = (char*)"ref3";
	ref3->flags = REF_VALUE;
	ref3->valueAlloc = refLetters2;
	ref3->unprocessed = 0;

	newLastItem(ref->list, ref2);
	newLastItem(ref->list, ref3);

	Parsing* parsing = newParsing();
	RefRegistry* refRegistry = newRefRegistry();
	newLastRegisteredRef(refRegistry, ref2);
	newLastRegisteredRef(refRegistry, ref3);


	processAppending(parsing, ref, refRegistry, (DefinedRefFlags)0);

	fprintf(stdout, "\nRef1 letters: %s\n", (char*)ref->valueAlloc);



	EXPECT_STREQ("adf129zdf77", (char*)ref->valueAlloc);

}

TEST(ProcessingTest, GetsUnprocessedRegisteredParams) {
	Ref* ref = newRef();

	Ref* ref2 = newRef();
	ref2->ref = (char*)"ref2";
	ref2->flags = REF_VALUE;
	ref2->unprocessed = 1;

	Ref* ref3 = newRef();
	ref3->ref = (char*)"ref3";
	ref3->flags = REF_VALUE;
	ref3->unprocessed = 0;

	newLastItem(ref->list, ref2);
	newLastItem(ref->list, ref3);

	Parsing* parsing = newParsing();
	RefRegistry* refRegistry = newRefRegistry();
	newLastRegisteredRef(refRegistry, ref2);
	newLastRegisteredRef(refRegistry, ref3);


	_int64 unprocessedCount = getUnprocessedRegisteredParams(ref, refRegistry);

	fprintf(stdout, "\nunprocessedCount: %d\n", unprocessedCount);



	EXPECT_EQ(1, unprocessedCount);





}


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

TEST(ProcessingTest, GetsLettersFromSingleRef) {
	Ref* ref = newRef();
	ref->flags = REF_VALUE;
	char* refLetters = "adf12";
	ref->valueAlloc = refLetters;


	fprintf(stdout, "\nRef1 letters: %s\n", refLetters);

	char* refLettersReturned = getRefLettersAlloc(ref);

	fprintf(stdout, "\nRef1 letters Returned: %s\n", refLettersReturned);
	EXPECT_STREQ(refLetters, refLettersReturned);

}

