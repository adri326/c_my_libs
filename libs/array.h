#ifndef MY_LIBS_ARRAY_H
#define MY_LIBS_ARRAY_H

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

// TODO: clean all refactor

void printArray(int* arr, size_t size);
void fill(int* arr, size_t size, int val);
void fillRandom(int* arr, size_t size, int max);
void fillLinear(int* arr, size_t size, int a, int b);
void copyArray(int* arr1, int* arr2, size_t size);
void userFill(int* arr, size_t size);
int arrayMax(int* arr, size_t size);
long int arraySum(int* arr, size_t size);
int arrayAverage(int* arr, size_t size);
char arrayEquals(int* arr1, int* arr2, size_t size);
int occurences(int* arr, size_t size, int value);
void invert(int* arr1, int* arr2, size_t size);
int arrayOccurences(int* arr1, size_t size1, int* arr2, size_t size2);

typedef struct IntArray {
  size_t length;
  int* values;
  int (*sum)(void*);
  int (*fill)(void*, int);
} IntArray;

IntArray* IntArray_new(size_t length);
int IntArray_sum(void* self);
int IntArray_fill(void* self, int value);
/*
typedef enum {
  type_char,
  type_int,
  type_float
} type_t;

size_t type_length(type_t type);

typedef struct Array {
  type_t type;
  size_t length;
  void* values;
} Array;

#define convert(type, value) ( \
  (type == type_char ? (char)value : ( \
  type == type_int ? (int)value : ( \
  type == type_float ? (float)value : ( \
    value \
  )))) \
)

#define convert_ptr(type, value) ( \
  (type == type_char ? (char*)value : ( \
  type == type_int ? (int*)value : ( \
  type == type_float ? (float*)value : ( \
    (void*)value \
  )))) \
)

Array* Array_new(type_t type, size_t length, void* value);
void* Array_get(Array* arr, size_t n);
void _Array_set(Array* arr, size_t n, void* value);

#define Array_set(arr, n, value) ({{ \
  switch (arr->type) { \
    case type_int: { \
      int x = value; \
      _Array_set(arr, n, &x); \
    } break; \
    case type_float: { \
      float x = value; \
      _Array_set(arr, n, &x); \
    } break; \
    case type_char: { \
      char x = value; \
      _Array_set(arr, n, &x); \
    } \
  } \
}})*/

#endif
