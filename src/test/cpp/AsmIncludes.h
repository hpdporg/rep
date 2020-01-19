#ifndef ASM_INCLUDES_H
#define ASM_INCLUDES_H

#include <Windows.h>


typedef struct ListItem {
	void* item;
	void* previous;
	_int64 nesting;
	void* next;
} ListItem;

typedef struct ItemMatch {
	void* item;
	_int64 index;
	_int64 nesting;
} ItemMatch;

typedef struct List {
	void* firstItem;
	_int64	listSize;
	_int64	itemsCount;
	_int64	index;
	void* indexItem;
	_int64	indexedItemIndex;
	void* itemMatch;
} List;

typedef struct Record {
	void* allocAddr;
	_int64	allocSize;
	char* name;
	char* location;
	char* builtLocation;
	HANDLE handle;
} Record;

typedef struct Matches {
	_int64	flags;
	_int64	transformFlags;
	List* containsRangeList;
	_int64 subRangeStartIndex;
	_int64 subRangeEndIndex;
} Matches;


typedef struct MatchFlow {
	_int64	contains;
	_int64	start;
	_int64	end;
	_int64	firstMatch;
	_int64	everyMatch;
	_int64	matchIndexCount; 
	_int64	startEndLength; 
} MatchFlow;

typedef enum MatchesFlags{
	MATCH_START = 1,
	MATCH_END = 2,
	MATCH_FIRST = 4,
	MATCH_EVERY = 8,
	MATCH_TRANSFORM = 16,
	MATCH_SUBRANGE = 32,
	MATCH_SUBRANGE_START_IND = 64,
	MATCH_SUBRANGE_END_IND = 128	
} MatchesFlags;

typedef enum TransformFlags{
	TRANSFORM_INSENSITIVE_CASE = 1,
	TRANSFORM_RANGE = 2,
	TRANSFORM_CONTAINS = 4,
	TRANSFORM_EXCLUDES = 8,
	TRANSFORM_CONTAINS_DISCONTINUOUS = 16,
	TRANSFORM_STARTS_WITH = 32,
	TRANSFORM_ENDS_WITH = 64,
	TRANSFORM_CONTAINS_SEQUENTIAL = 128,
	TRANSFORM_CONTAIN_OPTIONAL_COUNT = 256		
} TransformFlags;

								
typedef enum ReplaceFlags{
	REPLACE_BETWEEN = 1,
	REPLACE_INSERT = 2
} ReplaceFlags;

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

	// Letters
	char* numAsLetters(_int64 num);
	char* appendLetters(char* letters1, char* appendingLetters);
	_int64 letterLength(char* letters);
	char* lettersBetweenListsIndices(char* letters, List* indicesList);
	char* lettersBetweenIndices(char* letters, _int64 startIndex, _int64 endIndex);

	// Allocate
	void* linearAllocate(int size);

	// List
	List* newList();
	void newLastItem(List* list, void* item);
	void* getNextItem(List* list);
	void* getLastDivergedItem(List* list);
	void* getLastDivergedItemNesting(List* list);
	_int64 getNextItemNesting(List* list);
	_int64 getConvergedItemCount(List* list);
	void* getNextTangentItem(List* list, _int64 nesting);
	void* nextItemNesting(List* list, _int64 nesting);
	void resetIndex(List* list);
	void* newNextItem(List* list, void* item);
	void* getPriorItem(List* list);
	void* getNextItemMatch(List* list, void* itemMatch);
	void* getNextItemMatchComp(List* list, void* itemMatch, _int64 comp);

	//Storage
	Record* newStorage();
	Record* defineRecordPath(Record* record, char* name, char* location);
	Record* retrieve(Record* record);
	Record* storeLetters(Record* record, char* letters);
	Record* restoreLetters(Record* record, char* letters);
	List* retrieveRecordNames(Record* record);
	void removeRecord(Record* record);

	//Matches
	Matches* newMatches();
	MatchFlow* processMatchFlags(Matches* matches);
	List* getMatches(Matches* matches, char* letters);
	List* lettersSame(char* letters, char* containsLetters);


	//Replacement
	char* replaceLettersWithList(ReplaceFlags flags, char* letters, List* list, List* matchResultsList);

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