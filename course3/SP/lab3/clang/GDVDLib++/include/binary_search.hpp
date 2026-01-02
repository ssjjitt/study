#ifndef BINARY_SEARCH_HPP
#define BINARY_SEARCH_HPP

#define ARRAY_SIZE 1024

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

extern "C" EXPORT const int m_array[ARRAY_SIZE];

EXPORT int binary_search_iterative(int* a, int n, int x);

extern "C" EXPORT int binary_search_recursive(int* a, int x, int i, int j);

#endif 
