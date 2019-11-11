#include "AsmIncludes.h"
#include "ParsingTests.h"

TEST(ParsingTest, ReturnsFirstParsedValue) {
	Parsing* parsing = newParsing();
	char* letters = "FirstVal\tSecondVal\tThirdVal";

	char* parseVal = getNextParsingValue(parsing, letters);

	fprintf(stdout, "\nNext parsed val: %s\n", parseVal);

	EXPECT_STREQ("FirstVal",parseVal);
}


TEST(ParsingTest, ReturnsNextParsedValue) {
	Parsing* parsing = newParsing();
	char* letters = "FirstVal\tSecondVal\tThirdVal";

	char* parseVal = getNextParsingValue(parsing, letters);
	fprintf(stdout, "\nNext parsed val: %s\n", parseVal);
	fprintf(stdout, "\nParsing index: %d\n", parsing->index);
	char* nextParseVal = getNextParsingValue(parsing, letters);
	fprintf(stdout, "\nParsing index: %d\n", parsing->index);

	fprintf(stdout, "\nNext parsed val: %s\n", nextParseVal);

	EXPECT_STREQ("SecondVal",nextParseVal);
}

TEST(ParsingTest, ReturnsNextParsedValueOrDelimiter) {
	Parsing* parsing = newParsing();
	char* letters = "FirstVal\tSecondVal\tThirdVal";

	char* parseVal = getNextParsingValueOrDelimiter(parsing, letters);
	fprintf(stdout, "\nNext parsed val: %s\n", parseVal);
	fprintf(stdout, "\nParsing index: %d\n", parsing->index);
	char* nextParseVal = getNextParsingValueOrDelimiter(parsing, letters);
	fprintf(stdout, "\nParsing index: %d\n", parsing->index);

	fprintf(stdout, "\nNext parsed val: %s\n", nextParseVal);

	EXPECT_STREQ("",nextParseVal);												// Is this correct?
	nextParseVal = getNextParsingValueOrDelimiter(parsing, letters);
	fprintf(stdout, "\nParsing index: %d\n", parsing->index);

	fprintf(stdout, "\nNext parsed val: %s\n", nextParseVal);

}

TEST(ParsingTest, ParsesFirstRep) {
	RunCycles* runCycles = newRunCycles();
	RefRegistry* refRegistry = newRefRegistry();
	runCycles->refRegistry = refRegistry;
	
	loadRunCycleRefRegistry(runCycles);

	Parsing* parsing = newParsing();
	fprintf(stdout, "\nBefore Next: %d\n", parsing->index);	
	char* letters = "ref2	letters	Some letters1	";
	parseRep(parsing, letters, refRegistry);
	resetIndex(refRegistry->list);
	while(refRegistry->list->index < refRegistry->list->itemsCount){
		_int64 nesting = (_int64)getNextItemNesting(refRegistry->list);
		Ref* ref2 = (Ref*)getNextItem(refRegistry->list);
		if (refRegistry->list->index == 1){													// getNextItem increments index
			fprintf(stdout, "\nRef flags: %d\n", ref2->flags);
			EXPECT_EQ(1, ref2->flags);
			fprintf(stdout, "\nRep index: %d\n", ref2->repIndex);
			EXPECT_EQ(0, ref2->repIndex);
			fprintf(stdout, "\nRep name: %s\n", ref2->ref);
			EXPECT_STREQ("ref2", ref2->ref);
			fprintf(stdout, "\nRep nesting: %d\n", nesting);
			EXPECT_EQ(0, nesting);
		}
	}
}


TEST(ParsingTest, ParsesFirstValue) {
	RunCycles* runCycles = newRunCycles();
	RefRegistry* refRegistry = newRefRegistry();
	runCycles->refRegistry = refRegistry;
	
	loadRunCycleRefRegistry(runCycles);

	Parsing* parsing = newParsing();
	char* letters = "ref2	letters	Some letters1	";
	//nextParsing(parsing, letters, refRegistry);
	fprintf(stdout, "\nNext: %d\n", parsing->index);

}

TEST(ParsingTest, ParsingFirstRepUpdatesParsingFlags) {
	RunCycles* runCycles = newRunCycles();
	RefRegistry* refRegistry = newRefRegistry();
	runCycles->refRegistry = refRegistry;
	
	loadRunCycleRefRegistry(runCycles);

	Parsing* parsing = newParsing();
	fprintf(stdout, "\nBefore Next: %d\n", parsing->index);	
	char* letters = "ref2	letters	Some letters1	";
	parseRep(parsing, letters, refRegistry);
	fprintf(stdout, "\nParsing index: %d\n", parsing->index);
	EXPECT_EQ(4, parsing->index);
	fprintf(stdout, "\nParsing flags: %d\n", parsing->flags);
	EXPECT_EQ(PARSING_AT_LETTERS, parsing->flags);
	fprintf(stdout, "\nParsing lineRefCount: %d\n", parsing->lineRefCount);
	EXPECT_EQ(1, parsing->lineRefCount);
	
}

TEST(ParsingTest, ParsingFirstSecondRepUpdatesParsingFlags) {
	RunCycles* runCycles = newRunCycles();
	RefRegistry* refRegistry = newRefRegistry();
	runCycles->refRegistry = refRegistry;
	
	loadRunCycleRefRegistry(runCycles);

	Parsing* parsing = newParsing();
	fprintf(stdout, "\nBefore Next: %d\n", parsing->index);	
	char* letters = "ref2	letters	Some letters1	";
	
	parseRep(parsing, letters, refRegistry);
	fprintf(stdout, "\nParsing index: %d\n", parsing->index);
	EXPECT_EQ(4, parsing->index);
	fprintf(stdout, "\nParsing flags: %d\n", parsing->flags);
	EXPECT_EQ(PARSING_AT_LETTERS, parsing->flags);
	fprintf(stdout, "\nParsing lineRefCount: %d\n", parsing->lineRefCount);
	EXPECT_EQ(1, parsing->lineRefCount);
	
	parseRep(parsing, letters, refRegistry);
	fprintf(stdout, "\nParsing index: %d\n", parsing->index);
	EXPECT_EQ(5, parsing->index);
	fprintf(stdout, "\nParsing flags: %d\n", parsing->flags);
	EXPECT_EQ(PARSING_AT_DELIMITER, parsing->flags);
	fprintf(stdout, "\nParsing lineRefCount: %d\n", parsing->lineRefCount);
	EXPECT_EQ(1, parsing->lineRefCount);
	
}

TEST(ParsingTest, ParsingThirdRepUpdatesParsingFlags) {
	RunCycles* runCycles = newRunCycles();
	RefRegistry* refRegistry = newRefRegistry();
	runCycles->refRegistry = refRegistry;
	
	loadRunCycleRefRegistry(runCycles);

	Parsing* parsing = newParsing();
	fprintf(stdout, "\nBefore Next: %d\n", parsing->index);	
	char* letters = "ref2	letters	Some letters1	";
	
	parseRep(parsing, letters, refRegistry);
	parseRep(parsing, letters, refRegistry);
	parseRep(parsing, letters, refRegistry);

	fprintf(stdout, "\nParsing index: %d\n", parsing->index);
	EXPECT_EQ(12, parsing->index);
	fprintf(stdout, "\nParsing flags: %d\n", parsing->flags);
	EXPECT_EQ(PARSING_AT_LETTERS, parsing->flags);
	fprintf(stdout, "\nParsing lineRefCount: %d\n", parsing->lineRefCount);
	EXPECT_EQ(2, parsing->lineRefCount);
	
}

TEST(ParsingTest, ParsingFirstSecondRepUpdatesBaseRepOffset) {
	RunCycles* runCycles = newRunCycles();
	RefRegistry* refRegistry = newRefRegistry();
	runCycles->refRegistry = refRegistry;
	
	loadRunCycleRefRegistry(runCycles);

	Parsing* parsing = newParsing();
	fprintf(stdout, "\nBefore Next: %d\n", parsing->index);	
	char* letters = "ref2	letters	Some letters1	";
	parseRep(parsing, letters, refRegistry);
	fprintf(stdout, "\nParsing repOffset: %d\n", parsing->repOffset);
	EXPECT_EQ(0, parsing->repOffset);
	fprintf(stdout, "\nParsing baseRepOffset: %d\n", parsing->baseRepOffset);
	EXPECT_EQ(0, parsing->baseRepOffset);
	
	parseRep(parsing, letters, refRegistry);
	fprintf(stdout, "\nParsing repOffset: %d\n", parsing->repOffset);
	EXPECT_EQ(1, parsing->repOffset);
	fprintf(stdout, "\nParsing baseRepOffset: %d\n", parsing->baseRepOffset);
	EXPECT_EQ(0, parsing->baseRepOffset);
	
	
}

TEST(ParsingTest, ParsingFirstRepUpdatesRefRegistry) {
	RunCycles* runCycles = newRunCycles();
	RefRegistry* refRegistry = newRefRegistry();
	runCycles->refRegistry = refRegistry;
	
	loadRunCycleRefRegistry(runCycles);

	Parsing* parsing = newParsing();
	fprintf(stdout, "\nBefore Next: %d\n", parsing->index);	
	char* letters = "ref2	letters	Some letters1	";
	fprintf(stdout, "\nRefRegistry itemsCount: %d\n", refRegistry->list->itemsCount);
	EXPECT_EQ(0, refRegistry->list->itemsCount);
	parseRep(parsing, letters, refRegistry);
	fprintf(stdout, "\nRefRegistry itemsCount: %d\n", refRegistry->list->itemsCount);
	EXPECT_EQ(1, refRegistry->list->itemsCount);
	resetIndex(refRegistry->list);
	while(refRegistry->list->index < refRegistry->list->itemsCount){
		Ref* ref2 = (Ref*)getNextItem(refRegistry->list);
		if (refRegistry->list->index == 1){													// getNextItem increments index			
			fprintf(stdout, "\nRef flags: %d\n", ref2->flags);
			EXPECT_EQ(1, ref2->flags);
			fprintf(stdout, "\nRep index: %d\n", ref2->repIndex);
			EXPECT_EQ(0, ref2->repIndex);
			fprintf(stdout, "\nRep name: %s\n", ref2->ref);
			EXPECT_STREQ("ref2", ref2->ref);
		}
	}
}