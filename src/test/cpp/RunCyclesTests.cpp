#include "AsmIncludes.h"
#include "RunCyclesTests.h"

TEST(RunCyclesTest, LoadsReps) {
	Parsing* parsing = newParsing();
	char* letters = "FirstVal\tSecondVal\tThirdVal";

	char* parseVal = parseNext(parsing, letters);

	fprintf(stdout, "\nNext parsed val: %s\n", parseVal);

	EXPECT_STREQ("FirstVal",parseVal);
}


