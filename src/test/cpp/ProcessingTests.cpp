#include "AsmIncludes.h"
#include "ProcessingTests.h"


TEST(ProcessingTest, ProcessesARep) {

	Ref* ref = newRef();
	ref->flags = REF_VALUE;
	char* refLetters = "adf12";

	Ref* ref2 = newRef();
	ref2->definedRefFlags = DEFINED_REF_LETTERS;
	ref2->flags = REF_DEFINED;

	Ref* ref3 = newRef();
	ref3->ref = refLetters;

	newLastItem(ref->list, ref2);
	newLastItem(ref->list, ref3);

	Parsing* parsing = newParsing();
	RefRegistry* refRegistry = newRefRegistry();

	newLastItem(parsing->parsingRefs, ref);

	char* letters = "";
	processRep(parsing, letters, refRegistry);

	fprintf(stdout, "\nRef1 letters: %s\n", (char*)ref->valueAlloc);



	EXPECT_STREQ("adf12", (char*)ref->valueAlloc);


}

TEST(ProcessingTest, ProcessesRefItem) {
	Ref* ref = newRef();
	ref->flags = REF_VALUE;
	char* refLetters = "adf12";

	Ref* ref2 = newRef();
	ref2->definedRefFlags = DEFINED_REF_LETTERS;
	ref2->flags = REF_DEFINED;

	Ref* ref3 = newRef();
	ref3->ref = refLetters;

	newLastItem(ref->list, ref2);
	newLastItem(ref->list, ref3);

	Parsing* parsing = newParsing();
	RefRegistry* refRegistry = newRefRegistry();

	processRefItem(ref, 2, REF_BASE_DEFINED_REF_FIRST_PARAM, DEFINED_REF_LETTERS, parsing,  refRegistry);

	fprintf(stdout, "\nRef1 letters: %s\n", (char*)ref->valueAlloc);



	EXPECT_STREQ("adf12", (char*)ref->valueAlloc);




}

TEST(ProcessingTest, GetsUnprocessedParams) {
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
	


	_int64 unprocessedCount = getUnprocessedParams(ref);

	fprintf(stdout, "\nunprocessedCount: %d\n", unprocessedCount);



	EXPECT_EQ(1, unprocessedCount);





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

TEST(ProcessingTest, GetsLettersFromListRef) {
	Ref* ref = newRef();
	ref->ref = (char*)"ref";
	ref->flags = REF_LIST;

	
	Ref* ref2 = newRef();
	ref2->ref = (char*)"ref2";
	ref2->flags = REF_VALUE;
	ref2->valueAlloc = "A2R4";
	ref2->unprocessed = 0;

	Ref* ref3 = newRef();
	ref3->ref = (char*)"ref3";
	ref3->flags = REF_VALUE;
	ref3->valueAlloc = "Aab4";
	ref3->unprocessed = 0;

	newLastItem(ref->list, ref2);
	newLastItem(ref->list, ref3);
	
	

	List* refLettersList = getRefLettersList(ref);

	resetIndex(refLettersList);

	while (refLettersList->index < refLettersList->itemsCount) {
		char* nextLetters = (char*)getNextItem(refLettersList);
		fprintf(stdout, "\nNext: %s", nextLetters);
		if (refLettersList->index == 1) {		// List index incremented by one implicitly
			EXPECT_STREQ("A2R4", nextLetters);
		}
		if (refLettersList->index == 2) {		// List index incremented by one implicitly
			EXPECT_STREQ("Aab4", nextLetters);
		}

	}


}

TEST(ProcessingTest, GetsLettersAllocFromListRef) {
	Ref* ref = newRef();
	ref->ref = (char*)"ref";
	ref->flags = REF_LIST;


	Ref* ref2 = newRef();
	ref2->ref = (char*)"ref2";
	ref2->flags = REF_VALUE;
	ref2->valueAlloc = "A2R4";
	ref2->unprocessed = 0;

	Ref* ref3 = newRef();
	ref3->ref = (char*)"ref3";
	ref3->flags = REF_VALUE;
	ref3->valueAlloc = "Aab4";
	ref3->unprocessed = 0;

	newLastItem(ref->list, ref2);
	newLastItem(ref->list, ref3);



	List* refLettersList = getRefLettersList(ref);
	char* refLettersReturned = getRefLettersAlloc(ref);

	

	EXPECT_STREQ("A2R4Aab4", (char*)ref->valueAlloc);



}

