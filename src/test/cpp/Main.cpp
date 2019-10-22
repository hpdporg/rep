#include "gtest\gtest.h"
#include "AllocateTests.h"


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}