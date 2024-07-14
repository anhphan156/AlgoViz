#include "sortfns.h"
#include "step.h"

void swap(int *a, int *b) {
  if (*a != *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
  }
}

Step *insertion_sort(int *arr, int len) {
  int tmp, j;
  Step *step;
  for (int i = 1; i < len; i += 1) {
    tmp = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > tmp) {
      arr[j + 1] = arr[j];
      step_enqueue(j, j + 1);
      j -= 1;
    }
    arr[j + 1] = tmp;
  }

  return step;
}

Step *quick_sort(int *arr, int len, int step_offset) {
  Step *step;

  if (len <= 1)
    return (void *)0;

  int j = -1;
  int pivot = arr[len - 1];

  for (int i = 0; i < len; i += 1) {
    if (arr[i] < pivot) {
      j += 1;
      swap(arr + j, arr + i);
      if (i != j)
        step_enqueue(j + step_offset, i + step_offset);
    }
  }

  j += 1;
  swap(arr + len - 1, arr + j);
  if (len - 1 != j)
    step_enqueue(j + step_offset, len - 1 + step_offset);

  quick_sort(arr, j, step_offset);
  quick_sort(arr + j + 1, len - j - 1, step_offset + j + 1);

  return step;
}
