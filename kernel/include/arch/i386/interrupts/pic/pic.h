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
    // IDT offsets
    constexpr uint8_t kMasterOffset = 0x20;
    constexpr uint8_t kSlaveOffset = 0x28;

    // I/O base address for master and slave
    constexpr uint8_t kMasterAddress = 0x20;
    constexpr uint8_t kSlaveAddress = 0xA0;

    // master and slave command & data ports
    constexpr uint8_t kMasterCommand = kMasterAddress;
    constexpr uint16_t kMasterData = kMasterAddress + 1;
    constexpr uint8_t kSlaveCommand = kSlaveAddress;
    constexpr uint16_t kSlaveData = kSlaveAddress + 1;

    constexpr uint8_t kEOI	= 0x20;	// End-of-interrupt command code
    
    constexpr uint8_t kICW1ICW4	= 0x01;	// ICW4 (not) needed
    constexpr uint8_t kICW1Single =	0x02; // Single (cascade) mode
    constexpr uint8_t kICW1Interval4 = 0x04; // Call address interval 4 (8)
    constexpr uint8_t kICW1Level = 0x08;	// Level triggered (edge) mode
    constexpr uint8_t kICW1Init	= 0x10;	// Initialization - required!
 
    constexpr uint8_t kICW48086	= 0x01;	// 8086/88 (MCS-80/85) mode
    constexpr uint8_t kICW4Auto	= 0x02;	// Auto (normal) EOI
    constexpr uint8_t kICW4BufSlave = 0x08; // Buffered mode/slave
    constexpr uint8_t kICW4BufMaster = 0x0C; // Buffered mode/master
    constexpr uint8_t kICW4SFnm	= 0x10;	// Special fully nested (not)

    void Initialize(); // Encapsulate the remap function
    void Remap(int master_offset, int slave_offset); // Remap the master and slave PIC to new IDT offsets
    void SendEOI(uint8_t irq); // sends end-of-interrupt to the pic chip when the interrupt routine is done \ end
}