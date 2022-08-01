// SPDX-License-Identifier: GPL-2.0-only
/*
 *  linux/kernel/fork.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */
//

// SPDX-License-Identifier: GPL-2.0
/*
 *  linux/fs/file.c
 *
 *  Copyright (C) 1998-1999, Stephen Tweedie and Bill Hawes
 *
 *  Manage the dynamic fd arrays in the process files_struct.
 */


#include <linux/kernel.h>
#include <linux/fdtable.h>
#include <linux/syscalls.h>
#include <linux/cred.h>

/*
 * Function: count_open_files()
 *
 * Description:
 *  This function counts the number of open file descriptors.  It is taken from
 *  linux/fs/file.c and modified for our purposes.
 */
static unsigned int
count_open_files (struct fdtable *fdt) {
unsigned int size = fdt->max_fds;
  unsigned int i;
  unsigned int count = 0;

  /* Find the last open fd */
  for (i = 0; i < (size / BITS_PER_LONG); ++i) {
    if (fdt->open_fds[i]) {
    unsigned long mask;
      for (mask = 1u; mask != 0; mask = mask << 1u) {
        if (mask & fdt->open_fds[i]) {
          ++count;
        }
      }
    }
  }
  return count;
}

SYSCALL_DEFINE2(getNumFD, unsigned long *, credp, int *, numFD) {
  int num;

  /*
   * Find the location of the credential structure and write it into the memory
   * location to which credp points.
   */
  *credp = (unsigned long) (current_cred());

  /*
   * Find the number of open file descriptors and write that into the memory
   * location to which numFD points.
   */
  struct fdtable * fdtable = files_fdtable (current->files);
  *numFD = num = count_open_files(fdtable);
  return 0;
}
