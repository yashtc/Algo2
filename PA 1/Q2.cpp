/*
Question 2:
For this problem, use the same data set as in the previous problem.
Your task now is to run the greedy algorithm that schedules jobs (optimally) in decreasing order of the ratio (weight/length).
In this algorithm, it does not matter how you break ties.
You should report the sum of weighted completion times of the resulting schedule --- a positive integer --- in the box below. 
*/

#include <cstdlib>
#include <iostream>
#include <stdio.h>

using namespace std;

struct node
{
       int wt,len;
       float rat;
       node *left;
       node *right;
}*root;

void getInt(char *a, int n, int *wt, int *len)
{
     int i,j;
     char ab[10];
     for(i=0; a[i]!=' '; i++) ab[i]=a[i];
     ab[i]='\0';
     *wt=atoi(ab);
     for(j=0, i++; a[i]!='\n'; i++,j++) ab[j]=a[i];
     ab[j]='\0';
     *len=atoi(ab);
}

long long inorder(node *root)
{
     static long long swct;
     static long long time;
     if(root==NULL) return 0;
     inorder(root->left);
     time+=root->len;
     swct+=(root->wt*time);
     inorder(root->right);
     return swct;
}

int main(int argc, char *argv[])
{
    char a[50];
    FILE *f=fopen("jobs.txt","r");
    fgets(a,10,f);
    int no_jobs=atoi(a);
    int wt,len;
    root=new node;
    fgets(a,50,f);
    getInt(a,strlen(a),&wt,&len);
    root->wt=wt; root->len=len; root->rat=1.0*wt/len; root->left=NULL; root->right=NULL;
    while(fgets(a,50,f)!=NULL)
    {
            getInt(a,strlen(a),&wt,&len);
            node *nn=new node;
            nn->wt=wt; nn->len=len; nn->rat=1.0*wt/len; nn->left=NULL; nn->right=NULL;
            node *temp=root,*t2;
            while(temp!=NULL)
            {
                   t2=temp;
                   if(nn->rat<=temp->rat) temp=temp->right;
                   else temp=temp->left;
            }
            if(nn->rat<=t2->rat) t2->right=nn;
            else t2->left=nn;
    }
    cout<<"Sum of Weighted Completion Times: "<<inorder(root)<<endl;
    fclose(f);
    system("PAUSE");
    return EXIT_SUCCESS;
}