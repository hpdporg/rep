#include "../Rep.h"
#include "ProcessingProcessItemTests.h"


TEST(ProcessingProcessItemTest, RetrievesProcessItemList) {

	List* procList = getProcessItemList();
	fprintf(stdout, "\nCount: %d\n", procList->itemsCount);

	while (procList->index < procList->itemsCount) {
		ProcessItem* item = (ProcessItem*)getNextItem(procList);
		fprintf(stdout, "%s\n", item->label);
		fprintf(stdout, "\t%d\n", item->refFlags);
		fprintf(stdout, "\t%d\n", item->definedRefFlags);
		fprintf(stdout, "\t%d\n", item->paramCount);
		fprintf(stdout, "\t%d\n", item->refBaseFlags);
		fprintf(stdout, "\t%d\n", item->minParamCount);
		
		
	}
	
	EXPECT_EQ(7, procList->itemsCount);



}

TEST(ProcessingProcessItemTest, RefsInRefRegistryFromProcessItems) {

	
	RefRegistry* refRegistry = newRefRegistry();

	loadProcItemDefinedRefs(refRegistry);
	fprintf(stdout, "List item count %d\n", refRegistry->definedList->itemsCount);
	EXPECT_EQ(4, refRegistry->definedList->itemsCount);
}
