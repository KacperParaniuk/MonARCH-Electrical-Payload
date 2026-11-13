
#include "pwm.h"

// f_PWM = f_timer / ((PSC + 1) × (ARR + 1))
// duty  = CCR / (ARR + 1) 

 
uint32_t TIM_CLK_HZ = 80000000;

// In STM32CubeIDE, the Internal Clock source for TIM1 is associated with the APB2 bus clock (often designated as PCLK2 or the APB2 timer clock APB2_TIM), which is derived from the main system clock (SYSCLK) via the RCC clock tree.

void pwm_set(TIM_HandleTypeDef *htim, uint32_t channel,
             uint32_t freq_hz, uint32_t duty_pct)
{

    if (freq_hz == 0 || freq_hz > TIM_CLK_HZ) return;

    uint32_t ticks = TIM_CLK_HZ / freq_hz;
    uint32_t psc = (ticks - 1)/65536UL; // The - 1 before dividing turns C's round-down division into a round-up, then gives you PSC directly.
    uint32_t arr   = ticks / (psc + 1) - 1;
    uint32_t ccr   = (arr + 1) * duty_pct / 100;  // duty_pct: 0..100
    // The trick

    // ceil(a / b) = (a - 1) / b + 1      (integer division, a ≥ 1)

    __HAL_TIM_SET_PRESCALER(htim, psc);
    __HAL_TIM_SET_AUTORELOAD(htim, arr);
    __HAL_TIM_SET_COMPARE(htim, channel, ccr);

    HAL_TIM_GenerateEvent(htim, TIM_EVENTSOURCE_UPDATE);  // load PSC/ARR/CCR now and restart the period

    

}
