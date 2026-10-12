//
// Created by nhminh on 4/10/26.
//
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage: cp src dst\n"); 
        exit(1); 
    }
    char *src = argv[1]; 
    char* dst = argv[2]; 
    if (strcmp(src, dst) == 0) {
        printf("dst and src must be different\n");
        exit(1); 
    }
    int src_fd = open(src, O_RDONLY);
    if (src_fd == -1) {
        printf("cp: cannot open %s\n", src);
        exit(1);
    }

    int dst_fd = open(dst, O_CREATE | O_WRONLY | O_TRUNC);
    if (dst_fd == -1) {
        printf("cp: cannot open %s\n", dst);
        exit(1); 
    }
    char buffer[512];  
    int n; 
    while ((n = read(src_fd, buffer, sizeof(buffer))) > 0){
        if(write(dst_fd, buffer, n) != n) {
            printf("cp: write error\n"); 
            exit(1); 
        }
    }
    if (n < 0) {
        printf("cp: read error\n");
        exit(1);
    }
    close(src_fd);
    close(dst_fd);
    exit(0); 
}

