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