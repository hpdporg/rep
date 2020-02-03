#include "AsmIncludes.h"
#include "ProcessingRefValueTests.h"




TEST(ProcessingRefValueTest, ProcessesARefValue) {
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

	processRefValues(parsing, ref, refRegistry);

	fprintf(stdout, "\nRef1 letters: %s\n", (char*)ref->valueAlloc);



	EXPECT_STREQ("adf12", (char*)ref->valueAlloc);
	
}

TEST(ProcessingRefValueTest, ProcessesLetters) {
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

	processLetters(parsing, ref, refRegistry,DEFINED_REF_LETTERS);

	fprintf(stdout, "\nRef1 letters: %s\n", (char*)ref->valueAlloc);



	EXPECT_STREQ("adf12", (char*)ref->valueAlloc);

}

TEST(ProcessingRefValueTest, ProcessesAppending) {
	/*
	*	There is a bug where appending is used in list that appends many letter refs and does not resolve completely. Fixed when letter refs defined towards top of rep file, problems when just before appending.
	*	TO-DO: Repro and fix. list was first in rep file, then many other letters, appending, then appending that had problem, then store and retrieve files.
	*/
	Ref* ref = newRef();
	ref->flags = REF_VALUE;
	ref->definedRefFlags = 0;
	ref->ref = (char*)"ref";
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
	newLastRegisteredRef(refRegistry, ref);
	newLastRegisteredRef(refRegistry, ref2);
	newLastRegisteredRef(refRegistry, ref3);


	processAppending(parsing, ref, refRegistry, (DefinedRefFlags)0);

	fprintf(stdout, "\nRef1 letters: %s\n", (char*)ref->valueAlloc);



	EXPECT_STREQ("adf129zdf77", (char*)ref->valueAlloc);

}
