#include "AsmIncludes.h"
#include "RunCyclesTests.h"
#include "RunCyclesParsingProcessingTest.cpp"

TEST_F(RunCyclesParsingProcessingTest, ProcessesParsedRefs) {
	Record* record = newStorage();

	defineRecordPath(record, (char*)"testDefinedRefRep.rep", (char*)".\\");
	retrieve(record);


	Parsing* parsing = newParsing();
	RunCycles* runCycles = newRunCycles();
	RefRegistry* refRegistry = newRefRegistry();
	runCycles->refRegistry = refRegistry;

	loadRunCycleRefRegistry(runCycles);

	while ((parsing->index < parsing->endIndex)
		|| (parsing->index == 0)) {

		fprintf(stdout, "\nParsing index, endindex: %d %d\n", parsing->index, parsing->endIndex);
		parseRep(parsing, (char*)record->allocAddr, refRegistry);
		
		resetIndex(refRegistry->list);
		while (refRegistry->list->index < refRegistry->list->itemsCount) {
			Ref* registeredRef = (Ref*)getNextItem(refRegistry->list);
			fprintf(stdout, "\nNext Registered Ref, index: %s, %d", registeredRef->ref, (refRegistry->list->index - 1));
		}
		resetIndex(refRegistry->list);

		_int64 priorIndex = parsing->parsingRefs->index;
		resetIndex(parsing->parsingRefs);
		while (parsing->parsingRefs->index < parsing->parsingRefs->itemsCount) {
			Ref* nextRef = (Ref*)getNextItem(parsing->parsingRefs);
			fprintf(stdout, "\nRep name: %s\n", (char*)nextRef->ref);
			fprintf(stdout, "\nRep flags: %d\n", nextRef->flags);
			resetIndex(nextRef->list);
			while (nextRef->list->index < nextRef->list->itemsCount) {
				Ref* paramRef = (Ref*)getNextItem(nextRef->list);
				fprintf(stdout, "\nparamRep name: %s\n", (char*)paramRef->ref);
				fprintf(stdout, "\nparamRep flags: %d\n", paramRef->flags);
				fprintf(stdout, "\nparamRep index: %d\n", paramRef->repIndex);
			}
			resetIndex(nextRef->list);

		}
		parsing->parsingRefs->index = priorIndex;
		fprintf(stdout, "\nRep count: %d\n", parsing->parsingRefs->itemsCount);


	}
	processRep(parsing, (char*)record->allocAddr, refRegistry);
	resetIndex(parsing->parsingRefs);
	fprintf(stdout, "\nProcessing....\n\n\n");
	while (parsing->parsingRefs->index < parsing->parsingRefs->itemsCount) {
		Ref* nextRef = (Ref*)getNextItem(parsing->parsingRefs);
		fprintf(stdout, "\nRep name: %s\n", (char*)nextRef->ref);
		fprintf(stdout, "\nRep flags: %d\n", nextRef->flags);
		fprintf(stdout, "\nRep unprocessed: %d\n", nextRef->unprocessed);
		fprintf(stdout, "\nRep value alloc: %s\n", (char*)nextRef->valueAlloc);
		resetIndex(nextRef->list);
		while (nextRef->list->index < nextRef->list->itemsCount) {
			Ref* paramRef = (Ref*)getNextItem(nextRef->list);
			fprintf(stdout, "\nparamRep name: %s\n", (char*)paramRef->ref);
			fprintf(stdout, "\nparamRep flags: %d\n", paramRef->flags);
			fprintf(stdout, "\nparamRep index: %d\n", paramRef->repIndex);
			fprintf(stdout, "\nRep unprocessed: %d\n", paramRef->unprocessed);
			fprintf(stdout, "\nRep value alloc: %s\n", (char*)paramRef->valueAlloc);
		}
		resetIndex(nextRef->list);

	}
	resetIndex(parsing->parsingRefs);
}