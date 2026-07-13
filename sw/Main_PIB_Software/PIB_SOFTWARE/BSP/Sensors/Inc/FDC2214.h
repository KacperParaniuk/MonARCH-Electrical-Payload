#ifndef __FDC2214_H__
#define __FDC2214_H__

#include "stm32l4xx_hal.h"
#include "main.h"
#include "i2c.h"

#define FDC2214 0x2A
#define DATA_MSB_CH0 0x00
#define DATA_LSB_CH0 0x01
#define DATA_MSB_CH1 0x02
#define DATA_LSB_CH1 0x03
#define DATA_MSB_CH2 0x04
#define DATA_LSB_CH2 0x05
#define DATA_MSB_CH3 0x06
#define DATA_LSB_CH3 0x07
#define RCOUNT_CH0 0x08
#define RCOUNT_CH1 0x09
#define RCOUNT_CH2 0x0A
#define RCOUNT_CH3 0x0B
#define OFFSET_CH0 0x0C
#define OFFSET_CH1 0x0D
#define OFFSET_CH2 0x0E
#define OFFSET_CH3 0x0F
#define SETTLECOUNT_CH0 0x10
#define SETTLECOUNT_CH1 0x11
#define SETTLECOUNT_CH2 0x12
#define SETTLECOUNT_CH3 0x13
#define CLOCK_DIVIDERS_C_CH0 0x14
#define CLOCK_DIVIDERS_C_CH1 0x15
#define CLOCK_DIVIDERS_C_CH2 0x16
#define CLOCK_DIVIDERS_C_CH3 0x17
#define STATUS 0x18
#define ERROR_CONFIG 0x19
#define CONFIG 0x1A
#define MUX_CONFIG 0x1B
#define RESET_DEV 0x1C
#define DRIVE_CURRENT_CH0 0x1E
#define DRIVE_CURRENT_CH1 0x1F
#define DRIVE_CURRENT_CH2 0x20
#define DRIVE_CURRENT_CH3 0x21
#define MANUFACTURER_ID 0x7E
#define DEVICE_ID 0x7F
#define MANUFACTURER_ID_val 0x5449
#define DEVICE_ID_val 0x3055

// Circuit Values

#define FDC2214_L_HENRY       18e-6f   /* 18 uH inductor */
//#define FDC2214_C_PARALLEL    33e-12f  /* 33 pF fixed cap */
#define FDC2214_C_PARALLEL    100e-9f  /* 33 pF fixed cap */

#define FDC2214_F_REF         43400000.0f /* internal clock Hz Typical: 43.4 MHz */
#define FDC2214_CAP_EMPTY   0 // insert capacitance reading when container is empty
#define FDC2214_ACUM_HREF  500 // (mm)  insert height of container (units of desire)

// =============================================================================
// MUX_CONFIG fields
// =============================================================================
#define FDC2214_AUTOSCAN_DISABLED   (0x0000)
#define FDC2214_AUTOSCAN_ENABLED    (0x8000)

#define FDC2214_RR_SEQ_CH0_CH1      (0x0000)
#define FDC2214_RR_SEQ_CH0_CH1_CH2  (0x2000)
#define FDC2214_RR_SEQ_ALL          (0x4000)

// MUX_CONFIG reserved bits required by datasheet
#define FDC2214_MUX_RESERVED        (0x0208)

#define FDC2214_DEGLITCH_1MHZ       (0x0001)
#define FDC2214_DEGLITCH_3_3MHZ     (0x0004)
#define FDC2214_DEGLITCH_10MHZ      (0x0005)
#define FDC2214_DEGLITCH_33MHZ      (0x0007)



// =============================================================================
// CONFIG register fields
// =============================================================================
#define FDC2214_CONFIG_ACTIVE_CH0   (0x0000)
#define FDC2214_CONFIG_ACTIVE_CH1   (0x4000)
#define FDC2214_CONFIG_ACTIVE_CH2   (0x8000)
#define FDC2214_CONFIG_ACTIVE_CH3   (0xC000)

#define FDC2214_CONFIG_SLEEP_EN     (0x2000)  // bit 13
#define FDC2214_CONFIG_SENSOR_ACT_LP (0x0800) // bit 11 - low-power sensor activation
#define FDC2214_CONFIG_REF_CLK_EXT  (0x0400)  // bit 10
#define FDC2214_CONFIG_INTB_DIS     (0x0100)  // bit 8
#define FDC2214_CONFIG_HIGH_CURRENT (0x0080)  // bit 7

// CONFIG reserved bits the datasheet requires to be set (bit 12 + bit 0).
#define FDC2214_CONFIG_RESERVED     (0x1001)



// =============================================================================
// CLOCK_DIVIDERS fields
// =============================================================================
#define FDC2214_FIN_SEL_LOW_FREQ    (0x1000)  // sensor < 8.75 MHz, divider = 1
#define FDC2214_FIN_SEL_HIGH_FREQ   (0x2000)  // sensor 0.01 - 10 MHz, divider = 2


typedef enum {
    FDC2214_CH0 = 0,
    FDC2214_CH1 = 1,
    FDC2214_CH2 = 2,
    FDC2214_CH3 = 3
} fdc2214_channel_t;

// Cached CONFIG and MUX_CONFIG so individual setters can update single fields
// without losing the rest of the word.
uint16_t  _config;
uint16_t  _mux_config;

// Cached per-channel CLOCK_DIVIDERS so frequency conversion knows CH_FIN_DIVIDER.
uint16_t  _clock_div[4];

// ------------------------------------------------------------- lifecycle
uint8_t FDC2214_Begin();
uint8_t FDC2214_Init();
uint8_t reset_fdc2214();
void FDC2214_Device_ID(uint8_t buffer);
int FDC2214_Check_Device_ID();

// -------------------------------------------------------- channel config
void      setReferenceCount(fdc2214_channel_t ch, uint16_t rcount);
void      setSettleCount(fdc2214_channel_t ch, uint16_t scount);
void      setOffset(fdc2214_channel_t ch, uint16_t offset);
void      setClockDividers(fdc2214_channel_t ch, uint16_t fin_sel, uint16_t fref_div);
void      setDriveCurrent(fdc2214_channel_t ch, uint8_t idrive_5bit);

// --------------------- config
uint8_t FDC2214_configure_defaults(void);

// ------------------------------------------------------ device-wide config

void FDC2214_set_active_channel(fdc2214_channel_t ch);
void FDC2214_setAutoscan(uint8_t enable);
void FDC2214_setDeglitch(uint16_t deglitch_field);
void FDC2214_setReferenceClockSource(uint8_t external);
void FDC2214_setHighCurrentDrive(uint8_t enable);
void FDC2214_setSleep(uint8_t sleep);
void FDC2214_wakeup();
void FDC2214_sleep();

// ------------------------------------------------------
uint16_t read_register(uint16_t reg);
uint8_t write_register(uint16_t reg, uint16_t value);

uint32_t FDC2214_get_capacitance_data(uint8_t channel);
uint32_t FDC2214_read_data(uint8_t channel);
float FDC2214_read_capacitance(uint8_t channel, float *cap_pf);
float FDC2214_read_differential_capacitance(uint8_t accumulator);
uint8_t FDC2214_read_accumulator_height(uint8_t accumulator);
uint8_t isConnected();


void write_config();
void write_mux_config();



#endif
