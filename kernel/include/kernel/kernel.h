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
#include <arch/i386/interrupts/interrupts.h>
#include <kernel/keyboard/keyboard.h>
#include <kernel/keyboard/ps2/ps2_keyboard.h>
#include <kernel/logs/logs.h>
#include <kernel/common/kdefines.h>
#include <libc/stdio.h>
#include <libc/stdlib.h>
#include <kernel/common/kuseful.h>
#include <arch/i386/paging/paging.h>
#include <arch/i386/interrupts/pit/timer.h>
#include <kernel/cpp_support.h>
