/**
* @file fs.h
* @author Oshri Taub
* @brief <insert here file brief>
* @date 23/03/2022
* @copyright Copyright (c) 2022
*/
#pragma once

#include <arch/i386/i386.h>
#include <kernel/common/kuseful.h>


namespace FileSystem {

    //flags for the file type
    namespace FLags {
        constexpr uint32_t kFSFile = 0x01;
        constexpr uint32_t kFSDirectory = 0x02;
        constexpr uint32_t kFSChardevice = 0x03;
        constexpr uint32_t kFSBlockDevice = 0x04;
        constexpr uint32_t kFSPipe = 0x05;
        constexpr uint32_t kFSSymLink = 0x06;
        constexpr uint32_t kFSMountPoint = 0x08; // Is the file an active mountpoint?
    }

    //all the function needed for a fs can be at any arch just to match those types
    typedef uint32_t(*read_func)(struct FSNode *, uint32_t, uint32_t, uint8_t *);
    typedef uint32_t(*write_func)(struct FSNode *, uint32_t, uint32_t, uint8_t *);
    typedef void(*open_func)(struct FSNode *);
    typedef void(*close_func)(struct FSNode *);
    typedef struct Dirent *(*readDir_func)(struct FSNode *, uint32_t);
    typedef struct FSNode *(*findDir_func)(struct FSNode *, char *);

    struct FSNode {
        char name[128];     // The filename.
        uint32_t mask;        // The permissions mask.
        uint32_t uid;         // The owning user.
        uint32_t gid;         // The owning group.
        uint32_t flags;       // Includes the node type. (namespace Flags)
        uint32_t inode;       // This is device-specific.
        uint32_t length;      // Size of the file, in bytes.
        uint32_t impl;        // An implementation-defined number.
        read_func read;
        write_func write;
        open_func open;
        close_func close;
        readDir_func readdir;
        findDir_func finddir;
        FSNode *ptr; // Used by mountpoints and symlinks.
    };

    struct Dirent // One of these is returned by the readdir call, according to POSIX.
    {
        char name[128]; // Filename.
        uint32_t ino;     // Inode number. Required by POSIX.
    };


    extern FSNode *fs_root; //the root of the current fs

    //all are generic function encapsulate the fs function that can be at any arch (FAT EXT2)
    uint32_t read_fs(FileSystem::FSNode *node, uint32_t offset, uint32_t size, uint8_t *buffer);
    void open_fs(FileSystem::FSNode *node, uint8_t read, uint8_t write);
    uint32_t write_fs(FileSystem::FSNode *node, uint32_t offset, uint32_t size, uint8_t *buffer);
    void close_fs(FileSystem::FSNode *node);
    FileSystem::Dirent* readdir_fs(FileSystem::FSNode *node, uint32_t index);
    FileSystem::FSNode* finddir_fs(FileSystem::FSNode* node, char* name);
}