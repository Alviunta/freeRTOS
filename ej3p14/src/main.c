#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"
#include "board.h" //definicion de leds


#define mainDELAY_LOOP_COUNT        ( 0xffffff )

TaskHandle_t xTask2Handle; //variable global guardara id de tarea2

void vTarea1( void *pvParameters )
{
   UBaseType_t uxPriority;
   uxPriority = uxTaskPriorityGet( NULL ); //retorna la propia prioridad
	uint32_t ul;

   for( ;; ) {
      printf ( "Task1 esta running\r\n" );
	/* Delay for a period. */
      for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ ) {
      }
      printf ( "Aumentando la prioridad de Tarea2...\r\n" );
      vTaskPrioritySet( xTask2Handle, ( uxPriority + 1 ) ); // Tarea2 mas prioritaria
     

   }
}

/*-----------------------------------------------------------*/

void vTarea2( void *pvParameters )
{
   UBaseType_t uxPriority;
   uxPriority = uxTaskPriorityGet( NULL ); //NULL retorna la propia prioridad
int a;

   for( ;; ) {
      printf ( "Tarea2 esta running. " );
	if (a==0) {
	Board_LED_Set(5, TRUE); //prende "LED 5" 
	printf("LED ON. ");
	a=1;
	}
	else {
	Board_LED_Set(5, FALSE); //apaga "LED 5" 
	printf("LED OFF. ");
	a=0;
	}
	printf( "Disminuyendo mi prioridad(Tarea2)\r\n" );
      vTaskPrioritySet( NULL, ( uxPriority - 2 ) ); //NULL propio ID
     
   }
}
/*-----------------------------------------------------------*/

int main( void )
{
   xTaskCreate( vTarea1, "Tarea1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+2, NULL );
   xTaskCreate( vTarea2, "Tarea2", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, &xTask2Handle );

	vTaskStartScheduler(); /* y por último se arranca el planificador . */
    //Nunca llegara a ese lazo  .... espero
     for( ;; );
     return 0;

}
