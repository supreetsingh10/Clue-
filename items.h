#pragma once 

struct items; 
char options[6][10]; 
int rooms[6]; 
struct items *bask[10]; 
struct items *head[10]; 
void createList(int); 
void what_is_in_room(int); 
bool searchRoom(int, char []); 
bool valid_take(char [], int); 
void remove_Item_from_room(char [], int); 
void add_item_to_room(char [], int); 
bool look(int, int); 
void randomise_objects(); 
void execute(); 
void place_objects(); 
void init(); 

