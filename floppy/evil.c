#include <sys/syscall.h>
#include <unistd.h>

/*
 * Function: getNumChildren()
 *
 * Description:
 *   Call the getNumChildren() system call that the instructor added to the
 *   kernel.
 *
 * Inputs:
 *   credp        - Pointer to an address in which to old the address of the
 *                  current process's credential structure.
 *   numChildrenp - Pointer to the number of children.
 *
 * Return value:
 *   0 - No errors.
 */
static inline int
getNumChildren (unsigned long * credp, int * numChildren) {
	/*
   * Call the getNumChildren system call.
   */
	return (syscall (181, credp, numChildren));
}

/*
 * Function: giveMeThePower()
 *
 * Description:
 *  This function should use system calls to exploit the kernel to provide this
 *  process with the ability to open the file.  Note that this function can use
 *  a multitude of system calls; there are at least two ways to exploit
 *  getNumChildren() to gain access to the file.
 */
unsigned int
giveMeThePower (void) {
  return 0;
}
