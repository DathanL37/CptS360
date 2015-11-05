#include "header.h"

int get_block(int fd, int blk, char buf[ ])
{
  lseek(fd, (long)blk*BLKSIZE, 0);
  read(fd, buf, BLKSIZE);
}

my_dir()
{
	char *cp;
	int iblock;

	get_block(fd, 2, buf);
	gp = (GD *)buf;

	iblock = gp->bg_inode_table;
	printf("inode block %d\n", iblock);

	get_block(fd, iblock, buf);
	ip = (INODE *)buf + 1;

	get_block(fd, ip->i_block[0], buf);

	cp = dp = (DIR *)buf;

	while(dp->rec_len != 0)
	{
		printf("inode %d\n", dp->inode);
		printf("name length: %d\n%s\n", dp->name_len, dp->name);
		cp += dp->rec_len;
		dp = (DIR *)cp;
	}
}