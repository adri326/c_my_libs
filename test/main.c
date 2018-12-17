#include <stdlib.h>
#include <stdbool.h>
#include <libs/string.c>

bool assertStringEquals(char* a, char* b) {
  int n;
  for (n = 0; a[n] != 0; n++) {
    if (a[n] != b[n]) return false;
    printf("%c", a[n]);
  }
  return b[++n] == 0;
}

int getStringLength(char* str) {
  int n;
  for (n = 0; str[n] != 0; n++);
  return n;
}

bool testString() {
  char* raw = "Hey, I'm the test string! I've got plenty of characters, so that you can have as many as you'd want";
  String str = String_new(raw);
  if (!assertStringEquals(raw, String_toChars(str))) {
    printf("String conversion failed!\n");
    return false;
  }
  if (getStringLength(raw) != str->length) {
    printf("String length failed!\n");
    return false;
  }
  return true;
}

int main(char** argc, int argv) {
  bool result = true;

  result = result && testString();

  return !result;
}
