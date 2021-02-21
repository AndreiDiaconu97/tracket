#include "timers.h"

volatile int   cnt = 0;
void IRAM_ATTR timer_sidereal_isr(void *param) {
    uint32_t intr_status = TIMERG0.int_st_timers.val;

    TIMERG0.hw_timer[TIMER_0].update          = 1;
    TIMERG0.int_clr_timers.t0                 = 1;
    TIMERG0.hw_timer[TIMER_0].config.alarm_en = 1;
    cnt++;
}

void IRAM_ATTR timer_motor_RA_isr(void *param) {
    uint32_t intr_status = TIMERG0.int_st_timers.val;
}

void IRAM_ATTR timer_motor_DEC_isr(void *param) {
    uint32_t intr_status = TIMERG0.int_st_timers.val;
}

void init_timers_motors() {
    timer_group_t timer_group   = TIMER_GROUP_1;
    timer_idx_t   timer_idx_RA  = TIMER_0;
    timer_idx_t   timer_idx_DEC = TIMER_1;

    // RA SETUP
    timer_config_t config_RA;
    config_RA.divider     = 8000;
    config_RA.counter_dir = TIMER_COUNT_UP;
    config_RA.alarm_en    = TIMER_ALARM_EN;
    config_RA.auto_reload = TIMER_AUTORELOAD_EN; // Reset timer to 0 when end condition is triggered
    config_RA.intr_type   = TIMER_INTR_LEVEL;
    config_RA.counter_en  = TIMER_PAUSE;

    timer_init(timer_group, timer_idx_RA, &config_RA);
    timer_pause(timer_group, timer_idx_RA);
    timer_set_counter_value(timer_group, timer_idx_RA, 0x00000000ULL);
    timer_set_alarm_value(timer_group, timer_idx_RA, 10000);
    timer_enable_intr(timer_group, timer_idx_RA);
    timer_isr_register(timer_group, timer_idx_RA, timer_motor_RA_isr, NULL, ESP_INTR_FLAG_IRAM, NULL);
    timer_start(timer_group, timer_idx_RA);

    // DEC SETUP
    timer_config_t config_DEC;
    config_DEC.divider     = 8000;
    config_DEC.counter_dir = TIMER_COUNT_UP;
    config_DEC.alarm_en    = TIMER_ALARM_EN;
    config_DEC.auto_reload = TIMER_AUTORELOAD_EN; // Reset timer to 0 when end condition is triggered
    config_DEC.intr_type   = TIMER_INTR_LEVEL;
    config_DEC.counter_en  = TIMER_PAUSE;

    timer_init(timer_group, timer_idx_DEC, &config_DEC);
    timer_pause(timer_group, timer_idx_DEC);
    timer_set_counter_value(timer_group, timer_idx_DEC, 0x00000000ULL);
    timer_set_alarm_value(timer_group, timer_idx_DEC, 10000);
    timer_enable_intr(timer_group, timer_idx_DEC);
    timer_isr_register(timer_group, timer_idx_DEC, timer_motor_DEC_isr, NULL, ESP_INTR_FLAG_IRAM, NULL);
    timer_start(timer_group, timer_idx_DEC);
}

void init_timer_sidereal() {
    timer_group_t timer_group = TIMER_GROUP_0;
    timer_idx_t   timer_idx   = TIMER_0;

    timer_config_t config;
    config.divider     = 8000;
    config.counter_dir = TIMER_COUNT_UP;
    config.alarm_en    = TIMER_ALARM_EN;
    config.auto_reload = TIMER_AUTORELOAD_EN; // Reset timer to 0 when end condition is triggered
    config.intr_type   = TIMER_INTR_LEVEL;
    config.counter_en  = TIMER_PAUSE;

    timer_init(timer_group, timer_idx, &config);
    timer_pause(timer_group, timer_idx);
    timer_set_counter_value(timer_group, timer_idx, 0x00000000ULL);
    timer_set_alarm_value(timer_group, timer_idx, 5000);
    timer_enable_intr(timer_group, timer_idx);
    timer_isr_register(timer_group, timer_idx, timer_sidereal_isr, NULL, ESP_INTR_FLAG_IRAM, NULL);
    timer_start(timer_group, timer_idx);
}
