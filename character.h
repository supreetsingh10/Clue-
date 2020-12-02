#pragma once
struct inventory *start1; 
struct inventory;
struct inventory *createnode2(); 
void remove_Item_from_room(char [], int); 
bool  valid_take(char[], int); 
void take_item(int); 
bool searchInven(int, char []); 
void showInven(); 
void add_item_to_room(char [], int); 
void removeItem(int); 
struct gmap *move_character(struct gmap *); 

