#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xmmintrin.h>
#include <x86intrin.h>
#include <sys/time.h>
#include <pthread.h>
#include "myblockmm.h"

struct thread_info
{
    int tid;
    double **a, **b, **c;
    int array_size;
    int number_of_threads;
    int n;
};
void *mythreaded_vector_blockmm(void *t);

char name[128];
char SID[128];
#define VECTOR_WIDTH 4
void my_threaded_vector_blockmm(double **a, double **b, double **c, int n, int ARRAY_SIZE, int number_of_threads)
{
  int i=0;
  pthread_t *thread;
  struct thread_info *tinfo;
  strcpy(name,"Please replace this with your name!");
  strcpy(SID,"Please replace this with your SID!");
  thread = (pthread_t *)malloc(sizeof(pthread_t)*number_of_threads);
  tinfo = (struct thread_info *)malloc(sizeof(struct thread_info)*number_of_threads);

  for(i = 0 ; i < number_of_threads ; i++)
  {
    tinfo[i].a = a;
    tinfo[i].b = b;
    tinfo[i].c = c;
    tinfo[i].tid = i;
    tinfo[i].number_of_threads = number_of_threads;
    tinfo[i].array_size = ARRAY_SIZE;
    tinfo[i].n = n;
    pthread_create(&thread[i], NULL, mythreaded_vector_blockmm, &tinfo[i]);
  }  
  for(i = 0 ; i < number_of_threads ; i++)
    pthread_join(thread[i], NULL);

  return;
}

#define VECTOR_WIDTH 4
void *mythreaded_vector_blockmm(void *t)
{
  int i,j,k, ii, jj, kk, x;
  __m256d va, vb, vc;
  struct thread_info tinfo = *(struct thread_info *)t;
  int number_of_threads = tinfo.number_of_threads;
  int tid =  tinfo.tid;
  double **a = tinfo.a;
  double **b = tinfo.b;
  double **c = tinfo.c;
  int ARRAY_SIZE = tinfo.array_size;
  int n = tinfo.n;
    for(i = 0; i < ARRAY_SIZE; i+=(ARRAY_SIZE/n))
    {
        for(j = 0; j < ARRAY_SIZE; j+=(ARRAY_SIZE/n))
        {
            for(k = 0; k < ARRAY_SIZE; k+=(ARRAY_SIZE/n))
            {
                for(ii = i; ii < i+(ARRAY_SIZE/n)&& ii<ARRAY_SIZE; ii++)
                {
                    for(jj = j; jj < j+(ARRAY_SIZE/n)&& jj<ARRAY_SIZE; jj++)
                    {
                       register int indC00=ii*ARRAY_SIZE+jj;
                        //register int indC10=indC00+ARRAY_SIZE;
                     //   register double reg1=c[indC00/ARRAY_SIZE][indC00%ARRAY_SIZE],reg2=c[(indC00+1)/ARRAY_SIZE][(indC00+1)%ARRAY_SIZE],reg3=c[(indC10)/ARRAY_SIZE][(indC10)%ARRAY_SIZE],reg4=c[(indC10+1)/ARRAY_SIZE][(indC10+1)%ARRAY_SIZE];
                    
                       register double res=c[ii][jj]
                        for(kk = k; kk < k+(ARRAY_SIZE/n) && kk<ARRAY_SIZE; kk++)
                        
                            res+=a[ii][kk]*b[kk][jj];
                        c[ii][jj]=res;
//                        register int indA00=ii*ARRAY_SIZE+kk,indB00=kk*ARRAY_SIZE+jj;
//                        register int indA10=indA00+ARRAY_SIZE,indB10=indB00+ARRAY_SIZE;
//                        register double a00=a[indA00/ARRAY_SIZE][indA00%ARRAY_SIZE],a01=a[(indA00+1)/ARRAY_SIZE][(indA00+1)%ARRAY_SIZE],a10=a[indA10/ARRAY_SIZE][indA10%ARRAY_SIZE],a11=a[(indA10+1)/ARRAY_SIZE][(indA10+1)%ARRAY_SIZE];
//                          register double b00=b[indB00/ARRAY_SIZE][indB00%ARRAY_SIZE],b01=b[(indB00+1)/ARRAY_SIZE][(indB00+1)%ARRAY_SIZE],b10=b[indB10/ARRAY_SIZE][indB10%ARRAY_SIZE],b11=b[(indB10+1)/ARRAY_SIZE][(indB10+1)%ARRAY_SIZE];
//                         reg1+=a00*b00+a01*b10;
//                         reg2+=a00*b01+a01*b11;
//                         reg3+=a10*b00+a11*b10;
//                         reg4+=a10*b01+a11*b11;

                         
     
//                        c[indC00/ARRAY_SIZE][indC00%ARRAY_SIZE]=reg1;
//                         c[(indC00+1)/ARRAY_SIZE][(indC00+1)%ARRAY_SIZE]=reg2;
//                        c[(indC10)/ARRAY_SIZE][(indC10)%ARRAY_SIZE]=reg3;
//                         c[(indC10+1)/ARRAY_SIZE][(indC10+1)%ARRAY_SIZE]=reg4;
                    }
                }
            }
        }
    }
}


