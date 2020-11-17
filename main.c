//Kelly Zhou
//System Level Programming
//randfile

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

//Generates a random number by reading a certain number of bytes from /dev/random
int rand_num(int fd){
  int buffer[1];

  int random= read(fd, buffer, sizeof(buffer));
  if (random==-1){
    printf("Error reading bytes. %s\n", strerror(errno));
  }

  return buffer[0];
}

//Populates an array with random numbers, writes it to a file, and verifies that the numbers are the same
int main(){
  int rand_array[10];
  int i;

  //opening file
  int open_rand= open("/dev/random", O_RDONLY);
  if (open_rand==-1){
    printf("Error opening the file. %s\n", strerror(errno));
    return -1;
  }

  //Generating and populating the random numbers into the array
  printf("Generating random numbers:\n");
  for (i=0; i<10;i++){
    rand_array[i]=rand_num(open_rand);
    printf("rand %d: %d\n", i, rand_array[i]);
  }

  //opens the output text file to write
  int open_out=open("output.out", O_CREAT | O_WRONLY);
  if (open_out==-1){
    printf("Error opening the file. %s\n", strerror(errno));
    return -1;
  }

  //Writes the numbers to the output text file
  printf("Writing numbers to the file...\n");
  int write_file= write(open_out, rand_array,sizeof(rand_array));
  if (write_file==-1){
     printf("Error writing to the file. %s\n", strerror(errno));
     return -1;
   }
   close(open_out);

   //opens the output text file again, this time to read
   open_out=open("./output.out", O_RDONLY);
   if (open_out==-1){
     printf("Error opening the file. %s\n", strerror(errno));
     return -1;
   }

  //Reads the numbers in the output text file
  printf("Reading numbers from file...\n");
  int out_array[10];
  int read_out=read(open_out,out_array,sizeof(out_array));
  if (read_out==-1){
     printf("Error reading the file. %s", strerror(errno));
     return -1;
  }

  //Verifies that the numbers are the same
  printf("Verification that written values were the same:\n");
  for (i=0;i<10;i++){
    printf("random %d: %d\n", i, out_array[i]);
  }

  //close the file
  close(open_rand);
  close(open_out);
  return 0;
}
