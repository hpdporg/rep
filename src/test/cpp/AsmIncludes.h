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
	void* getNextItemNesting(List* list);
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

	//Matches
	Matches* newMatches();
	MatchFlow* processMatchFlags(Matches* matches);
	List* getMatches(Matches* matches, char* letters);
	List* lettersSame(char* letters, char* containsLetters);


	//Replacement
	char* replaceLettersWithList(ReplaceFlags flags, char* letters, List* list, List* matchResultsList);

}


#endif