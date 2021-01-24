#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quicksort(int arr[], int low, int high){
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int *merge(int *v1, int n1, int *v2, int n2){
    int i = 0,j = 0,k = 0;
    int *result = (int *)malloc((n1 + n2) * sizeof(int));
    
    while (k < n1 + n2){
        if (i >= n1)
            result[k] = v2[j++];
        else if (j >= n2)
            result[k] = v1[i++];
        else if (v1[i] < v2[j])
            result[k] = v1[i++];
        else
            result[k] = v2[j++];
        k++;
    }
    return result;
}

int main(int argc, char **argv)
{
    int tot_num,chunk_size,curr_size,other_size;
    int step, num_proc, id;
    int *data = NULL;
    int *chunk;
    int *other;
    MPI_Status status;

    FILE * file = NULL;
    int root_process = 0;
    double time;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    if (id == root_process){
        file = fopen(argv[1],"r");
        fscanf(file,"%d", &tot_num);

        if (tot_num % num_proc != 0)
            chunk_size = tot_num / num_proc + 1;
        else
            chunk_size = tot_num / num_proc;

        data = (int *)calloc(num_proc * chunk_size,sizeof(int));
        for (int i = 0; i < tot_num; i++)
            fscanf(file,"%d", &data[i]);
        fclose(file);
    }

    time = - MPI_Wtime();
    MPI_Bcast(&tot_num, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(tot_num % num_proc != 0) 
        chunk_size = tot_num / num_proc + 1;
    else 
        chunk_size = tot_num / num_proc;

    chunk = (int *)calloc(chunk_size,sizeof(int));
    MPI_Scatter(data, chunk_size, MPI_INT, chunk, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    if(tot_num >= chunk_size * (id + 1)) 
        curr_size = chunk_size;
    else 
        curr_size = tot_num - chunk_size * id;

    quicksort(chunk, 0, curr_size);
    free(data);
    data = NULL;

    step = 1;
    while(step < num_proc){
        if (id % (2 * step) != 0){
            MPI_Send(chunk, curr_size, MPI_INT, id - step, 0, MPI_COMM_WORLD);
            break;
        }
        if (id + step < num_proc){

            if(tot_num >= chunk_size * (id + 2 * step)) 
                other_size = chunk_size * step; 
            else 
                other_size = tot_num - chunk_size*id - chunk_size*step;

            other = (int *)calloc(other_size,sizeof(int));
            MPI_Recv(other, other_size, MPI_INT, id + step, 0, MPI_COMM_WORLD, &status);

            data = merge(chunk, curr_size, other, other_size);
            chunk = data;
            curr_size += other_size;
        }
        step *= 2;
    }

    time += MPI_Wtime();

    if (id == root_process){
        file = fopen(argv[2],"w");
        for (int i = 0; i < curr_size - 1; i++)
            fprintf(file,"%d ", chunk[i]);
        fprintf(file,"%d\n", chunk[curr_size - 1]);
        fclose(file);
        printf("The time taken is : %f seconds.\n",time);
    }

    MPI_Finalize();
    return 0;
}