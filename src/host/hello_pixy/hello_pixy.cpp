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
	
	while ((!pixy_init_status == 0) && run_flag) {
		// Connect to Pixy //
		pixy_init_status = pixy_init();

		// Catch CTRL+C (SIGINT) signals //
		signal(SIGINT, handle_SIGINT);
		
		// Was there an error initializing pixy? //
		if (!pixy_init_status == 0) {
			// Error initializing Pixy //
			pixy_error(pixy_init_status);
			pixy_init_status = 1;
		} else {
			pixy_init_status = 0;
		}
	}

#if 0
	// Pixy Command Examples //
	{
		int32_t response;
		int		 return_value;

		// Execute remote procedure call "cam_setAWB" with one output (host->pixy) parameter (Value = 1)
		//
		//	 Parameters:								 Notes:
		//
		//	 pixy_command("cam_setAWB",	String identifier for remote procedure
		//												0x01,	Length (in bytes) of first output parameter
		//													 1,	Value of first output parameter
		//													 0,	Parameter list seperator token (See value of: END_OUT_ARGS)
		//									 &response,	Pointer to memory address for return value from remote procedure call
		//													 0); Parameter list seperator token (See value of: END_IN_ARGS)
		//

		// Enable auto white balance //
		pixy_command("cam_setAWB", UINT8(0x01), END_OUT_ARGS,	&response, END_IN_ARGS);

		// Execute remote procedure call "cam_getAWB" with no output (host->pixy) parameters
		//
		//	 Parameters:								 Notes:
		//
		//	 pixy_command("cam_setAWB",	String identifier for remote procedure
		//													 0,	Parameter list seperator token (See value of: END_OUT_ARGS)
		//									 &response,	Pointer to memory address for return value from remote procedure call
		//													 0); Parameter list seperator token (See value of: END_IN_ARGS)
		//

		// Get auto white balance //
		return_value = pixy_command("cam_getAWB", END_OUT_ARGS, &response, END_IN_ARGS);

		// Set auto white balance back to disabled //
		pixy_command("cam_setAWB", UINT8(0x00), END_OUT_ARGS,	&response, END_IN_ARGS);
	}
#endif

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
	
	pixy_close();
}
