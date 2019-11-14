//
// Created by Anthony/Samiratu/Lhet on 11/14/19.
//

#include<stdio.h>
#include<stdlib.h>
int buffer,empty,full=0,mutex=1,op,x=0;

int wait(int s){
    while(s<=0);
    return --s;
}
int signal(int s){
    return ++s;
}
void Chef(){
    if(mutex==1 && empty!=0){
        mutex=wait(mutex);
        full=signal(full);

        empty=wait(empty);
        mutex=signal(mutex);
        ++x;
        printf("\n Chef produces a pizza %d \n\n",x);
    }else
        printf("\n Tray is Full , cannot produce\n");

}

void Client(){
    if(mutex==1 && full!=0){
        mutex=wait(mutex);

        full=wait(full);
        empty=signal(empty);

        mutex=signal(mutex);

        printf("\n Client consumed a pizza %d \n\n",x);
        --x;
    }else
        printf("\n Tray is Empty , cannot consume\n");

}


void main(){

    printf("Enter the Tray size ");
    scanf("%d",&buffer);
    empty=buffer;

    while(1){
        printf("\n \t choose the operation : ");
        printf("\n1.Chef to produce\n2.Client to consume\n3.exit\tinput here:");
        scanf("%d",&op);
        switch(op){
            case 1: Chef();
                break;
            case 2: Client();
                break;
            case 3: exit(0);
        }
    }
}