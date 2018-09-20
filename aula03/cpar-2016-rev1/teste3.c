/* --- Arquivo : teste3.c --- */

/* --- inicializacao () --- */
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
typedef struct {pthread_mutex_t sem; int ativado;} Event;
#define Semaph sem_t
#include "type_teste3.h"  /* typedef's */
#include "vgp_teste3.h"   /* global privada*/
#include "vsl_teste3.h"   /* shared local  */
#include "partask_teste3.h"
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

#include "cob_teste3.h"
#include <stdio.h>
main()
{

int _id_thread_,_i_;

int _cpar_id_thread_;
for (_i_=0;_i_<1000;_i_++)

   list_thread[_i_].id_thread = -1;

insert_id_thread();

_id_thread_=get_id_thread_gl();

  _cpar_num_tasks_=0;

  glbpriv=calloc(_MAX_THREADS_,sizeof(gl_priv));

  initial_main(_cpar_num_tasks_);


   printf("INICIO\n");
 fflush(stdout);
 
pthread_t  _cpar_tid_1;

pthread_mutex_lock(&_cpar_mutex_create_thread_);
pthread_create(&_cpar_tid_1,NULL,ROT1,(void *) NULL);

pthread_mutex_unlock(&_cpar_mutex_create_thread_);

pthread_t  _cpar_tid_2;
pthread_create(&_cpar_tid_2,NULL,ROT2,(void *) NULL);

pthread_t  _cpar_tid_3;
pthread_create(&_cpar_tid_3,NULL,ROT3,(void *) NULL);

pthread_join(_cpar_tid_1,NULL);

pthread_join(_cpar_tid_2,NULL);

pthread_join(_cpar_tid_3,NULL);

    wait_all();      /* --- rs307()  */
}

#include "cob_teste3"
