/*
Question 1
In this assignment you will implement one or more algorithms for the traveling salesman problem, such as the dynamic programming algorithm covered in the video lectures.
Here is a data file describing a TSP instance. The first line indicates the number of cities.
Each city is a point in the plane, and each subsequent line indicates the x- and y-coordinates of a single city.

The distance between two cities is defined as the Euclidean distance --- that is, two cities at locations (x,y) and (z,w) have distance sqrt((x-z)^2+(y-w)^2) between them.

In the box below, type in the minimum cost of a traveling salesman tour for this instance, rounded down to the nearest integer.

OPTIONAL: If you want bigger data sets to play with, check out the TSP instances from around the world here.
The smallest data set (Western Sahara) has 29 cities, and most of the data sets are much bigger than that.
What's the largest of these data sets that you're able to solve --- using dynamic programming or, if you like, a completely different method?
*/

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <math.h>
#define INFINITE 99999
#define MIN(a,b) a<b?a:b
typedef unsigned long long uint_t;
using namespace std;

void getFloat(char *a, float *val1, float *val2)
{
     int i,j;
     char ab[10];
     for(j=0, i=0; a[i]!=' '; i++,j++) ab[j]=a[i];
     ab[j]='\0';
     *val1=atof(ab);
     for(j=0, i++; a[i]!='\n'; i++,j++) ab[j]=a[i];
     ab[j]='\0';
     *val2=atof(ab);
}

uint_t nextnum(uint_t x)
{
 
  uint_t rightOne;
  uint_t nextHigherOneBit;
  uint_t rightOnesPattern;
 
  uint_t next = 0;
 
  if(x)
  {
 
    // right most set bit
    rightOne = x & -(signed long)x;
 
    // reset the pattern and set next higher bit
    // left part of x will be here
    nextHigherOneBit = x + rightOne;
 
    // nextHigherOneBit is now part [D] of the above explanation.
 
    // isolate the pattern
    rightOnesPattern = x ^ nextHigherOneBit;
 
    // right adjust pattern
    rightOnesPattern = (rightOnesPattern)/rightOne;
 
    // correction factor
    rightOnesPattern >>= 2;
 
    // rightOnesPattern is now part [A] of the above explanation.
 
    // integrate new pattern (Add [D] and [A])
    next = nextHigherOneBit | rightOnesPattern;
  }
 
  return next;
}

long long getSize(int n, int m)
{
     long long num=1, den=1;
     if(n==m) return 1;
     for(int i=0; i<m; i++) num*=(n-i);
     for(int i=1; i<=m; i++) den*=i;
     return num/den;
}

int main(int argc, char *argv[])
{
    struct node
    {
       long s;
       float *a;
       node *next;
    };
    char line[30];
    int num_cities;
    FILE *f=fopen("tsp.txt","r");
    fgets(line,30,f);
    num_cities=atoi(line);
    float **g=new float*[num_cities+1];
    float **cord=new float*[num_cities+1];
    for(int i=1; i<=num_cities; i++)
    {
            cord[i]=new float[2];
            fgets(line,30,f);
            float x,y;
            getFloat(line,&x,&y);
            cord[i][0]=x; cord[i][1]=y;
    }
    fclose(f);
    g[0]=new float[num_cities+1];
    for(int i=1; i<=num_cities; i++)
            g[i]=new float[num_cities+1];
            
    for(int i=1; i<=num_cities; i++)
    {
            g[i][i]=0;
            for(int j=i+1; j<=num_cities; j++)
                    {
                           g[i][j]=sqrt(pow(cord[i][0]-cord[j][0],2)+pow(cord[i][1]-cord[j][1],2));
                           g[j][i]=g[i][j];
                    }
    }
    delete cord;
    
    node **arr=new node*[num_cities+1];
    for(int i=0; i<=num_cities; i++) arr[i]=NULL;
    for(int h=1; h<=num_cities; h++) 
    {
            long s=1<<(h-1);
            long index=s%num_cities;
            if(arr[index]==NULL)
            {
                arr[index]=new node;
                arr[index]->next=NULL;
                arr[index]->s=s;
                arr[index]->a=new float[num_cities+1];
                arr[index]->a[num_cities]=INFINITE;
                if(s==1) arr[index]->a[num_cities]=0;
            }
            else
            {
                node *temp=arr[index];
                while(temp->next!=NULL) temp=temp->next;
                node *newnode=new node;
                newnode->next=NULL;
                newnode->s=s;
                newnode->a=new float[num_cities+1];
                newnode->a[num_cities]=INFINITE;
                temp->next=newnode;
            }
    }

    long long S=1<<num_cities;
    long count=num_cities, lcount;
    long long newSize=count, lsize;
    node **curr_arr;
    
    for(int m=2; m<=num_cities; m++)
    {
            lcount=count; count=0;
            lsize=newSize;
            int tempm=m;
            if(m>(num_cities/2))
            {
                tempm=num_cities-m+1;
                if(num_cities%2==1 && m==((num_cities/2)+1)) tempm=m;
            }
            newSize=getSize(num_cities-1,tempm-1);
            curr_arr=new node*[newSize+1];
            for(long long i=0; i<=newSize; i++) curr_arr[i]=NULL;
            long long s=0;
            for(int i=0; i<m; i++)
            s+=(long long)(((long long)1)<<i);
            while(s<S)
            {
                    ++count;
                    node *newnode=new node;
                    newnode->next=NULL;
                    newnode->s=s;
                    newnode->a=new float[num_cities+1];
                    for(int p=0; p<=num_cities; p++) newnode->a[p]=INFINITE;
                    for(int j=num_cities-1; j>0; j--)
                    {
                            if((s&(1<<(num_cities-j))))
                            {
                                    long long ttemp=s&~(1<<(num_cities-j));
                                    newnode->a[j]=INFINITE;
                                    for(int k=num_cities; k>0; k--)
                                    {
                                            if((s&(1<<(num_cities-k))) && k!=j)
                                            {
                                            long long indexx=ttemp%lsize;
                                            node *old=arr[indexx];
                                            while(old!=NULL && (old->s)!=ttemp) old=old->next;
                                            float val=INFINITE;
                                            if(old!=NULL) val=old->a[k];
                                            if(newnode->a[j]>(val+g[num_cities-k+1][num_cities-j+1]))
                                                    newnode->a[j]=val+g[num_cities-k+1][num_cities-j+1];
                                            }
                                    }
                                    
                            }
                    }
                    unsigned long long index=s%newSize;
                    if(curr_arr[index]!=NULL)
                    {
                        node *temp=curr_arr[index];
                        while(temp->next!=NULL) temp=temp->next;
                        temp->next=newnode;
                    }
                    else curr_arr[index]=newnode;
                    s=s>>1;
                    s=(signed)nextnum(s);
                    s=(s<<1)+1;
            }
            delete arr;
            arr=curr_arr;
            curr_arr=NULL;
    }
    
    float min=INFINITE;
    count=(S-1)%newSize;
    for(int j=1; j<num_cities; j++)
        if(((arr[count]->a[j])+g[num_cities-j+1][1])<min)
            min=(arr[count]->a[j])+g[num_cities-j+1][1];
    delete arr,curr_arr,g;
    
    cout<<"Mininum Cost Travelling Salesman Tour: "<<(int)min<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
