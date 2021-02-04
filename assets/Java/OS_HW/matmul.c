// If the comments are hard to read because of the color,
// type ':set background=dark'

/***
	This program multiplies two matrics.
		Usage: ./a.out <row> <col> <# of threads>

	[Mission] Implement the multi-threaded version of MatrixMul() by completing the following two functions at the end of this file.
	
	// multiply matricx using multiple threads	
	void MatrixMul_MT(Matrix *mat1, Matrix *mat2, Matrix *res, int no_thread);
	// thread function for MatrixMul_MT
	void* MatrixMul_Thread(void *vparam);


	Example) Results on a 4 cores 8 threads CPU varying with the number of threads
		$ gcc matmul_solution.c -pthread			// compilation

		// Note the execution time!
		$ ./a.out 200 200 1
		Multipying 200 x 200 matrics using 1 threads
		computing time = 0 sec 120387 microsec		// slowest
		$ ./a.out 200 200 2
		Multipying 200 x 200 matrics using 2 threads
		computing time = 0 sec 60960 microsec
		$ ./a.out 200 200 4
		Multipying 200 x 200 matrics using 4 threads
		computing time = 0 sec 44943 microsec
		$ ./a.out 200 200 8
		Multipying 200 x 200 matrics using 8 threads
		computing time = 0 sec 31111 microsec		// fastest
		$ ./a.out 200 200 12
		Multipying 200 x 200 matrics using 12 threads
		computing time = 0 sec 38302 microsec
		$ ./a.out 200 200 16
		Multipying 200 x 200 matrics using 16 threads
		computing time = 0 sec 36914 microsec

	Compile with -pthread flag
		Ex) gcc matmul.c -pthread

***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>


// Uncomment the next line after completing the MatrixMul_MT()
#define	__MultiThread__

typedef struct {
	int row, col;
	float *data;
} Matrix;


void CreateMatrix(Matrix *mat, int row, int col);
void DeleteMatrix(Matrix *mat);
void DisplayMatrix(Matrix *mat, char *mesg);

void FillMatrixRowMajor(Matrix *mat);
void FillMatrixColumnMajor(Matrix *mat);

// matrix multiplication (single-threaded version)
void MatrixMul(Matrix *mat1, Matrix *mat2, Matrix *res);

// matrix multiplication (multi-threaded version)
void MatrixMul_MT(Matrix *mat1, Matrix *mat2, Matrix *res, int no_thread);

int main(int argc, char *argv[])
{
	if(argc < 4){
		printf("Usage: %s <row> <col> <# of threads>\n", argv[0]);
		return -1;
	}
	int row = atoi(argv[1]);
	int col = atoi(argv[2]);
	int no_thread = atoi(argv[3]);
	printf("Multipying %d x %d matrics using %d threads\n", row, col, no_thread);

	Matrix matA = { 0 };
	Matrix matB = { 0 };
	Matrix product = { 0 };

	CreateMatrix(&matA, row, col);
	FillMatrixRowMajor(&matA);
	if(row < 20 && col < 20)
		DisplayMatrix(&matA, "A = ");

	CreateMatrix(&matB, col, row);
	FillMatrixColumnMajor(&matB);
	if(row < 20 && col < 20)
		DisplayMatrix(&matB, "B = ");

	CreateMatrix(&product, row, row);

	struct timeval start_time, end_time;
	gettimeofday(&start_time, NULL);

// Don't forget to uncomment '#define __MultiThread__' after completing MatrixMul_MT()

#ifdef	__MultiThread__
	MatrixMul_MT(&matA, &matB, &product, no_thread);
#else	__MultiThread__
	MatrixMul(&matA, &matB, &product);
#endif	__MultiThread__

	gettimeofday(&end_time, NULL);
	end_time.tv_sec -= start_time.tv_sec;
	end_time.tv_usec -= start_time.tv_usec;
	if(end_time.tv_usec < 0){	// handle carry
		end_time.tv_sec--;
		end_time.tv_usec += 1000000;
	}

	if(row < 20 && col < 20)
		DisplayMatrix(&product, "A x B = ");
	printf("computing time = %ld sec %ld microsec\n", end_time.tv_sec, end_time.tv_usec);

	DeleteMatrix(&matA);
	DeleteMatrix(&matB);
	DeleteMatrix(&product);

	return 0;
}

void CreateMatrix(Matrix *mat, int row, int col)
{
	if(mat->data)
		free(mat->data);
	
	mat->data = malloc(row * col * sizeof(float));
	if(mat->data == NULL){
		printf("Failed to allocate memory in %s.\n", __FUNCTION__);
		mat->row = mat->col = 0;
		return;
	}

	memset(mat->data, 0, row * col * sizeof(float));

	mat->row = row;
	mat->col = col;
}

void DeleteMatrix(Matrix *mat)
{
	if(mat){
		free(mat->data);
		mat->row = mat->col = 0;
	}
}

void DisplayMatrix(Matrix *mat, char *mesg)
{
	if(mesg != NULL)
		printf("%s\n", mesg);

	printf("%d x %d matrix:\n", mat->row, mat->col);

	for(int i = 0; i < mat->row; i++){
		for(int j = 0; j < mat->col; j++)
			printf("%5.1f ", mat->data[i * mat->col + j]);
		printf("\n");
	}
}

void FillMatrixRowMajor(Matrix *mat)
{
	int n = 1;

	for(int i = 0; i < mat->row; i++){
		for(int j = 0; j < mat->col; j++)
			mat->data[i * mat->col + j] = (float)n++;
	}
}

void FillMatrixColumnMajor(Matrix *mat)
{
	int n = 1;

	for(int j = 0; j < mat->col; j++){
		for(int i = 0; i < mat->row; i++)
			mat->data[i * mat->col + j] = (float)n++;
	}
}

// single-threaded matrix multiplication
void MatrixMul(Matrix *mat1, Matrix *mat2, Matrix *res)
{
	for(int i = 0; i < mat1->row; i++){
		for(int j = 0; j < mat2->col; j++){
			float sum = 0.F;
			for(int k = 0; k < mat1->col; k++)
				sum += mat1->data[i * mat1->col + k] * mat2->data[k * mat2->col + j];
			res->data[i * res->col + j] = sum;
		}
	}
}

#ifdef	__MultiThread__

typedef struct {
	// TO DO: fill out this structure
    Matrix *mat1;
    Matrix *mat2;
    Matrix *res;

    int thread_idx;
    int no_thread;

} ThreadParam;

void* MatrixMul_Thread(void *vparam);

void MatrixMul_MT(Matrix *mat1, Matrix *mat2, Matrix *res, int no_thread)
{
	// TO DO: fill out this function
	// DO NOT use global variables
    int t = 0;
    pthread_t tid[no_thread];
    ThreadParam param[no_thread];

    //parameter setting
    for(t=0; t < no_thread; t++)
    {   
        param[t].mat1 = mat1;
        param[t].mat2 = mat2;
        param[t].res = res;
        param[t].thread_idx = t;
        param[t].no_thread = no_thread;
    }
    //launch threads
    for(t=0; t < no_thread; t++)
    {
        pthread_create(&tid[t], NULL, MatrixMul_Thread, &param[t]);
    }
    //join threads
    for(t=0; t < no_thread; t++)
    {
        pthread_join(tid[t], NULL);
    }

}

void* MatrixMul_Thread(void *vparam)
{
    ThreadParam *param = (ThreadParam*)vparam;
    Matrix *mat1 = param->mat1;
    Matrix *mat2 = param->mat2;
    Matrix *res = param->res;
	// TO DO: fill out this function
    for(int i = param->thread_idx; i < mat1->row; i += param->no_thread){
		for(int j = 0; j < mat2->col; j++){
			float sum = 0.F;
			for(int k = 0; k < mat1->col; k++)
				sum += mat1->data[i * mat1->col + k] * mat2->data[k * mat2->col + j];
			res->data[i * res->col + j] = sum;
		}
	}
	return NULL;
}

#endif	//	__MultiThread__
