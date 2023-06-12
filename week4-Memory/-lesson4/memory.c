// Demonstrates memory errors via valgrind -it checks to see if you free all the memory you allocated.

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *x = malloc(3 * sizeof(int));
    x[1] = 72;
    x[2] = 73;
    x[3] = 33;
    free(x); //FIX
}

//before FIX: week4 -Memory/lesson4/ $ valgrind ./memory
// ==10385== Memcheck, a memory error detector
// ==10385== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
// ==10385== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
// ==10385== Command: ./memory
// ==10385==
// ==10385== Invalid write of size 4
// ==10385==    at 0x109170: main (memory.c:11)
// ==10385==  Address 0x4bb504c is 0 bytes after a block of size 12 alloc'd
// ==10385==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==10385==    by 0x109151: main (memory.c:8)
// ==10385==
// ==10385==
// ==10385== HEAP SUMMARY:
// ==10385==     in use at exit: 12 bytes in 1 blocks
// ==10385==   total heap usage: 1 allocs, 0 frees, 12 bytes allocated
// ==10385==
// ==10385== 12 bytes in 1 blocks are definitely lost in loss record 1 of 1
// ==10385==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==10385==    by 0x109151: main (memory.c:8)
// ==10385==
// ==10385== LEAK SUMMARY:
// ==10385==    definitely lost: 12 bytes in 1 blocks
// ==10385==    indirectly lost: 0 bytes in 0 blocks
// ==10385==      possibly lost: 0 bytes in 0 blocks
// ==10385==    still reachable: 0 bytes in 0 blocks
// ==10385==         suppressed: 0 bytes in 0 blocks
// ==10385==
// ==10385== For lists of detected and suppressed errors, rerun with: -s
// ==10385== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

//after FIX:
// ==11630== Memcheck, a memory error detector
// ==11630== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
// ==11630== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
// ==11630== Command: ./memory
// ==11630==
// ==11630== Invalid write of size 4
// ==11630==    at 0x109180: main (memory.c:11)
// ==11630==  Address 0x4bb504c is 0 bytes after a block of size 12 alloc'd
// ==11630==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==11630==    by 0x109161: main (memory.c:8)
// ==11630==
// ==11630==
// ==11630== HEAP SUMMARY:
// ==11630==     in use at exit: 0 bytes in 0 blocks
// ==11630==   total heap usage: 1 allocs, 1 frees, 12 bytes allocated
// ==11630==
// ==11630== All heap blocks were freed -- no leaks are possible
// ==11630==
// ==11630== For lists of detected and suppressed errors, rerun with: -s
// ==11630== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)