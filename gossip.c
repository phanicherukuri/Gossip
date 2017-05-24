/* Project #2, Phani Cherukuri */


#include "csim.h"
#include <stdio.h>
#define TRANS_TIME 1.0 

struct node
{
FACILITY cpu;
MBOX input;
long list[100];
long top;
};
struct node nodes[1000];

struct values
{
long x; //packet id
long y; // no. of hops
};
typedef struct values *msg_t;
struct values results;
struct values new_packet(int);

void send_msg(struct values *results);    //declarations
int forward(struct values *results,int);
int reciever(int t,struct values *results);

int count1,count2,count3,count4,count5,count6; 
int element[20][50];                             // initializations
int i;
int j,k;
int row=20;
int col=50;
int mb;
char str[1000];
 
void sim()
{
int n=0;
int end=0;
 create("sim");
  printf("process sim has created\n");
  for(i=0;i<20;i++) //20*50 mesh network creation
   for(j=0;j<50;j++)
    {          
    element[i][j]=n;
    n++;
    }         
    printf("mesh network created\n");
    max_mailboxes(1000);
    max_events(2*1000*1000);
    for(mb=0;mb<1000;mb++) //initialization of mailbox to each node
     {
      sprintf(str,"input.%d",mb);
      nodes[mb].input=mailbox(str);
     }
    for(k=0;k<100;k++) //packet generation
    {                
     printf("source generates the %d packet\n",k);
     struct values result;
     result = new_packet(k);
     int d=1;
     end = forward(&result,d); 
     printf("end value is %d\n",end);//reaching to destination
     printf("packet %d have been transmitted to destination\n",k);
     hold(exponential(TRANS_TIME));
    }
     //printf("hop10:%d\n hop20:%d\n hop30:%d\n",count1,count2,count3);
     //printf("hop40:%d\n hop50:%d\n hop60:%d\n",count4,count5,count6);
    printf("successfully completed\n");
}
 
struct values new_packet(int k)
{
 struct values result;
 result.x=k; //storing packet id
 result.y=0; //storing hop count as 0
 return result;
}
int forward(struct values *results,int d)
{ 
do
 {
    if(d==999) //destination node
    {
    return 1;
    break; 
    }
    else if(d==0) //source node
    {
    printf("the adjacent elements are %d and %d\n",d+1,d+col);
    printf("Now sending for %d\n",d+1);
    printf("id before sending for %ld\n",results->x);
    printf("%d is sending to %d\n",d,d+1);
    send(nodes[d+1].input,(long)results);
    if(reciever(d+1,results)==1)
    {
     return 1;
    }
    printf("Now sending for %d\n",d+col);
    printf("%d is sending to %d\n",d,d+col);
    send(nodes[d+col].input,(long)results);
    if(reciever(d+col,results)==1)
    {
     return 1;
    } 
    }
    else if(d+1==col)
    {
    printf("the adjacent elements are %d and %d\n",d-1,d+col);
    printf("Now sending for %d\n",d-1);
    printf("%d is sending to %d\n",d,d-1);
    send(nodes[d-1].input,(long)results);
    if(reciever(d-1,results)==1)
    {
     return 1;
    } 
    printf("Now sending for %d\n",d+col);
    printf("%d is sending to %d\n",d,d+col);
    send(nodes[d+col].input,(long)results);
    if(reciever(d+col,results)==1)
    {
     return 1;
    } 
    }
    else if(((((d+1)%col)==0)&&(d+1)!=col)&&(d+1)!=(col*row))
    {
    printf("the adjacent elements are %d,%d and %d\n",d-1,d+col,d-col);
    printf("%d is sending to %d\n",d,d-1);
    send(nodes[d-1].input,(long)results);
    if(reciever(d-1,results)==1)
    {
     return 1;
    } 
    printf("%d is sending to %d\n",d,d+col);
    send(nodes[d+col].input,(long)results);
    if(reciever(d+col,results)==1)
    {
     return 1;
    } 
    printf("%d is sending to %d\n",d,d-col);
    send(nodes[d-col].input,(long)results);
    if(reciever(d-col,results)==1)
    {
     return 1;
    } 
    }
    else if((d+1)==(row*col))
    {
    printf("the neighbour elements are %d and %d\n",d-1,d-col);
    printf("%d is sending to %d\n",d,d-1);
    send(nodes[d-1].input,(long)results);
    if(reciever(d-1,results)==1)
    {
     return 1;
    } 
    printf("%d is sending to %d\n",d,d-col);
    send(nodes[d-col].input,(long)results);
    if(reciever(d-col,results)==1)
    {
     return 1;
    } 
    }
    else if((d+1)==((row*(col-1))+1))
    {
    printf("the neighbour elements are %d and %d\n",d+1,d-col);
    printf("%d is sending to %d\n",d,d+1);
    send(nodes[d+1].input,(long)results);
    if(reciever(d+1,results)==1)
    {
     return 1;
    } 
    printf("%d is sending to %d\n",d,d-col);
    send(nodes[d-col].input,(long)results);
    if(reciever(d-col,results)==1)
    {
     return 1;
    } 
    }
    else if(((d+1)%col)==1)
    {
    printf("the neighbour elements are %d,%d and %d\n", d+1,d-col,d+col);
    printf("%d is sending to %d\n",d,d+1);
    send(nodes[d+1].input,(long)results);
    if(reciever(d+1,results)==1)
    {
     return 1;
    } 
    printf("%d is sending to %d\n",d,d-col);
    send(nodes[d-col].input,(long)results);
    if(reciever(d-col,results)==1)
    {
     return 1;
    } 
    printf("%d is sending to %d\n",d,d+col);
    send(nodes[d+col].input,(long)results);
    if(reciever(d+col,results)==1)
    {
     return 1;
    } 
    }
    else if(((d+1)%(row*(col-1)))==2)
    {
    printf("the neighbour elements are %d and %d\n", d+1,d-1);
    printf("%d is sending to %d\n",d,d+1);    
    send(nodes[d+1].input,(long)results);
    if(reciever(d+1,results)==1)
    {
     return 1;
    } 
    printf("%d is sending to %d\n",d,d-1);
    send(nodes[d-1].input,(long)results);
    if(reciever(d-1,results)==1)
    {
     return 1;
    } 
    }
    else if((((d+1)/col)==0)&&((((d+1)%col)>=2)&&(((d+1)%col)<=(col-1))))
    {
    printf("the neighbour elements are %d,%d and %d\n",d-1,d+1,d+col);
    printf("%d is sending to %d\n",d,d-1);
    send(nodes[d-1].input,(long)results);
    if(reciever(d-1,results)==1)
    {
     return 1;
    } 
    printf("%d is sending to %d\n",d,d+1);
    send(nodes[d+1].input,(long)results);
    if(reciever(d+1,results)==1)
    {
     return 1;
    } 
    printf("%d is sending to %d\n",d,d+col);
    send(nodes[d+col].input,(long)results);
    if(reciever(d+col,results)==1)
    {
     return 1;
    } 
    }
    else if(((d+1)/col)==(row-1))
    {
    printf("the neighbour elements are %d,%d and %d\n",d-1,d+1,d-col);
    printf("%d is sending to %d\n",d,d-1);
    send(nodes[d-1].input,(long)results);
    if(reciever(d-1,results)==1)
    {
     return 1;
    }
    printf("%d is sending to %d\n",d,d+1);
    send(nodes[d+1].input,(long)results);
    if(reciever(d+1,results)==1)
    {
     return 1;
    } 
    printf("%d is sending to %d\n",d,d-col);
    send(nodes[d-col].input,(long)results);
    if(reciever(d-col,results)==1)
    {
     return 1;
    }
    }
    else //intermediate nodes
    {
    printf("the neighbour elemets are %d,%d,%d and %d\n",d-1,d+1,d+col,d-col);
    printf("%d is sending to %d\n",d,d-1);
    send(nodes[d-1].input,(long)results);
    if(reciever(d-1,results)==1)
    {
     return 1;
    } 
    printf("%d is sending to %d\n",d,d+1);
    send(nodes[d+1].input,(long)results);
    if(reciever(d+1,results)==1)
    {
     return 1;
    } 
    printf("%d is sending to %d\n",d,d+col);
    send(nodes[d+col].input,(long)results);
    if(reciever(d+col,results)==1)
    {
     return 1;
    } 
    printf("%d is sending to %d\n",d,d-col);
    send(nodes[d-col].input,(long)results);
    if(reciever(d-col,results)==1)
    {
     return 1;
    } 
    }
 }while(0);
return 0;
}
 
int reciever(int number,struct values *msg)
{ 
 long topelement;
 long d=number;
 topelement = nodes[d].top;
 long found=0;
 long p;
 long ch;
 struct values oldResult;
 float prob=0.72;
 float gossip;
 msg_t m; // using results produces wrong results as it is declared as global
 m = (msg_t)do_malloc(sizeof(struct values));
 receive(nodes[d].input,(long*)&m); 
 long id=m->x;
 long hc=m->y;
 switch(hc)
  {
   case 10: count1++;
            break;
   case 20: count2++;
            break;
   case 30: count3++;
            break;
   case 40: count4++;
            break;
   case 50: count5++;
            break;
   case 60: count6++;
            break;
  }
 printf("id is %ld\n",id);
 printf("top element of array is %ld\n",topelement);
 for(p=0;p<100;p++)
 {
  if(id==nodes[d].list[p])
      {
       found=1;
       printf("the packet has already been revieved, found = %d\n",found); 
       break;
      }
 }   
  if(found!=1)
      {
        nodes[d].list[topelement]=id;
        topelement++;
        nodes[d].top=topelement;
        printf("the packet haven't recieved earlier\n");
        if(hc<=4)
           {
            ch=hc++;
            results.y=ch;
           if(forward(msg,d)==1)
             {
              return 1;
             }
           }
        else   
         {    
           gossip=uniform(0,1);
           if(prob>gossip)
             { 
               ch=hc++;
               results.y=ch;
                if(forward(msg,d)==1)
                {
                 return 1;
                }
             }
           else
             {
               printf("the gossiping probability fails\n");
             }
         }         
}
return 0;
}
 
 
 
 
