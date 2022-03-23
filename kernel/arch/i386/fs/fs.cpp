/**
* @file fs.cpp
* @author Oshri Taub
* @brief <insert here file brief>
* @date 23/03/2022
* @copyright Copyright (c) 2022
*/
#include <arch/i386/fs/fs.h>

FileSystem::FSNode *FileSystem::fs_root = 0;

/**
 * read a node content
 * @param node - the node
 * @param offset - the offset to read
 * @param size - the size
 * @param buffer - where to content will be saved
 * @return - status
 */
uint32_t FileSystem::read_fs(FileSystem::FSNode* node, uint32_t offset, uint32_t size, uint8_t* buffer) {

    if (node->read)
        return node->read(node, offset, size, buffer);
    else
        return 0;
}

/**
 * open a node
 * @param node - the node
 * @param read - is read
 * @param write is write
 */
void FileSystem::open_fs(FileSystem::FSNode* node, uint8_t read, uint8_t write) {
    if (node->open)
        node->open(node);

}

/**
 * write to file
 * @param node the node to write
 * @param offset - the offset to write
 * @param size - the size of the input
 * @param buffer - the content
 * @return - status
 */
uint32_t FileSystem::write_fs(FileSystem::FSNode* node, uint32_t offset, uint32_t size, uint8_t* buffer) {

    if (node->write)
        return node->write(node, offset, size, buffer);
    else
        return 0;
}

/**
 * close file
 * @param node the node to close
 * @return -
 */
void FileSystem::close_fs(FileSystem::FSNode* node) {

    if (node->close)
        node->close(node);
}

/**
 * return the index pos child of a dir
 * @param node - the node to search
 * @param index - the child to return
 * @return - the index pos child
 */
FileSystem::Dirent* readdir_fs(FileSystem::FSNode* node, uint32_t index) {

    if ((node->flags&0x7) == FileSystem::FLags::kFSDirectory && node->readdir)
        return node->readdir(node,index);
    else
        return 0;
}

/**
 * function to find a child inside dir
 * @param node - the node
 * @param name -the name of the dir
 * @return - the node
 */
FileSystem::FSNode* finddir_fs(FileSystem::FSNode* node, char* name) {

    if ((node->flags&0x7) == FileSystem::FLags::kFSDirectory && node->finddir)
        return node->finddir(node, name);
    else
        return 0;
}