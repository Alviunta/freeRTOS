
#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "string.h"
#include "stdlib.h"



#define TAM_PILA 150
# define TAM_COLA 20 /* 20 mensajes */
# define TAM_MSG 4 

QueueHandle_t cola; // Global, se usa de distintas tareas

static void vTarea1(void *pvParameters)
{

   const TickType_t xDelay1000ms = pdMS_TO_TICKS( 1000UL ); //macro para convertir ms en ticks
   BaseType_t xStatus;
	char mensaje[5];
	strcpy(mensaje,"1000");
	for ( ;; ){
       printf("Tarea 1 escribiendo en la cola (1000)\r\n");
	xStatus = xQueueSend (cola, (void *) mensaje, portMAX_DELAY);
	if (xStatus==pdFAIL) printf("Error en la escritura (Tarea1)\r\n");
       vTaskDelay( xDelay1000ms );  // tarea pasa a estado Bloqueado hasta que expira timer
   }
}

static void vTarea2(void *pvParameters)
{

   const TickType_t xDelay1000ms = pdMS_TO_TICKS( 1000UL ); //macro para convertir ms en ticks
   BaseType_t xStatus;
	char mensaje[5];
	strcpy(mensaje,"2000");
	for ( ;; ){
       printf("Tarea 2 escribiendo en la cola (2000)\r\n");
	xStatus = xQueueSend (cola, (void *) mensaje, portMAX_DELAY);
	if (xStatus==pdFAIL) printf("Error en la escritura (Tarea2)\r\n");
       vTaskDelay( xDelay1000ms );  // tarea pasa a estado Bloqueado hasta que expira timer
   }
}

static void vTarea3(void *pvParameters)
{
	char cad [5];
	TickType_t xLastWakeTime;
   	int a;
   	xLastWakeTime = xTaskGetTickCount(); /* se inicializa la variable con la actual cantidad de ticks. Luego es manejada por la API de vTaskDelayUntil()*/

   	TickType_t xDelayms;
	const TickType_t xDelay500ms= pdMS_TO_TICKS( 500UL ); //macro para convertir ms en ticks;
   
	for ( ;; ){
       	printf("Tarea 3 leyendo cola: ");
	if (xQueueReceive (cola, (void *) cad,(portTickType) 0xFFFFFFFF )==pdTRUE)
	{
		a=atoi(cad);
		xDelayms = pdMS_TO_TICKS( a ); //macro para convertir ms en ticks
		printf("%d. \r\n", a);
		Board_LED_Set(3, TRUE);
		vTaskDelayUntil( &xLastWakeTime, xDelayms );
	}
	else printf("Error en la lectura.\r\n");
	
	Board_LED_Set(3, FALSE);
	vTaskDelayUntil( &xLastWakeTime, xDelay500ms );

        }
}



int main(void)
{
    	cola = xQueueCreate (TAM_COLA, TAM_MSG);
	
	//Se inicializa HW
	/* Se crean las tareas */
	xTaskCreate(vTarea1, (const char *)"Tarea1", TAM_PILA, NULL, tskIDLE_PRIORITY+3, NULL );
	xTaskCreate(vTarea2, (const char *)"Tarea2", TAM_PILA, NULL, tskIDLE_PRIORITY+3, NULL );
	xTaskCreate(vTarea3, (const char *)"Tarea3", TAM_PILA, NULL, tskIDLE_PRIORITY+1, NULL );


	vTaskStartScheduler(); /* y por último se arranca el planificador . */
    //Nunca llegara a ese lazo  .... espero
     for( ;; );
     return 0;
}


