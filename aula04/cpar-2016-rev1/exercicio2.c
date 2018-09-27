/* --- Arquivo : exercicio2.c --- */

/* --- inicializacao () --- */
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
typedef struct {pthread_mutex_t sem; int ativado;} Event;
#define Semaph sem_t
#include "type_exercicio2.h"  /* typedef's */
#include "vgp_exercicio2.h"   /* global privada*/
#include "vsl_exercicio2.h"   /* shared local  */
#include "partask_exercicio2.h"
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

#include "cob_exercicio2.h"
#include <stdio.h>
   int x[2000], y[2000], a[2000], b[2000], c[2000];

   Semaph sem1, sem2;

void *tar1 (void * arg);   /* --- spec () */
/* -- rs400() : definicao de task  */
void *tar1 (void * arg) 
{
int i;

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
   for(i=0; i<1999; i++) {
    a[i] = x[i] * 3;
    printf("unlock a[%d]\n", i); 
    unlock(&sem1);
    unlock(&sem2);
  }

   }
   end_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_);
   rm_thread_conflict();
}

void *tar2 (void * arg);   /* --- spec () */
/* -- rs400() : definicao de task  */
void *tar2 (void * arg) 
{
int i;

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
   b[0] = 1;
  for(i=1; i<2000; i++) {
    lock(&sem1);
    printf("b[%d]", i);
    b[i] = y[i] + a[i-1];
  }

   }
   end_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_);
   rm_thread_conflict();
}

void *tar3 (void * arg);   /* --- spec () */
/* -- rs400() : definicao de task  */
void *tar3 (void * arg) 
{
int i;

   _cpar_arg_task_2_ *_cpar_arg_t_;
   int _cpar_id_thread_;
   int _cpar_numthreads_;
   int _cpar_id_task_;
   _cpar_id_task_=2;
   _cpar_arg_t_= (_cpar_arg_task_2_ *)arg;
   _cpar_id_thread_=_cpar_arg_t_->id_thread;
   _cpar_numthreads_=_cpar_arg_t_->numthreads;
   int _id_thread_;
   insert_id_thread();
   _id_thread_=get_id_thread_gl();

   if (_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_))
   {
   c[0] = 1;
  for(i=1; i<2000; i++) {
    lock(&sem2);
    printf("c[%d]", i);
    c[i]=a[i-1]*2;
  }

   }
   end_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_);
   rm_thread_conflict();
}

main()
{
int nprocs, i;


int _id_thread_,_i_;

int _cpar_id_thread_;
for (_i_=0;_i_<1000;_i_++)

   list_thread[_i_].id_thread = -1;

insert_id_thread();

_id_thread_=get_id_thread_gl();

  _cpar_arg_task_0_ *_cpar_arg_0_;

  _cpar_arg_task_1_ *_cpar_arg_1_;

  _cpar_arg_task_2_ *_cpar_arg_2_;

  _cpar_num_tasks_=3;

  glbpriv=calloc(_MAX_THREADS_,sizeof(gl_priv));

  initial_main(_cpar_num_tasks_);


   for(i=0; i<2000; i++) {
    x[i] = i;
    y[i] = i+1;
  }
  create_sem(&sem1, 0);
  create_sem(&sem2, 0);
    
   init_create_task(0,1);

   sh_0=(shared_local_0 *) calloc(1,sizeof(shared_local_0));

   _cpar_arg_0_=(_cpar_arg_task_0_ *) calloc(1,sizeof(_cpar_arg_task_0_ ));

   for(_cpar_id_thread_=0;_cpar_id_thread_<1;_cpar_id_thread_++) {

      _cpar_arg_0_[_cpar_id_thread_].id_thread=_cpar_id_thread_;

      _cpar_arg_0_[_cpar_id_thread_].numthreads=1;

      pthread_mutex_lock(&_cpar_mutex_create_thread_);

      if (pthread_create(&_cpar_tid_[0][_cpar_id_thread_],NULL,tar1,(void *)&_cpar_arg_0_[_cpar_id_thread_])){

        fprintf(stderr,"Cannot create thread ");

      pthread_mutex_unlock(&_cpar_mutex_create_thread_);

        exit(1);

    } 

      pthread_mutex_unlock(&_cpar_mutex_create_thread_);

 }  

      pthread_mutex_unlock(&_cpar_create_task_flag_[0]);

      _cpar_task_wait_flag_[0]=0;

    
   init_create_task(1,1);

   sh_1=(shared_local_1 *) calloc(1,sizeof(shared_local_1));

   _cpar_arg_1_=(_cpar_arg_task_1_ *) calloc(1,sizeof(_cpar_arg_task_1_ ));

   for(_cpar_id_thread_=0;_cpar_id_thread_<1;_cpar_id_thread_++) {

      _cpar_arg_1_[_cpar_id_thread_].id_thread=_cpar_id_thread_;

      _cpar_arg_1_[_cpar_id_thread_].numthreads=1;

      pthread_mutex_lock(&_cpar_mutex_create_thread_);

      if (pthread_create(&_cpar_tid_[1][_cpar_id_thread_],NULL,tar2,(void *)&_cpar_arg_1_[_cpar_id_thread_])){

        fprintf(stderr,"Cannot create thread ");

      pthread_mutex_unlock(&_cpar_mutex_create_thread_);

        exit(1);

    } 

      pthread_mutex_unlock(&_cpar_mutex_create_thread_);

 }  

      pthread_mutex_unlock(&_cpar_create_task_flag_[1]);

      _cpar_task_wait_flag_[1]=0;

    
   init_create_task(2,1);

   sh_2=(shared_local_2 *) calloc(1,sizeof(shared_local_2));

   _cpar_arg_2_=(_cpar_arg_task_2_ *) calloc(1,sizeof(_cpar_arg_task_2_ ));

   for(_cpar_id_thread_=0;_cpar_id_thread_<1;_cpar_id_thread_++) {

      _cpar_arg_2_[_cpar_id_thread_].id_thread=_cpar_id_thread_;

      _cpar_arg_2_[_cpar_id_thread_].numthreads=1;

      pthread_mutex_lock(&_cpar_mutex_create_thread_);

      if (pthread_create(&_cpar_tid_[2][_cpar_id_thread_],NULL,tar3,(void *)&_cpar_arg_2_[_cpar_id_thread_])){

        fprintf(stderr,"Cannot create thread ");

      pthread_mutex_unlock(&_cpar_mutex_create_thread_);

        exit(1);

    } 

      pthread_mutex_unlock(&_cpar_mutex_create_thread_);

 }  

      pthread_mutex_unlock(&_cpar_create_task_flag_[2]);

      _cpar_task_wait_flag_[2]=0;

  wait_all();
  rem_sem(&sem1);
  for(i=0; i<20; i++) {
    printf("%d\n", b[i]);
  } 
   wait_all();      /* --- rs307()  */
}

#include "cob_exercicio2"
