/**
* @file cpp_support.cpp
* @author Ori Feldman
* @brief <insert here file brief>
* @date 3/21/22
* @copyright Copyright (c) 2022
*/

#include <kernel/cpp_support.h>

void* operator new(size_t size) {
    return malloc(size);
}

void* operator new[](size_t size) {
    return malloc(size);
}

void operator delete(void* p) {
    free(p);
}

void operator delete[](void* p) {
   free(p);
}

void operator delete(void* p, long unsigned int size) {
    (void)(size);
    free(p);
}

void operator delete[](void* p, long unsigned int size) {
    (void)(size);
    free(p);
}