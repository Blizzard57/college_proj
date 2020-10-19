#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <wait.h>
#include <time.h>

void merge(int a[], int beg, int mid, int end) {      
    
    int tot=end-beg+1;
    int temp[tot];
    int i=beg, k=mid+1, m=0; 
    
    while (i<=mid && k<=end) { 
        if (a[i]<a[k]) 
            temp[m++]=a[i++]; 
        else if (a[k]<a[i]) 
            temp[m++]=a[k++]; 
        else if (a[i]==a[k]) { 
            temp[m++]=a[i++]; 
            temp[m++]=a[k++]; 
        } 
    } 
  
    while (i<=mid) 
        temp[m++]=a[i++]; 
  
    while (k<=end) 
        temp[m++]=a[k++]; 
  
    for (int i=0; i<tot; i++,beg++) 
        a[beg] = temp[i]; 
}

int insertionSort(int arr[],int len){
    int i,j,k; 
    for (i = 1; i < len; i++) { 
        k = arr[i]; 
        j = i-1; 
  
        while (j >= 0 && arr[j] > k) { 
            arr[j+1] = arr[j]; 
            j = j-1; 
        } 
        arr[j+1] = k; 
    } 
}

int concurrent_mergeSort(int arr[],int start,int end){
    int len = (end - start + 1);
    if(len <= 5){
        insertionSort(arr+start,len);
        return 0;
    }
    
    pid_t l_half,r_half;
    
    l_half = fork();
    if(l_half < 0){
        fprintf(stderr,"mergesort : could not fork\n");
        _exit(-1);
    }

    if(l_half == 0){
        concurrent_mergeSort(arr,start,start+len/2 - 1);
        _exit(0);
    }
    else{
        r_half = fork();
        if(r_half < 0){
            fprintf(stderr,"mergesort : could not fork\n");
            exit(-1);
        }
        
        if(r_half == 0){
            concurrent_mergeSort(arr,start + len/2,end);
            _exit(0);
        }
    }

    int stat;
    waitpid(l_half,&stat,0);
    waitpid(r_half,&stat,0);

    merge(arr,start,start + (end - start)/2,end);
    
    return 0;
}

void mergeSort(int arr[], int l, int r)  
{  
    if (l < r) {  
        int m = l + (r - l) / 2;  
  
        mergeSort(arr, l, m);  
        mergeSort(arr, m + 1, r);  
  
        merge(arr, l, m, r);  
    }  
}  

void printArray(int arr[],int size){
    for(int i=0;i<size;i++)
        printf("%d ",arr[i]);
    printf("\n");
}

int main(){
    int shm_id;
    int arr_size;
    printf("Enter size of array :\n");
    scanf("%d",&arr_size);

    shm_id = shmget(IPC_PRIVATE,arr_size*sizeof(int),IPC_CREAT | 0666);
    if(shm_id < 0){
        fprintf(stderr,"mergesort : could not create shared memort id\n");
        _exit(-1);
    }
    
    int *arr;
    arr = shmat(shm_id,NULL,0);
    if(arr == (int *)-1){
        fprintf(stderr,"mergesort : could not create shared memort array\n");
        _exit(-1);
    }

    printf("Enter the array :\n");
    for(int i=0;i<arr_size;i++)
        scanf("%d",&arr[i]);

    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);

    long double st = ts.tv_nsec/(1e9)+ts.tv_sec;

    concurrent_mergeSort(arr,0,arr_size-1);
    printf("\nRunning concurrent_mergesort for n = %d\n", arr_size);
    printf("The sorted array is :\n");
    printArray(arr,arr_size);

    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    long double en = ts.tv_nsec/(1e9)+ts.tv_sec;
    printf("time = %Lf\n", en - st);
    long double t1 = en - st;

    int brr[arr_size];
    for(int i=0;i<arr_size;i++)
        brr[i] = arr[i];

    st = ts.tv_nsec/(1e9)+ts.tv_sec;

    mergeSort(brr,0,arr_size-1);
    printf("\nRunning normal mergesort for n = %d\n", arr_size);
    printf("The sorted array is :\n");
    printArray(brr,arr_size);

    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    en = ts.tv_nsec/(1e9)+ts.tv_sec;
    printf("time = %Lf\n", en - st);
    long double t2 = en - st;

    printf("The normal mergesort is %Lf times quicker than concurrent mergesort\n",t2/t1);
    
    if(shmdt(arr) == -1){
        fprintf(stderr,"mergesort : error performing shmdt\n");
        _exit(-1);
    }

    if(shmctl(shm_id,IPC_RMID,NULL) == -1){
        fprintf(stderr,"mergesort : error performing shmctl\n");
        _exit(-1);
    }

    return 0;
}