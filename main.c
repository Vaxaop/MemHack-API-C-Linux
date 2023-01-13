#include "Mem-Api.h"

// command to compile = gcc -std=c17 -m64 -Wall utils.h main.c -o main
// dont forget to run your programme in sudo ex sudo ./programme-name

int main(int argc, char ** argv) {
    ulongl addr = 0x5565200c0010;
    uint processID = GetTargetPid("TestProgramme");
    printf("The pid of the test programme is : %d\n", processID);
    void * value_read = RPM(addr, sizeof(int));
    printf("The value read = %d\n", *(int*)value_read);
    int vriting_valuee = 1234;
    WPM(addr, &vriting_valuee, sizeof(vriting_valuee));
    printf("value just got wriiting \n");
    free(value_read);
    return 0;
}
