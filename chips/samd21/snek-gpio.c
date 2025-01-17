/*
 * Copyright © 2019 Keith Packard <keithp@keithp.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#include <ao.h>
#include <ao-snek.h>
#include <snek.h>

static uint8_t	power_pin;
static uint8_t	dir_pin;
static uint16_t	power[AO_SNEK_NUM_PIN];
static uint32_t	on_pins;

struct ao_snek_pin {
	void	*gpio;
	void	*timer;
	uint8_t	pin;
	uint8_t	channel;
	uint8_t	adc;
	uint8_t flags;
};

#ifndef AO_SNEK_FLAGS_0
#define AO_SNEK_FLAGS_0 0
#endif
#ifndef AO_SNEK_FLAGS_1
#define AO_SNEK_FLAGS_1 0
#endif
#ifndef AO_SNEK_FLAGS_2
#define AO_SNEK_FLAGS_2 0
#endif
#ifndef AO_SNEK_FLAGS_3
#define AO_SNEK_FLAGS_3 0
#endif
#ifndef AO_SNEK_FLAGS_4
#define AO_SNEK_FLAGS_4 0
#endif
#ifndef AO_SNEK_FLAGS_5
#define AO_SNEK_FLAGS_5 0
#endif
#ifndef AO_SNEK_FLAGS_6
#define AO_SNEK_FLAGS_6 0
#endif
#ifndef AO_SNEK_FLAGS_7
#define AO_SNEK_FLAGS_7 0
#endif
#ifndef AO_SNEK_FLAGS_8
#define AO_SNEK_FLAGS_8 0
#endif
#ifndef AO_SNEK_FLAGS_9
#define AO_SNEK_FLAGS_9 0
#endif
#ifndef AO_SNEK_FLAGS_10
#define AO_SNEK_FLAGS_10 0
#endif
#ifndef AO_SNEK_FLAGS_11
#define AO_SNEK_FLAGS_11 0
#endif
#ifndef AO_SNEK_FLAGS_12
#define AO_SNEK_FLAGS_12 0
#endif
#ifndef AO_SNEK_FLAGS_13
#define AO_SNEK_FLAGS_13 0
#endif
#ifndef AO_SNEK_FLAGS_14
#define AO_SNEK_FLAGS_14 0
#endif
#ifndef AO_SNEK_FLAGS_15
#define AO_SNEK_FLAGS_15 0
#endif
#ifndef AO_SNEK_FLAGS_16
#define AO_SNEK_FLAGS_16 0
#endif
#ifndef AO_SNEK_FLAGS_17
#define AO_SNEK_FLAGS_17 0
#endif
#ifndef AO_SNEK_FLAGS_18
#define AO_SNEK_FLAGS_18 0
#endif
#ifndef AO_SNEK_FLAGS_19
#define AO_SNEK_FLAGS_19 0
#endif
#ifndef AO_SNEK_FLAGS_20
#define AO_SNEK_FLAGS_20 0
#endif
#ifndef AO_SNEK_FLAGS_21
#define AO_SNEK_FLAGS_21 0
#endif
#ifndef AO_SNEK_FLAGS_22
#define AO_SNEK_FLAGS_22 0
#endif
#ifndef AO_SNEK_FLAGS_23
#define AO_SNEK_FLAGS_23 0
#endif
#ifndef AO_SNEK_FLAGS_24
#define AO_SNEK_FLAGS_24 0
#endif
#ifndef AO_SNEK_FLAGS_25
#define AO_SNEK_FLAGS_25 0
#endif
#ifndef AO_SNEK_FLAGS_26
#define AO_SNEK_FLAGS_26 0
#endif
#ifndef AO_SNEK_FLAGS_27
#define AO_SNEK_FLAGS_27 0
#endif
#ifndef AO_SNEK_FLAGS_28
#define AO_SNEK_FLAGS_28 0
#endif
#ifndef AO_SNEK_FLAGS_29
#define AO_SNEK_FLAGS_29 0
#endif
#ifndef AO_SNEK_FLAGS_30
#define AO_SNEK_FLAGS_30 0
#endif

static const struct ao_snek_pin ao_snek_pin[AO_SNEK_NUM_PIN] = {
	{ .gpio = AO_SNEK_GPIO_0, .pin = AO_SNEK_PIN_0, .timer = AO_SNEK_TIMER_0, .channel = AO_SNEK_CHANNEL_0, .adc = AO_SNEK_ADC_0, .flags = AO_SNEK_FLAGS_0 },
	{ .gpio = AO_SNEK_GPIO_1, .pin = AO_SNEK_PIN_1, .timer = AO_SNEK_TIMER_1, .channel = AO_SNEK_CHANNEL_1, .adc = AO_SNEK_ADC_1, .flags = AO_SNEK_FLAGS_1 },
	{ .gpio = AO_SNEK_GPIO_2, .pin = AO_SNEK_PIN_2, .timer = AO_SNEK_TIMER_2, .channel = AO_SNEK_CHANNEL_2, .adc = AO_SNEK_ADC_2, .flags = AO_SNEK_FLAGS_2 },
	{ .gpio = AO_SNEK_GPIO_3, .pin = AO_SNEK_PIN_3, .timer = AO_SNEK_TIMER_3, .channel = AO_SNEK_CHANNEL_3, .adc = AO_SNEK_ADC_3, .flags = AO_SNEK_FLAGS_3 },
	{ .gpio = AO_SNEK_GPIO_4, .pin = AO_SNEK_PIN_4, .timer = AO_SNEK_TIMER_4, .channel = AO_SNEK_CHANNEL_4, .adc = AO_SNEK_ADC_4, .flags = AO_SNEK_FLAGS_4 },
	{ .gpio = AO_SNEK_GPIO_5, .pin = AO_SNEK_PIN_5, .timer = AO_SNEK_TIMER_5, .channel = AO_SNEK_CHANNEL_5, .adc = AO_SNEK_ADC_5, .flags = AO_SNEK_FLAGS_5 },
	{ .gpio = AO_SNEK_GPIO_6, .pin = AO_SNEK_PIN_6, .timer = AO_SNEK_TIMER_6, .channel = AO_SNEK_CHANNEL_6, .adc = AO_SNEK_ADC_6, .flags = AO_SNEK_FLAGS_6 },
	{ .gpio = AO_SNEK_GPIO_7, .pin = AO_SNEK_PIN_7, .timer = AO_SNEK_TIMER_7, .channel = AO_SNEK_CHANNEL_7, .adc = AO_SNEK_ADC_7, .flags = AO_SNEK_FLAGS_7 },
	{ .gpio = AO_SNEK_GPIO_8, .pin = AO_SNEK_PIN_8, .timer = AO_SNEK_TIMER_8, .channel = AO_SNEK_CHANNEL_8, .adc = AO_SNEK_ADC_8, .flags = AO_SNEK_FLAGS_8 },
	{ .gpio = AO_SNEK_GPIO_9, .pin = AO_SNEK_PIN_9, .timer = AO_SNEK_TIMER_9, .channel = AO_SNEK_CHANNEL_9, .adc = AO_SNEK_ADC_9, .flags = AO_SNEK_FLAGS_9 },
	{ .gpio = AO_SNEK_GPIO_10, .pin = AO_SNEK_PIN_10, .timer = AO_SNEK_TIMER_10, .channel = AO_SNEK_CHANNEL_10, .adc = AO_SNEK_ADC_10, .flags = AO_SNEK_FLAGS_10 },
	{ .gpio = AO_SNEK_GPIO_11, .pin = AO_SNEK_PIN_11, .timer = AO_SNEK_TIMER_11, .channel = AO_SNEK_CHANNEL_11, .adc = AO_SNEK_ADC_11, .flags = AO_SNEK_FLAGS_11 },
	{ .gpio = AO_SNEK_GPIO_12, .pin = AO_SNEK_PIN_12, .timer = AO_SNEK_TIMER_12, .channel = AO_SNEK_CHANNEL_12, .adc = AO_SNEK_ADC_12, .flags = AO_SNEK_FLAGS_12 },
	{ .gpio = AO_SNEK_GPIO_13, .pin = AO_SNEK_PIN_13, .timer = AO_SNEK_TIMER_13, .channel = AO_SNEK_CHANNEL_13, .adc = AO_SNEK_ADC_13, .flags = AO_SNEK_FLAGS_13 },
	{ .gpio = AO_SNEK_GPIO_14, .pin = AO_SNEK_PIN_14, .timer = AO_SNEK_TIMER_14, .channel = AO_SNEK_CHANNEL_14, .adc = AO_SNEK_ADC_14, .flags = AO_SNEK_FLAGS_14 },
	{ .gpio = AO_SNEK_GPIO_15, .pin = AO_SNEK_PIN_15, .timer = AO_SNEK_TIMER_15, .channel = AO_SNEK_CHANNEL_15, .adc = AO_SNEK_ADC_15, .flags = AO_SNEK_FLAGS_15 },
	{ .gpio = AO_SNEK_GPIO_16, .pin = AO_SNEK_PIN_16, .timer = AO_SNEK_TIMER_16, .channel = AO_SNEK_CHANNEL_16, .adc = AO_SNEK_ADC_16, .flags = AO_SNEK_FLAGS_16 },
	{ .gpio = AO_SNEK_GPIO_17, .pin = AO_SNEK_PIN_17, .timer = AO_SNEK_TIMER_17, .channel = AO_SNEK_CHANNEL_17, .adc = AO_SNEK_ADC_17, .flags = AO_SNEK_FLAGS_17 },
	{ .gpio = AO_SNEK_GPIO_18, .pin = AO_SNEK_PIN_18, .timer = AO_SNEK_TIMER_18, .channel = AO_SNEK_CHANNEL_18, .adc = AO_SNEK_ADC_18, .flags = AO_SNEK_FLAGS_18 },
	{ .gpio = AO_SNEK_GPIO_19, .pin = AO_SNEK_PIN_19, .timer = AO_SNEK_TIMER_19, .channel = AO_SNEK_CHANNEL_19, .adc = AO_SNEK_ADC_19, .flags = AO_SNEK_FLAGS_19 },
#if AO_SNEK_NUM_PIN > 20
	{ .gpio = AO_SNEK_GPIO_20, .pin = AO_SNEK_PIN_20, .timer = AO_SNEK_TIMER_20, .channel = AO_SNEK_CHANNEL_20, .adc = AO_SNEK_ADC_20, .flags = AO_SNEK_FLAGS_20 },
#endif
#if AO_SNEK_NUM_PIN > 21
	{ .gpio = AO_SNEK_GPIO_21, .pin = AO_SNEK_PIN_21, .timer = AO_SNEK_TIMER_21, .channel = AO_SNEK_CHANNEL_21, .adc = AO_SNEK_ADC_21, .flags = AO_SNEK_FLAGS_21 },
#endif
#if AO_SNEK_NUM_PIN > 22
	{ .gpio = AO_SNEK_GPIO_22, .pin = AO_SNEK_PIN_22, .timer = AO_SNEK_TIMER_22, .channel = AO_SNEK_CHANNEL_22, .adc = AO_SNEK_ADC_22, .flags = AO_SNEK_FLAGS_22 },
#endif
#if AO_SNEK_NUM_PIN > 23
	{ .gpio = AO_SNEK_GPIO_23, .pin = AO_SNEK_PIN_23, .timer = AO_SNEK_TIMER_23, .channel = AO_SNEK_CHANNEL_23, .adc = AO_SNEK_ADC_23, .flags = AO_SNEK_FLAGS_23 },
#endif
#if AO_SNEK_NUM_PIN > 24
	{ .gpio = AO_SNEK_GPIO_24, .pin = AO_SNEK_PIN_24, .timer = AO_SNEK_TIMER_24, .channel = AO_SNEK_CHANNEL_24, .adc = AO_SNEK_ADC_24, .flags = AO_SNEK_FLAGS_24 },
#endif
#if AO_SNEK_NUM_PIN > 25
	{ .gpio = AO_SNEK_GPIO_25, .pin = AO_SNEK_PIN_25, .timer = AO_SNEK_TIMER_25, .channel = AO_SNEK_CHANNEL_25, .adc = AO_SNEK_ADC_25, .flags = AO_SNEK_FLAGS_25 },
#endif
#if AO_SNEK_NUM_PIN > 26
	{ .gpio = AO_SNEK_GPIO_26, .pin = AO_SNEK_PIN_26, .timer = AO_SNEK_TIMER_26, .channel = AO_SNEK_CHANNEL_26, .adc = AO_SNEK_ADC_26, .flags = AO_SNEK_FLAGS_26 },
#endif
#if AO_SNEK_NUM_PIN > 27
	{ .gpio = AO_SNEK_GPIO_27, .pin = AO_SNEK_PIN_27, .timer = AO_SNEK_TIMER_27, .channel = AO_SNEK_CHANNEL_27, .adc = AO_SNEK_ADC_27, .flags = AO_SNEK_FLAGS_27 },
#endif
#if AO_SNEK_NUM_PIN > 28
	{ .gpio = AO_SNEK_GPIO_28, .pin = AO_SNEK_PIN_28, .timer = AO_SNEK_TIMER_28, .channel = AO_SNEK_CHANNEL_28, .adc = AO_SNEK_ADC_28, .flags = AO_SNEK_FLAGS_28 },
#endif
#if AO_SNEK_NUM_PIN > 29
	{ .gpio = AO_SNEK_GPIO_29, .pin = AO_SNEK_PIN_29, .timer = AO_SNEK_TIMER_29, .channel = AO_SNEK_CHANNEL_29, .adc = AO_SNEK_ADC_29, .flags = AO_SNEK_FLAGS_29 },
#endif
#if AO_SNEK_NUM_PIN > 30
	{ .gpio = AO_SNEK_GPIO_30, .pin = AO_SNEK_PIN_30, .timer = AO_SNEK_TIMER_30, .channel = AO_SNEK_CHANNEL_30, .adc = AO_SNEK_ADC_30, .flags = AO_SNEK_FLAGS_30 },
#endif
#if AO_SNEK_NUM_PIN > 31
#error too many pins
#endif
};


void
ao_snek_port_init(void)
{
	uint8_t p;
	for (p = 0; p < AO_SNEK_NUM_PIN; p++) {
		ao_snek_clr_pwm(ao_snek_pin[p].gpio, ao_snek_pin[p].pin);
		ao_enable_input(ao_snek_pin[p].gpio, ao_snek_pin[p].pin, AO_EXTI_MODE_PULL_NONE);
	}

	memset(power, 0xff, sizeof(power));
}

static void
ao_snek_port_set_pwm(uint8_t p, uint16_t pwm)
{
	ao_snek_set_pwm(ao_snek_pin[p].gpio, ao_snek_pin[p].pin, ao_snek_pin[p].timer, ao_snek_pin[p].channel, pwm);
}

static void
ao_snek_port_clr_pwm(uint8_t p)
{
	ao_snek_clr_pwm(ao_snek_pin[p].gpio, ao_snek_pin[p].pin);
}

static void
ao_snek_port_set(uint8_t p, uint16_t value)
{
	ao_gpio_set(ao_snek_pin[p].gpio, ao_snek_pin[p].pin, !!value);
}

static uint8_t
ao_snek_port_get(uint8_t p)
{
	return ao_gpio_get(ao_snek_pin[p].gpio, ao_snek_pin[p].pin);
}

static uint16_t
ao_snek_port_get_analog(uint8_t p)
{
	return ao_snek_get_adc(ao_snek_pin[p].adc);
}

static bool
has_pwm(uint8_t p)
{
	return ao_snek_pin[p].timer != NULL;
}

static bool
has_adc(uint8_t p)
{
	return ao_snek_pin[p].adc != 0xff;
}

static bool
is_on(uint8_t pin)
{
	return (on_pins >> pin) & 1;
}

static void
set_on(uint8_t pin)
{
	on_pins |= ((uint32_t) 1) << pin;
}

static void
set_off(uint8_t pin)
{
	on_pins &= ~(((uint32_t) 1) << pin);
}

static snek_poly_t
_set_out(uint8_t pin, uint16_t p)
{
	if (has_pwm(pin)) {
		if (0 < p && p < SNEK_PWM_MAX) {
			ao_snek_port_set_pwm(pin, p);
			return SNEK_NULL;
		}
		ao_snek_port_clr_pwm(pin);
	}
	ao_snek_port_set(pin, p);
	return SNEK_NULL;
}

#ifdef SNEK_DRV8833
static snek_poly_t
set_out(uint8_t pin)
{
	uint16_t	p = 0;

	if (IS_DRV8833_DIR(pin) || IS_DRV8833_PWM(pin)) {
		uint8_t	dir, pwm;

		if (IS_DRV8833_DIR(pin)) {
			dir = pin;
			pwm = DRV8833_FIND_PWM(pin);
		} else {
			pwm = pin;
			dir = DRV8833_FIND_DIR(pin);
		}
		if (is_on(pwm))
			p = power[pwm];
		if (is_on(dir)) {
			_set_out(pwm, 0);
			return _set_out(dir, p);
		} else {
			_set_out(dir, 0);
			return _set_out(pwm, p);
		}
	} else {
		if (is_on(pin))
			p = power[pin];

		return _set_out(pin, p);
	}
}
#else
static snek_poly_t set_out(uint8_t pin)
{
	uint16_t	p = 0;

	if (is_on(pin))
		p = power[pin];

	return _set_out(pin, p);
}
#endif

static void
set_dir(uint8_t pin, uint8_t d)
{
	if (d) {
		if (has_adc(pin))
			ao_snek_clr_adc(ao_snek_pin[pin].gpio, ao_snek_pin[pin].pin);
		ao_enable_output(ao_snek_pin[pin].gpio, ao_snek_pin[pin].pin, is_on(pin) && power[pin] != 0);
		set_out(pin);
	} else {
		uint32_t mode = AO_EXTI_MODE_PULL_UP;
		if (has_adc(pin)) {
			ao_snek_set_adc(ao_snek_pin[pin].gpio, ao_snek_pin[pin].pin);
			mode = AO_EXTI_MODE_PULL_NONE;
		} else if (ao_snek_pin[pin].flags & SNEK_PIN_PULL_DOWN) {
			mode = AO_EXTI_MODE_PULL_DOWN;
		}
		ao_enable_input(ao_snek_pin[pin].gpio, ao_snek_pin[pin].pin, mode);
	}
}

static uint8_t
snek_poly_get_pin(snek_poly_t a)
{
	snek_soffset_t p = snek_poly_get_soffset(a);
	if (p < 0 || AO_SNEK_NUM_PIN <= p)
		snek_error_value(a);
	return p;
}

snek_poly_t
snek_builtin_talkto(snek_poly_t a)
{
	snek_list_t *l;
	uint8_t p, d;

	if (snek_poly_type(a) == snek_list) {
		l = snek_poly_to_list(a);
		p = snek_poly_get_pin(snek_list_get(l, SNEK_ZERO, true));
		d = snek_poly_get_pin(snek_list_get(l, SNEK_ONE, true));
	} else {
		p = d = snek_poly_get_pin(a);
	}
	if (!snek_abort) {
		set_dir(p, 1);
		if (p != d)
			set_dir(d, 1);
		power_pin = p;
		dir_pin = d;
	}
	return SNEK_NULL;
}

snek_poly_t
snek_builtin_setpower(snek_poly_t a)
{
	float p = snek_poly_get_float(a);
	if (p < 0.0f) p = 0.0f;
	if (p > 1.0f) p = 1.0f;
	power[power_pin] = (uint16_t) (p * SNEK_PWM_MAX + 0.5f);
	return set_out(power_pin);
}

snek_poly_t
snek_builtin_setleft(void)
{
	set_on(dir_pin);
	return set_out(dir_pin);
}

snek_poly_t
snek_builtin_setright(void)
{
	set_off(dir_pin);
	return set_out(dir_pin);
}

snek_poly_t
snek_builtin_on(void)
{
	set_on(power_pin);
	return set_out(power_pin);
}

snek_poly_t
snek_builtin_off(void)
{
	set_off(power_pin);
	return set_out(power_pin);
}

snek_poly_t
snek_builtin_onfor(snek_poly_t a)
{
	snek_builtin_on();
	snek_builtin_time_sleep(a);
	snek_builtin_off();
	return a;
}

#define analog_reference 1

snek_poly_t
snek_builtin_read(snek_poly_t a)
{
	uint8_t p = snek_poly_get_pin(a);
	if (snek_abort)
		return SNEK_NULL;
	set_dir(p, 0);

	if (has_adc(p)) {
		float value = ao_snek_port_get_analog(p) / (float) AO_ADC_MAX;
		return snek_float_to_poly(value);
	} else {
		return snek_bool_to_poly(ao_snek_port_get(p));
	}
}

snek_poly_t
snek_builtin_stopall(void)
{
	uint8_t p;
	for (p = 0; p < AO_SNEK_NUM_PIN; p++)
		if (on_pins & ((uint32_t) 1 << p)) {
			set_off(p);
			set_out(p);
		}
	return SNEK_NULL;
}


static uint8_t
snek_poly_to_inten(snek_poly_t a)
{
	float f = snek_poly_get_float(a);
	if (f < 0.0f) f = 0.0f;
	if (f > 1.0f) f = 1.0f;
	return (uint8_t) (f * 255.0f + 0.5f);
}

struct snek_neopixel *snek_neopixels;
static snek_offset_t	snek_neopixel_count;

snek_poly_t
snek_builtin_neopixel(snek_poly_t pixels)
{
	if (snek_poly_type(pixels) != snek_list)
		return snek_error_type_1(pixels);
	snek_list_t *pixels_list = snek_poly_to_list(pixels);
	if (snek_list_type(pixels_list) == snek_list_dict)
		return snek_error_type_1(pixels);

	if (snek_neopixels == NULL || snek_neopixel_count < pixels_list->size) {
		snek_neopixels = snek_alloc(pixels_list->size * sizeof (struct snek_neopixel));
		if (!snek_neopixels)
			return SNEK_NULL;
		snek_neopixel_count = pixels_list->size;
	}

	snek_poly_t *pixels_data = snek_list_data(pixels_list);
	for (int p = 0; p < pixels_list->size; p++) {
		snek_poly_t pixel = pixels_data[p];

		if (snek_poly_type(pixel) != snek_list)
			return snek_error_type_1(pixel);
		snek_list_t *pixel_list = snek_poly_to_list(pixel);
		if (snek_list_type(pixel_list) == snek_list_dict || pixel_list->size != 3)
			return snek_error_type_1(pixel);
		snek_poly_t *pixel_data = snek_list_data(pixel_list);
		snek_neopixels[p].r = snek_poly_to_inten(pixel_data[0]);
		snek_neopixels[p].g = snek_poly_to_inten(pixel_data[1]);
		snek_neopixels[p].b = snek_poly_to_inten(pixel_data[2]);
		if (snek_abort)
			return SNEK_NULL;
	}
	if (power_pin == dir_pin)
		ao_snek_neopixel_write(ao_snek_pin[power_pin].gpio, ao_snek_pin[power_pin].pin,
				       pixels_list->size, snek_neopixels);
	else
		ao_snek_apa102_write(ao_snek_pin[power_pin].gpio,
				     ao_snek_pin[power_pin].pin,
				     ao_snek_pin[dir_pin].gpio,
				     ao_snek_pin[dir_pin].pin,
				     pixels_list->size, snek_neopixels);
	return SNEK_NULL;
}
