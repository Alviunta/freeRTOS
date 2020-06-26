
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

#define PRIO_TAREA1 1
#define PRIO_TAREA2 2
#define TAM_PILA 150
#define mainDELAY_LOOP_COUNT        ( 0xffffff )


int a=0;


static void vTarea2(void *pvParameters)
{
     	printf("Tarea 2: ");
        if (a==0) {
	Board_LED_Set(3, TRUE); //prende "LED 3" ( amarillo )
	printf("LED ON.\r\n");
	a=1;
	}
	else {
	Board_LED_Set(3, FALSE); //apaga "LED 3" ( amarillo )
	printf("LED OFF.\r\n");
	a=0;
	}
	vTaskDelete( NULL );
	
}

static void vTarea1(void *pvParameters)
{
   	const TickType_t xDelay500ms = pdMS_TO_TICKS( 500UL );
   /* As per most tasks, this task is implemented in an infinite loop. */
   for( ;; ) {
        printf( "Tarea 1. Creando tarea 2...\r\n" );
	xTaskCreate(vTarea2, (const char *)"Tarea2", TAM_PILA, NULL, PRIO_TAREA2, NULL );
	vTaskDelay( xDelay500ms );
       }
}


int main(void)
{
    //Se inicializa HW
	/* Se crean las tareas */
	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, NULL, PRIO_TAREA1, NULL );
	
	vTaskStartScheduler(); /* y por último se arranca el planificador . */
    //Nunca llegara a ese lazo  .... espero
     for( ;; );
     return 0;

}

