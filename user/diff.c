//
// Created by nhminh on 5/10/26.
//
#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"


int readline(int fd, char *buf, int max) {
    int idx = 0;
    int n;
    char c;

    while ((n = read(fd, &c, 1)) == 1) {
        if (c == '\n') {
            buf[idx] = '\0';
            return idx;
        }

        if (idx >= max - 1)
            return -2;

        buf[idx++] = c;
    }
    if (n < 0)
        return -2;
    if (idx == 0)
        return -1;
    buf[idx] = '\0';
    return idx;
}

int isMatch(char* str1, char* str2, int n) {
    for (int i = 0; i < n; i++){
        if (str1[i] != str2[i]) return 0;
    }
    return 1;
}
int main(int argc, char* args[]) {
    int mode = 0;
    int file_count = 0;
    char *files[2];

    for (int i = 1; i < argc; i++) {
        if (strcmp(args[i], "-q") == 0) {
            mode++;
            continue;
        }

        if (file_count < 2)
            files[file_count++] = args[i];
        else
            break;
    }

    if (file_count != 2 || mode > 1 || argc != 3 + mode) {
        printf("usage: diff [-q ] f1 f2\n");
        exit(1);
    }

    char* f1 = files[0];
    char* f2 = files[1];

    int f1_fd = open(f1, O_RDONLY);
    int f2_fd = open(f2, O_RDONLY);

    if (f1_fd == -1) {
        printf("diff: cannot open file %s\n", f1);
        exit(1);
    }
    if (f2_fd == -1) {
        printf("diff: cannot open file %s\n", f2);
        exit(1);
    }

    char line_f1[1024];
    char line_f2[1024];
    int line = 1;

    while (1) {
        line_f1[0] = '\0';
        line_f2[0] = '\0';

        int len1 = readline(f1_fd, line_f1, 1024);
        int len2 = readline(f2_fd, line_f2, 1024);

        if (len1 == -2 || len2 == -2) {
            printf("diff: read error\n");
            exit(1);
        }

        if (len1 == -1 && len2 == -1) break;

        if (len1 != len2) {
            if (mode == 1) {
                printf("diff: files differ\n");
                exit(0);
            }

            printf("f1:%d: < %s\n", line,
                len1 == -1 ? "EOF" : line_f1);
            printf("f2:%d: > %s\n", line,
                len2 == -1 ? "EOF" : line_f2);

            line++;
            continue;
        }
        int checkMatch = isMatch(line_f1, line_f2, len1);

        if (!checkMatch) {
            if (mode == 1) {
                printf("diff: files differ\n");
                exit(0);
            }

            printf("f1:%d: < %s\n", line, line_f1);
            printf("f2:%d: > %s\n", line, line_f2);

            line++;
            continue;
        }

        line++;
    }

    close(f1_fd);
    close(f2_fd);
    exit(0);

}