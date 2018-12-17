#ifndef MY_LIBS_STRING_H
#define MY_LIBS_STRING_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// TODO: clean

struct Stringling {
  char* content;
  char last;
  size_t length;
  struct Stringling* next;
};

typedef struct Stringling* Stringling;



struct String {
  size_t length;
  Stringling stringling;
};

typedef struct String* String;

String String_new(char* from);
String String_empty();
char* String_toChars(String str);
void String_append(String str1, String str2);
char String_charAt(String str, size_t n);
bool String_equals(String str1, String str2);
void String_print(String str);
void String_destroy(String str);

Stringling Stringling_new(char* content, size_t length);
Stringling Stringling_empty();
void Stringling_destroy(Stringling stringling);

#endif
