#ifndef NEW_STRING
#define NEW_STRING
typedef struct String {
  char *start;
  int length;
  int is_malloc;
} String;

String StringCreate(char *str);
void StringCopy(String source, String *dest);
int StringFind(String str, String obj);
char *StringGetPrintable(String str);
String *StringSplit(String str, String delimiter, int *item_count);
int StringCompare(String str1, String str2);
void StringConcat(String *str1, String str2);
void StringFree(String *str);
#endif
