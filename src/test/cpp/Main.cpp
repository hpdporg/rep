#include "gtest\gtest.h"
#include "AsmIncludes.h"
#include "ParsingTests.h"


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	
	/*RunCycles* runCycles = newRunCycles();

	beginRunCycles(runCycles);
	*/
	}