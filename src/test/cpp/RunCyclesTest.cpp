#include "AsmIncludes.h"
#include "RunCyclesTests.h"


class RunCyclesTest : public ::testing::Test {
 protected:
  void SetUp() override {
  
	Record* backupFile = newStorage();
	defineRecordPath(backupFile, (char*)"testRepListDefinedRefReps.rep", (char*)"..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nRestoring test data: %s\n", (backupFile->builtLocation));		
	retrieve(backupFile);

	Record* record = newStorage();
	defineRecordPath(record, (char*)"testRepListDefinedRefReps.rep", (char*)".\\");
	fprintf(stdout, "\nRestoring test data: %s\n", (record->builtLocation));	
	restoreLetters(record,(char*)backupFile->allocAddr);
	
	

  }

   void TearDown() override {
	Record* backupFile = newStorage();
	defineRecordPath(backupFile, (char*)"testRepListDefinedRefReps.rep", (char*)"..\\..\\..\\..\\src\\resources");
	fprintf(stdout, "\nRestoring test data: %s\n", (backupFile->builtLocation));		
	retrieve(backupFile);

	Record* record = newStorage();
	defineRecordPath(record, (char*)"testRepListDefinedRefReps.rep", (char*)".\\");
	fprintf(stdout, "\nRestoring test data: %s\n", (record->builtLocation));	
	restoreLetters(record,(char*)backupFile->allocAddr);
	


   }


};