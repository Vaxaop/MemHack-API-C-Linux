#include "Mem-Api.h"

// command to compile = gcc -std=c17 -m64 -Wall Mem-Api.h main.c -o main
// dont forget to run your programme in sudo ex sudo ./main

int main(int argc, char ** argv) {
    ulongl addr = 0x5565200c0010; //change the address here
    uint processID = GetTargetPid("TestProgramme");
    printf("The pid of the test programme is : %d\n", processID);
    
    void * value_read = RPM(addr, sizeof(int));
    printf("The value read = %d\n", *(int*)value_read);
    
    int write_value = 1234;
    WPM(addr, &write_value , sizeof(write_value));
    printf("value just got write to it\n");
    
    free(value_read);
    return 0;
}
