#include "sortfns.h"
#include "step.h"

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
