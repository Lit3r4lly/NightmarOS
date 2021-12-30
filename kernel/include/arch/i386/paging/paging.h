/**
* @file paging.h
* @author Oshri Taub
* @brief <insert here file brief>
* @date 23/12/2021
* @copyright Copyright (c) 2021
*/
#pragma once

#include <kernel/common/kuseful.h>
#include <kernel/logs/logs.h>
#include <arch/i386/i386.h>

/*
 * 1. Normal memory is firstly and once mapped in the initialization of the OS -> kernel memory region is from 0x0 to 0xXXXXXXX and no need to mess with it all along
 * 2. Heap memory is located in random place in the memory, and it's mapped by growing whenever needed (malloc makes new mapping for page frames)
 */

namespace Paging {
    constexpr uint32_t kPageDirectorySize = 1024;
    constexpr uint32_t kPageTableSize = 1024;

    struct Page {
        uint32_t is_present : 1;
        uint32_t rw : 1;
        uint32_t is_user : 1;
        uint32_t was_accessed : 1;
        uint32_t was_written : 1;
        uint32_t reserved : 4;
        uint32_t flags : 3;
        uint32_t frame_addr : 20;
    };

    struct PageTable {
        Page entries[kPageTableSize];
    };

    struct PageDirectory {
        PageTable* entries[kPageDirectorySize]; //pointers to page tables
        uint32_t physical_table_addresses[kPageDirectorySize]; //pointers to physical addresses of tables
        uint32_t physical_addresses; //physical addresses of the array above
    };

    void  Initialize(); //function to init the paging
    Paging::Page* GetPage(uint32_t address, int make, PageDirectory* directory); // function to get a page
};

ASM_SCOPE void enable_paging();
ASM_SCOPE void load_page_directory(uint32_t page_directory_addr);