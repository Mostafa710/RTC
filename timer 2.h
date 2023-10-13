#ifndef TIMER_2_H_
#define TIMER_2_H_

void timer2_overflow_init_interrupt(void);
void timer2_CTC_init_interrupt(void);
void timer2_wave_non_PWM(void);
void timer2_wave_fast_PWM(void);
void timer2_wave_phase_correct_PWM(void);

#endif