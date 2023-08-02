/*defining libraries*/
#ifndef Header
#define Header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
/*define structs*/
typedef struct manot
{
    char *Productname;
    int Price;
    int Quantity;
    struct manot*next;
    
}manot;
typedef struct order
{
    char Productname[50];
    int Quantity;
    int Price;
    struct order*next;
}order;

typedef struct table
{
    int Tnum;
    int bill;
    int quantity;
    order*head;
}table;
/*define functions*/
/*function that gets the data from manot.txt and build linked list of all the dishes*/
manot*CreateProducts(FILE*in,manot*head,FILE*Out);
/*function that add quantity to one of the dishes in the kitchen*/
void AddItem(manot*head,char *Pname,int Q,FILE*Out);
/*function that add a dish to a table using pointers array, the dish is added to a linked list of every table*/
void OrderItem(int Tnum,char *Mname,int q,manot*Mhead,table*arr,FILE*Out);
/*function that remove a dish from table and change his bill*/
void RemoveItem(char Tnum,char *Pname,int q,table*arr,manot*head,FILE*Out);
/*function that print the currect state of the kitchen*/
void PrintKitchen(manot*head,FILE*Out);
/*function that check if the dish is in the kitchen and if there is enough quantity*/
int Checkdish(char*Dname,manot*head,int q);
/*function that set upthe pointers array for the tables*/
table* Setuparr(table*arr,int q);
/*function that gets the instruction from instruction.txt and operate the functions*/
table* Getfile(FILE*inst,FILE*in,manot*headmanot,table*arr,FILE*Out);
/*function that free all the memory allocations*/
void Freememory(manot**head,table *arr);

#endif
