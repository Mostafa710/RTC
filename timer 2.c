#include <avr/interrupt.h>
#include "std_macros.h"

void timer2_overflow_init_interrupt(void)
{
	/* select timer clock */
	SET_BIT(ASSR,AS2);
	/* select timer pre-scaler */
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS22);
	/* enable interrupt */
	sei();
	SET_BIT(TIMSK,TOIE2);
}
void timer2_CTC_init_interrupt(void)
{
	/* select CTC mode */
	SET_BIT(TCCR2,WGM21);
	/* load a value in OCR2 */
	OCR2=64;
	/* select timer clock */
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	/* enable interrupt */
	sei();
	SET_BIT(TIMSK,OCIE2);
}
void timer2_wave_non_PWM(void)
{
	/* set OC2 as output pin */
	SET_BIT(DDRD,7);
	/* select CTC mode */
	SET_BIT(TCCR2,WGM21);
	/* load a value in OCR2 */
	OCR2=64;
	/* select timer clock */
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	/* toggle OC2 on compare match */
	SET_BIT(TCCR2,COM20);
}
void timer2_wave_fast_PWM(void)
{
	/* set OC2 as output pin */
	SET_BIT(DDRD,7);
	/* select fast PWM mode */
	SET_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);
	/* load a value in OCR2 */
	OCR2=64;
	/* select timer clock */
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	/* clear OC2 on compare match, set OC2 at BOTTOM (non-inverting mode) */
	SET_BIT(TCCR2,COM21);
}
void timer2_wave_phase_correct_PWM(void)
{
	/* set OC2 as output pin */
	SET_BIT(DDRD,7);
	/* select phase correct PWM mode */
	SET_BIT(TCCR2,WGM20);
	/* load a value in OCR2 */
	OCR2=64;
	/* select timer clock */
	SET_BIT(TCCR2,CS20);
	SET_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	/* set OC2 on compare match when up-counting, clear OC2 on compare match when down-counting */
	SET_BIT(TCCR2,COM20);
	SET_BIT(TCCR2,COM21);
}