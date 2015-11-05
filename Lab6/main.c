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

int get_dirname(char *path)
{
	char *token = strtok(path, "/");
	while(token != NULL)
	{
		dirname = token;
		token = strtok(NULL, "/");
	}
}

int get_basename(char *path)
{
	char *token = strtok(path, "/");
	strcat(basename, "/");
	while(token != NULL)
	{
		strcat(basename, token);
		token = strtok(NULL, "/");
	}


void gd()
{
  // read SUPER block
  get_block(fd, 2, buf);  
  gp = (GD *)buf;

  printf("bg_block_bitmap = %d\n", gp->bg_block_bitmap);
  printf("bg_inode_bitmap = %d\n", gp->bg_inode_bitmap);

  printf("bg_inode_table = %d\n", gp->bg_inode_table);
  printf("bg_free_blocks_count = %d\n", gp->bg_free_blocks_count);
  printf("bg_free_inodes_count = %d\n", gp->bg_free_inodes_count);
  printf("bg_used_dirs_count = %d\n", gp->bg_used_dirs_count);
}

void super()
{
  // read SUPER block
  get_block(fd, 1, buf);  
  gp = (GD *)buf;

  printf("bg_block_bitmap = %d\n", gp->bg_block_bitmap);
  printf("bg_inode_bitmap = %d\n", gp->bg_inode_bitmap);

  printf("bg_inode_table = %d\n", gp->bg_inode_table);
  printf("bg_free_blocks_count = %d\n", gp->bg_free_blocks_count);
  printf("bg_free_inodes_count = %d\n", gp->bg_free_inodes_count);
  printf("bg_used_dirs_count = %d\n", gp->bg_used_dirs_count);
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("run the program in the form:\nshowblock DEVICE PATHNAME\n");
		exit(1);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd < 0){
	    printf("open failed\n");
	    exit(1);
	}

	get_basename(argv[2]);
	get_dirname(argv[2]);


}