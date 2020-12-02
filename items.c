#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "items.h"
struct items{
    char item[10];
    struct items *next2;
};
char options[6][10] = {"knife", "food", "book", "lamp", "gun", "table"};        //you can change the name of the things if you want here. 
int rooms[6];                                                                   // rooms is storing the UNIQUE numbers from  1 to 6 this will be used to randomise the objects. 
struct items *bask[10];                                                         //bask is the array
struct items *head[10]; 
void createList(int n){
    for(int i = 1; i<n; i++){
       bask[i] = (struct items *)malloc(sizeof(struct items));                  // bask storing the adderesses of the nodes. There will be 9 nodes, starting from 1 - 9.  
       bask[i]->next2 = NULL;                                                    // Best part about this one is that 1 - 9 are room numbers, in room.h, hence this will work as the link
       head[i] = bask[i];
    }
}
void what_is_in_room(int gmap_room_no){
    struct items *temp; 
    temp = bask[gmap_room_no];
    if((temp->next2 == NULL) && (strcmp(temp->item, "")==0)){
        printf("Nothing is in the room\n");
    }else{
         while(temp!=NULL){
            printf("%s is in room\n", temp->item); 
            temp = temp->next2; 
        }
    }
}
bool searchRoom(int gmap_room_no, char murder_weapon_used[10]){
    struct items *temp; 
    temp = bask[gmap_room_no]; 
    while(temp != NULL){
        if(strcmp(temp->item, murder_weapon_used)==0){
            return true;
        }
        temp = temp->next2; 
    }
    return false; 
}
bool valid_take(char x[10], int gmap_room_no){                                  //This is called in character.h They are connected.
    struct items *temp;
    temp = bask[gmap_room_no];
    if(strcmp(temp->item, x)==0){
        return true; 
    }
    while(temp->next2 != NULL){
        if(strcmp(x, temp->item)==0){ 
            return true;
        }
        temp = bask[gmap_room_no]->next2;
    }
    return false; 
}
void remove_Item_from_room(char x[], int gmap_room_no){                     // Called and connected in character.h
    if(bask[gmap_room_no]->next2 == NULL){
        strcpy(bask[gmap_room_no]->item,"nothing"); 
    }else{
        struct items *begin = bask[gmap_room_no]; 
        struct items *temp = bask[gmap_room_no];
        if(strcmp(begin->item, x) == 0){
            temp = begin; 
            begin = begin->next2;
            free(temp);
        }else{  
            while(temp->next2 != NULL){
                if(strcmp(temp->item, x) == 0){
                    break;     
                }
               temp = temp->next2; 
            }
            struct items *t; 
            t = begin; 
            while(t->next2!=temp){
                t->next2 = temp->next2; 
                free(temp);
            }
        }
    }
}
void add_item_to_room(char x[10], int gmap_room_no){
   if(strcmp(bask[gmap_room_no]->item, "") == 0 || (strcmp(bask[gmap_room_no]->item, "nothing")==0)){
       strcpy(bask[gmap_room_no]->item, x);
       head[gmap_room_no] = bask[gmap_room_no];
   }else{
       struct items *n; 
       struct items *temp;
       temp = head[gmap_room_no];
       n = (struct items *)malloc(sizeof(struct items));
       strcpy(n->item, x);
       while(temp->next2 != NULL){
           temp = temp->next2;
       }
       if(temp->next2 == NULL){
           temp->next2 = n;
           temp = temp->next2;
           temp->next2 = NULL;
       }else{
           temp = temp->next2;
           printf("%p\t", temp);
           temp->next2 = n;
           temp->next2 = NULL;
       } 
   } 
}
bool look(int, int);                //not related to look command. Just used to and prevent dupilication of random numbers in rooms[]
void randomise_objects(){
   int s = -1; 
   while(s<6){
       int inp; 
       inp = 1+rand()%8;               // rooms is filled with unique random numbers from 1 - 9.
       if(s == -1){
           s += 1;
           rooms[s] = inp;
       }else{
           bool flag  = look(inp, s);
           if(flag){
               s += 1; 
               rooms[s] = inp;
           }
       }
   } 
}
bool look(int x, int s){        
    for(int i = 0 ; i<=s; i++){
        if(rooms[i] == x){
            return false;
        }
    }
    return true; 
}
void execute(){                 
    createList(10);         //check definition 
    randomise_objects();    
}
void place_objects(){
    for(int i = 0; i<6; i++){
        strcpy(bask[rooms[i]]->item, options[i]);       //read this carefully, a lot is going on here. 
    }
}
void init(){                    //called in adventure.c 
    execute();              
    place_objects();                
}

