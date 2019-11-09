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


TEST(ParsingTest, ParsesFirstRep) {
	RunCycles* runCycles = newRunCycles();
	RefRegistry* refRegistry = newRefRegistry();
	runCycles->refRegistry = refRegistry;
	
	loadRunCycleRefRegistry(runCycles);

	Parsing* parsing = newParsing();
	char* letters = "ref2	letters	Some letters1	";
	parseRep(parsing, letters, refRegistry);

/*
	char* parseVal = parseNext(parsing, letters);
	fprintf(stdout, "\nNext parsed val: %s\n", parseVal);
	fprintf(stdout, "\nParsing index: %d\n", parsing->index);
	char* nextParseVal = parseNext(parsing, letters);
	fprintf(stdout, "\nParsing index: %d\n", parsing->index);

	fprintf(stdout, "\nNext parsed val: %s\n", nextParseVal);

	EXPECT_STREQ("SecondVal",nextParseVal);
	*/
}


TEST(ParsingTest, ParsesFirstValue) {
	RunCycles* runCycles = newRunCycles();
	RefRegistry* refRegistry = newRefRegistry();
	runCycles->refRegistry = refRegistry;
	
	loadRunCycleRefRegistry(runCycles);

	Parsing* parsing = newParsing();
	char* letters = "ref2	letters	Some letters1	";
	nextParsing(parsing, letters, refRegistry);

/*
	char* parseVal = parseNext(parsing, letters);
	fprintf(stdout, "\nNext parsed val: %s\n", parseVal);
	fprintf(stdout, "\nParsing index: %d\n", parsing->index);
	char* nextParseVal = parseNext(parsing, letters);
	fprintf(stdout, "\nParsing index: %d\n", parsing->index);

	fprintf(stdout, "\nNext parsed val: %s\n", nextParseVal);

	EXPECT_STREQ("SecondVal",nextParseVal);
	*/
}
