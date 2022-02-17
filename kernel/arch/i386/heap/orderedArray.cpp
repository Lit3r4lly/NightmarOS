/**
* @file orderedArray.cpp
* @author Oshri Taub
* @brief <insert here file brief>
* @date 27/01/2022
* @copyright Copyright (c) 2022
*/

#include <arch/i386/paging/memory_manager.h>

int8_t OrderedArray::LessThan(type_t first, type_t second) {
    return (first < second)?1:0;
}

/***
 * function to create new array using the allocation function
 * @param max_size the max size of the array
 * @param less_than the function to base the sort upon
 * @return the array
 */
OrderedArray::Array OrderedArray::CreateOrderedArray(uint32_t max_size, lessThanPredicate_t less_than) {
    OrderedArray::Array array;

    array.array = (type_t*)MemoryManager::AllocateMemory(max_size * sizeof (type_t),0,0);
    array.size = 0;
    array.max_size = max_size;
    array.less_than = less_than;

    return array;
}

/***
 * function to create new array at a given address
 * @param address - the address to use
 * @param max_size - the max size of the array
 * @param less_than - the function to base the sort upon
 * @return the array
 */
OrderedArray::Array OrderedArray::PlaceOrderedArray(type_t address, uint32_t max_size, lessThanPredicate_t less_than) {
    OrderedArray::Array array;

    array.array = (type_t*)address;
    memset(array.array, 0, max_size* sizeof (max_size));
    array.max_size = max_size;
    array.size = 0;
    array.less_than = less_than;

    return array;
}

/***
 * function to insert mew element to the array
 * @param item the element to insert
 * @param array the array to insert into
 */
void OrderedArray::InsertToArray(type_t item, OrderedArray::Array* array) {
    uint32_t iter {};
    while (iter < array->size && array->less_than(array->array[iter], item))
        iter++;

    if (iter == array->size) {
        array->array[array->size++] = item;
    } else {
        type_t tmp = array->array[iter];
        array->array[iter] = item;

        while (iter < array->size) {
            iter++;
            type_t tmp2 = array->array[iter];
            array->array[iter] = tmp;
            tmp = tmp2;
        }
        array->size++;
    }
}

/***
 * function to return the element at a given location
 * @param index the index to get its value
 * @param array the array to search from
 * @return the value
 */
type_t OrderedArray::Find(uint32_t index, OrderedArray::Array* array) {
    if (index >= array->size)
        return (type_t)-1; //the given index is not in the array

    return array->array[index];
}

/***
 * function to remove element from the array at a given index
 * @param index the index to remove the element from
 * @param array the array to remove from
 */
void OrderedArray::Remove(uint32_t index, Array *array) {
    while (index < array->size) {
        array->array[index] = array->array[++index];
    }
    array->size--;
}

/***
 * function to free the memory of the array
 * @param array the array to free its memory
 */
void OrderedArray::DestroyOrderedArray(Array *array) {
    MemoryManager::DeallocatePage(Paging::GetPage((uint32_t)&array->array, 0, MemoryManager::CurrentDir));
}