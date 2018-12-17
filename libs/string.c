#include "string.h"
#define STRINGLING_SIZE 16

String String_new(char* from) {
  String str = (String)malloc(sizeof(struct String));
  int n = 0;
  int sub = 0;
  Stringling stringling;
  size_t len = 0;
  str->length = 0;
  while (from[n] != 0) {
    str->length++;
    n++;
  }
  if (str->length % STRINGLING_SIZE == 0) {
    len = str->length / STRINGLING_SIZE;
  }
  else {
    len = (str->length - (str->length % STRINGLING_SIZE)) / STRINGLING_SIZE + 1;
  }
  str->stringling = Stringling_new(from, len == 1 ? str->length : STRINGLING_SIZE);
  stringling = str->stringling;
  for (n = 1; n < len; n++) {
    stringling->last = 0;
    stringling->next = Stringling_new(from + n * STRINGLING_SIZE, n == len - 1 ? str->length - n * STRINGLING_SIZE : STRINGLING_SIZE);
    stringling = stringling->next;
  }
  stringling->last = 1;

  return str;
}

String String_empty() {
  String str = (String)malloc(sizeof(String));
  str->length = 0;
  str->stringling = Stringling_empty();

  return str;
}

char* String_toChars(String str) {
  Stringling stringling = str->stringling;
  char* result = (char*)malloc(sizeof(char) * str->length);
  int n = 0;
  int x;
  while (stringling->last == 0) {
    for (x = 0; x < STRINGLING_SIZE; x++) {
      result[n * STRINGLING_SIZE + x] = stringling->content[x];
    }
    stringling = stringling->next;
    n++;
  }
  for (x = 0; x < stringling->length; x++) {
    result[n * STRINGLING_SIZE + x] = stringling->content[x];
  }
  return result;
}

char String_charAt(String str, size_t n) {
  Stringling stringling = str->stringling;
  int x = 0;
  if (n >= str->length) return 0;
  while (++x * STRINGLING_SIZE < n + 1) {
    stringling = stringling->next;
  }
  //printf(": %d, %d ~ %d\n", x, n % STRINGLING_SIZE, stringling->content[n % STRINGLING_SIZE]);
  return stringling->content[n % STRINGLING_SIZE];
}

void String_append(String str1, String str2) {
  size_t length = str1->length, toSwallow = str2->length;
  Stringling current_stringling = str1->stringling;
  while (current_stringling->last == 0) {
    current_stringling = current_stringling->next;
  }
  while (toSwallow > 0) {
    if (current_stringling->length < STRINGLING_SIZE) {
      current_stringling->content[current_stringling->length] = String_charAt(str2, str2->length - toSwallow);
      current_stringling->length++;
    }
    else {
      current_stringling->last = 0;
      current_stringling->next = Stringling_new((char[1]){String_charAt(str2, str2->length - toSwallow)}, 1);
      current_stringling = current_stringling->next;
    }
    toSwallow--;
  }

  str1->length += str2->length;
}

bool String_equals(String str1, String str2) {
  Stringling current_stringling1 = str1->stringling;
  Stringling current_stringling2 = str2->stringling;
  if (str1->length != str2->length) return false;
  while (true) {
    int x;
    if (current_stringling1->length != current_stringling2->length) return false;
    for (x = 0; x < current_stringling1->length; x++) {
      if (current_stringling1->content[x] != current_stringling2->content[x]) return false;
    }
    if (current_stringling1->last == 0 && current_stringling2->last == 0) {
      current_stringling1 = current_stringling1->next;
      current_stringling2 = current_stringling2->next;
    }
    else break;
  }
  if (current_stringling1->last != current_stringling2->last) return false;
  return true;
}

void String_print(String str) {
  Stringling current_stringling = str->stringling;
  while (true) {
    int n;
    for (n = 0; n < current_stringling->length; n++) {
      printf("%c", current_stringling->content[n]);
    }
    if (current_stringling->last) break;
    current_stringling = current_stringling->next;
  }
  printf("\n");
}

void String_destroy(String str) {
  Stringling_destroy(str->stringling);
  free(str);
}

Stringling null_Stringling;

Stringling Stringling_new(char* content, size_t length) {
  Stringling stringling = (Stringling)malloc(sizeof(struct Stringling));
  int x;
  stringling->content = (char*)malloc(sizeof(char) * STRINGLING_SIZE);
  stringling->last = 1;
  stringling->length = length;
  stringling->next = null_Stringling;
  for (x = 0; x < STRINGLING_SIZE && x < length; x++) {
    stringling->content[x] = content[x];
  }
  return stringling;
}

Stringling Stringling_empty() {
  Stringling stringling = (Stringling)malloc(sizeof(Stringling));
  stringling->content = (char*)malloc(sizeof(char) * STRINGLING_SIZE);
  stringling->last = 1;
  stringling->length = 0;
  stringling->next = null_Stringling;
  return stringling;
}

void Stringling_destroy(Stringling stringling) {
  if (!stringling->last) {
    Stringling_destroy(stringling->next);
  }
  free(stringling->content);
  free(stringling);
}
