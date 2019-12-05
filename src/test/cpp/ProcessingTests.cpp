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

TEST(ProcessingTest, ProcessesStoreFile) {
	Ref* ref = newRef();
	ref->flags = REF_DEFINED;
	ref->definedRefFlags = DEFINED_REF_STORE_FILE;
	
	Ref* ref2 = newRef();

	ref2->flags = REF_VALUE;
	ref2->ref = (char*)"ref2";
	ref2->unprocessed = 0;
	ref2->valueAlloc = "fileName3.txt";
	
	Ref* ref3 = newRef();
	ref3->ref = (char*)"ref3";
	ref3->flags = REF_VALUE;
	ref3->unprocessed = 0;
	ref3->valueAlloc = "ABC281";

	newLastItem(ref->list, ref2);
	newLastItem(ref->list, ref3);

	Parsing* parsing = newParsing();
	RefRegistry* refRegistry = newRefRegistry();
	newLastRegisteredRef(refRegistry, ref2);
	newLastRegisteredRef(refRegistry, ref3);

	fprintf(stdout, "\nRef2 letters: %s\n", (char*)ref2->valueAlloc);

	processStoreFile(parsing, ref, refRegistry, DEFINED_REF_STORE_FILE);

	Record* record = newStorage();
	record->builtLocation = "fileName3.txt";
	retrieve(record);
	fprintf(stdout, "\nRecord letters: %s\n", (char*)record->allocAddr);



	EXPECT_STREQ("ABC281", (char*)record->allocAddr);

	removeRecord(record);

}

TEST(ProcessingTest, ProcessesRetrieveFile) {

	Record* record = newStorage();
	record->builtLocation = "fileName4.txt";
	storeLetters(record, (char*)"ABC281");

	Ref* ref = newRef();
	ref->flags = REF_DEFINED;
	ref->definedRefFlags = DEFINED_REF_RETRIEVE_FILE;

	Ref* ref2 = newRef();

	ref2->flags = REF_VALUE;
	ref2->ref = (char*)"ref2";
	ref2->unprocessed = 0;
	ref2->valueAlloc = "fileName4.txt";

	Ref* ref3 = newRef();
	ref3->ref = (char*)"ref3";
	ref3->flags = REF_VALUE;
	


	newLastItem(ref->list, ref2);
	newLastItem(ref->list, ref3);

	Parsing* parsing = newParsing();
	RefRegistry* refRegistry = newRefRegistry();
	newLastRegisteredRef(refRegistry, ref2);
	newLastRegisteredRef(refRegistry, ref3);

	fprintf(stdout, "\nRecord letters: %s\n", (char*)"ABC281");

	processRetrieveFile(parsing, ref, refRegistry, DEFINED_REF_RETRIEVE_FILE);

	fprintf(stdout, "\nRef3 letters: %s\n", (char*)ref3->valueAlloc);

	


	EXPECT_STREQ("ABC281", (char*)ref3->valueAlloc);

	removeRecord(record);

}

TEST(ProcessingTest, ProcessesReplaceLettersList) {
	
	Ref* ref = newRef();
	ref->flags = REF_VALUE;
	ref->ref = (char*)"ref";
	ref->unprocessed = 1;
	
	Ref* ref2 = newRef();
	ref2->ref = "replaceLettersList";
	ref2->flags = REF_DEFINED;
	ref2->definedRefFlags = DEFINED_REF_REPLACE_LETTERS_LIST;

	Ref* ref3 = newRef();
	ref3->ref = (char*)"ref3";
	ref3->flags = REF_VALUE;
	ref3->valueAlloc = "2fdsepValsal lssepValdafj 11";
	ref3->unprocessed = 0;

	Ref* ref4 = newRef();
	ref4->ref = (char*)"ref4";
	ref4->flags = REF_LIST;
	ref4->unprocessed = 0;

	Ref* ref5 = newRef();
	ref5->ref = (char*)"sepVal";
	ref5->flags = REF_VALUE;

	Ref* ref6 = newRef();
	ref6->ref = (char*)"ref6";
	ref6->flags = REF_VALUE;
	ref6->valueAlloc = "A2R4";
	ref6->unprocessed = 0;
	
	Ref* ref7 = newRef();
	ref7->ref = (char*)"ref7";
	ref7->flags = REF_VALUE;
	ref7->valueAlloc = "Aab4";
	ref7->unprocessed = 0;

	newLastItem(ref4->list, ref6);
	newLastItem(ref4->list, ref7);

	newLastItem(ref->list, ref2);
	newLastItem(ref->list, ref3);
	newLastItem(ref->list, ref4);
	newLastItem(ref->list, ref5);

	Parsing* parsing = newParsing();
	RefRegistry* refRegistry = newRefRegistry();
	//newLastRegisteredRef(refRegistry, ref2);
	newLastRegisteredRef(refRegistry, ref3);
	newLastRegisteredRef(refRegistry, ref4);
	newLastRegisteredRef(refRegistry, ref5);
	newLastRegisteredRef(refRegistry, ref6);
	newLastRegisteredRef(refRegistry, ref7);

	fprintf(stdout, "\nLetters: %s\n", (char*)"2fdsepValsal lssepValdafj 11");


	processReplaceLettersList(parsing, ref, refRegistry, DEFINED_REF_REPLACE_LETTERS_LIST);
	
	
	fprintf(stdout, "\nRef letters: %s\n", (char*)ref->valueAlloc);




	EXPECT_STREQ("2fdA2R4sal lsAab4dafj 11", (char*)ref->valueAlloc);

	
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
