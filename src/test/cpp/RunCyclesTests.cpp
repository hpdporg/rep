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

	EXPECT_EQ(3,runCycles->repRecordList->itemsCount);
}

TEST_F(RunCyclesTest, LoadsRepAllocation) {
	RunCycles* runCycles = newRunCycles();

	
	loadRunCycleReps(runCycles);
	
	fprintf(stdout, "\nRunCycle Rep count: %d\n", runCycles->repRecordList->itemsCount);

	loadRunCycleRepAllocation(runCycles);

	fprintf(stdout, "\nRunCycle Rep allocation: \n%s",runCycles->repAllocation);
	EXPECT_NE(0,(_int64)runCycles->repAllocation);
}

TEST_F(RunCyclesTest, LoadsRefRegistry) {
	RunCycles* runCycles = newRunCycles();
	RefRegistry* refRegistry = newRefRegistry();
	runCycles->refRegistry = refRegistry;
	
	loadRunCycleRefRegistry(runCycles);
	fprintf(stdout, "\nLoading complete\n");
	fprintf(stdout, "\nRunCycle Ref List count: %d\n", runCycles->refRegistry->list->itemsCount);
	fprintf(stdout, "\nRunCycle Ref Defined List count: %d\n", runCycles->refRegistry->definedList->itemsCount);

	EXPECT_EQ(5,runCycles->refRegistry->definedList->itemsCount);
}

TEST_F(RunCyclesTest,ParsesProcessReps) {
	
	//Record* record = newStorage();

	//defineRecordPath(record, (char*)"testRepListDefinedRefReps.rep", (char*)".\\");
	//retrieve(record);
	RunCycles* runCycles = newRunCycles();

	
	loadRunCycleReps(runCycles);
	
	fprintf(stdout, "\nRunCycle Rep count: %d\n", runCycles->repRecordList->itemsCount);
	resetIndex(runCycles->repRecordList);
	while (runCycles->repRecordList->index < runCycles->repRecordList->itemsCount) {
		char* nextRecordName = (char*)getNextItem(runCycles->repRecordList);
		fprintf(stdout, "\nNext record name: %s\n", nextRecordName);
	}
	resetIndex(runCycles->repRecordList);
	loadRunCycleRepAllocation(runCycles);

	RefRegistry* refRegistry = newRefRegistry();
	runCycles->refRegistry = refRegistry;
	
	loadRunCycleRefRegistry(runCycles);
	Parsing* parsing = newParsing();
	runCycles->parsing = parsing;
	fprintf(stdout, "\nRunCycle allocation: %s\n", runCycles->repAllocation);

	while ((parsing->index < parsing->endIndex)
		|| (parsing->index == 0)) {
		parseRep(parsing, (char*)runCycles->repAllocation, refRegistry);
	
	fprintf(stdout, "\nDone1\n");
	}
	processRep(parsing, (char*)runCycles->repAllocation,refRegistry);
	fprintf(stdout, "\nDone2\n");

	processRep(parsing, (char*)runCycles->repAllocation,refRegistry);
	processRep(parsing, (char*)runCycles->repAllocation,refRegistry);
	fprintf(stdout, "\nDone\n");


}

TEST_F(RunCyclesTest, BeginsRunCycles) {
	fprintf(stdout, "\nBeginning load \n");
	RunCycles* runCycles = newRunCycles();

	beginRunCycles(runCycles);
		

	//EXPECT_EQ(1,runCycles->repRecordList->itemsCount);
	fprintf(stdout, "\nLoading complete\n");
	fprintf(stdout, "\nRunCycle Ref List count: %d\n", runCycles->refRegistry->list->itemsCount);
	fprintf(stdout, "\nRunCycle Defined Ref List count: %d\n", runCycles->refRegistry->definedList->itemsCount);

	//EXPECT_EQ(5,runCycles->refRegistry->definedList->itemsCount);
	fprintf(stdout, "\nRunCycle Rep allocation: \n%s",runCycles->repAllocation);
	//EXPECT_STRNE(0,runCycles->repAllocation);

	/*Record* record = newStorage();
	defineRecordPath(record, (char*)"fileName3.txt", (char*)".\\");
	fprintf(stdout, "\nRemoving test data: %s\n", (record->builtLocation));
	removeRecord(record);*/
	
}
