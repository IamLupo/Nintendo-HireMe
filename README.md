# Nintendo - Hire Me - Challenge

#### Solution:
	
First i separated the algorithem in 3 parts.

Part A:
	
	for(u8 j=0;j<32;j++) {
		output[j]=confusion[input[j]];
		input[j]=0;
	}
		
Part B:

	for(u8 j=0;j<32;j++)
		for(u8 k=0;k<32;k++)
			input[j]^=output[k]*((diffusion[j]>>k)&1);

Part C:

	for(u8 i=0;i<16;i++)
			output[i]=confusion[input[i*2]]^confusion[input[i*2+1]+256];
			
Part A was the easiest part. This is just a basic list to convert the value.
Because the list contains some values multiple times we can determain if reverse
Part B will give a valid value.

Part B needs first need some rewriting. Watch the file : /Solution/Rewrite/HireMe.cpp line 125.
These xor pattern can be reverse with Gaussian elimination. See /Solution/Part B/

Part C has a lot of different possebilities to check. Basicly in the /Solution/Reverse/main.cpp
I bruteforce all possebilities and check if he can reverse Part A and B 256 times.
If he pass he found a valid key.

In the end he cracked the challenge in like 15 seconds.

	Nintendo - HireMe/Solution/Reverse$ ./main
	Crack Part C
	Found final input = 0x5d, 0xc5, 0xda, 0x80, 0x81, 0xad, 0xe, 0xe6, 0xda, 0x88, 0xd9, 0x67, 0x43, 0x63, 0x1c, 0x87, 0x8b, 0x72, 0x60, 0x24, 0x4d, 0xbc, 0xd9, 0xa7, 0xfa, 0x86, 0x19, 0x26, 0x1e, 0x69, 0x3, 0x6
		

#### Compile and Crack:

	cd Solution/Reverse
	./compile
	./main

