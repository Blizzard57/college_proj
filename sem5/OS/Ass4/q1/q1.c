#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <pthread.h>

typedef struct{
    int *arr;
    int left,right;
}args;

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

void normal_mergeSort(int arr[], int l, int r)  {  
    if (l < r) {  
        int m = l + (r - l) / 2;  
  
        normal_mergeSort(arr, l, m);  
        normal_mergeSort(arr, m + 1, r);  
  
        merge(arr, l, m, r);  
    }  
}

void *thread_mergesort(void *arg){
    args *val = (args *)arg;
    int len = (val->right - val->left + 1);
    if(len <= 5){
        insertionSort(val->arr+val->left,len);
        return 0;
    }

    args *arg1 = (args *)malloc(sizeof(args));
    arg1->arr = val->arr;
    arg1->left = val->left;
    arg1->right = val->left + (val->right - val->right)/2;

    args *arg2 = (args *)malloc(sizeof(args));
    arg2->arr = val->arr;
    arg2->left = val->left + (val->right - val->right)/2 + 1;
    arg2->right = val->right;
    
    pthread_t l_half,r_half;
    pthread_create(&l_half,NULL,thread_mergesort,(void *)arg1);
    pthread_create(&r_half,NULL,thread_mergesort,(void *)arg2);

    pthread_join(l_half,NULL);
    pthread_join(r_half,NULL);

    merge(val->arr,val->left,val->left + (val->right - val->right)/2,val->right);
    //return;
}

void printArray(int arr[],int size){
    for(int i=0;i<size;i++)
        printf("%d ",arr[i]);
    printf("\n");
}

void fillData(int arr[],int arr_size){
    for(int i=0;i<arr_size;i++) arr[i] = rand() % 10000;
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

    int template_arr[arr_size];
    for(int i=0;i<arr_size;i++) template_arr[i] = arr[i];

    //fillData(arr,arr_size);

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
        brr[i] = template_arr[i];

    st = ts.tv_nsec/(1e9)+ts.tv_sec;

    normal_mergeSort(brr,0,arr_size-1);
    printf("\nRunning normal mergesort for n = %d\n", arr_size);
    printf("The sorted array is :\n");
    printArray(brr,arr_size);

    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    en = ts.tv_nsec/(1e9)+ts.tv_sec;
    printf("time = %Lf\n", en - st);
    long double t2 = en - st;

    args *arg = (args *)malloc(sizeof(args));
    arg->arr = (int *)malloc(arr_size*sizeof(int));
    for(int i=0;i<arr_size;i++) arg->arr[i] = template_arr[i];
    arg->left = 0;
    arg->right = arr_size - 1;
    pthread_t main_id;
    pthread_create(&main_id,NULL,thread_mergesort,(void *)arg);
    printf("The threaded mergesort gave the following result\n");
    printArray(arg->arr,arr_size);

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