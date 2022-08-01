#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/* User ID of the nobody user on our QEMU virtual machine */
const static unsigned int nobody = 65534;

/* Group ID of the nogroup group on our QEMU virtual machine */
const static unsigned int nogroup = 65534;

/* Name of the file to open */
const static char * pathname = "/sesame";

/* Data to put into the file once it is opened */
const static char data[] = "Your Linux kernel has been hax0red!\n";

/* Prototype for the function for students to implement */
extern unsigned int giveMeThePower();


/*
 * Function: main()
 *
 * Description:
 *   Entry point for this program.
 *
 * Inputs:
 *   argc - The number of argument with which this program was executed.
 *   argv - Array of pointers to strings containing the command-line arguments. 
 *
 * Return value:
 *   0 - This program terminated normally.
 */
int
main (int argc, char ** argv) {
  /* File descriptor */
  int fd;

  /* Length of data written to file */
  int length;

  /*
   * Set the group IDs.  We can do this as we're currently executing as the
   * root user.
   */
  if ((setresgid (nogroup, nogroup, nogroup)) == -1) {
    perror ("Failed to enter the nogroup group");
    return 1;
  }

  /*
   * We are currently running as the root user.  Change our real, effective,
   * and saved UIDs so that we are not root and do not own the file which we
   * should open.
   */
  if ((setresuid (nobody, nobody, nobody)) == -1) {
    perror ("Failed to become a nobody.");
    return 1;
  }

  /*
   * Call the function that students will implement.  This function will hack
   * the kernel so that we can open the file.
   */
  giveMeThePower();

  /*
   * Attempt to open the file.
   */
  if ((fd = open (pathname, O_RDWR | O_TRUNC)) == -1) {
    perror ("Failed to open file");
    return 1;
  } else {
    /*
     * Rewrite the contents of the file.
     */
    if ((length = write (fd, data, strlen(data))) == -1) {
      perror ("Failed to write to file");
      return 1;
    }
  }

	/* Exit the program */
	return 0;
}
