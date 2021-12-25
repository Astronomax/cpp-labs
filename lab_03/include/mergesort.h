#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int mergesort(void* arr, size_t elements, size_t element_size, int(*comparator)(const void* el1, const void* el2));
