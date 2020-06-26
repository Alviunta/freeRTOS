#include "board.h"
#include "FreeRTOS.h"
#include "task.h"


#define TAM_PILA 150

const char *pcTextoTarea1 = "Tarea1 is running\r\n";
const char *pcTextoTarea2 = "Tarea2 is running\r\n";


void vApplicationIdleHook( void )
{
	TickType_t xLastWakeTime;
	xLastWakeTime=xTaskGetTickCount();
	const TickType_t xDelay300ms = pdMS_TO_TICKS( 300UL ); //macro para convertir ms en ticks
	
	while((xTaskGetTickCount()-xLastWakeTime)<xDelay300ms)
	{
	}
	Board_LED_Toggle(2);

}

static void vTarea(void *pvParameters)
{

   const TickType_t xDelay500ms = pdMS_TO_TICKS( 500UL ); //macro para convertir ms en ticks
   char *pcTaskName;
   /* The string to print out is passed in via the parameter.  Cast this to a
   character pointer. */
   pcTaskName = ( char * ) pvParameters;
   for ( ;; ){
       printf( pcTaskName );
       vTaskDelay( xDelay500ms );  // tarea pasa a estado Bloqueado hasta que expira timer
   }
}



int main(void)
{
    //Se inicializa HW
	/* Se crean las tareas */
	xTaskCreate(vTarea, (const char *)"Tarea1", TAM_PILA, (void*)pcTextoTarea1, tskIDLE_PRIORITY+1, NULL );
	xTaskCreate(vTarea, (const char *)"Tarea2", TAM_PILA, (void*)pcTextoTarea2, tskIDLE_PRIORITY+2, NULL );

	vTaskStartScheduler(); /* y por último se arranca el planificador . */
    //Nunca llegara a ese lazo  .... espero
     for( ;; );
     return 0;
}

