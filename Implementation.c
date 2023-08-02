#include "Header.h"
/*function that gets the data from manot.txt and build linked list of all the dishes and print the results to out file*/
manot*CreateProducts(FILE*in,manot*head,FILE*Out)
{
    manot*temp;
    char name[MAX];
    int size;
    temp = (manot*)malloc(sizeof(manot));
    if (temp==NULL)
        {
            printf("malloc fail");
            exit(1);
        }
    while (fscanf(in,"%s %d %d",name,&temp->Price,&temp->Quantity)!=EOF)
    {
        size=strlen(name);
        temp->Productname=(char*)malloc(size*sizeof(char));
        strcpy(temp->Productname,name);
        temp->next=head;
        head = temp;
        temp = (manot*)malloc(sizeof(manot));
        if (temp==NULL)
        {
            printf("malloc fail");
            exit(1);
        }
    }
    printf("The kitchen was created\n");
    fprintf(Out,"The kitchen was created\n");
    return head;
}
/*function that add quantity to one of the dishes in the kitchen and print the results to out file*/
void AddItem(manot*head,char *Pname,int Q,FILE*Out)
{
    int i=-1;
    manot*temp;
    temp = head;
    char name[MAX];
    while (temp->next!=NULL)
    {
        strcpy(name,temp->Productname);
        if(strcmp(name,Pname)==0)
        {
            temp->Quantity=temp->Quantity+Q;
            printf("%d %s were added to the kitchen\n",Q,Pname);
            fprintf(Out,"%d %s were added to the kitchen\n",Q,Pname);
            i=1;
            break;
        }
      temp=temp->next;
        
    }
    if (i==-1)
    {
        printf("%s Not fount",Pname);
        fprintf(Out,"%s Not fount",Pname);
    }
}
/*function that add a dish to a table using pointers array, the dish is added to a linked list of every table and print the resulets to out file*/
void OrderItem(int Tnum,char *Mname,int q,manot*Mhead,table*arr,FILE*Out)
{
    int i=0;
    manot*temp;
    temp =(manot*)malloc(sizeof(manot));
        if (temp==NULL)
            {
                printf("malloc fail");
                exit(1);
            }
    temp=Mhead;
    order*save;
    save =(order*)malloc(sizeof(order));
        if (save==NULL)
            {
                printf("malloc fail");
                exit(1);
            }
    if(Tnum>arr[0].quantity)
    {
        printf("The table number is invalid");
        fprintf(Out,"The table number is invalid");
    }
    else if(Checkdish(Mname,Mhead,q)==1)
    {
        for (i=0; i<arr[0].quantity;i++)
        {
            if(arr[i].Tnum==Tnum)
            {
                while (temp->next!=NULL)
                {
                    if(strcmp(temp->Productname,Mname)==0)
                    {
                        strcpy(save->Productname,temp->Productname);
                        save->Price=temp->Price;
                        save->Quantity=save->Quantity+q;
                        temp->Quantity=temp->Quantity-q;
                        save->next=NULL;
                        save->next=arr[i].head;
                        arr[i].head = save;
                        arr[i].bill=arr[i].bill+(save->Price*q);
                        printf("%d %s were added to table number %d\n",q,Mname,Tnum);
                        fprintf(Out,"%d %s were added to table number %d\n",q,Mname,Tnum);
                    }
                    temp=temp->next;
                }
            }
        }
    }
    else
    {
        printf("We don't have %s, sorry!\n",Mname);
        fprintf(Out,"We don't have %s, sorry!\n",Mname);
    }
}
/*function that check if the dish is in the kitchen and if there is enough quantity if the dish name is exist and the quantity ok its return 1 else -1*/
int Checkdish(char*Dname,manot*head,int q)
{
    manot*temp;
    temp =(manot*)malloc(sizeof(manot));
        if (temp==NULL)
            {
                printf("malloc fail");
                exit(1);
            }
    temp =head;
    int ch=-1,gg=0;
    while (temp->next!=NULL)
    {
        gg=strcmp(temp->Productname,Dname);
        if(strcmp(temp->Productname,Dname)==0&&temp->Quantity>=q)
        {
            ch=1;
        }
        temp=temp->next;
    }
    return ch;
}
/*function that set up the pointers array for the tables fill it and allocate his memory*/
table* Setuparr(table*arr,int q)
{
    int i=0;
    arr=(table*)malloc(q*sizeof(table));
    if(arr==NULL)
    {
        printf("mallloc fail");
        free(arr);
        exit(1);
    }
    for (i=0; i<q; i++)
    {
        arr[i].quantity=q;
        arr[i].Tnum=i+1;
        arr[i].head=NULL;
    }
    return arr;
}
/*function that remove a dish from table,change his bill and print the resultes to out file*/
void RemoveItem(char Tnum,char *Pname,int q,table*arr,manot*head,FILE*Out)
{
    int i=0,ch=-1;
    order*save;
    save =(order*)malloc(sizeof(order));
        if (save==NULL)
            {
                printf("malloc fail");
                exit(1);
            }
    if (Tnum>arr[0].quantity)
    {
        printf("Table number dont exist");
        fprintf(Out,"Table number dont exist");
    }
    for (i=0;i<arr[0].quantity; i++)
    {
        if(arr[i].Tnum==Tnum)
        {
            if(arr[i].head!=NULL)
            {
                save=arr[i].head;
                while (save!=NULL)
                {
                    if(strcmp(save->Productname,Pname)==0)
                    {
                        if (q>save->Quantity||q<0)
                        {
                            printf("Number to remove is invalid\n");
                            fprintf(Out,"Number to remove is invalid\n");
                            break;
                        }
                        else if(save->Quantity==1)
                        {
                            arr[i].head=save->next;
                            free(save);
                            ch=1;
                            break;
                        }
                        else if(save->Quantity>1)
                        {
                            save->Quantity=save->Quantity-q;
                            ch=1;
                            break;
                        }
                    }
                    save=save->next;
                }
                if(ch==-1)
                {
                    printf("Table %d didnt order %s",Tnum,Pname);
                    fprintf(Out,"Table %d didnt order %s",Tnum,Pname);
                }
            }
            else
            {
                printf("Table %d has no active order",Tnum);
                fprintf(Out,"Table %d has no active order",Tnum);
            }
        }
    }
    if(ch==1)
    {
        printf("%d %s was returned to the kitchen from table number %d\n",q,Pname,Tnum);
        fprintf(Out,"%d %s was returned to the kitchen from table number %d\n",q,Pname,Tnum);
    }
}
/*function that print the currect state of the kitchen and print the resultes to out file*/
void PrintKitchen(manot*head,FILE*Out)
{
    printf("Kitchen:");
    fprintf(Out,"Kitchen:");
    printf(" %s %d",head->Productname,head->Quantity);
    fprintf(Out," %s %d",head->Productname,head->Quantity);
    while (head->next!=NULL)
    {
        printf(" %s %d",head->next->Productname,head->next->Quantity);
        fprintf(Out," %s %d",head->next->Productname,head->next->Quantity);
        head=head->next;
    }
}
/*function that gets the instruction from instruction.txt and operate the functions*/
table* Getfile(FILE*inst,FILE*in,manot*headmanot,table*arr,FILE*Out)
{
    manot**ptr;
    ptr=&headmanot;
    int func=0,Tnumber=0,x=0,y=0;
    char txt[MAX];
    fscanf(inst,"%d",&Tnumber);
    arr = Setuparr(arr,Tnumber);
    while(fscanf(inst,"%d",&func)!=EOF)
    {
        if(func==1)
        {
            *ptr = CreateProducts(in,headmanot,Out);
        }
        else if(func==2)
        {
            fscanf(inst,"%s",txt);
            fscanf(inst,"%d",&x);
            AddItem(headmanot,txt,x,Out);
            
        }
        else if(func==3)
        {
            fscanf(inst,"%d",&x);
            fscanf(inst,"%s",txt);
            fscanf(inst,"%d",&y);
            OrderItem(x,txt,y,headmanot,arr,Out);
            
        }
        else if(func==4)
        {
            fscanf(inst,"%d",&x);
            fscanf(inst,"%s",txt);
            fscanf(inst,"%d",&y);
            RemoveItem(x,txt,y,arr,headmanot,Out);
        }
        else if(func==5)
        {
            PrintKitchen(headmanot,Out);
        }
        else
        {
            printf("No such function:%d",func);
            fprintf(Out,"No such function:%d",func);
            break;
        }
    }
    printf("\nFINISH!");
    return arr;
}
/*function that free all the memory allocations*/
void Freememory(manot**head,table *arr)
{
    manot*temp;
    order*save=NULL;
    int i=0;
    /*free the manot linked list*/
    while (*head!=NULL)
    {
        temp=(*head);
        free((*head)->Productname);
        (*head)=((*head)->next);
        free(temp);
    }
    /*free the pointers array*/
    for (i=0; i<arr[0].quantity;i++)
    {
        if(arr[i].head==NULL)
        {
            free(arr[i].head);
        }
        else
        {
            while (arr[i].head->next!=NULL)
            {
                save=arr[i].head;
                arr[i].head=arr[i].head->next;
                free(save);
            }
            free(arr[i].head);
        }
    }
    free(arr);
}
