#ifndef NEW_STRING_H_
#define NEW_STRING_H_

#include <stdlib.h>
#include <string.h>

typedef struct String {
  char *start;
  int length;
  int is_malloc;
} String;

String StringCreate(char *, int);
void StringCopy(String, String *);
int StringFind(String, String);
char *StringGetPrintable(String);
String *StringSplit(String, String, int *);
int StringCompare(String, String);
void StringConcat(String *, String);
void StringFree(String *);

String StringCreate(char *str, int is_malloc) {
  String string = {str, strlen(str), is_malloc};
  return string;
}

void StringCopy(String source, String *dest) {
  char *new_start = malloc(source.length);
  for (int i = 0; i < source.length; i++) {
    *(new_start + i) = *(source.start + i);
  }
  dest->start = new_start;
  dest->is_malloc = 1;
  dest->length = source.length;
}

int StringFind(String str, String obj) {
  if (obj.length > str.length) {
    return -1;
  } else if (obj.length == str.length) {
    if (StringCompare(str, obj))
      return 0;
    return -1;
  }
  for (int i = 0; i < str.length - obj.length + 1; i++) {
    String cmpstr = {str.start + i, obj.length, 0};
    if (StringCompare(cmpstr, obj))
      return i;
  }
  return -1;
}

char *StringGetPrintable(String str) {
  char *tmp = malloc(str.length + 1);
  for (int i = 0; i < str.length; i++) {
    *(tmp + i) = *(str.start + i);
  }
  *(tmp + str.length) = 0;
  return tmp;
}

String *StringSplit(String str, String delimiter, int *item_count) {
  String base_str;
  StringCopy(str, &base_str);
  if (base_str.length == 0 || delimiter.length == 0) {
    if (item_count)
      *item_count = 0;
    return NULL;
  }
  int count = 1;
  String cut_str = base_str;
  int pos;
  while ((pos = StringFind(cut_str, delimiter)) != -1) {
    count++;
    cut_str.start += pos + delimiter.length;
    cut_str.length -= pos + delimiter.length;
  }

  String *split_arr = malloc(sizeof(String) * count);
  if (!split_arr)
    return NULL;
  if (count == 1) {
    *split_arr = str;
    return split_arr;
  }
  cut_str = base_str;
  for (int i = 0; i < count - 1; i++) {
    pos = StringFind(cut_str, delimiter);
    split_arr[i] = (String){cut_str.start, pos, 0};
    cut_str.start += pos + delimiter.length;
    cut_str.length -= pos + delimiter.length;
  }
  split_arr[count - 1] = cut_str;
  if (item_count)
    *item_count = count;
  return split_arr;
}

int StringCompare(String str1, String str2) {
  if (str1.length != str2.length)
    return 0;
  for (int i = 0; i < str1.length; i++) {
    if (*(str1.start + i) != *(str2.start + i))
      return 0;
  }
  return 1;
}

void StringConcat(String *str1, String str2) {
  char *cat = malloc(str1->length + str2.length);
  memcpy(cat, str1->start, str1->length);
  memcpy(cat + str1->length, str2.start, str2.length);
  if (str1->is_malloc)
    free(str1->start);

  str1->start = cat;
  str1->length += str2.length;
  str1->is_malloc = 1;
}

void StringFree(String *str) {
  if (str->is_malloc) {
    free(str->start);
    str->length = 0;
  }
}

#endif /* NEW_STRING_H_ */
