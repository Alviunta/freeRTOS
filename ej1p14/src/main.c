#include "board.h"
#include "FreeRTOS.h"
#include "task.h"


#define PRIO_TAREA1 1
#define PRIO_TAREA2 2
#define TAM_PILA 150
#define mainDELAY_LOOP_COUNT        ( 0xffffff )


static void vTarea1(void *pvParameters)
{
    uint32_t ul;
   /* As per most tasks, this task is implemented in an infinite loop. */
   for( ;; ) {
      /* Print out the name of this task. */
      printf( "Tarea 1\r\n" );
	/* Delay for a period. */
      for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ ) {
      }

       }
}

static void vTarea2(void *pvParameters)
{
     	const TickType_t xDelay1000ms = pdMS_TO_TICKS( 1000UL );

	printf ( "cuantos tics por ms: %d\r\n",portTICK_RATE_MS );

	int a;
	/* As per most tasks, this task is implemented in an infinite loop. */
   for( ;; ) {
	printf("Tarea 2: ");
        if (a==0) {
	Board_LED_Set(3, TRUE); //prende "LED 5" ( amarillo )
	printf("LED ON. ");
	a=1;
	}
	else {
	Board_LED_Set(3, FALSE); //apaga "LED 5" ( amarillo )
	printf("LED OFF. ");
	a=0;
	}
	printf("Tics: %d\r\n", xDelay1000ms );
	vTaskDelay( xDelay1000ms );
	
   }
}


int main(void)
{
    //Se inicializa HW
	/* Se crean las tareas */
	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, NULL, PRIO_TAREA1, NULL );
	xTaskCreate(vTarea2, (const char *)"Tarea2", TAM_PILA, NULL, PRIO_TAREA2, NULL );

	vTaskStartScheduler(); /* y por último se arranca el planificador . */
    //Nunca llegara a ese lazo  .... espero
     for( ;; );
     return 0;

}

