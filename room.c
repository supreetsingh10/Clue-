#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"room.h"
/*struct gmap{
    struct gmap *north; 
    struct gmap *west; 
    int room; 
    struct gmap *east; 
    struct gmap *south;     
};
struct person{
    char character[10]; 
    int stay; 
    struct person *next; 
};*/
char peeps[5][10] = {"Samael", "Nancy", "Lizzy", "Tony", "Ozzy"}; 
void createnode(int n){
    adds[n] = (struct gmap *)malloc(sizeof(struct gmap)); 
    adds[n]->room = 0; 
    adds[n]->north = NULL;
    adds[n]->south = NULL;
    adds[n]->east = NULL;
    adds[n]->west = NULL;
}
void createnode_for_person(int n){
   rooms_and_people[n] = (struct person *)malloc(sizeof(struct person));
   strcpy(rooms_and_people[n]->character, ""); 
   rooms_and_people[n]->next = NULL;
   headers[n] = rooms_and_people[n]; 
}
void connections(){
    for(int i = 0; i<9-3; i++){
        int j = i + 3; 
        struct gmap *up, *down; 
        up = adds[i], down = adds[j];
        up->south = down; 
    }
    for(int i = 8; i >= 3; i--){
        int j = i - 3; 
        struct gmap *up, *down; 
        down = adds[i], up = adds[j];
        down->north = up;
    }
    for(int i = 0; i < 8; i++){
        int j = i+1; 
        struct gmap *right, *left; 
        right = adds[i], left = adds[j]; 
        if((i == 2) ||(i == 5)){
            continue;
        }else{
            right->east = left; 
        }
    }
    for(int i = 8; i>0; i--){
        int j = i - 1;
        struct gmap *left, *right; 
        left = adds[i], right = adds[j];
        if((i == 6) || (i == 3)){
            continue; 
        }else{
            left->west = right; 
        }
    }
}
int search_for_human(char human[10]){
   struct person *temp666, *t;
   for(int i = 1; i<10; i++){
       temp666 = rooms_and_people[i]; 
       t = temp666; 
       while(t != NULL){
           if(strcmp(t->character, human)==0){
               return i; 
           }else{
               t = t->next;
           } 
       }
   }   
   return 666;
}
void move_away_from_room(int gmap_room_no, char human[10]){
    struct person *temp555;
    char shift_person[10];
    temp555 = headers[gmap_room_no];
    if((temp555->next == NULL) && (strcmp(temp555->character, human)==0)){
        strcpy(temp555->character, ""); 
    }else{
        if((temp555->next != NULL) && strcmp(temp555->character, human)==0){
            headers[gmap_room_no] = temp555->next; 
            free(temp555);
        }else{
            while(temp555 != NULL){
                if(strcmp(temp555->character, human)==0){
                    struct person *temp444; 
                    temp444 = headers[gmap_room_no];
                    while(temp444->next != temp555 ){
                        temp444 = temp444->next;
                    }
                    temp444->next = temp555->next; 
                    free(temp555); 
                    break; 
                }else{
                    temp555 = temp555->next;
                } 
            }
        }
    }
}
void move_to_the_room(int gmap_room_no, char human[10]){
    int staying_room = search_for_human(human); 
    if(staying_room == 666){
        printf("Check the entered name\n"); 
    }else if(staying_room == gmap_room_no){
        printf("Character already in the room\n");
    }else if((staying_room != 666)&&(staying_room != gmap_room_no)){
        char shift_person[10];
        struct person *temp777;
        struct person *temp666; 
        temp777 = headers[gmap_room_no]; 
        temp666 = headers[staying_room];     
        if((temp777->next == NULL) && (strcmp(temp777->character, human)!=0) && (strcmp(temp777->character, "") == 0)){
            strcpy(temp777->character, human); 
            move_away_from_room(staying_room, human);
        }else{
            struct person *visiter; 
            visiter = (struct person *)malloc(sizeof(struct person));
            strcpy(visiter->character, human);
            while(temp777->next != NULL){
                temp777 = temp777->next; 
            }
            temp777->next = visiter; 
            move_away_from_room(staying_room, human);
        }
    }
}
void people(){
    int s = -1; 
    while(s<5){
        int inp = 1+rand()%7;
        s = insert(inp, s);
    }
    for(int i = 0; i<5; i++){
        strcpy(rooms_and_people[putpeople[i]]->character, peeps[i]);
        rooms_and_people[putpeople[i]]->stay = putpeople[i];
    }
}
int insert(int x, int s){
    if(s == -1){
        s += 1;
        putpeople[s] = x; 
        return s;
    }else{
        bool flag; 
        flag = lookup(x, s);
        if(flag == true){
            return s;
        }else{
            s += 1;
            putpeople[s] = x; 
            return s;
        }
    }
}
bool lookup(int x, int s){
    for(int i = 0; i<=s; i++){
        if(putpeople[i] == x){
            return true;
        }
    }
    return false;
}

void printconn(struct gmap *one, struct gmap *two){
    struct gmap *temp;
    temp = one; 
    while(temp->west!=NULL){
        printf("ADD %p\n", temp->west);
        temp = temp->west;
    }
}
void initialize(){
    for(int i = 0; i<9; i++){
        createnode(i);
    }
    for(int i = 1; i<10; i++){
        createnode_for_person(i);
    }
    connections(); 
    people();
}
