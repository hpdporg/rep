#include "AsmIncludes.h"
#include "AllocateTests.h"

TEST(LinearAllocateTest, ReturnsAllocation) {
	int res = (int)linearAllocate(4);
	fprintf(stdout, "\nOutput: %d\n", res);
	EXPECT_TRUE((res !=0));
}
