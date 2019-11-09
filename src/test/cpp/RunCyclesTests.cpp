#include "AsmIncludes.h"
#include "RunCyclesTests.h"
#include "RunCyclesTest.cpp"

TEST_F(RunCyclesTest, LoadsReps) {
	RunCycles* runCycles = newRunCycles();

	
	loadRunCycleReps(runCycles);
	
	fprintf(stdout, "\nRunCycle Rep count: %d\n", runCycles->repRecordList->itemsCount);

	List* repRecordList = runCycles->repRecordList;
	while (repRecordList->index < repRecordList->itemsCount){
		char* nextRecordName = (char*)getNextItem(repRecordList);
		fprintf(stdout, "\nNext record name: %s\n",nextRecordName);
	}

	EXPECT_EQ(1,runCycles->repRecordList->itemsCount);
}

TEST_F(RunCyclesTest, LoadsRepAllocation) {
	RunCycles* runCycles = newRunCycles();

	
	loadRunCycleReps(runCycles);
	
	fprintf(stdout, "\nRunCycle Rep count: %d\n", runCycles->repRecordList->itemsCount);

	loadRunCycleRepAllocation(runCycles);

	fprintf(stdout, "\nRunCycle Rep allocation: \n%s",runCycles->repAllocation);
	EXPECT_STRNE(0,runCycles->repAllocation);
}

TEST_F(RunCyclesTest, LoadsRefRegistry) {
	RunCycles* runCycles = newRunCycles();
	RefRegistry* refRegistry = newRefRegistry();
	runCycles->refRegistry = refRegistry;
	
	loadRunCycleRefRegistry(runCycles);
	fprintf(stdout, "\nLoading complete\n");
	fprintf(stdout, "\nRunCycle Ref List count: %d\n", runCycles->refRegistry->list->itemsCount);
	fprintf(stdout, "\nRunCycle Ref List count: %d\n", runCycles->refRegistry->definedList->itemsCount);

	EXPECT_EQ(5,runCycles->refRegistry->definedList->itemsCount);
}

TEST_F(RunCyclesTest, BeginsRunCycles) {
	RunCycles* runCycles = newRunCycles();
	beginRunCycles(runCycles);
		

	EXPECT_EQ(1,runCycles->repRecordList->itemsCount);
	fprintf(stdout, "\nLoading complete\n");
	fprintf(stdout, "\nRunCycle Ref List count: %d\n", runCycles->refRegistry->list->itemsCount);
	fprintf(stdout, "\nRunCycle Ref List count: %d\n", runCycles->refRegistry->definedList->itemsCount);

	EXPECT_EQ(5,runCycles->refRegistry->definedList->itemsCount);
	fprintf(stdout, "\nRunCycle Rep allocation: \n%s",runCycles->repAllocation);
	EXPECT_STRNE(0,runCycles->repAllocation);
	
}
