/*
Question 1
In this programming problem and the next you'll code up the knapsack algorithm from lecture. Let's start with a warm-up.
Download the text file here. This file describes a knapsack instance, and it has the following format:
[knapsack_size][number_of_items]
[value_1] [weight_1]
[value_2] [weight_2]
...
For example, the third line of the file is "50074 659", indicating that the second item has value 50074 and size 659, respectively.

You can assume that all numbers are positive. You should assume that item weights and the knapsack capacity are integers.

In the box below, type in the value of the optimal solution.

ADVICE: If you're not getting the correct answer, try debugging your algorithm using some small test cases.
And then post them to the discussion forum!

Question 2
This problem also asks you to solve a knapsack instance, but a much bigger one.

Download the text file here. This file describes a knapsack instance, and it has the following format:
[knapsack_size][number_of_items]
[value_1] [weight_1]
[value_2] [weight_2]
...
For example, the third line of the file is "50074 834558", indicating that the second item has value 50074 and size 834558, respectively.
As before, you should assume that item weights and the knapsack capacity are integers.

This instance is so big that the straightforward iterative implemetation uses an infeasible amount of time and space.
So you will have to be creative to compute an optimal solution.
One idea is to go back to a recursive implementation, solving subproblems --- and, of course, caching the results to avoid redundant work --- only on an "as needed" basis.
Also, be sure to think about appropriate data structures for storing and looking up solutions to subproblems.

In the box below, type in the value of the optimal solution.

ADVICE: If you're not getting the correct answer, try debugging your algorithm using some small test cases.
And then post them to the discussion forum!
*/

#include <cstdlib>
#include <iostream>
#include <stdio.h>

#define MAX(a,b) a>b?a:b

using namespace std;

struct node
{
       int n1,n2,cost;
       node *left;
       node *right;
};

void getLong(char *a, int n, long long *val1, long long *val2)
{
     int i,j;
     char ab[20];
     for(i=0; a[i]!=' '; i++) ab[i]=a[i];
     ab[i]='\0';
     *val1=atol(ab);
     for(j=0, i++; a[i]!='\n'; i++,j++) ab[j]=a[i];
     ab[j]='\0';
     *val2=atol(ab);
}

int main(int argc, char *argv[])
{
    char a[50];
    long long W, no_items, *w, *v, k=1;
    FILE *f=fopen("knapsack2.txt","r");
    fgets(a,50,f);
    getLong(a,strlen(a),&W,&no_items);
    w=new long long[no_items+1];
    v=new long long[no_items+1];
    long long *cal[2];
    for(int j=0; j<2; j++) cal[j]=new long long[W+1];
    while(fgets(a,50,f))
    {
        long long val, wt;
        getLong(a,strlen(a),&val,&wt);
        w[k]=wt;
        v[k++]=val;
    }
    fclose(f);
    for(long long j=0; j<=W; j++) cal[0][j]=0;
    for(int i=1; i<=no_items; i++)
    {
          for(long long x=0; x<=W; x++)
             if(x>=w[i])
                cal[1][x]=MAX(cal[0][x],cal[0][x-w[i]]+v[i]);
             else
                cal[1][x]=cal[0][x];
          for(long long j=0; j<=W; j++)
             cal[0][j]=cal[1][j];
    }
    cout<<"Optimal Solution: "<<cal[1][W]<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
