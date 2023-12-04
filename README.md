# RTOS-Labs

#include "pendulum.h"
#include <pthread.h>
#include <stddef.h>
#include <unistd.h>
#include <math.h>

/* Watek sterujacy wahadlem */
void* controller(void* unused)
{
  double position = 0.0;
  double velocity = 0.0;


  double kinetic = 0.0;
  double potential = 0.0;

  // odkomentowane vel kin i pot

  int dir = 0;
  int done = 0;

  int thread_identifier;

  (void)unused;


  /* TODO: ustawic parametry poczatkowe symulacji i zasygnalizować to innym
   *       watkom (zmienna warunkowa/condition variable) */
  /* pendulum_params.position = 0.0;
   * //...
     pendulum_params.ready = 1;
        * pendulum_params.condvar = 1;
     */


  //swoje

  pthread_mutex_lock(&pendulum_params.mutex);

  pendulum_params.velocity = velocity;
  pendulum_params.position = position;
  pendulum_params.ready = 1;


  pthread_cond_signal(&pendulum_params.condvar);

  pthread_mutex_unlock(&pendulum_params.mutex);

  //koniec swoich

  while(!done)
    {
      /* TODO: wczytac stan wahadla do zmiennych lokalnych */
	  	 pthread_mutex_lock(&pendulum_params.mutex);

         position = pendulum_state.position ;
         velocity = pendulum_state.velocity ;
         kinetic = pendulum_state.kinetic ;
         potential = pendulum_state.potential ;

         pthread_mutex_unlock(&pendulum_params.mutex);


      /* Na samym szczycie (N) energia potencjalna wynosi ok 1.30 */
      if(sin(position) >= 0)
        {
          /******************************************************************
           * Wahadlo w prawej polplaszczyznie (wschod).
           *
           *                 ,,,,,
           *                 --+--
           *                    \
           *                     \
           *                      O
           *
           *  - albo przykladamy moment przeciwzegarowo (dir=1),
           *  - albo zdejmujemy (dir=0).
           *
           ******************************************************************/

          /* TODO: wyznaczyc sterowanie, dir = ... */

    	  if (velocity < 0 || kinetic+potential < 1.25){
    		  dir = 1;
    	  } else {
    		  dir = 0;
    	  }

        }
      else
        {
          /******************************************************************
           * Wahadlo w lewej polplaszczyznie (zachod):
           *
           *                 ,,,,,
           *                 --+--
           *                  /
           *                 /
           *                O
           *
           *  - albo przykladamy moment wpolzegarowo (dir=-1),
           *  - albo zdejmujemy (dir=0).
           *
           ******************************************************************/

          /* TODO: wyznaczyc sterowanie, dir = ... */
    	  if (velocity  > 0 || kinetic+potential < 1.25){
    		  dir = -1;
    	  } else{
    		  dir = 0;
    	  }
        }

      /* Zadajemy obliczone sterowanie */
      /* TODO: zweryfikowac, czy nic tu wiecej nie potrzeba */

      pthread_mutex_lock(&pendulum_params.mutex);

      pendulum_control.dir = dir;

      pthread_mutex_unlock(&pendulum_params.mutex);

      usleep(100000); /* 100 ms */
    }

  thread_identifier = pthread_self();

  pthread_mutex_lock(&pendulum_params.mutex);
  done = pendulum_state.done;
  pthread_mutex_unlock(&pendulum_params.mutex);



  return NULL;
}

/* Tworzy watek sterujacy wahadlem i zwraca jego identyfikator */
pthread_t start_controller()
{
  pthread_t thread = (pthread_t)NULL;
  /* TODO: utworzyc watek */

  pthread_create(&thread, NULL, &controller, NULL);
  return thread;
}
