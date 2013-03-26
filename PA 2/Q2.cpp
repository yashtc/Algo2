/*
Question 2:
In this question your task is again to run the clustering algorithm from lecture, but on a MUCH bigger graph.
So big, in fact, that the distances (i.e., edge costs) are only defined implicitly, rather than being provided as an explicit list.

The data set is here. The format is:
[# of nodes] [# of bits for each node's label]
[first bit of node 1] ... [last bit of node 1]
[first bit of node 2] ... [last bit of node 2]
...
For example, the third line of the file "0 1 1 0 0 1 1 0 0 1 0 1 1 1 1 1 1 0 1 0 1 1 0 1" denotes the 24 bits associated with node #2.

The distance between two nodes u and v in this problem is defined as the Hamming distance--- the number of differing bits --- between the two nodes' labels.
For example, the Hamming distance between the 24-bit label of node #2 above and the label "0 1 0 0 0 1 0 0 0 1 0 1 1 1 1 1 1 0 1 0 0 1 0 1" is 3 (since they differ in the 3rd, 7th, and 21st bits).

The question is: what is the largest value of k such that there is a k-clustering with spacing at least 3?
That is, how many clusters are needed to ensure that no pair of nodes with all but 2 bits in common get split into different clusters?

NOTE: The graph implicitly defined by the data file is so big that you probably can't write it out explicitly, let alone sort the edges by cost.
So you will have to be a little creative to complete this part of the question.
For example, is there some way you can identify the smallest distances without explicitly looking at every pair of nodes?
*/

#include <cstdlib>
#include <iostream>
#include <stdio.h>

using namespace std;

void getInt(char *a, int n, int *val1, int *val2)
{
     int i,j;
     char ab[10];
     for(i=0; a[i]!=' '; i++) ab[i]=a[i];
     ab[i]='\0';
     *val1=atoi(ab);
     for(j=0, i++; a[i]!='\n'; i++,j++) ab[j]=a[i];
     ab[j]='\0';
     *val2=atoi(ab);
}

int main(int argc, char *argv[])
{
    int no_nodes,bits;
    char a[15];
    FILE *f=fopen("clustering2.txt","r");
    fgets(a,15,f);
    getInt(a,strlen(a),&no_nodes,&bits);
    char** nodes=new char*[no_nodes];
    int *node_clus=new int[no_nodes];
    int *node_ones=new int[no_nodes];
    for(int i=0; i<no_nodes; i++)
    {
            node_clus[i]=i;
            node_ones[i]=0;
            nodes[i]=new char[55];
            fgets(nodes[i],55,f);
            for(int j=0; j<strlen(nodes[i]); j+=2) if(nodes[i][j]=='1') node_ones[i]++;
    }
    fclose(f);
    int no_of_clus=no_nodes;
    for(int i=0; i<no_nodes; i++)
    {
            int curr_clus=node_clus[i], ones=node_ones[i];
            for(int j=0; j<no_nodes; j++)
            if(node_clus[j]!=curr_clus && ( ( (ones-node_ones[j]>=0) && (ones-node_ones[j]<3) ) || ( (node_ones[j]-ones>=0) && (node_ones[j]-ones<3) ) ) )
            {
                   int count=0;
                   for(int k=0; (k<bits*2) && (count<3); k+=2)
                   if(nodes[i][k]!=nodes[j][k]) count++;
                   if(count<3)
                   {
                              int old_clus=node_clus[j];
                              for(int t=0; t<no_nodes; t++)
                              if(node_clus[t]==old_clus)
                              node_clus[t]=curr_clus;
                              no_of_clus--;
                   }
            }
    }
    cout<<"Largest value of k: "<<no_of_clus<<endl;
    system("PAUSE");
    return EXIT_SUCCESS;
}
