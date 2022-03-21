/**
* @file cpp_support.h
* @author Ori Feldman
* @brief <insert here file brief>
* @date 3/21/22
* @copyright Copyright (c) 2022
*/

#pragma once

#include <libc/stdlib.h>

// useless functions
inline void* operator new(size_t, void* p) { return p; }
inline void* operator new[](size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}
inline void operator delete[](void*, void*) {}

// operators used for allocating and freeing memory
void* operator new(size_t size);
void* operator new[](size_t size);
void operator delete(void* p);
void operator delete[](void* p);
void operator delete(void* p, long unsigned int size);
void operator delete[](void* p, long unsigned int size);