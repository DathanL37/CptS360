#include "header.h"
/*
 * Name: Thom Hemenway
 * ID: 11337255
 * Lab: 6
 */

int get_block(int fd, int blk, char buf[ ])
{
  lseek(fd, (long)blk*BLKSIZE, 0);
  read(fd, buf, BLKSIZE);
}

int find_file(char *path[])
{

}



int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("run the program in the form:\nshowblock DEVICE PATHNAME\n");
		exit(1);
	}

	fd = open(disk, O_RDONLY);
	if (fd < 0){
	    printf("open failed\n");
	    exit(1);
	}
}