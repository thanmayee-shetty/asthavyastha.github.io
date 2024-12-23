#include<bits/stdc++.h>
using namespace std;
int a[10];
int p=10;
class msort
{
    public:
        int merge(int a[],int p);
        int mergesort(int b[],int c[],int a[],int p,int q);
        void display();
};
int msort::merge(int a[],int p)
{
    if(p<=1)
    {
        return 0;
    }
    int q=p/2;
    int b[q],c[p-q];
    for(int i=0;i<q;i++)
    {
        b[i]=a[i];
    }
    for(int i=q;i<p;i++)
    {
        c[i-q]=a[i];
    }
    merge(b,q);
    merge(c,p-q);
    mergesort(b,c,a,q,p-q);
}
int msort::mergesort(int b[],int c[],int a[],int p,int q)
{
    int i=0,j=0,k=0;
    while(i<p&&j<q)
    {
        if(b[i]<=c[j])
        {
            a[k]=b[i];
            i++;
        }
        else
        {
            a[k]=c[j];
            j++;
        }
        k++;
    }
    if(i==p)
    {
        while(j<q)
        {
            a[k]=c[j];
            j++;
            k++;
        }
    }
    else
    {
        while(i<p)
        {
            a[k]=b[i];
            i++;
            k++;
        }
    }
}
void msort::display()
{
    cout<<"sorted array:\n";
    for(int i=0;i<10;i++)
    {
        cout<<i<<":  "<<a[i]<<endl;
    }
}
int main()
{
    msort s;
    cout<<"Enter array elements:\n";
    for(int i=0;i<10;i++)
    {
        cout<<i<<":\t";
        cin>>a[i];
    }
    s.merge(a,p);
    s.display();
}