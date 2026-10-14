#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    char b = 'x';
    int p2c[2]; //pipe cha
    int c2p[2]; //pipe con
    //0 - doc, 1 - ghi
    if(pipe(p2c) < 0 || pipe(c2p) < 0){ //tao pipe va kiem tra
        fprintf(2, "pingpong: pipe failed\n");
        exit(1);
    }

    int pid = fork(); //dung fork tao tien trinh con
    if(pid < 0 ){
        //tao loi
        fprintf(2, "pingpong: fork failed\n");
        exit(1);
    }

    if(pid ==0){
        //chi tien trinh con
        close(c2p[0]); //khong doc pipe con
        close(p2c[1]); //khong ghi pipe cha
        
        if(read(p2c[0], &b, 1) != 1){
            //con doc loi
            fprintf(2, "pingpong: child read failed\n");
            exit(1);
        }
        printf("%d: received ping\n", getpid());
        write(c2p[1], &b, 1);
        close(c2p[1]);
        close(p2c[0]);
        exit(0);
    }
    else{
        //chi tien trinh cha
        close(p2c[0]); //khong doc pipe cha
        close(c2p[1]); //khong ghi pipe con
        
        write(p2c[1], &b, 1);
        if(read(c2p[0],&b, 1) != 1){
            //cha doc loi
            fprintf(2, "pingpong: parent read failed\n");
            exit(1);
        }
        printf("%d: received pong\n", getpid());
        close(p2c[1]);
        close(c2p[0]);
        wait(0);
        exit(0);
    }


}