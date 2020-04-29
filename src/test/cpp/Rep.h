#ifndef REP_H
#define REP_H

#include <Windows.h>
#include "datap.h"



typedef enum ParsingFlags{
	PARSING_AT_NEWLINE = 1,
	PARSING_AT_DELIMITER = 2,
	PARSING_AT_LETTERS = 4
} ParsingFlags;


typedef enum RefBaseFlags{
	REF_BASE_DEFINED_REF_FIRST_PARAM = 1,
	REF_BASE_ITEM_DEFINED_REF = 2,
	REF_BASE_DEFINED_REF_NOT_FIRST_SECOND_PARAM	 = 4
} RefBaseFlags;

typedef enum RefFlags {
	REF_VALUE = 1,
	REF_LIST = 2,
	REF_DEFINED = 4,
	REF_FILTER = 8
} RefFlags;

typedef enum DefinedRefFlags {
	DEFINED_REF_STORE_FILE = 1,
	DEFINED_REF_RETRIEVE_FILE = 2,
	DEFINED_REF_LETTERS = 4,
	DEFINED_REF_REPLACE_LETTERS_LIST = 8,
	DEFINED_REF_SEPARATOR = 16
} DefinedRefFlags;

typedef struct Ref{
	char* ref;
	_int64 flags;
	_int64 unprocessed;
	_int64 paramCount;
	_int64 repIndex;
	void* valueAlloc;
	List* listAlloc;
	_int64 definedRefFlags;
	List* list;
} Ref;

typedef struct ProcessItem {
	char* label;
	_int64 refFlags;
	_int64 definedRefFlags;
	_int64 paramCount;
	_int64 refBaseFlags;
	_int64 minParamCount;
} ProcessItem;

typedef struct Parsing{
	char* delimiter;
	_int64 baseRepOffset;
	_int64 repOffset;
	char* endDelimiter;
	_int64 index;
	_int64 unParsedIndex;
	_int64 lineRefCount;
	_int64 multilineRefCount;
	List* parsingRefs;
	List* nestedParsingRefs;
	Ref* parsingDefinedRef;
	_int64 flags;
	_int64 endIndex;
} Parsing;

typedef struct RefRegistry{
	List* list;
	List* definedList;
} RefRegistry;

typedef struct RunCycles{
	RefRegistry* refRegistry;
	Parsing* parsing;
	List* repRecordList;
	_int64 cycleIndex;
	_int64 maxCycleCount;
	char* repAllocation;	
} RunCycles;


///extern char* pathSepLettersChar;
extern "C" {


	//Parsing
	Parsing* newParsing();
	char* getNextParsingValue(Parsing* parsing, char* letters);
	char* getNextParsingValueOrDelimiter(Parsing* parsing, char* letters);
	Ref* parseRep(Parsing* parsing, char* letters, RefRegistry* refRegistry);
	char* nextParsing(Parsing* parsing, char* letters, RefRegistry* refRegistry);
	char* parseRef(Parsing* parsing, char* letters, RefRegistry* refRegistry);
	char* buildRep(Parsing* parsing, char* letters, RefRegistry* refRegistry);

	//Processing
	char* processRep(Parsing* parsing, char* letters, RefRegistry* refRegistry);
	Ref* processRefValues(Parsing* parsing, Ref* item, RefRegistry* refRegistry);
	Ref* processRefItem(Ref* item, _int64 minParamCount, _int64 refBaseFlags, _int64 definedRefFlags, Parsing* parsing, RefRegistry* refRegistry);
	Ref* processLetters(Parsing* parsing, Ref* item, RefRegistry* refRegistry, DefinedRefFlags definedRefFlags);
	Ref* processAppending(Parsing* parsing, Ref* item, RefRegistry* refRegistry, DefinedRefFlags definedRefFlags);
	Ref* processStoreFile(Parsing* parsing, Ref* item, RefRegistry* refRegistry, DefinedRefFlags definedRefFlags);
	Ref* processRetrieveFile(Parsing* parsing, Ref* item, RefRegistry* refRegistry, DefinedRefFlags definedRefFlags);
	Ref* processReplaceLettersList(Parsing* parsing, Ref* item, RefRegistry* refRegistry, DefinedRefFlags definedRefFlags);
	void defineAsProcessed(Ref* ref, RefRegistry* refRegistry);
	Ref* getBaseRefAtIndex(Ref* item, _int64 index);
	Ref* getBaseRefUsingFlags(Ref* item, _int64 refBaseFlags);
	char* getRefLettersAlloc(Ref* item);
	List* getRefLettersList(Ref* item);
	_int64 getUnprocessedParams(Ref* item);
	_int64 getUnprocessedRegisteredParams(Ref* item, RefRegistry* refRegistry);

	List* getProcessItemList();
	void loadProcItemDefinedRefs(RefRegistry* refRegistry);

	//Ref
	Ref* newRef();
	void newLastRegisteredRef(RefRegistry* refRegistry, Ref* ref);
	void newLastRegisteredDefinedRef(RefRegistry* refRegistry, Ref* ref);
	Ref* getRegisteredRef(RefRegistry* refRegistry, Ref* ref, _int64 repIndex);
	RefRegistry* newRefRegistry();

	//RunCycles
	RunCycles* newRunCycles();
	void beginRunCycles(RunCycles* runCycles);
	void loadRunCycleReps(RunCycles* runCycles);
	void loadRunCycleRepAllocation(RunCycles* runCycles);	
	void loadRunCycleRefRegistry(RunCycles* runCycles);

}


#endif