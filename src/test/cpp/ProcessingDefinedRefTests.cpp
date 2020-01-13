#include "AsmIncludes.h"
#include "ProcessingDefinedRefTests.h"





TEST(ProcessingDefinedRefTest, ProcessesStoreFile) {
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

TEST(ProcessingDefinedRefTest, ProcessesRetrieveFile) {

	Record* record = newStorage();
	record->builtLocation = "fileName5.txt";
	storeLetters(record, (char*)"ABC281");

	Ref* ref = newRef();
	ref->flags = REF_DEFINED;
	ref->definedRefFlags = DEFINED_REF_RETRIEVE_FILE;

	Ref* ref2 = newRef();

	ref2->flags = REF_VALUE;
	ref2->ref = (char*)"ref2";
	ref2->unprocessed = 0;
	ref2->valueAlloc = "fileName5.txt";

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

TEST(ProcessingDefinedRefTest, ProcessesReplaceLettersList) {
	
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
	getRefLettersList(ref4);

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

