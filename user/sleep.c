#include "kernel/types.h"
#include "user/user.h"

int main(int argc,char* argv[]){
    if(argc < 2){                                                                       
        fprintf(2, "No ticket yet");
        exit(1);
    }
    int ticket = atoi(argv[1]);                         
    sleep(ticket);
    printf("Woke up!\n");
    exit(0);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
}                                                            
