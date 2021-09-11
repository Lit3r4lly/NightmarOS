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

    constexpr u8int kPic1 = 0x20;		/* IO base address for master PIC */
    constexpr u8int kPic2 = 0xA0;		/* IO base address for slave PIC */
    constexpr u8int kPic1Command = kPic1;
    constexpr u16int kPic1Data = kPic1+1;
    constexpr u8int kPic2Command = kPic2;
    constexpr u16int kPic2Data = kPic2+1;
    constexpr u8int kPicEoi	= 0x20;		/* End-of-interrupt command code */
    
    constexpr u8int kIcw1Icw4	= 0x01;		/* ICW4 (not) needed */
    constexpr u8int kIcw1Single =	0x02;		/* Single (cascade) mode */
    constexpr u8int kIcw1Interval4 = 0x04;		/* Call address interval 4 (8) */
    constexpr u8int kIcw1Level = 0x08;		/* Level triggered (edge) mode */
    constexpr u8int kIcw1Init	= 0x10;		/* Initialization - required! */
 
    constexpr u8int kIcw48086	= 0x01;		/* 8086/88 (MCS-80/85) mode */
    constexpr u8int kIcw4Auto	= 0x02;		/* Auto (normal) EOI */
    constexpr u8int kIcw4BufSlave = 0x08;		/* Buffered mode/slave */
    constexpr u8int kIcw4BufMaster = 0x0C;		/* Buffered mode/master */
    constexpr u8int kIcw4SFnm	= 0x10;		/* Special fully nested (not) */

    void PicRemap(int offset1, int offset2);
    void Initialize();

}