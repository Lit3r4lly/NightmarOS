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
#include <arch/i386/interrupts/pic/pic.h>
#include <arch/i386/i386.h>

namespace paging {



    C_SCOPE void enable_paging();
    C_SCOPE void load_page_directory(uint32_t directory_pointer);
}