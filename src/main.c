/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Sample app to demonstrate PWM-based RGB LED control
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>

#include <stm32_ll_tim.h>

static const struct pwm_dt_spec u_svpwm_out = PWM_DT_SPEC_GET(DT_NODELABEL(u_svpwm_out));
static const struct pwm_dt_spec v_svpwm_out = PWM_DT_SPEC_GET(DT_NODELABEL(v_svpwm_out));
static const struct pwm_dt_spec w_svpwm_out = PWM_DT_SPEC_GET(DT_NODELABEL(w_svpwm_out));

#define STEP_SIZE PWM_USEC(2000)

int main(void)
{
	// uint32_t pulse_red, pulse_green, pulse_blue; /* pulse widths */
	int ret;

	printk("PWM-based RGB LED control\n");

	// @see https://github.com/zephyrproject-rtos/zephyr/blob/213da72d06ee9c411019ca93ed8e4f4b6f72e39b/drivers/pwm/pwm_stm32.c#L379C31-L379C47
	LL_TIM_SetCounterMode(TIM4, LL_TIM_COUNTERMODE_CENTER_DOWN);

	if (!pwm_is_ready_dt(&u_svpwm_out) || !pwm_is_ready_dt(&v_svpwm_out) || !pwm_is_ready_dt(&w_svpwm_out))
	{
		printk("Error: one or more PWM devices not ready\n");
		return 0;
	}

	if ((ret = pwm_set_pulse_dt(&u_svpwm_out, 16667)) != 0)
	{
		printk("Error: Failed to set PWM pulse width. Error code: %d\n", ret);
		return 1;
	}
	if ((ret = pwm_set_pulse_dt(&v_svpwm_out, 25000)) != 0)
	{
		printk("Error: Failed to set PWM pulse width. Error code: %d\n", ret);
		return 1;
	}
	if ((ret = pwm_set_pulse_dt(&w_svpwm_out, 8333)) != 0)
	{
		printk("Error: Failed to set PWM pulse width. Error code: %d\n", ret);
		return 1;
	}

	while (1)
	{
		k_sleep(K_SECONDS(1));
	}
	return 0;
}
