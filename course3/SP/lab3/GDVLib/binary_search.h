#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#define ARRAY_SIZE 1024

extern const int m_array[ARRAY_SIZE];

int binary_search_iterative(int arr[], int size, int target);
int binary_search_recursive(int arr[], int left, int right, int target);

#endif