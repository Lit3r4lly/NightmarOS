/**
* @file containers.h
* @author Oshri Taub
* @brief <insert here file brief>
* @date 27/01/2022
* @copyright Copyright (c) 2022
*/
#pragma once
#include <kernel/common/kuseful.h>
#include <arch/i386/paging/memory_manager.h>

//array that keeps the items ordered
namespace OrderedArray {

    using lessThanPredicate_t = int8_t(*)(type_t, type_t);
    struct Array {
        type_t* array; //the beginning of the array
        uint32_t size; //the current size of the array
        uint32_t max_size; //the max size of the array
        lessThanPredicate_t less_than; //function to sort the items
    };

    //default function for the sort
    int8_t LessThan(type_t first, type_t second);

    //create the array
    Array CreateOrderedArray(uint32_t max_size, lessThanPredicate_t less_then = OrderedArray::LessThan); //create using kmalloc
    Array PlaceOrderedArray(void* address, uint32_t max_size, lessThanPredicate_t less_than = OrderedArray::LessThan); //creating at index

    //destroy the array
    void DestroyOrderedArray(Array* array);

    //insert element
    void InsertToArray(type_t* item, Array* array);

    //find element at index
    type_t Find(uint32_t index, Array* array);

    //remove element at index
    void Remove(uint32_t index, Array* array);
};