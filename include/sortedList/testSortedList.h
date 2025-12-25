#pragma once
#include <stdbool.h>

struct TestCase {
    bool (*func)(void);
    const char* name;
};

bool testCreateAndDestroy(void);
bool testInsertSingle(void);
bool testInsertMultipleAscending(void);
bool testInsertMultipleDescending(void);
bool testInsertRandomOrder(void);
bool testInsertDuplicates(void);
bool testDeleteExisting(void);
bool testDeleteNonExisting(void);
bool testDeleteHead(void);
bool testDeleteTail(void);
bool testDeleteFromEmpty(void);
bool testDeleteAllElements(void);
bool testNegativeNumbers(void);
bool testPrintEmpty(void);
void runAllTests(void);
int runTestsWithSummary(void);