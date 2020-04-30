#ifndef DATAP_INCLUDES_H
#define DATAP_INCLUDES_H

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


typedef struct Flow {
	List* lists;
	_int64	width;
	_int64	i;
	_int64	j;
	_int64	length;
	_int64	paddingValue;
} Flow;

typedef struct Record {
	void* allocAddr;
	_int64	allocSize;
	char* name;
	char* location;
	char* builtLocation;
	HANDLE handle;
	_int64	allocFlags;
	char* jDelimiter;
	char* iDelimiter;
} Record;

typedef enum StorageAllocFlags {
	STORAGE_ALLOC_LETTERS = 1,
	STORAGE_ALLOC_LIST = 2,
	STORAGE_ALLOC_FLOW = 4,
	STORAGE_ALLOC_BINARY = 8,
} StorageAllocFlags;

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


								
typedef struct Time{
	_int64	year;
	_int64	month;
} Time;

typedef struct NumericParsing {
	_int64	opFlags;
} NumericParsing;

typedef enum NumericParsingOpFlags {
	NUM_PARS_OP_MORE = 1,
	NUM_PARS_OP_LESS = 2,
	NUM_PARS_OP_DIV = 4,
	NUM_PARS_OP_MUL = 8,
} NumericParsingOpFlags;

typedef struct NumericExpression {
	_int64	numericConditionFlag;
	char*	expressionAlloc;
	List*	expressionExtractList;
	List*	numExpRefValList;
	_int64	evalFlags;
	_int64	expressionFlags;
	_int64	result;
	NumericParsing* numericParsing;
} NumericExpression;

typedef enum ExpressionFlags {
	NUM_EXP_MORE = 1,
	NUM_EXP_LESS = 2,
	NUM_EXP_SAME = 4,
	NUM_EXP_DEF_ONLY = 8,
	NUM_EXP_DEF_NUM = 16,
	NUM_EXP_CONTAINS = 32,
	NUM_EXP_WITHIN = 64
} ExpressionFlags;

typedef enum EvalFlags {
	NUM_EXP_EVAL_PARSED = 1,
	NUM_EXP_EVAL_REFS_PARSED = 2,
	NUM_EXP_EVAL_REFS_PROCESSED = 4,
	NUM_EXP_EVAL_PROCESSED = 8,
	NUM_EXP_EVAL_RESULT_EXISTS = 16,
} EvalFlags;

typedef struct NumExpRefVal {
	char*	labelAlloc;
	_int64	val;
	_int64	flags;
	_int64	refFlags;
	_int64	refFilterFlags;
} NumExpRefVal;

typedef enum NumExpRefValFlags {
	NUM_EXP_REF_VAL_REF = 1,
	NUM_EXP_REF_VAL_INTEGER = 2,
	NUM_EXP_REF_VAL_FLOAT = 4,
	NUM_EXP_REF_VAL_DATE = 8,
} NumExpRefValFlags;

typedef enum NumExpRefFlags {
	NUM_EXP_REF_LOC = 1,
	NUM_EXP_REF_LIST = 2,
	NUM_EXP_REF_FLOW = 4,
} NumExpRefFlags;

typedef enum NumExpRefFiltFlags {
	NUM_EXP_REF_FILT_NO_FILT = 1,
	NUM_EXP_REF_FILT_HAS_FILT = 2,
} NumExpRefFiltFlags;




///extern char* pathSepLettersChar;
extern "C" {

	// Letters
	char* numAsLetters(_int64 num);
	char* appendLetters(char* letters1, char* appendingLetters);
	_int64 letterLength(char* letters);
	char* lettersBetweenListsIndices(char* letters, List* indicesList);
	char* lettersBetweenIndices(char* letters, _int64 startIndex, _int64 endIndex);
	_int64 lettersAsNum(char* letters);


	// Allocate
	void* linearAllocate(int size);
	void* allocateNew(int lastMemberOffset);		// Initializes a struc

	// List
	List* newList();
	void newLastItem(List* list, void* item);
	void* getNextItem(List* list);
	void* getLastDivergedItem(List* list);
	void* getLastDivergedItemNesting(List* list);
	_int64 getNextItemNesting(List* list);
	_int64 getConvergedItemCount(List* list);
	void* getNextTangentItem(List* list, _int64 nesting);
	void* nextItemNesting(List* list, _int64 nesting);						// Updates next item's nesting
	void* lastItemNesting(List* list, _int64 nesting);						// Updates last item's nesting
	void resetIndex(List* list);
	void* newNextItem(List* list, void* item);
	void* getPriorItem(List* list);
	void* getNextItemMatch(List* list, void* itemMatch);
	void* getNextItemMatchComp(List* list, void* itemMatch, _int64 comp);
	List* extendList(List* list, List* extensionList);

	//Flow
	Flow* newFlow();
	void newLastFlowList(Flow* flow, List* list);
	void newLastFlowIVals(Flow* flow, List* iVals);
	void increaseFlowWidth(Flow* flow, _int64 width);
	void resetFlowIJ(Flow*);
	void* getNextFlowItem(Flow*);

	//Storage
	Record* newStorage();
	Record* defineRecordPath(Record* record, char* name, char* location);
	Record* retrieve(Record* record);
	Record* storeLetters(Record* record, char* letters);
	Record* restoreLetters(Record* record, char* letters);
	List* retrieveRecordNames(Record* record);
	void removeRecord(Record* record);
	Record* storeList(Record* record, List* list);
	Record* restoreList(Record* record, List* list);
	
	void debugNum(_int64 num);
	void debugLetters(char* letters);
	void debugNumMsg(_int64 num);
	void debugLettersMsg(char* letters);

	//Matches
	Matches* newMatches();
	MatchFlow* processMatchFlags(Matches* matches);
	List* getMatches(Matches* matches, char* letters);
	List* lettersSame(char* letters, char* containsLetters);
	_int64 lettersSameExact(char* letters, char* containsExactLetters);
	_int64 getNextMatchIndex(char* letters, char* containsLetters);
	_int64 hasMatch(char* letters, char* containsLetters);
	_int64 listHasMatch(List* list, char* containsLetters);
	List* extractBetween(char* letters, char* delimiter);
	Flow* extractFlowBetween(char* letters, char* iDelimiter, char* jDelimiter);

	//Replacement
	char* replaceLettersWithList(ReplaceFlags flags, char* letters, List* list, List* matchResultsList);
	char* replaceContainsLettersWithList(char* letters, List* list, char* containsLetters);
	List* replaceContainsLettersWithFlow(char* letters, Flow* flow, char* containsLetters);

	//Time
	Time* newTime();
	Time* getNow();


	//NumericExpressions
	NumericExpression* newNumericExpression();
	void parseNumExpression(NumericExpression* numericExpression);
	List* getNumExpTermList();
	List* getCondExpTermList();
	List* getDefExpTermList();

	NumExpRefVal* newNumExpRefVal();
	NumExpRefVal* parseNumExpRefVal(NumExpRefVal* numExpRefVal);
	NumExpRefVal* processNumExpRefVal(NumExpRefVal* numExpRefVal);

	NumericParsing* newNumericParsing();

}



#endif