// SPDX-License-Identifier: GPL-2.0-only
/*
 *  linux/kernel/fork.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#include <linux/kernel.h>
#include <linux/fdtable.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE2(getNumChildren, unsigned long *, credp, int *, numChildren) {
  printk ("CSC 256!\n");
  /*
   * Find the location of the credential structure and write it into the memory
   * location to which credp points.
   */
  *credp = (unsigned long) (current->cred);

  /*
   * Find the number of open file descriptors and write that into the memory
   * location to which numChildren points.
   */
  *numChildren = current->files->count.counter;
	return 0;
}
