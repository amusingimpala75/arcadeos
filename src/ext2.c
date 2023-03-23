#include "arcadeos/ext2.h"

#include "ctype.h"
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

const uint32_t EXT2_ROOT_INODE_INDEX = 2;

struct ext2_fs {
  void (*read)(ext2_fs_t *fs, uint32_t offset, size_t count, uint8_t *buffer);
  uint32_t block_size;
};

typedef uint32_t block_ptr;

typedef struct inode {
  uint64_t size;
  block_ptr direct[12];
  block_ptr indirect_block;
  block_ptr double_indirect_block;
  block_ptr triple_indirect_block;
  bool is_file;
} inode_t;

inode_t *ext2_fs_get_inode(ext2_fs_t *fs, uint64_t index);

inode_t *inode_get_child(inode_t *inode, const char *name);

bool valid_path(const char *path) {
  while (path[0] != '\0') {
    if (!isalnum(path[0]) | (path[0] != '_') | (path[0] != '-') |
        (path[0] != '/'))
      return false;
  }
  return true;
}

void read_block(ext2_fs_t *fs, block_ptr block, size_t count, uint8_t *buffer) {
  fs->read(fs, block * fs->block_size, count, buffer);
}

ext2_error_t ext2_read_file(ext2_fs_t *fs, const char *path, size_t *size,
                            uint8_t **buffer) {
  // only accept absolute paths
  if (!valid_path(path) | (path[0] != '/'))
    return ext2_error_invalid_path;
  path++;
  // find root inode
  inode_t *inode = ext2_fs_get_inode(fs, EXT2_ROOT_INODE_INDEX);
  // traverse down the directory structure
  const char *step_end = path;
  // while there is still a '/' in the filepath pick sub-inode
  while ((step_end = strchr(path, '/')) != NULL) {
    // allocate space for a string that holds the directory name
    char *step = malloc(sizeof(char) * (step_end - path));
    if (step == NULL)
      return ext2_error_malloc;
    // copy the string and null terminate
    memcpy(step, path, step_end - path - 1);
    step[step_end - path - 1] = '\0';
    // get the child inode
    inode = inode_get_child(inode, step);
    free(step);
    // if NULL then the file either doesn't exist
    if (inode == NULL)
      return ext2_error_no_file;
    // update the new path to only include the remaining subdirectories
    path = ++step_end;
  }
  // check and make sure this is a file, not a directory
  if (!inode->is_file)
    return ext2_error_no_file;
  // read file size
  size_t file_size = inode->size;
  *size = file_size;
  // allocate file buffer
  uint8_t *buf = malloc(sizeof(uint8_t) * file_size);
  *buffer = buf;
  if (buf == NULL)
    return ext2_error_malloc;
  uint32_t pointer_index = 0;
  // while there are still more bytes to copy
  while (file_size > 0) {
    // copy by block size or file size, which ever is smaller
    size_t how_much = file_size > fs->block_size ? fs->block_size : file_size;
    if (pointer_index < 12) {
      read_block(fs, inode->direct[pointer_index], how_much, buf);
    } else {
      // indirect cases TODO
      return ext2_error_corrupt;
    }
    // decrease file size remaining and increase buffer position
    // by how much we have read
    file_size -= how_much;
    buf += how_much;
    // go to next block pointer
    pointer_index++;
  }
  return ext2_error_other;
}

ext2_error_t ext2_write_file(ext2_fs_t *fs, const char *path, size_t size,
                             uint8_t *buffer) {
  return ext2_error_other;
}
