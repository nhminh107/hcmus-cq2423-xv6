#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

#define MAXPATH 512
void tree(char*path, int level, int maxDepth, int dir)
{
    if(maxDepth!=-1 && level >= maxDepth) return;
    char buf[MAXPATH], *p;
    int fd;
    struct dirent de;
    struct stat st;
    fd=open(path,0);
    if(fd<0)
    {
        fprintf(2,"tree can not open %s\n", path);
        return;
    }
    if(fstat(fd, &st)<0)
    {
        fprintf(2, "tree can not stat %s\n", path);
        close(fd);
        return;
    }
    if(level==0)
    {
        printf("%s\n", path);
    }
    if(st.type==T_DIR)
    {
        if(strlen(path)+1+DIRSIZ+1>sizeof (buf))
        {
            printf("tree path too long\n");
            close(fd);
            return;
        }
        strcpy(buf, path);
        p=buf+strlen(buf);
        *p++='/';
        while(read(fd, &de, sizeof(de))==sizeof(de))
        {
            if(de.inum==0)
            {
                continue;
            }
            if(strcmp(de.name, ".")==0 || strcmp(de.name, "..")==0) continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ]=0;
            if(stat(buf, &st)<0)
            {
                printf("tree cannot stat%s\n", buf);
                continue;
            }
            if(dir&&st.type!=T_DIR) continue;
            for(int i=0;i<level; i++)
            {
                printf("    ");

            }
            printf("|--%s\n", de.name);
            if(st.type==T_DIR)
            {
                tree(buf, level+1, maxDepth, dir);
            }
        }
    }
    close(fd);
}

int main(int argc, char*argv[])
{
    int maxDepth=-1;
    int dir=0;
    char*path=".";

    for(int i=1; i<argc; i++)
    {
        if(strcmp(argv[i], "-L")==0&&i+1<argc)
        {
            maxDepth=atoi(argv[i+1]);
            i++;
        }
        else if(strcmp(argv[i], "-d")==0)
        {
            dir=1;
        }
        else
        {
            path=argv[i];
        }
    }
    tree(path, 0, maxDepth, dir);
    exit(0);
}