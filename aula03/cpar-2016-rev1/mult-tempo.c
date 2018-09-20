/* --- Arquivo : mult-tempo.c --- */

/* --- inicializacao () --- */
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
typedef struct {pthread_mutex_t sem; int ativado;} Event;
#define Semaph sem_t
#include "type_mult-tempo.h"  /* typedef's */
#include "vgp_mult-tempo.h"   /* global privada*/
#include "vsl_mult-tempo.h"   /* shared local  */
#include "partask_mult-tempo.h"
#define _MAX_THREADS_ 100
#define get_mi_id() get_mi_id(_cpar_id_thread_)
pthread_t **_cpar_tid_;
int *_cpar_task_nthreads_;
extern int *_cpar_sec_parbegin_ ;
extern int *_cpar_count_bar_ ;
extern int *_cpar_count_end_bar_ ;
extern int *_cpar_end_barrier_;
int _cpar_id_task_;
extern int _cpar_num_tasks_;

extern int *_cpar_task_wait_flag_;

extern pthread_mutex_t *_cpar_create_task_flag_;

extern pthread_mutex_t _cpar_mutex_create_thread_ ;

extern pthread_mutex_t *_cpar_mutex_task_flag_ ;

extern pthread_mutex_t *_cpar_mutex_parbegin_ ;

extern pthread_mutex_t *_cpar_mutex_ ;

extern pthread_mutex_t *_cpar_mutex2_ ;

extern pthread_mutex_t *_cpar_mutex3_ ;

extern pthread_mutex_t *_cpar_mutex_bar_ ;

gl_priv *glbpriv;

extern int id_thread_global_next;

typedef struct {unsigned long int tid;int id_thread;struct type_next_id_thread *next;} type_next_id_thread;

typedef struct {unsigned long int tid;int id_thread;type_next_id_thread *next_id_thread;}type_list_id_thread;

extern type_list_id_thread list_thread[1000];

#include "cob_mult-tempo.h"
/* #define IMPRIME 1 */
/*multiplicacao de matrizes: outer-product*/
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include "mede_time.h"
   int SIZE;

   double a[2000][2000];

   double b[2000][2000];

   double c[2000][2000];

/*inicia matriz*/
void *init_matrix (void * arg);   /* --- spec () */
/* -- rs400() : definicao de task  */
void *init_matrix (void * arg) 
{
int i, j, k;

   _cpar_arg_task_0_ *_cpar_arg_t_;
   int _cpar_id_thread_;
   int _cpar_numthreads_;
   int _cpar_id_task_;
   _cpar_id_task_=0;
   _cpar_arg_t_= (_cpar_arg_task_0_ *)arg;
   _cpar_id_thread_=_cpar_arg_t_->id_thread;
   _cpar_numthreads_=_cpar_arg_t_->numthreads;
   int _id_thread_;
   insert_id_thread();
   _id_thread_=get_id_thread_gl();

   if (_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_))
   {
             };

      end_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_);

{
   int i_, n_;
   n_ = ((SIZE-1) - 0 + 1) / _cpar_numthreads_;
   if ((((SIZE-1) - 0 + 1) % _cpar_numthreads_) != 0)
      n_++;
   i_ = 0 + _cpar_id_thread_ * n_;

   for (i = i_; ((i < (i_ + n_)) && (i <= (SIZE-1))); i++) {  
       for (j=0;j<SIZE;j++){
         a[i][j]=1.0;
         b[i][j]=1.0;
         c[i][j]=(double)0.0;
       }
      }
}
     if (_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_))  /* --- forall () */
  {

  
   }
   end_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_);
   rm_thread_conflict();
}

/*multiplicacao*/
void *mat_mul (void * arg);   /* --- spec () */
/* -- rs400() : definicao de task  */
void *mat_mul (void * arg) 
{
int i, j, k, cont;

   _cpar_arg_task_1_ *_cpar_arg_t_;
   int _cpar_id_thread_;
   int _cpar_numthreads_;
   int _cpar_id_task_;
   _cpar_id_task_=1;
   _cpar_arg_t_= (_cpar_arg_task_1_ *)arg;
   _cpar_id_thread_=_cpar_arg_t_->id_thread;
   _cpar_numthreads_=_cpar_arg_t_->numthreads;
   int _id_thread_;
   insert_id_thread();
   _id_thread_=get_id_thread_gl();

   if (_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_))
   {
             };

      end_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_);

{
   int i_, n_;
   n_ = ((SIZE-1) - 0 + 1) / _cpar_numthreads_;
   if ((((SIZE-1) - 0 + 1) % _cpar_numthreads_) != 0)
      n_++;
   i_ = 0 + _cpar_id_thread_ * n_;

   for (i = i_; ((i < (i_ + n_)) && (i <= (SIZE-1))); i++) {
        for (k=0;k<SIZE;k++) 
          for (j=0;j<SIZE;j++)
            c[i][j]=c[i][j]+a[i][k]*b[k][j];
      }
}
     if (_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_))  /* --- forall () */
  {

  
   }
   end_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_);
   rm_thread_conflict();
}

/*imprime matriz */
print_mat(a)
double a[2000][2000];
{
int i, j;


int _id_thread_=get_id_thread_gl();

   for (i=0;i<SIZE;i++){
       for (j=0;j<SIZE;j++)
         printf (" %10.2f", a[i][j]);
       puts ("");
      }
      puts ("");
   }

/*imprime resultado*/
print_mats(a, b, c)
double a[2000][2000], b[2000][2000], c[2000][2000];
{

int _id_thread_=get_id_thread_gl();

   puts ("Matriz A");
      print_mat (a);

      puts ("Matriz B");
      print_mat (b);

      puts ("Matriz C");
      print_mat (c);
   }

main(argc, argv)
int argc;
char **argv;
{
int nprocs;


int _id_thread_,_i_;

int _cpar_id_thread_;
for (_i_=0;_i_<1000;_i_++)

   list_thread[_i_].id_thread = -1;

insert_id_thread();

_id_thread_=get_id_thread_gl();

  _cpar_arg_task_0_ *_cpar_arg_0_;

  _cpar_arg_task_1_ *_cpar_arg_1_;

  _cpar_num_tasks_=2;

  glbpriv=calloc(_MAX_THREADS_,sizeof(gl_priv));

  initial_main(_cpar_num_tasks_);


   if (argc>1) { 
    SIZE = atoi(argv[1]);
    printf("Matriz %dx%d\n",SIZE,SIZE);
  }
  else {
    printf("Tamanho da matriz: ");
    scanf("%d",&SIZE);
  }
  if (argc>2) {
    nprocs = atoi(argv[2]);
    printf("Usando %d processadores\n",nprocs);
  }
  else {
    printf ("Numero de processadores: ");
    scanf("%d",&nprocs);
  }
 
    
   init_create_task(0,nprocs);

   sh_0=(shared_local_0 *) calloc(1,sizeof(shared_local_0));

   _cpar_arg_0_=(_cpar_arg_task_0_ *) calloc(nprocs,sizeof(_cpar_arg_task_0_ ));

   for(_cpar_id_thread_=0;_cpar_id_thread_<nprocs;_cpar_id_thread_++) {

      _cpar_arg_0_[_cpar_id_thread_].id_thread=_cpar_id_thread_;

      _cpar_arg_0_[_cpar_id_thread_].numthreads=nprocs;

      pthread_mutex_lock(&_cpar_mutex_create_thread_);

      if (pthread_create(&_cpar_tid_[0][_cpar_id_thread_],NULL,init_matrix,(void *)&_cpar_arg_0_[_cpar_id_thread_])){

        fprintf(stderr,"Cannot create thread ");

      pthread_mutex_unlock(&_cpar_mutex_create_thread_);

        exit(1);

    } 

      pthread_mutex_unlock(&_cpar_mutex_create_thread_);

 }  

      pthread_mutex_unlock(&_cpar_create_task_flag_[0]);

      _cpar_task_wait_flag_[0]=0;

  wait_all();
  TIMER_CLEAR;
  TIMER_START; 
    
   init_create_task(1,nprocs);

   sh_1=(shared_local_1 *) calloc(1,sizeof(shared_local_1));

   _cpar_arg_1_=(_cpar_arg_task_1_ *) calloc(nprocs,sizeof(_cpar_arg_task_1_ ));

   for(_cpar_id_thread_=0;_cpar_id_thread_<nprocs;_cpar_id_thread_++) {

      _cpar_arg_1_[_cpar_id_thread_].id_thread=_cpar_id_thread_;

      _cpar_arg_1_[_cpar_id_thread_].numthreads=nprocs;

      pthread_mutex_lock(&_cpar_mutex_create_thread_);

      if (pthread_create(&_cpar_tid_[1][_cpar_id_thread_],NULL,mat_mul,(void *)&_cpar_arg_1_[_cpar_id_thread_])){

        fprintf(stderr,"Cannot create thread ");

      pthread_mutex_unlock(&_cpar_mutex_create_thread_);

        exit(1);

    } 

      pthread_mutex_unlock(&_cpar_mutex_create_thread_);

 }  

      pthread_mutex_unlock(&_cpar_create_task_flag_[1]);

      _cpar_task_wait_flag_[1]=0;

  wait_all();
  TIMER_STOP;
  printf ("TEMPO [%d]: %12.7f\n",SIZE,TIMER_ELAPSED );

#ifdef IMPRIME 
  print_mats(a,b,c);
#endif 
   wait_all();      /* --- rs307()  */
}

#include "cob_mult-tempo"
