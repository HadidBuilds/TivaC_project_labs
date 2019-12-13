/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-B06
 */

#include <xdc/std.h>

#include <ti/sysbios/hal/Hwi.h>
extern const ti_sysbios_hal_Hwi_Handle Timer_2A_INT;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle ledToggleTask;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle mailbox_queue_Sem;

#include <ti/sysbios/knl/Mailbox.h>
extern const ti_sysbios_knl_Mailbox_Handle LED_Mbx;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle mailbox_queue_Task;

#include <ti/sysbios/knl/Queue.h>
extern const ti_sysbios_knl_Queue_Handle LED_Queue;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle QueSem;

extern int xdc_runtime_Startup__EXECFXN__C;

extern int xdc_runtime_Startup__RESETFXN__C;

