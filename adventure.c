#include<stdio.h>
#include<time.h>
#include<stdbool.h>
#include<string.h>                                                                  
#include<stdlib.h>                                  
#include "room.h"                                                               
#include "character.h"                                                  
#include "items.h"                                                  //Not even a single variable is extra in all 3 files, so please be very careful when you make changes. 
void printarr();
bool flagKiller = false, flagRoom = false, flagObj=false;                                       //flags that will be used to detect winning 
char killer[10], murder_weapon[10]; 
int murder_room; 
int roomie[8];                                                                                  //Rommie is the array of the room numbers that will be used to randomize the people
char orders[50];                                                                                //input for the commands
char secorder[50];                                                                                          
int cluecount = 0; 
int s = -1; 
char commands[8][15] = {"list", "help", "go", "drop", "clue", "take","look", "inventory" };     //used for testing the validity of the commands 
char directions[4][6] = {"north", "south", "east", "west"};
struct gmap *birth;                                                                             //The most important object of the structure "gmap", helps in communicating with room.h
void fix_the_killer(); 
void warns();                       
bool clue(); 
void to_do();
void vdir();
int whichco(char []);   //returns the command number from the commands[][]
void who(int);      //used to show who is in the room 
void push(int);         //used for randomisation of rooms
void roomnumber();      
bool executor(char []);
bool search(int);
void action(char[15]);
int main(){
    srand(time(0));
    initialize();       //check room.h
    init();             //check item.h
    fix_the_killer(); 
    while(s<8){
        int inp = 1+rand()%9; //Randomisation of ROOM numbers is here because I was not able to randomise in room.h, so I just shifted here. 
        push(inp);
    } 
    roomnumber();
    birth = adds[roomie[rand()%9]]; //check room.h, adds[] has all the address of the ROOM nodes, so birth is the player starts the game. Roomie, is the array of random numbers. and rand() is giving out a single random number. 
    bool valid = false;
    bool gameover = false; 
    printf("Welcome to the game of clue\n You are Jeff and you have to find out who is the murderer\n");
    printf("type 'help' to see all the commands that are avialiable to you");
    while(gameover != true){
       while(valid!=true){
           warns();
           to_do();
           scanf("%s", orders);
           valid = executor(orders);
           if(valid == false){
               printf("Invalid command try again or type help: ");
           }else{
               break;
           }
       }
       if(cluecount>=10){
           gameover = true;
           printf("You lost!");
           exit(0);
       }else if((flagKiller = true) && (flagObj == true) && (flagRoom == true)){
           printf("You won!"); 
           gameover = true; 
           exit(0);
       }
       valid = false;
       action(orders);
    }
    return 0;
}

void roomnumber(){
    for(int i = 0; i<9; i++){
        adds[i]->room = roomie[i]; //random numbers being assigned to room numbers in the structure object 
    }
}

void push(int x){                   
    if(s == -1){
        s += 1; 
        roomie[s] = x;
    }else{
        bool flag = search(x); 
        if(flag == true){
            s += 1;
            roomie[s] = x;
        } 
    }
}

bool search(int x){
    for(int i = 0; i<=s; i++){
        if(roomie[i] == x){
            return false; 
        }
    }
    return true; 
}

void printarr(){
     for(int i = 0; i<9; i++){
        printf("%p\n", adds[i]);
        printf("Room number %d\n", adds[i]->room);
    }
    for(int i = 0; i<s; i++){
        printf("%d\n", roomie[i]);
    } 
}

void warns(){
    printf("Type in lowercase\n");
}

void to_do(){
    printf("What will you do next?\n");
}

bool executor(char x[]){
    for(int i = 0; i<8; i++){
        if(strcmp(x, commands[i])==0){  
            return true;
        }
    }
    return false;
}

int whichco(char x[]){
    for(int i = 0; i<8; i++){
        if(strcmp(x, commands[i])==0){  
            return i; 
        }
    }
    return 0;
}

void vdir(){
    if(birth->east != NULL){
        printf("You can go towards east\n"); 
    }
    if(birth->west != NULL){
        printf("You can go towards west\n");
    }
    if(birth->south != NULL){
        printf("You can go towards south\n");
    }    
    if(birth->north != NULL){
        printf("You can go towards north\n");
    }
}

void who(int gmap_room_no){
    struct person *ref; 
    ref = headers[gmap_room_no];
    while(ref != NULL){
        if((strcmp("", ref->character)==0) && (ref->next == NULL)){
            printf("Nobody is in the room\n");
            break;
        }else{
            printf("%s is in the room\n", ref->character);
            ref = ref->next; 
        }
    }
}
void fix_the_killer(){
    strcpy(killer, peeps[rand()%4]);
    strcpy(murder_weapon,options[rand()%5]);
    murder_room = 1+rand()%8;    
}
bool clue(int gmap_room_no){
    char human[10]; 
    ++cluecount;
    scanf("%s", human);
    if(murder_room == birth->room){
        flagRoom = true; 
        printf("Room Match\n"); 
    }if(strcmp(human, killer)==0){
        printf("Character match\n");
        flagKiller = true;
        move_to_the_room(birth->room, human);
    }else if(strcmp(human, killer) !=0){
        move_to_the_room(birth->room, human); 
    }if(searchInven(birth->room, murder_weapon) || searchRoom(birth->room, murder_weapon)){
        printf("Item match\n"); 
        flagObj = true; 
    }
    if(flagObj && flagRoom && flagKiller){
        return true;
    }else{
        return false;
    } 
}
void action(char x[]){                                              
    int nos = whichco(x);
    switch(nos){
        case 0:
            printf("You are in room number %d\n", birth->room);
            who(birth->room);
            printf("The names of characters are: "); 
            for(int i = 0; i<5; i++){
                printf("%s ", peeps[i]);
            }
            printf("\n");
            printf("The name of the things are: ");
            for(int i = 0; i<6; i++){
                printf("%s ", options[i]); 
            }
            printf("\n");
            break;
        case 1:
            for(int i = 0; i<8; i++){
                printf("%s\n", commands[i]);
            }
            break;
        case 2:
            birth  = move_character(birth);
            break; 
        case 3:
            removeItem(birth->room);
            break;
        case 4: 
            clue(birth->room); 
            break;
        case 5: 
            take_item(birth->room);
            break;
        case 6: 
            printf("You are in %d room\n", birth->room);
            who(birth->room);
            vdir();
            what_is_in_room(birth->room);
            break;
        case 7: 
            showInven();
            break;
    }
}
