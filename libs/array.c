#include "array.h"

void printArray(int* arr, size_t size) {
  size_t i;
  for (i = 0; i < size; i++) {
    printf("%d: %d\n", i, arr[i]);
  }
}

void fill(int* arr, size_t size, int val) {
  size_t i;
  for (i = 0; i < size; i++) {
    arr[i] = val;
  }
}

void fillRandom(int* arr, size_t size, int max) {
  size_t i;
  for (i = 0; i < size; i++) {
    arr[i] = (int)(rand() % max);
  }
}

void fillLinear(int* arr, size_t size, int a, int b) {
  size_t i;
  for (i = 0; i < size; i++) {
    arr[i] = a*i+b;
  }
}

void userFill(int* arr, size_t size) {
  size_t i;
  for (i = 0; i < size; i++) {
    printf("%d: ", i);
    scanf("%d", &arr[i]);
  }
}

void copyArray(int* arr1, int* arr2, size_t size) {
  size_t i;
  for (i = 0; i < size; i++) {
    arr2[i] = arr1[i];
  }
}

int arrayMax(int* arr, size_t size) {
  size_t i;
  int maximum = INT_MIN;
  for (i = 0; i < size; i++) {
    if (maximum < arr[i]) {
      maximum = arr[i];
    }
  }
  return maximum;
}

long int arraySum(int* arr, size_t size) {
  long int sum = 0;
  size_t i;
  for (i = 0; i < size; i++) {
    sum += (long int)arr[i];
  }
  return sum;
}

int arrayAverage(int* arr, size_t size) {
  return (int)(arraySum(arr, size) / size);
}

char arrayEquals(int* arr1, int* arr2, size_t size) {
  size_t i;
  for (i = 0; i < size; i++) {
    if (arr1[i] != arr2[i]) return 0;
  }
  return 1;
}

int occurences(int* arr, size_t size, int value) {
  size_t i;
  int counter = 0;
  for (i = 0; i < size; i++) {
    if (arr[i] == value) counter++;
  }
  return counter;
}

void invert(int* arr1, int* arr2, size_t size) {
  int i;
  for (i = 0; i < size; i++) {
    arr2[i] = arr1[size - i];
  }
}

int arrayOccurences(int* arr1, size_t size1, int* arr2, size_t size2) {
  size_t i, j;
  int counter = 0;
  for (i = 0; i < size1 - size2; i++) {
    if (arrayEquals(arr1 + i, arr2, size2)) counter++;
  }
  return counter;
}

IntArray* IntArray_new(size_t length) {
  IntArray* arr = (IntArray*)malloc(sizeof(struct IntArray));
  int i;
  arr->values = (int*)malloc(sizeof(int) * length);
  arr->length = length;

  for (i = 0; i < length; i++) {
    arr->values[i] = 0;
  }

  arr->sum = &IntArray_sum;
  arr->fill = &IntArray_fill;

  return arr;
}

/*size_t type_length(type_t type) {
  switch (type) {
    case type_char:
      return sizeof(char);
    case type_int:
      return sizeof(int);
    case type_float:
      return sizeof(unsigned int);
  }
}*/

int IntArray_sum(void* _self) {
  IntArray* self = (IntArray*)_self;
  int i;
  int sum;
  for (i = 0; i < self->length; i++) {
    sum += self->values[i];
  }
  return sum;
}

int IntArray_fill(void* _self, int value) {
  IntArray* self = (IntArray*)_self;
  int i;
  for (i = 0; i < self->length; i++) {
    self->values[i] = value;
  }
}
/*
void _Array_set(Array* arr, size_t n, void* value) {
  #define set(type) ((type*)arr->values)[n] = *(type*)value
  switch (arr->type) {
    case type_int:
      set(int);
      break;
    case type_float:
      set(float);
      break;
    case type_char:
      set(char);
  }
}

Array* Array_new(type_t type, size_t length, void* value) {
  // printf("%d\n", *value);
  Array* arr = (Array*)malloc(sizeof(Array));
  int n;
  arr->type = type;
  arr->values = malloc(type_length(type));
  arr->length = length;
  for (n = 0; n < length; n++) {
    _Array_set(arr, n, value);
  }
  return arr;
}

void* Array_get(Array* arr, size_t n) {
  return arr->values + n * type_length(arr->type);
}*/
