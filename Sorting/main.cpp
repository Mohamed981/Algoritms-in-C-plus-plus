#include <iostream>
#include <time.h>
#include<fstream>
#include <bits/stdc++.h>

using namespace std;
#ifndef BUBBLE
void bubble(int *arr,int n){
    int i,j;

    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1])
                swap(arr[j],arr[j+1]);
        }
    }


}
#endif // BUBBLE
#ifndef SELECTION
void selection(int *arr,int n){
    int i,j,imin;
    for(i=0;i<n;i++){
            imin=i;
        for(j=i+1;j<n;j++){
        if(arr[j]<arr[imin])
        imin=j;

    }
    if(imin!=j)
            swap(arr[i],arr[imin]);
    }
}
#endif // SELECTION
#ifndef INSERTION
void insertion(int *arr,int n){
    int i,j,current,s;
    for(i=1;i<n;i++){
            current=arr[i];
            j=i;
            while(arr[j-1]>current&&j>0){
                    s=arr[j];
                arr[j]=arr[j-1];
                j--;

            }arr[j]=current;
}

}
#endif // INSERTION
#ifndef merge

void merge1(int*arr,int l,int middle,int r){

    int i,j,L[middle-l],R[r-middle],k;

    for(i=0;i<middle;i++){
        L[i]=arr[i+l];
        cout<<L[i]<<" ";
    }
    cout<<"\n";
    for(i=0;i<r-middle;i++){
        R[i]=arr[i+middle];
        cout<<R[i]<<" ";
    }

    i=0;
    j=0;

    for(k=l;k<=r;k++){
        if(L[i]<R[j]){
            arr[k]=L[i];
            i++;
        }else{
            arr[k]=R[j];
            j++;
        }
    }



}

void mergesort(int*arr,int l,int r){
    int i;
    int middle;
    if(r>l){
       middle=(l+r)/2;
    mergesort(arr,l,middle);
    mergesort(arr,middle+1,r);
    merge1(arr,l,middle,r);
    }
}
#endif
void print(int*arr){
    int i;
    cout<<"\n";
    for(i=0;i<10;i++)
    cout<<arr[i]<<" ";

}

int main()
{
    int i=0,j;
    int arr1[]={5,2,7,3,9,8,1,10,6,11};
    int arr2[]={5,3,1,4,2};
    clock_t t;



ifstream myfile1,myfile2,myfile3;

  char output[100];
  int a[1000],b[1000],c[1000]; //Temp arrays
#ifndef BUBBLE

 //Opening the files
myfile1.open ("best.txt");
myfile2.open("worst.txt");
myfile3.open("average.txt");

//Read data from the files
 while (!myfile1.eof()||!myfile2.eof()||!myfile3.eof()) {
if (myfile1.is_open())
    myfile1 >> a[i];

    if (myfile2.is_open())
    myfile2 >> b[i];

    if (myfile3.is_open())
    myfile3 >> c[i];

    i++;
 }
i=0;

myfile1.close();
myfile2.close();
myfile3.close();

cout<<"BUBBLE"<<"\n";
    t = clock();
    bubble(a,1000);
    t = clock() - t;
   double time_taken = ((double)t)/CLOCKS_PER_SEC;

  cout<<"BEST:"<<time_taken<<setprecision(5)<<"\n";
   t = clock();
    bubble(b,1000);
    t = clock() - t;
   time_taken = ((double)t)/CLOCKS_PER_SEC;
  cout<<"WORST:"<<time_taken<<setprecision(5)<<"\n";
   t = clock();
    bubble(c,1000);
    t = clock() - t;
   time_taken = ((double)t)/CLOCKS_PER_SEC;


   cout<<"AVERAGE:"<<time_taken<<setprecision(5)<<"\n";
#endif // BUBBLE
#ifndef SELECTION
myfile1.open ("best.txt");
myfile2.open("worst.txt");
myfile3.open("average.txt");

while (!myfile1.eof()||!myfile2.eof()||!myfile3.eof()) {
if (myfile1.is_open())
    myfile1 >> a[i];

    if (myfile2.is_open())
    myfile2 >> b[i];

    if (myfile3.is_open())
    myfile3 >> c[i];

    i++;

 }
i=0;
myfile1.close();
  myfile2.close();
  myfile3.close();

cout<<"\nSELECTION"<<"\n";

    t = clock();
    selection(a,1000);
    t = clock() - t;
   time_taken = ((double)t)/CLOCKS_PER_SEC;
  cout<<"BEST:"<<time_taken<<setprecision(5)<<"\n";
   t = clock();
    selection(b,1000);
    t = clock() - t;
   time_taken = ((double)t)/CLOCKS_PER_SEC;
  cout<<"WORST:"<<time_taken<<setprecision(5)<<"\n";
   t = clock();
    selection(c,1000);
    t = clock() - t;
   time_taken = ((double)t)/CLOCKS_PER_SEC;


   cout<<"AVERAGE:"<<time_taken<<setprecision(5)<<"\n";
#endif // SELECTION
#ifndef INSERTION
myfile1.open ("best.txt");
myfile2.open("worst.txt");
myfile3.open("average.txt");
while (!myfile1.eof()||!myfile2.eof()||!myfile3.eof()) {
if (myfile1.is_open())
    myfile1 >> a[i];

    if (myfile2.is_open())
    myfile2 >> b[i];

    if (myfile3.is_open())
    myfile3 >> c[i];

    i++;

 }i=0;
myfile1.close();
myfile2.close();
myfile3.close();

     cout<<"\nINSERTION"<<"\n";

    t = clock();
    insertion(a,1000);
    t = clock() - t;
   time_taken = ((double)t)/CLOCKS_PER_SEC;
  cout<<"BEST:"<<time_taken<<setprecision(5)<<"\n";
   t = clock();
    insertion(b,1000);
    t = clock() - t;
   time_taken = ((double)t)/CLOCKS_PER_SEC;
  cout<<"WORST:"<<time_taken<<setprecision(5)<<"\n";
   t = clock();
    insertion(c,1000);
    t = clock() - t;
   time_taken = ((double)t)/CLOCKS_PER_SEC;


   cout<<"AVERAGE:"<<time_taken<<setprecision(5)<<"\n";
#endif // INSERTION
#ifndef MERGE



#endif // MERGE
    return 0;
}
