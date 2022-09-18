#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

#define ADC_INPUT_CHANNEL        CHANNEL0
/*AVCC
 * AREF
 * RESERVED
 * INTERNAL
 */
#define ADC_REF_VOLT_SELECTION   AVCC
#define ADC_ENABLE      ENABLE
/*PRESCALER_DIV_BY_2
 * PRESCALER_DIV_BY_4
 * PRESCALER_DIV_BY_8
 * PRESCALER_DIV_BY_16
 * PRESCALER_DIV_BY_32
 * PRESCALER_DIV_BY_64
 * PRESCALER_DIV_BY_128
 *
 *
 */
#define ADC_PRESCALER    PRESCALER_DIV_BY_64

#endif
