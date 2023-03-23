#pragma once

#include "stddef.h"
#include "stdint.h"

typedef struct ext2_fs ext2_fs_t;
typedef struct ext2_file ext2_file_t;

typedef enum ext2_error {
  ext2_error_none = 0,
  ext2_error_no_file,
  ext2_error_corrupt,
  ext2_error_malloc,
  ext2_error_invalid_path,
  ext2_error_other
} ext2_error_t;

ext2_error_t ext2_read_file(ext2_fs_t *fs, const char *path, size_t *size,
                            uint8_t **buffer);
ext2_error_t ext2_write_file(ext2_fs_t *fs, const char *path, size_t size,
                             uint8_t *buffer);
