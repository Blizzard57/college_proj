#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define max_number 100000

int main(int argc, char **argv){

    MPI_Status status;

    long double sum, partial_sum;
    int ierr, sender, num_rows_received;
    int my_id, an_id, root_process;
    int start, end, avg_rows_per_process,start_num;
    int tot_num, num_procs, tot_send, tot_recv;

    FILE * file = NULL;
    root_process = 0;
    double time;

    ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    int i;
    if (my_id == root_process){
        file = fopen(argv[1],"r");
        fscanf(file,"%i", &tot_num);
        fclose(file);

        if (tot_num > max_number){
            printf("Numbers exceed the given limit.\n");
            exit(1);
        }
        time = - MPI_Wtime();

        avg_rows_per_process = tot_num / num_procs;
        if(avg_rows_per_process < 1)
            avg_rows_per_process = 1;
        
        for (an_id = 1; an_id < num_procs; an_id++){
            
            start = an_id * avg_rows_per_process + 1;
            end = (an_id + 1) * avg_rows_per_process;

            if (tot_num < avg_rows_per_process + end)
                end = tot_num - 1;

            tot_send = end - start + 1;

            ierr = MPI_Send(&tot_send, 1, MPI_INT,
                            an_id, 0, MPI_COMM_WORLD);

            ierr = MPI_Send(&start, 1, MPI_INT,
                            an_id, 0, MPI_COMM_WORLD);
        }

        sum = 0.0;
        for (i = 0; i < avg_rows_per_process + 1; i++)
            sum += 1.0/((i+1)*(i+1));

        for (an_id = 1; an_id < num_procs; an_id++){

            ierr = MPI_Recv(&partial_sum, 1, MPI_LONG_DOUBLE, MPI_ANY_SOURCE,
                            1, MPI_COMM_WORLD, &status);

            sender = status.MPI_SOURCE;
            sum += partial_sum;
        }

        time += MPI_Wtime();

        file = fopen(argv[2],"w");
        fprintf(file,"%Lf\n", sum);

        printf("The time taken is : %f seconds.\n",time);
    }

    else{
        ierr = MPI_Recv(&tot_recv, 1, MPI_INT,
                        root_process, 0, MPI_COMM_WORLD, &status);

        ierr = MPI_Recv(&start_num, 1, MPI_INT,
                        root_process, 0, MPI_COMM_WORLD, &status);

        num_rows_received = tot_recv;

        partial_sum = 0;
        for (i = start_num; i < num_rows_received + start_num; i++)
            partial_sum += (double) 1.0/((i+1)*(i+1));

        ierr = MPI_Send(&partial_sum, 1, MPI_LONG_DOUBLE, root_process,
                        1, MPI_COMM_WORLD);
    }
    ierr = MPI_Finalize();
}
