#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "character.h"
#include "room.h"
struct inventory{                                                                                           
    char items[50];
    struct inventory *link; 
}; 
typedef struct inventory inven; 
inven *start1 = NULL;            
inven *createnode2(){
    inven *n; 
    n = (struct inventory *)malloc(sizeof(struct inventory)); 
    return n; 
}
void remove_Item_from_room(char [], int);                                   //gets called when you ADD A THING TO YOUR INVENTORY!!!!!!!!!!!
bool valid_take(char [], int );                                             //MAKES SURE THAT YOU DO NOT ADD THINGS OUTSIDE YOUR ROOM. //take a look at item.h side by side 
void take_item(int room_number){                                            
  //  printf("Enter the item you want to take: ");
    char x[50]; 
    bool  validity = false; 
    while(validity != true){
        scanf("%s", x);
        validity = valid_take(x, room_number);                              
        if(validity == false){
           printf("Item not present\n");
           break; 
        }
    }
    if(validity == true){                                                   //if the item is valid it will make a node and add it to the linked list
        inven *temp, *t; 
        temp = createnode2();
        char y[50]; 
        strcpy(y, x); 
        if(start1 == NULL || (strcmp(start1->items, "nothing")==0)){
            start1 = temp;
            strcpy(temp->items,y);
        }else{
            t = start1; 
            while(t->link){
                t = t->link;
            }
            t->link = temp; 
            strcpy(temp->items, y);
        }
        printf("Item added to inventory\n");
        remove_Item_from_room(x, room_number);                          //THIS IS VERY IMPORTANT, PLEASE TAKE A LOOK AT items.h
    }
}
bool searchInven(int room_number, char murder_weapon_used[10]){
   inven *temp;
   temp = start1; 
   while(temp != NULL){
       if(strcmp(temp->items, murder_weapon_used)==0){
           return true;
       }
       temp = temp->link;
   }
   return false; 
}
void showInven(){
    inven *temp; 
    if(start1 == NULL || strcmp(start1->items, "nothing")==0){
        printf("Inventory is empty\n");
    }else{
        temp = start1; 
        while(temp->link!=NULL){
           printf("%s\n", temp->items);
           temp = temp->link; 
        }
        if(temp->link==NULL){
            printf("%s\n", temp->items);
        }
    }
}
void add_item_to_room(char [], int);                    //function from item.h, defined here so that the compiler knows about it before it is called. Since it is from a different file. 
void removeItem(int present){                           //removes the item, from the inventory.     
    bool flaglol = false; 
    char x[50]; 
    scanf("%s", x);
    inven *temp;
    bool flag2 , flag1; 
    if(start1 == NULL || strcmp(start1->items, "nothing")==0){
        printf("Inventory is empty so you nothing can be removed\n ");
    }else{
       inven *visi;
       temp = start1;
       if((strcmp(x, temp->items)==0)&&(temp->link == NULL)){
           add_item_to_room(x, present);
           strcpy(temp->items, "nothing");
           flaglol = true;
       }else{
       while(temp->link!=NULL){                     //for iterating through the linked list. 
           if(strcmp(x, temp->items)==0){
              flag1 = true; 
               if(temp == start1){
                  start1 = temp->link; 
                 free(temp);
              }else if(temp!=start1 && (temp->link!= NULL)){
                  visi = temp;
                  temp = start1; 
                  while(temp->link!=visi){
                     temp = temp->link; 
                  }
                  temp->link = (temp->link)->link;
                  free(visi);
              }
           }
         temp = temp->link;
       } 
       if(strcmp(x, temp->items)==0){
           flag2 = true;                        //checking the last element of the linked list because it will be missed in the first loop.
           inven *visi;
           visi = temp;
           temp = start1; 
           while(temp->link != visi){
               temp = temp->link;
           }
           temp->link = NULL;
           free(visi);
          }
       }
    }
    if(flag1 == true || flag2 == true){
        printf("%s, dropped", x);
        add_item_to_room(x, present);       //VERY IMPORTANT PART HERE AGAIN, REFER ITEMS.H
    }else{
        if(flaglol == false){
            printf("No Item like this\n");
        }
    }
}

struct gmap *move_character(struct gmap* location){                                         //Movement of character in character.h
    char dir[15];
    while(true){
       scanf("%s", dir);
       if(strcmp(dir, "north")==0 && (location->north != NULL)){
          location = location->north; 
          return location; 
       }else if((strcmp(dir, "south") == 0)&&(location->south != NULL)){
           location = location->south; 
           return location; 
       }else if((strcmp(dir, "west") == 0)&&(location->west != NULL)){
           location = location->west;
           return location; 
       }else if((strcmp(dir, "east") == 0) && (location->east != NULL)){
           location = location->east; 
           return location; 
       }else{
          printf("Enter a valid direction\n"); 
       }
    }
}
