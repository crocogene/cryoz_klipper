#ifndef __SCHED_H
#define __SCHED_H

#include <stdint.h> // uint32_t
#include "ctr.h" // DECL_CTR

#include "command.h" // _DECL_STATIC_STR

// Declare an init function (called at firmware startup)
#define DECL_INIT(FUNC) _DECL_CALLLIST(ctr_run_initfuncs, FUNC)
// Declare a task function (called periodically during normal runtime)
#define DECL_TASK(FUNC) _DECL_CALLLIST(ctr_run_taskfuncs, FUNC)
// Declare a shutdown function (called on an emergency stop)
#define DECL_SHUTDOWN(FUNC) _DECL_CALLLIST(ctr_run_shutdownfuncs, FUNC)

// Timer structure for scheduling timed events (see sched_add_timer() )
struct timer {
    struct timer *next;
    uint_fast8_t (*func)(struct timer*);
    uint32_t waketime;
    uint_fast8_t too_close_shutdown_reason; //debug "Timer too close" error
};

enum { SF_DONE=0, SF_RESCHEDULE=1 };

// Task waking struct
struct task_wake {
    uint8_t wake;
};

// sched.c
void sched_add_timer(struct timer*);
void sched_del_timer(struct timer *del);
unsigned int sched_timer_dispatch(void);
void sched_timer_reset(void);
void sched_wake_tasks(void);
uint8_t sched_check_set_tasks_busy(void);
void sched_wake_task(struct task_wake *w);
uint8_t sched_check_wake(struct task_wake *w);
uint8_t sched_is_shutdown(void);
void sched_clear_shutdown(void);
void sched_try_shutdown(uint_fast8_t reason);
void sched_shutdown(uint_fast8_t reason) __noreturn;
void sched_report_shutdown(void);
void sched_main(void);

// Compiler glue for DECL_X macros above.
#define _DECL_CALLLIST(NAME, FUNC)                                      \
    DECL_CTR("_DECL_CALLLIST " __stringify(NAME) " " __stringify(FUNC))

#endif // sched.h

#define TOO_CLOSE_ANALOG_IN _DECL_STATIC_STR("Timer ANALOG_IN too close")
#define TOO_CLOSE_ANALOG_IN_SHUTDOWN _DECL_STATIC_STR("Timer ANALOG_IN_SHUTDOWN too close")
#define TOO_CLOSE_QUEUE_DIGITAL_OUT _DECL_STATIC_STR("Timer QUEUE_DIGITAL_OUT too close")
#define TOO_CLOSE_UPDATE_DIGITAL_OUT _DECL_STATIC_STR("Timer UPDATE_DIGITAL_OUT too close")
#define TOO_CLOSE_PULSE_COUNTER _DECL_STATIC_STR("Timer PULSE_COUNTER too close")
#define TOO_CLOSE_PWM _DECL_STATIC_STR("Timer PWM too close")
#define TOO_CLOSE_ADS1220 _DECL_STATIC_STR("Timer ADS1220 too close")
#define TOO_CLOSE_ADXL345 _DECL_STATIC_STR("Timer ADXL345 too close")
#define TOO_CLOSE_SENSOR_ANGLE _DECL_STATIC_STR("Timer SENSOR_ANGLE too close")
#define TOO_CLOSE_HX71X _DECL_STATIC_STR("Timer HX71X too close")
#define TOO_CLOSE_ICM20948 _DECL_STATIC_STR("Timer ICM20948 too close")
#define TOO_CLOSE_LDC1612 _DECL_STATIC_STR("Timer LDC1612 too close")
#define TOO_CLOSE_LIS2DW _DECL_STATIC_STR("Timer LIS2DW too close")
#define TOO_CLOSE_MPU9250 _DECL_STATIC_STR("Timer MPU9250 too close")
#define TOO_CLOSE_THERMOCOUPLE _DECL_STATIC_STR("Timer THERMOCOUPLE too close")
#define TOO_CLOSE_TMCUART_SEND_SYNC _DECL_STATIC_STR("Timer TMCUART_SEND_SYNC too close")
#define TOO_CLOSE_TMCUART_SEND _DECL_STATIC_STR("Timer TMCUART_SEND too close")
#define TOO_CLOSE_PCA9685 _DECL_STATIC_STR("Timer PCA9685 too close")
#define TOO_CLOSE_DS18B20 _DECL_STATIC_STR("Timer DS18B20 too close")
#define TOO_CLOSE_BUTTONS _DECL_STATIC_STR("Timer BUTTONS too close")
#define TOO_CLOSE_ENDSTOP _DECL_STATIC_STR("Timer ENDSTOP too close")
#define TOO_CLOSE_LCP_HOME _DECL_STATIC_STR("Timer LOAD_CELL_PROBE_HOME too close")
#define TOO_CLOSE_STEPPER _DECL_STATIC_STR("Timer STEPPER too close")
#define TOO_CLOSE_TRSYNC_REPORT _DECL_STATIC_STR("Timer TRSYNC_REPORT too close")
#define TOO_CLOSE_TRSYNC_EXPIRE _DECL_STATIC_STR("Timer TRSYNC_EXPIRE too close")
#define TOO_CLOSE_GD32E23X_WRAP _DECL_STATIC_STR("Timer GD32E23X_WRAP too close")
#define TOO_CLOSE_ARMCM_WRAP _DECL_STATIC_STR("Timer ARMCM_WRAP too close")
#define TOO_CLOSE_STM32F0_WRAP _DECL_STATIC_STR("Timer STM32F0_WRAP too close")