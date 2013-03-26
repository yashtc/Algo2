/*
Question 3:
In this programming problem you'll code up Prim's minimum spanning tree algorithm.
Download the text file here. This file describes an undirected graph with integer edge costs. It has the format

[number_of_nodes] [number_of_edges]
[one_node_of_edge_1] [other_node_of_edge_1] [edge_1_cost]
[one_node_of_edge_2] [other_node_of_edge_2] [edge_2_cost]
...
For example, the third line of the file is "2 3 -8874", indicating that there is an edge connecting vertex #2 and vertex #3 that has cost -8874.
You should NOT assume that edge costs are positive, nor should you assume that they are distinct.

Your task is to run Prim's minimum spanning tree algorithm on this graph.
You should report the overall cost of a minimum spanning tree --- an integer, which may or may not be negative --- in the box below.

IMPLEMENTATION NOTES: This graph is small enough that the straightforward O(mn) time implementation of Prim's algorithm should work fine.
OPTIONAL: For those of you seeking an additional challenge, try implementing a heap-based version.
The simpler approach, which should already give you a healthy speed-up, is to maintain relevant edges in a heap (with keys = edge costs).
The superior approach stores the unprocessed vertices in the heap, as described in lecture.
Note this requires a heap that supports deletions, and you'll probably need to maintain some kind of mapping between vertices and their positions in the heap.
*/

#include <cstdlib>
#include <iostream>
#include <stdio.h>
using namespace std;

struct node
{
       int nodenum,cost;
       node *next;
}**g;

void getInt(char *a, int nos, int *val1, int *val2, int *val3=NULL)
{
     int i,j;
     char ab[10];
     for(i=0; a[i]!=' '; i++) ab[i]=a[i];
     ab[i]='\0';
     *val1=atoi(ab);
     for(j=0, i++; (a[i]!='\n' && a[i]!=' '); i++,j++) ab[j]=a[i];
     ab[j]='\0';
     *val2=atoi(ab);
     if(nos==3)
     {
               for(j=0, i++; a[i]!='\n'; i++,j++) ab[j]=a[i];
               ab[j]='\0';
               *val3=atoi(ab);
     }
}

int main(int argc, char *argv[])
{
    char a[20];
    int num_nodes,num_edges;
    FILE *f=fopen("edges.txt","r");
    fgets(a,20,f);
    getInt(a,2,&num_nodes,&num_edges);
    g=new node*[num_nodes];
    for(int i=1; i<=num_nodes; i++)
    {
            g[i]=new node;
            g[i]->next=NULL;
            g[i]->nodenum=i;
            g[i]->cost=0;
    }
    for(int i=0; i<num_edges; i++)
    {
            int node1,node2,cost;
            fgets(a,20,f);
            getInt(a,3,&node1,&node2,&cost);
            node *newnode=new node;
            newnode->nodenum=node2;
            newnode->cost=cost;
            newnode->next=NULL;
            node *temp=g[node1];
            while(temp->next!=NULL) temp=temp->next;
            temp->next=newnode;
            
            newnode=new node;
            newnode->nodenum=node1;
            newnode->cost=cost;
            newnode->next=NULL;
            temp=g[node2];
            while(temp->next!=NULL) temp=temp->next;
            temp->next=newnode;
    }
    bool *spanned=new bool[num_nodes+1];
    for(int i=0; i<=num_nodes; spanned[i++]=false);
    spanned[1]=true;
    long long tot_cost=0;
    for(int i=1; i<num_nodes; i++)
    {
            long minedge_cost=1000000;
            int node1, node2;
            for(int j=1; j<num_nodes; j++)
            {
                    if(!spanned[j]) continue;
                    node *t=g[j];
                    while(t->next!=NULL)
                    {
                         if(!spanned[(t->next)->nodenum])
                         {
                             if((t->next)->cost<minedge_cost) {node1=j; node2=(t->next)->nodenum; minedge_cost=(t->next)->cost; }
                         }
                         t=t->next;
                    }
            }
            spanned[node2]=true;
            tot_cost+=minedge_cost;
    }
    cout<<"Overall cost of MST: "<<tot_cost<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
