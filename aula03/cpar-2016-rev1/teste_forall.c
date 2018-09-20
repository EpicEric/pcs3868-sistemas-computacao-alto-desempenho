/* --- Arquivo : teste_forall.c --- */

/* --- inicializacao () --- */
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
typedef struct {pthread_mutex_t sem; int ativado;} Event;
#define Semaph sem_t
#include "type_teste_forall.h"  /* typedef's */
#include "vgp_teste_forall.h"   /* global privada*/
#include "vsl_teste_forall.h"   /* shared local  */
#include "partask_teste_forall.h"
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

#include "cob_teste_forall.h"
#include <stdio.h>
void *tar (void * arg);   /* --- spec () */
/* -- rs400() : definicao de task  */
void *tar (void * arg) 
{
int i;

int inicio = 0;

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
   printf("inicio tar\n");
  fflush(stdout);
      
          };

      end_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_);

{
   int i_, n_;
   n_ = (10000 - 1 + 1) / _cpar_numthreads_;
   if (((10000 - 1 + 1) % _cpar_numthreads_) != 0)
      n_++;
   i_ = 1 + _cpar_id_thread_ * n_;

   for (i = i_; ((i < (i_ + n_)) && (i <= 10000)); i++) { if (inicio==0) {
          printf("i inicial=%d \n",i);
          fflush(stdout);
          inicio=1;
      }   
    }
}
     if (_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_))  /* --- forall () */
  {

  printf("ultimo i=%d\n",i);
  fflush(stdout);

   }
   end_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_);
   rm_thread_conflict();
}

void main()
{

int _id_thread_,_i_;

int _cpar_id_thread_;
for (_i_=0;_i_<1000;_i_++)

   list_thread[_i_].id_thread = -1;

insert_id_thread();

_id_thread_=get_id_thread_gl();

  _cpar_arg_task_0_ *_cpar_arg_0_;

  _cpar_num_tasks_=1;

  glbpriv=calloc(_MAX_THREADS_,sizeof(gl_priv));

  initial_main(_cpar_num_tasks_);


    
   init_create_task(0,16);

   sh_0=(shared_local_0 *) calloc(1,sizeof(shared_local_0));

   _cpar_arg_0_=(_cpar_arg_task_0_ *) calloc(16,sizeof(_cpar_arg_task_0_ ));

   for(_cpar_id_thread_=0;_cpar_id_thread_<16;_cpar_id_thread_++) {

      _cpar_arg_0_[_cpar_id_thread_].id_thread=_cpar_id_thread_;

      _cpar_arg_0_[_cpar_id_thread_].numthreads=16;

      pthread_mutex_lock(&_cpar_mutex_create_thread_);

      if (pthread_create(&_cpar_tid_[0][_cpar_id_thread_],NULL,tar,(void *)&_cpar_arg_0_[_cpar_id_thread_])){

        fprintf(stderr,"Cannot create thread ");

      pthread_mutex_unlock(&_cpar_mutex_create_thread_);

        exit(1);

    } 

      pthread_mutex_unlock(&_cpar_mutex_create_thread_);

 }  

      pthread_mutex_unlock(&_cpar_create_task_flag_[0]);

      _cpar_task_wait_flag_[0]=0;

    wait_all();      /* --- rs307()  */
}

#include "cob_teste_forall"
