#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "pixy.h"

#define BLOCK_BUFFER_SIZE		25

// Pixy Block buffer // 
struct Block blocks[BLOCK_BUFFER_SIZE];
static bool run_flag = true;

void handle_SIGINT(int unused) {
	// On CTRL+C - abort! //
	run_flag = false;
}

int main(int argc, char * argv[]) {
	int			i = 0;
	int			index;
	int			blocks_copied;
	int			pixy_init_status = 1;
	char		buf[128];

	// Wait for request //

	// Wait for new blocks to be available //
	while(!pixy_blocks_are_new() && run_flag); 

	// Get blocks from Pixy //
	blocks_copied = pixy_get_blocks(BLOCK_BUFFER_SIZE, &blocks[0]);

	if(blocks_copied < 0) {
		// Error: pixy_get_blocks //
		printf("pixy_get_blocks(): ");
		pixy_error(blocks_copied);
	}

	// Display received blocks //
	printf("frame %d:\n", i);
	for(index = 0; index != blocks_copied; ++index) {		
		 blocks[index].print(buf);
		 printf(buf);
	}
	i++;
}
