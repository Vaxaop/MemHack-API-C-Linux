#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/uio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
typedef unsigned long ulong;
typedef unsigned long long ulongl;
typedef unsigned int uint;

uint pID;

uint GetTargetPid(const char * processname) {
    char Processnamestr[1024];
    strcpy(Processnamestr, processname);
    struct dirent *DirectoryObject = NULL;
    DIR *DirectoryHandle = NULL;
    
    if((DirectoryHandle = opendir("/proc/")) == NULL) {
        printf("failed to open /proc/ (how is it even possible)!\n");
        exit(1);
    }
    while((DirectoryObject = readdir(DirectoryHandle)) != NULL) {
        if(atoi(DirectoryObject->d_name) != 0) {
            char filepath[1000];
            char * filebuf = NULL;
            __off_t filelen = 128;
            int fd = 0;

            sprintf(filepath, "/proc/%s/status", DirectoryObject->d_name);
            if((fd = open(filepath, O_RDONLY)) < 0) {
                printf("failed to open file (somehow)\n");
                exit(1);
            }

            if((filebuf = (char*)malloc(filelen)) == NULL) {
                printf("malloc failed at filebuf ! \n");
                exit(1);
            }
            memset(filebuf, 0, filelen);

            if(read(fd, filebuf, filelen) < 0) {
                printf("failed to read file\n");
                exit(1);
            }
            close(fd);

            if(strstr(filebuf, Processnamestr) != NULL) {
                pID = atol(DirectoryObject->d_name);
                return pID;
            }
        }
    }
}

void * RPM(ulongl address, size_t size_of_reading) {
    void * value = malloc(size_of_reading);

    struct iovec local[1]; //defining what variable is going to be stored from the reading : MORE INFO HERE : https://man7.org/linux/man-pages/man2/process_vm_readv.2.html
    struct iovec remote[1]; //defining what the address is going to be
    ssize_t nread;
    pid_t pid = pID;

    local[0].iov_base = value;
    local[0].iov_len = size_of_reading;
    remote[0].iov_base = (void *)address;
    remote[0].iov_len = size_of_reading;

    nread = process_vm_readv(pid, local, 1, remote, 1, 0);
    if (nread != size_of_reading) {
        printf("Failed RPM at this address : %p", address);
        return value;
    }
    else {
        return value;
    }
}

void WPM (ulongl address, void * buffer, size_t size_of_writing) {

    struct iovec local[1]; //defining what variable is going to be stored from the reading : MORE INFO HERE : https://man7.org/linux/man-pages/man2/process_vm_readv.2.html
    struct iovec remote[1]; //defining what the address is going to be
    pid_t pid = pID;

    local[0].iov_base = buffer;
    local[0].iov_len = size_of_writing;
    remote[0].iov_base = (void *)address;
    remote[0].iov_len = size_of_writing;

    process_vm_writev(pid, local, 1, remote, 1, 0);
}

// size_of_offsets = sizeof(offsets) / sizeof(offsets[0])
ulongl GetPointerAddress(ulongl base_address, ulongl offsets[], size_t size_of_offsets) {
    ulongl address = base_address;
    ulongl current_reading = 0x0;
    for (int i = 0; i < size_of_offsets; i++) {
        
        current_reading = (ulongl)RPM(address, sizeof(address));
        current_reading = current_reading + offsets[i];
        address = current_reading;
    }
    return address;
}

ulongl GetModuleBaseAddr() {
    // to be continued
}