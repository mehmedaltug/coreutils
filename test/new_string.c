#include "new_string.h"
#include <stdio.h>

int main(){
    String str1 = StringCreate("123,321");
    String str2 = StringCreate("123,321");
    String str3 = StringCreate("123,321,");
    String str4 = StringCreate("321");
    String delim = StringCreate(",");

    char* names[] = {"Compare", "Find", "Get Printable", "Split", "Concat", "Copy"};
    char* state[] = {"FAILED", "PASSED"};
    int tests[] = {0, 0, 0, 0, 0, 0};
    int test_count = 6;

    tests[0] = StringCompare(str1, str2);
    tests[1] = StringFind(str1, str4) != -1;
    tests[2] = StringCompare(StringCreate(StringGetPrintable(str1)), str1);
    int count = 0;
    String* splits = StringSplit(str1, delim, &count);
    tests[3] = StringCompare(splits[0], StringCreate("123")) && StringCompare(splits[1], str4) && count == 2;
    StringConcat(&str1, delim);
    tests[4] = StringCompare(str1, str3);
    StringCopy(str1, &str4);
    tests[5] = StringCompare(str1, str4) && str1.start != str4.start;

    for(int i = 0; i < test_count; i++){
        printf("%s: %s\n", names[i], state[tests[i]]);
    }
    if(!tests[0] || !tests[5])
        printf("\nWARNING: As Compare | Copy Failed, Results Are Deemed Inaccurate");
}
