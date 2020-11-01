#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
    int id;
    int no_times; // No of times the person is vaccinated
}Student;

typedef struct{
    int k; /* no of students for that vaccination : formulae k = min(8,no of vaccines left, no of students) */
    int no_vac; // no of vaccines currently in the zone : no_vac \in [0,p]
}Zone;

typedef struct{
    int w; // time taken to prepare vaccine : w \in [2,5]
    int r; // no of batches produced : r \in [1,5]
    int p; // no of vaccines per batches : p \in [10,20]
    int prob; // probability of success of each batches
}Pharma;

Pharma* pharmas;
Zone* zones;
Student* students;
int *pharma_prob;
/* as students[i].mutex is not global, this is required */
pthread_mutex_t *pharma_mutex, *zone_mutex;

void initialize(int n,int m,int o){
    students = (Student *)malloc(o*sizeof(Student));

    /* each pharma has a mutex it can lock */
    pharmas = (Pharma *)malloc(n*sizeof(Pharma));
    pharma_mutex = (pthread_mutex_t *)malloc(n*sizeof(pthread_mutex_t));
    for(int i=0;i<n;i++) pthread_mutex_init(&pharma_mutex[i],NULL);

    /* each zone has a mutex it can lock */
    zones = (Zone *)malloc(m*sizeof(Zone));
    zone_mutex = (pthread_mutex_t *)malloc(n*sizeof(pthread_mutex_t));
    for(int i=0;i<m;i++) pthread_mutex_init(&zone_mutex[i],NULL);

    return;
}

void *operation_student(void *args){

}

void *operation_pharma(void *args){

}

int main(){
    int n,m,o;
    scanf("%d %d %d",&n,&m,&o);
    
    pharma_prob = (int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++) scanf("%d",&pharma_prob[i]);

    if(o < 1){
        printf("No students, hence drive ended\n");
        return 0;
    }
    if(m < 1){
        printf("No vaccination zones, hence drive ended\n");
        return 0;
    }
    if(n < 1){
        printf("No pharmaceutical companies, hence drive ended\n");
        return 0;
    }

    initialize(n,m,o);

    pthread_t *student_threads = (pthread_t *)malloc(o*sizeof(pthread_t));
    for(int i=0;i<o;i++) pthread_create(&student_threads[i],NULL,operation_student,(void *)i);
}