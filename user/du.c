#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

#define MAXPATH 512

int du(char *path, int all, int summary)
{
    char buf[MAXPATH], *p;
    struct dirent de;
    struct stat st;
    int fd;
    fd= open(path, 0);
    if (fd<0)
    {
        printf("du cannot open %s\n", path);
        return 0;
    }
    if(fstat(fd, &st)<0)
    {
        printf("du cannot stat%s\n", path);
        close(fd);
        return 0;
    }
    if (st.type==T_FILE)
    {
        int size= st.size;
        close(fd);
        if(all && !summary)
        {
            printf("%d\t %s\n", size, path);
        }
        return size;
    }
    int total=0;
    if (st.type == T_DIR) {
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
            printf("du path too long\n");
            close(fd);
            return 0;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        while(read(fd, &de, sizeof(de))== sizeof(de))
        {
            if (de.inum==0) continue;
            if(strcmp(de.name, ".")==0 || strcmp(de.name, "..")==0) continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ]=0;
            total +=du(buf, all, summary);
        }
        if(!summary)
        {
            printf("%d\t%s\n", total, path);
        }
    }
    close(fd);
    return total;

}

int main(int argc, char*argv[])
{
    char *path=".";
    int all =0;
    int summary =0;
    for (int i=1; i<argc; i++)
    {
        if(strcmp(argv[i], "-a")==0)
        {
            all=1;
        }
        else if(strcmp(argv[i], "-s")==0)
        {
            summary=1;
        }
        else
        {
            path=argv[i];
        }
    }
    int total=du(path, all, summary);
    if(summary)
    {
        printf("%d\t%s\n", total, path);
    }
    exit(0);
}