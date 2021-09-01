/**
* @file kernel.h
* @author Ori Feldman
* @brief declare kernel entry point (main) header
* @date 8/25/21
* @copyright Copyright (c) 2021
*/

#pragma once

#include <arch/i386/tty/tty.h>
#include <arch/i386/gdt/gdt.h>
#include <kernel/logs/logs.h>
#include <kernel/common/kdefines.h>
#include <libc/stdio.h>