/**
* @file pic.h
* @author Oshri Taub
* @brief this file declare th PIC handler
* @date 11/09/2021
* @copyright Copyright (c) 2021
*/

#pragma once
#include <kernel/common/kdefines.h>
#include <kernel/common/kuseful.h>
#include <kernel/logs/logs.h>
#include <kernel/ports/ports.h>

namespace PIC {
    constexpr u8int kPICMaster = 0x20;	// IO base address for master PIC
    constexpr u8int kPICSlave = 0xA0; // IO base address for slave PIC
    constexpr u8int kPICMasterCommand = kPICMaster;
    constexpr u16int kPICMasterData = kPICMaster + 1;
    constexpr u8int kPICSlaveCommand = kPICSlave;
    constexpr u16int kPICSlaveData = kPICSlave + 1;
    constexpr u8int kPICEOI	= 0x20;	// End-of-interrupt command code
    
    constexpr u8int kICW1ICW4	= 0x01;	// ICW4 (not) needed
    constexpr u8int kICW1Single =	0x02; // Single (cascade) mode
    constexpr u8int kICW1Interval4 = 0x04; // Call address interval 4 (8)
    constexpr u8int kICW1Level = 0x08;	// Level triggered (edge) mode
    constexpr u8int kICW1Init	= 0x10;	// Initialization - required!
 
    constexpr u8int kICW48086	= 0x01;	// 8086/88 (MCS-80/85) mode
    constexpr u8int kICW4Auto	= 0x02;	// Auto (normal) EOI
    constexpr u8int kICW4BufSlave = 0x08; // Buffered mode/slave
    constexpr u8int kICW4BufMaster = 0x0C; // Buffered mode/master
    constexpr u8int kICW4SFnm	= 0x10;	// Special fully nested (not)

    void PICRemap(int master_offset, int slave_offset); // Remap the master and slave PIC to new IDT offsets
    void Initialize(); // Encapsulate the remap function
}