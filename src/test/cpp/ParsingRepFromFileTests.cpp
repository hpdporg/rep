#include "AsmIncludes.h"
#include "ParsingRepFromFileTests.h"
#include "ParsingRepFromFileTest.cpp"



TEST_F(ParsingRepFromFileTest, ParsingRefValuesAndRetrieveFile) {
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
			fprintf(stdout, "\nRep definedRefFlags: %d\n", nextRef->definedRefFlags);
			resetIndex(nextRef->list);
			while (nextRef->list->index < nextRef->list->itemsCount) {
				Ref* paramRef = (Ref*)getNextItem(nextRef->list);
				fprintf(stdout, "\nparamRep name: %s\n", (char*)paramRef->ref);
				fprintf(stdout, "\nparamRep flags: %d\n", paramRef->flags);
				fprintf(stdout, "\nparamRep index: %d\n", paramRef->repIndex);
				fprintf(stdout, "\nRep definedRefFlags: %d\n", paramRef->definedRefFlags);
			}
			resetIndex(nextRef->list);
		
		}
		parsing->parsingRefs->index = priorIndex;
		fprintf(stdout, "\nRep count: %d\n", parsing->parsingRefs->itemsCount);
		

	}



}