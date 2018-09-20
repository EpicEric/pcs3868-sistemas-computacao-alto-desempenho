/* --- Arquivo : exercicio1.c --- */

/* --- inicializacao () --- */
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
typedef struct {pthread_mutex_t sem; int ativado;} Event;
#define Semaph sem_t
#include "type_exercicio1.h"  /* typedef's */
#include "vgp_exercicio1.h"   /* global privada*/
#include "vsl_exercicio1.h"   /* shared local  */
#include "partask_exercicio1.h"
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

#include "cob_exercicio1.h"
#include <stdio.h>
void *tarefa1 (void * arg);   /* --- spec () */
void *tarefa2 (void * arg);   /* --- spec () */
void *tarefa3 (void * arg);   /* --- spec () */
void *tarefa4 (void * arg);   /* --- spec () */
void *tarefa5 (void * arg);   /* --- spec () */
void *tarefa6 (void * arg);   /* --- spec () */
/* -- rs400() : definicao de task  */
void *tarefa1 (void * arg) 
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
   for(i=0;i<5000;i++)
 {printf("%c",'1');
  fflush(stdout);
 }

   }
   end_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_);
   rm_thread_conflict();
}

/* -- rs400() : definicao de task  */
void *tarefa2 (void * arg) 
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
   for(i=0;i<5000;i++)
 {printf("%c",'2');
  fflush(stdout);
 }

   }
   end_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_);
   rm_thread_conflict();
}

/* -- rs400() : definicao de task  */
void *tarefa3 (void * arg) 
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
   for(i=0;i<5000;i++)
 {printf("%c",'3');
  fflush(stdout);
 }

   }
   end_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_);
   rm_thread_conflict();
}

/* -- rs400() : definicao de task  */
void *tarefa4 (void * arg) 
{
int i;

   _cpar_arg_task_3_ *_cpar_arg_t_;
   int _cpar_id_thread_;
   int _cpar_numthreads_;
   int _cpar_id_task_;
   _cpar_id_task_=3;
   _cpar_arg_t_= (_cpar_arg_task_3_ *)arg;
   _cpar_id_thread_=_cpar_arg_t_->id_thread;
   _cpar_numthreads_=_cpar_arg_t_->numthreads;
   int _id_thread_;
   insert_id_thread();
   _id_thread_=get_id_thread_gl();

   if (_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_))
   {
   for(i=0;i<5000;i++)
 {printf("%c",'4');
  fflush(stdout);
 }

   }
   end_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_);
   rm_thread_conflict();
}

/* -- rs400() : definicao de task  */
void *tarefa5 (void * arg) 
{
int i;

   _cpar_arg_task_4_ *_cpar_arg_t_;
   int _cpar_id_thread_;
   int _cpar_numthreads_;
   int _cpar_id_task_;
   _cpar_id_task_=4;
   _cpar_arg_t_= (_cpar_arg_task_4_ *)arg;
   _cpar_id_thread_=_cpar_arg_t_->id_thread;
   _cpar_numthreads_=_cpar_arg_t_->numthreads;
   int _id_thread_;
   insert_id_thread();
   _id_thread_=get_id_thread_gl();

   if (_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_))
   {
   for(i=0;i<5000;i++)
 {printf("%c",'5');
  fflush(stdout);
 }

   }
   end_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_);
   rm_thread_conflict();
}

/* -- rs400() : definicao de task  */
void *tarefa6 (void * arg) 
{
int i;

   _cpar_arg_task_5_ *_cpar_arg_t_;
   int _cpar_id_thread_;
   int _cpar_numthreads_;
   int _cpar_id_task_;
   _cpar_id_task_=5;
   _cpar_arg_t_= (_cpar_arg_task_5_ *)arg;
   _cpar_id_thread_=_cpar_arg_t_->id_thread;
   _cpar_numthreads_=_cpar_arg_t_->numthreads;
   int _id_thread_;
   insert_id_thread();
   _id_thread_=get_id_thread_gl();

   if (_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_))
   {
   for(i=0;i<5000;i++)
 {printf("%c",'6');
  fflush(stdout);
 }

   }
   end_barrier(_cpar_id_task_,_cpar_id_thread_,_cpar_numthreads_);
   rm_thread_conflict();
}

main()
{

int _id_thread_,_i_;

int _cpar_id_thread_;
for (_i_=0;_i_<1000;_i_++)

   list_thread[_i_].id_thread = -1;

insert_id_thread();

_id_thread_=get_id_thread_gl();

  _cpar_arg_task_0_ *_cpar_arg_0_;

  _cpar_arg_task_1_ *_cpar_arg_1_;

  _cpar_arg_task_2_ *_cpar_arg_2_;

  _cpar_arg_task_3_ *_cpar_arg_3_;

  _cpar_arg_task_4_ *_cpar_arg_4_;

  _cpar_arg_task_5_ *_cpar_arg_5_;

  _cpar_num_tasks_=6;

  glbpriv=calloc(_MAX_THREADS_,sizeof(gl_priv));

  initial_main(_cpar_num_tasks_);


   printf("INICIO TESTE\n");
 fflush(stdout);
 printf("\nseq1\n");
 
pthread_t  _cpar_tid_1;

pthread_mutex_lock(&_cpar_mutex_create_thread_);
pthread_create(&_cpar_tid_1,NULL,ROT1,(void *) NULL);

pthread_mutex_unlock(&_cpar_mutex_create_thread_);

pthread_t  _cpar_tid_2;
pthread_create(&_cpar_tid_2,NULL,ROT2,(void *) NULL);

pthread_join(_cpar_tid_1,NULL);

pthread_join(_cpar_tid_2,NULL);

 wait_all();
 printf("\nFIM\n");
 fflush(stdout);
   wait_all();      /* --- rs307()  */
}

#include "cob_exercicio1"
