#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

int randPicker() {
    int fd = open("/dev/random", O_RDONLY);

    if (fd == -1) {
        printf("%s", strerror(errno));
    }
    // num = buffer
    int num;
    int result = read(fd, &num, sizeof(int));
    if (result == -1) {
        printf("%s", strerror(errno));
    }

    result = close(fd);
    if (result == 1) {
        printf("Did not work! %s\n", strerror(errno));
    }

    return num;
}

int main() {
    int rand_array[10];
    
    /* testing randPicker() function
    int i;
    for (i = 0; i < 10; i++) {
        printf("%ul\n", randPicker());
    }
    */

   printf("Creating array...");
   int i; 
   for (i = 0; i < 10; i++) {
       rand_array[i] = randPicker();
   }

   printf("Writing file with contents of the array...\n");
   int w_fd = open("./testfile", O_RDWR | O_CREAT, 0644);
   // error
   if (w_fd == -1) {
       printf("Did not work! %s\n", strerror(errno));
   }
   write(w_fd, rand_array, sizeof(int) * 10);
   lseek(w_fd, 0, SEEK_SET);

   printf("Testing by reading newly created file...\n");
   unsigned int array2[10];
   int result = read(w_fd, array2, sizeof(int) * 10);
   int a;
   for (a = 0; a < 10; a++) {
       printf("%d\t%d\n", rand_array[a], array2[a]);
   }
}