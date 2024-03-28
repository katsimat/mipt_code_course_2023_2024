#include <iostream>

struct Heap {
  int64_t* heap;
  int64_t size;
  int64_t capacity;
};

struct ValueMax {
  int64_t value = 0;
  int64_t ind = 0;
};

int64_t LeftSon(int64_t n) {
  return 2 * n + 1;
}

int64_t RightSon(int64_t n) {
  return 2 * n + 2;
}

int64_t Parent(int64_t n) {
  return (n - 1) / 2;
}

void CopyArray(int64_t* array1, int64_t* array2, int64_t n) {
  for (int i = 0; i < n; ++i) {
    array2[i] = array1[i];
  }
}

int64_t SiftDown(Heap& heap_arr, int64_t node) {
  int64_t* heap = heap_arr.heap;
  int64_t size = heap_arr.size;
  int64_t left_child = LeftSon(node);
  int64_t right_child = RightSon(node);

  if (left_child >= size) {
    return node;
  }

  int64_t to_swap = left_child;
  if (right_child < size && heap[to_swap] < heap[right_child]) {
    to_swap = right_child;
  }

  if (heap[to_swap] > heap[node]) {
    std::swap(heap[to_swap], heap[node]);
    return SiftDown(heap_arr, to_swap);
  }
  return node;
}
ValueMax ExtractMax(Heap& heap_arr) {
  int64_t* heap = heap_arr.heap;
  int64_t size = heap_arr.size;

  std::swap(heap[0], heap[size - 1]);
  heap_arr.size--;

  ValueMax ans;
  ans.ind = SiftDown(heap_arr, 0);

  ans.value = heap[size - 1];
  return ans;
}

int64_t SiftUp(Heap& heap_arr, int64_t node) {
  int64_t parent = Parent(node);
  if (node > 0 && heap_arr.heap[parent] < heap_arr.heap[node]) {
    std::swap(heap_arr.heap[parent], heap_arr.heap[node]);
    return SiftUp(heap_arr, parent);
  }

  return node;
}

int64_t Push(Heap& heap_arr, int64_t node) {
  int64_t* heap = heap_arr.heap;
  int64_t size = heap_arr.size;

  if (size == heap_arr.capacity) {
    return -1;
  }

  heap[size] = node;
  heap_arr.size += 1;

  int64_t ind = SiftUp(heap_arr, size);

  return ind;
}

int64_t Delete(Heap& heap_arr, int64_t ind) {
  int64_t* heap = heap_arr.heap;
  int64_t size = heap_arr.size;

  std::swap(heap[ind - 1], heap[size - 1]);
  heap_arr.size--;

  if (heap[ind - 1] < heap[size - 1]) {
    SiftDown(heap_arr, ind - 1);
  } else {
    SiftUp(heap_arr, ind - 1);
  }

  return heap[size - 1];
}