#include "header.h"

int get_block(int fd, int blk, char buf[ ])
{
  lseek(fd, (long)blk*BLKSIZE, 0);
  read(fd, buf, BLKSIZE);
}

int chk_bit(char *buf, int bit)
{
  int i, j;
  i = bit / 8;  j = bit % 8;
  if (buf[i] & (1 << j))
     return 1;
  return 0;
}

bmap()
{
	int nbnodes = 0, bmap, i = 0;

	get_block(fd, 1, buf);
	sp = (SUPER *)buf;
	nbnodes = sp->s_blocks_count;

	printf("nbnodes = %d\n", nbnodes);

	get_block(fd, 2, buf);
	gp = (GD *)buf;

	bmap = gp->bg_block_bitmap;
	get_block(fd, bmap, buf);

	for (i; i < nbnodes; ++i)
	{
		(chk_bit(buf, i)) ? putchar('1') : putchar('0');
		if(i && (i%8) == 0) putchar(' ');
	}
	printf("\n");
}