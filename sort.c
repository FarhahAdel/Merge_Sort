#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int n=0;
int * arr;
typedef struct {
  int low;
  int high;
}ARG;
//read from file
void readFile(){
  FILE *f1=fopen("input.txt","r");
  if(f1 == NULL)
     	  perror("Error!");
  fscanf(f1,"%d",&n);
  fscanf(f1,"\n");
  arr = malloc(n*sizeof(int));
  for(int i=0;i<n;i++)
    fscanf(f1,"%d",&arr[i]);
  fclose(f1);
}
//combine and sort
void merge(int low,int mid,int high)
{

 int n1= mid-low+1;
 int n2=high-mid;
 int buffer1[n1],buffer2[n2];

 for(int i=0;i<n1;i++)
    buffer1[i]=arr[low+i];
 
 for(int j=0;j<n2;j++)
    buffer2[j]=arr[mid+j+1];

 int i=0,j=0,k=low;
 while(i<n1 && j<n2){

    if(buffer1[i]<=buffer2[j]){
      arr[k]=buffer1[i];
      i++;}

    else{
      arr[k]=buffer2[j];
      j++;}

    k++;
 }

 while(i<n1){
  arr[k]=buffer1[i];
  i++;
  k++;
 }

 while(j<n2){
  arr[k]=buffer2[j];
  j++;
  k++;
 }
}
//divide array
void * merge_sort (void* args){
 ARG *arg2=(ARG *) args;
 int low=arg2->low, high=arg2->high;
 int mid=0;
 if(low<high){
 mid = (low+(high-1))/2;
 ARG arg3,arg4;
 arg3.low=low;
 arg3.high=mid;
 arg4.low=mid+1;
 arg4.high=high;
 pthread_t th1,th2;
 pthread_create(&th1,NULL,merge_sort,&arg3);
 pthread_create(&th2,NULL,merge_sort,&arg4);
 pthread_join(th1, NULL);
 pthread_join(th2, NULL);
 merge(arg2->low,mid,arg2->high);
 pthread_exit(NULL);
 }
}
int main(){

 readFile();
  //Priniting input array
 printf("**INPUT*** \n");
 for(int i=0;i<n;i++)
  printf("%d ",arr[i]);
 printf("\n");
 ARG arg1;
 arg1.low=0;
 arg1.high=n-1;
 pthread_t th0;
 pthread_create(&th0,NULL,merge_sort,&arg1);
 pthread_join(th0, NULL);
  //Priniting output array
 printf("**OUTPUT*** \n");
 for(int i=0;i<n;i++)
  printf("%d ",arr[i]);
 printf("\n");
 return 0;
}
