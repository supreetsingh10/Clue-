#pragma once 

struct gmap{
    struct gmap *north;
    struct gmap *west; 
    int room; 
    struct gmap *east;
    struct gmap *south;  
}; 
struct gmap *adds[9]; 
struct person{
    char character[10];
    int stay; 
    struct person *next; 
}; 
struct person *headers[10]; 
struct person *rooms_and_people[10]; 
char peeps[5][10]; 
int putpeople[5]; 
void createnode(int); 
void createnode_for_person(int); 
void connections(); 
int search_for_human(char []); 
void move_away_from_room(int, char []); 
void move_to_the_room(int, char []); 
int insert(int, int);
bool lookup(int, int); 
void people(); 
void printconn(struct gmap *, struct gmap *); 
void initialize(); 

