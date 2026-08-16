#include <FDC2214.h>

// Kacper Paraniuk 03/21/26


// Inspired by Protocentral_fdc2214_arduino driver
// https://github.com/Protocentral/protocentral_fdc2214_arduino/blob/main/src/Protocentral_FDC2214.cpp#L268

// Also inspired by lifzcn STM32 HAL Driver.
// https://github.com/lifzcn/FDC2214_C_HAL/blob/main/Drivers/fdc2214.c

extern I2C_HandleTypeDef hi2c4;


uint8_t cof[2];
volatile uint16_t check[2];
HAL_StatusTypeDef ret;

// Cached CONFIG and MUX_CONFIG so individual setters can update single fields
// without losing the rest of the word.
static uint16_t  _config;
static uint16_t  _mux_config;

// Cached per-channel CLOCK_DIVIDERS so frequency conversion knows CH_FIN_DIVIDER.
static uint16_t  _clock_div[4];




// ============================================================================
// Lifecycle
// ============================================================================


uint8_t FDC2214_Begin(){

	if(isConnected()!=0){
		return -1;
	}
	else{
		return 0;
	}

}


uint8_t isConnected(){

	ret = HAL_I2C_Mem_Read(&hi2c4, FDC2214, MANUFACTURER_ID, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -24;
	}

	check[0] = ((uint16_t)cof[0] << 8) | cof[1];  // big endian 	(RECONSTRUCT BITS INTO A 16 BIT VALUE) assuming we are using big endian


	ret = HAL_I2C_Mem_Read(&hi2c4, FDC2214, DEVICE_ID, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -25;
	}

	check[1] = ((uint16_t)cof[0] << 8) | cof[1];

	if ((check[0] == MANUFACTURER_ID_val) && (check[1] == DEVICE_ID_val))
		return 0;
	else
		return -1;

}

uint8_t reset_fdc2214(){
	// Reset Registers in Device.

	return write_register(RESET_DEV, 0x80);

}


int FDC2214_get_device_id(){

	HAL_I2C_Mem_Read(&hi2c4, FDC2214, DEVICE_ID, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	check[1] = ((uint16_t)cof[0] << 8) | cof[1];


	return check[1];
}



int FDC2214_Check_Device_ID(){


	HAL_I2C_Mem_Read(&hi2c4, FDC2214, MANUFACTURER_ID, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);


	check[0] = ((uint16_t)cof[0] << 8) | cof[1];  // big endian 	(RECONSTRUCT BITS INTO A 16 BIT VALUE) assuming we are using big endian

	if(check[0] == MANUFACTURER_ID_val){
		return 1;
	}
	else{
		return check[0];
	}

	HAL_I2C_Mem_Read(&hi2c4, FDC2214, DEVICE_ID, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	check[1] = ((uint16_t)cof[0] << 8) | cof[1];

	if ((check[0] == MANUFACTURER_ID_val) && (check[1] == DEVICE_ID_val))
		return 1;
	else
		return 0;


}

// ============================================================================
// Channel configuration
// ============================================================================

void setReferenceCount(fdc2214_channel_t ch, uint16_t rcount){
	write_register(RCOUNT_CH0 + ch, rcount);

}

void setSettleCount(fdc2214_channel_t ch, uint16_t scount){
	write_register(SETTLECOUNT_CH0 + ch, scount);
}

void setOffset(fdc2214_channel_t ch, uint16_t offset){
	write_register(OFFSET_CH0 + ch, offset);
}

void setClockDividers(fdc2214_channel_t ch, uint16_t fin_sel, uint16_t fref_div){
    // CLOCK_DIVIDERS layout:
    //   bits [13:12] = CHx_FIN_SEL (1 = sensor < 8.75 MHz, 2 = high-freq path /2)
    //   bits [9:0]   = CHx_FREF_DIVIDER (must be >= 1)
	if (fref_div == 0) fref_div = 1;
	uint16_t v = (fin_sel & 0x3000) | (fref_div & 0x03FF);
	_clock_div[ch] = v;
	write_register(CLOCK_DIVIDERS_C_CH0 + ch, v);

}




void setDriveCurrent(fdc2214_channel_t ch, uint8_t idrive_5bit){
    // DRIVE_CURRENT_CHx layout:
    //   bits [15:11] = IDRIVE (0..31)
    //   bits [10:6]  = INIT_IDRIVE (auto-calibrated, leave 0 for user-set)
    uint16_t v = ((uint16_t)(idrive_5bit & 0x1F)) << 11;
    write_register(DRIVE_CURRENT_CH0 + ch, v);

}

// ============================================================================
// One-shot sensible defaults
// ============================================================================

uint8_t FDC2214_configure_defaults(void)
{
	// FDC2214 Register Setup.

    // Per-channel: maximum reference count for best resolution, generous settle
    // count, high-frequency input path (sensor up to 10 MHz), reference divider 1,
    // mid-range drive current.

	for(uint8_t i = 0; i<4; i++){
		fdc2214_channel_t ch = (fdc2214_channel_t)i;
		setReferenceCount(ch, 0xFFFF);
		setSettleCount(ch, 0x000A);
		setOffset(ch,0x0000);
		setClockDividers(ch, FDC2214_FIN_SEL_HIGH_FREQ, 0x0001);
		setDriveCurrent(ch, 0x0F);
	}

    // Disable per-channel error reporting on data outputs (kept clean by default).
    write_register(ERROR_CONFIG, 0x0000);

    // MUX_CONFIG: autoscan disabled by default, single CH0, 10 MHz deglitch.
    _mux_config = FDC2214_AUTOSCAN_DISABLED | FDC2214_MUX_RESERVED | FDC2214_DEGLITCH_10MHZ;
    write_mux_config();

    // CONFIG: hold device in sleep until start() is called. Internal oscillator,
    // INTB enabled, full-current sensor activation, low-current drive.
    _config = FDC2214_CONFIG_RESERVED | FDC2214_CONFIG_ACTIVE_CH0 | FDC2214_CONFIG_SLEEP_EN;
    write_config();

    return 0;

}

	// R-COUNT || R-Count MAXIMIZED = Highest Accuracy (Num Bits of Accuracy)

//	cof[0] = 0xFF;
//	cof[1] = 0xFF;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, RCOUNT_CH0, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);      //	for (i = 0; i < 20; i++)
//	HAL_Delay(20);
//
//	//;
//
//	if(ret != HAL_OK){
//		return -1;
//	}
//
//	cof[0] = 0xFF;
//	cof[1] = 0xFF;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, RCOUNT_CH1, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -2;
//	}
//
//	cof[0] = 0xFF;
//	cof[1] = 0xFF;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, RCOUNT_CH2, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -3;
//	}
//
//	cof[0] = 0xFF;
//	cof[1] = 0xFF;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, RCOUNT_CH3, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -4;
//	}

	// OFFSET || NO OFFSET
//
//	cof[0] = 0x00;
//	cof[1] = 0x00;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, OFFSET_CH0, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -5;
//	}
//
//	cof[0] = 0x00;
//	cof[1] = 0x00;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, OFFSET_CH1, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -6;
//	}
//
//	cof[0] = 0x00;
//	cof[1] = 0x00;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, OFFSET_CH2, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -7;
//	}
//
//
//	cof[0] = 0x00;
//	cof[1] = 0x00;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, OFFSET_CH3, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -8;
//	}

	// SETTLE COUNT ||
//
//	Amplitude
//	    |
//	    |               plateau (stable - measure here)
//	    |         ___________________________
//	    |        /
//	    |       /   ← settling period
//	    |      /
//	    |_____/
//	    |
//	    └─────────────────────────────────── time
//	           ^                ^
//	       channel          measurement
//	       activated          starts
//	           └── SETTLECOUNT ┘



	// fclk ranges from 35 Mhz - 55 Mhz with a TYPICAL clock speed of 43.4 Mhz
	// SETTLECOUNT = 0x0064 (100 decimal) — good balance of speed vs stability (100 Cycles)

	//  (1.8 x 43.4e6 x 35e-12 x 9.87) / (32 x 0.00157) = 0.47,

	// 100 is definitely on the safe side.


	// WE CAN PLAY AROUND WITH THE SETTLE TIME.

//	cof[0] = 0x00;
//	cof[1] = 0x64;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, SETTLECOUNT_CH0, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -9;
//	}
//
//	cof[0] = 0x00;
//	cof[1] = 0x64;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, SETTLECOUNT_CH1, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -10;
//	}
//
//	cof[0] = 0x00;
//	cof[1] = 0x64;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, SETTLECOUNT_CH2, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//
//	if(ret != HAL_OK){
//		return -11;
//	}
//
//	cof[0] = 0x00;
//	cof[1] = 0x64;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, SETTLECOUNT_CH3, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -12;
//	}

	// CLOCK DIVIDERS || This register configures both F_IN_SEL & F_REF_Divder -> CHx_FIN_SEL -> b01 for differential config and between 0.01 Mhz and 8.75 Mhz
	// Bit pattern: 00 01 00 0000000001 = 0x1001

//	cof[0] = 0x10; // differential pair divide by sensor F_IN by 1 (Divide by two for single is setting byte value to 0x11)
//	cof[1] = 0x01; // 0x01 equals full clock speed. fREFx = (f_clk / FREF_divider)
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, CLOCK_DIVIDERS_C_CH0, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -13;
//	}
//
//	cof[0] = 0x10; // [13:12]
//	cof[1] = 0x01; // [9:0]
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, CLOCK_DIVIDERS_C_CH1, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -14;
//	}
//
//	cof[0] = 0x10;
//	cof[1] = 0x01;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, CLOCK_DIVIDERS_C_CH2, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -15;
//	}
//
//	cof[0] = 0x10;
//	cof[1] = 0x01;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, CLOCK_DIVIDERS_C_CH3, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -16;
//	}

	// Error CONFIG
	// controls which error conditions drive the interrupt pin.
	// 0x0000 -> No error conditions

//	cof[0] = 0x00;
//	cof[1] = 0x00;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, ERROR_CONFIG, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -17;
//	}

	// DRIVE CURRENT

	// The goal is to achieve oscillation amplitude between 1.2 Vpk and 1.8 Vpk. Too low = insufficient oscillation, noisy reading. Too high = clipping, distorted result.


	// DRIVE_CURRENT: IDRIVE in bits [15:11]
	// 0x1F << 11 = 0b1111100000000000 = 0xF800
	// MAX CURRENT FOR FAST RISE TIME (for testing) -> 1.57 mA

//	cof[0] = 0xF8;
//	cof[1] = 0x00;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, DRIVE_CURRENT_CH0, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -18;
//	}
//
//	cof[0] = 0xF8;
//	cof[1] = 0x00;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, DRIVE_CURRENT_CH1, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//
//	if(ret != HAL_OK){
//	    return -19;
//	}
//
//	cof[0] = 0xF8;
//	cof[1] = 0x00;
//	HAL_Delay(20);
//
//	cof[0] = 0xF8;
//	cof[1] = 0x00;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, DRIVE_CURRENT_CH3, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//	if(ret != HAL_OK){
//		return -20;
//	}


	// MUX CONFIG

	// 0xC2 1100 0010 # Auto Scan Enable, Ch0, Ch1, Ch2, Ch3 single conversion on each sequence and loops. AND places neccessary bit with 2
	// 0x0C 0000 1101 # 1 bit for necessary setup + 101 for deglitch filter (10 Mhz)
//
//	cof[0] = 0xC2; // 1100 0010
//	cof[1] = 0x0C; // 0000 1101
//
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, MUX_CONFIG, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(20);
//
//
//	if(ret != HAL_OK){
//		return -21;
//	}


	// CONFIG - takes chip out of sleep mode and begins convertsions.

	// 00 0 1 1 1 0 0 1 0 000001

	// 0x1A 0001 1100
	// 0x81 1000 0001

	// Active Channel Sequential ON
	// Sleep Mode_EN = OFF
	// RESERVED = 1
	// SENSOR ACTIVATE SEL = LOW POWER ACTIVATION MODE -> uses programmed driver current chx
	// RESERVED = 1
	// REF_CLK_SRC = 0 INTERNAL CLOCK = ON
	// RESERVED = 0
	// INTB_DIS = ON -> don't need interrupts
	// HIGH_CURRENT_DRV = 0 -> DRIVES with normal sensor current
	// RESERVED = 00 0001

//	cof[0] = 0x1A;
//	cof[1] = 0x81;
//	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, CONFIG, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
//	HAL_Delay(200);
//
//	if(ret != HAL_OK){
//		return -22;
//	}

void FDC2214_set_active_channel(fdc2214_channel_t ch){
	_config &= ~0xC000;
	_config |= ((uint16_t)ch) << 14;
	write_config();
}


void FDC2214_setAutoscan(uint8_t enable)
{
	uint16_t rr_sequence = FDC2214_RR_SEQ_ALL;
    _mux_config &= ~(0x8000 | 0x6000);
    if (enable) {
        _mux_config |= FDC2214_AUTOSCAN_ENABLED;
        _mux_config |= (rr_sequence & 0x6000);
    }
    write_mux_config();
}

void FDC2214_setDeglitch(uint16_t deglitch_field)
{
    _mux_config &= ~0x0007;
    _mux_config |= (deglitch_field & 0x0007);
    write_mux_config();
}

void FDC2214_setReferenceClockSource(uint8_t external)
{
    if (external) _config |= FDC2214_CONFIG_REF_CLK_EXT;
    else          _config &= ~FDC2214_CONFIG_REF_CLK_EXT;
    write_config();
}

void FDC2214_setHighCurrentDrive(uint8_t enable)
{
    if (enable) _config |= FDC2214_CONFIG_HIGH_CURRENT;
    else        _config &= ~FDC2214_CONFIG_HIGH_CURRENT;
    write_config();
}

void FDC2214_setSleep(uint8_t sleep)
{
    if (sleep) _config |= FDC2214_CONFIG_SLEEP_EN;
    else       _config &= ~FDC2214_CONFIG_SLEEP_EN;
    write_config();
}

void FDC2214_wakeup()
{
    _config &= ~FDC2214_CONFIG_SLEEP_EN;
    write_config();
}

void FDC2214_sleep()
{
    _config |= FDC2214_CONFIG_SLEEP_EN;
    write_config();
}

// ============================================================================


uint8_t FDC2214_is_data_ready(fdc2214_channel_t ch){

    uint16_t status = readStatus();
    uint16_t mask;
    switch (ch) {
        case FDC2214_CH0: mask = FDC2214_STATUS_CH0_UNREAD; break;
        case FDC2214_CH1: mask = FDC2214_STATUS_CH1_UNREAD; break;
        case FDC2214_CH2: mask = FDC2214_STATUS_CH2_UNREAD; break;
        case FDC2214_CH3: mask = FDC2214_STATUS_CH3_UNREAD; break;
        default: return -1;
    }
    return (status & mask) != 0;
}


// data = ( f_sensor * 2^28 ) / f_ref

//uint32_t FDC2214_read_data(uint8_t channel) // read 28 bit value. (RAW)
//{
//	volatile uint32_t data;
//	uint8_t pdata[4];
//
//	switch (channel)
//	{
//	case 0:
//		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_MSB_CH0, I2C_MEMADD_SIZE_8BIT, pdata, 2, 100); // size of two indicates two bytes.
//		HAL_Delay(20);
//
//		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_LSB_CH0, I2C_MEMADD_SIZE_8BIT, pdata + 2, 2, 100); // pdata + 2 = third item in the array
//		HAL_Delay(20);
//
//		data = ((pdata[0] << 24 | pdata[1] << 16 | pdata[2] << 8 | pdata[3]) & 0x0fffffff); // & masks off status bits. but they can be read also if wanted in the future.
//		return data;
//	case 1:
//		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_MSB_CH1, I2C_MEMADD_SIZE_8BIT, pdata, 2, 100);
//		HAL_Delay(20);
//
//		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_LSB_CH1, I2C_MEMADD_SIZE_8BIT, pdata + 2, 2, 100);
//		HAL_Delay(20);
//
//		data = ((pdata[0] << 24 | pdata[1] << 16 | pdata[2] << 8 | pdata[3]) & 0x0fffffff);
//		return data;
//	case 2:
//		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_MSB_CH2, I2C_MEMADD_SIZE_8BIT, pdata, 2, 100);
//		HAL_Delay(20);
//
//		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_LSB_CH2, I2C_MEMADD_SIZE_8BIT, pdata + 2, 2, 100);
//		HAL_Delay(20);
//
//		data = ((pdata[0] << 24 | pdata[1] << 16 | pdata[2] << 8 | pdata[3]) & 0x0fffffff);
//		return data;
//	case 3:
//		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_MSB_CH3, I2C_MEMADD_SIZE_8BIT, pdata, 2, 100);
//		HAL_Delay(20);
//
//		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_LSB_CH3, I2C_MEMADD_SIZE_8BIT, pdata + 2, 2, 100);
//		HAL_Delay(20);
//
//		data = ((pdata[0] << 24 | pdata[1] << 16 | pdata[2] << 8 | pdata[3]) & 0x0fffffff); // strip status / error bits
//		return data;
//	default:
//		return 0;
//	}
//}


// takes a capacitance_reading data and converts it into an actual capacitance
// the digitized output for each channel is proportional to the ratio of fSENSOR/fREF
// calculate Fsensor from reading.

// ============================================================================
// Data access
// ============================================================================


uint32_t FDC2214_readRawChannel(fdc2214_channel_t ch)
{
    uint16_t msb = read_register(DATA_MSB_CH0 + (ch * 2));
    uint16_t lsb = read_register(DATA_LSB_CH0 + (ch * 2));

    // Top 4 bits are error flags; data is 28 bits.
    uint32_t raw = ((uint32_t)(msb & 0x0FFF) << 16) | lsb;
    return raw & FDC2214_DATA_MASK_28BIT;
}

float FDC2214_readFrequencyHz(fdc2214_channel_t ch)
{
    uint32_t raw = FDC2214_readRawChannel(ch);
    if (raw == 0) return 0.0f;

    uint16_t cdiv     = _clock_div[ch];
    uint16_t fref_div = cdiv & 0x03FF;
    if (fref_div == 0) fref_div = 1;

    // CH_FIN_DIVIDER is 1 for low-freq sensor mode, 2 for high-freq mode.
    float ch_fin_divider = ((cdiv & 0x3000) == FDC2214_FIN_SEL_HIGH_FREQ) ? 2.0f : 1.0f;
    float f_ref          = FDC2214_F_REF / (float)fref_div;

    // f_sensor = (DATA / 2^28) * f_REF * CH_FIN_DIVIDER
    return ((float)raw / 268435456.0f) * f_ref * ch_fin_divider;
}

float FDC2214_readCapacitancePf(fdc2214_channel_t ch, float inductance_uH)
{
    float f = FDC2214_readFrequencyHz(ch);
    if (f <= 0.0f || inductance_uH <= 0.0f) return 0.0f;

    // C = 1 / (L * (2*pi*f)^2). Result in farads.
    float L = inductance_uH * 1.0e-6f;
    float w = 2.0f * 3.14 * f;
    float C = 1.0f / (L * w * w);

    return C * 1.0e12f; // farads -> picofarads
}



//float FDC2214_read_capacitance(uint8_t channel, float *cap_pf){
//
//	uint64_t raw = FDC2214_read_data(channel);
//	uint64_t f_sensor;
//
//	// convert into f_sensor data
//
//	f_sensor = (((float) raw) / ((float)(1UL << 28))) * FDC2214_F_REF; // datasheet equation
//
//    /* Step 2: frequency -> total capacitance (pF) */
//
//	float omega = 2.0f * 3.14159265f * f_sensor;
//	float total_c = (1.0f/(FDC2214_L_HENRY * omega * omega));
//
//
//	/* Step 3: Subtract Parallel Capacitor */
//
//	*cap_pf = (total_c - (FDC2214_C_PARALLEL)) * (1e12);
//
//	return 1;
//
//}


float FDC2214_read_differential_capacitance(uint8_t accumulator){

//	float c1;
//	float c2;


	// eliminates any errors due to noise

	switch(accumulator){
	// 1st Accumulator
		case 1:

			return FDC2214_readCapacitancePf(0, FDC2214_L_HENRY); // reads from channel 0

//			c1 = FDC2214_readCapacitancePf(0, FDC2214_L_HENRY);
//			c2 = FDC2214_readCapacitancePf(1, FDC2214_L_HENRY);
//			return c2 - c1;

	// 2nd Accumulator
		case 2:
			return FDC2214_readCapacitancePf(1, FDC2214_L_HENRY); // reads from channel 1


//			c1 = FDC2214_readCapacitancePf(2, FDC2214_L_HENRY);
//			c2 = FDC2214_readCapacitancePf(3, FDC2214_L_HENRY);
//			return c2 - c1;
	}

	return -1;


}

uint8_t FDC2214_read_accumulator_height(uint8_t accumulator){

	float c_dif_reading = FDC2214_read_differential_capacitance(accumulator);

	return FDC2214_ACUM_HREF*(c_dif_reading - FDC2214_CAP_EMPTY); // formula from data-sheet (may want to alter this formula with reference capacitors or an adequate formula for calculating liquid level

}


uint16_t readStatus()
{
    return read_register(STATUS);
}

uint16_t readErrorConfig()
{
    return read_register(ERROR_CONFIG);
}



uint16_t read_register(uint16_t reg){

	ret = HAL_I2C_Mem_Read(&hi2c4, FDC2214, reg, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(200);



	if(ret != HAL_OK){
		return -22;
	}

	return (cof[0] << 8) | cof[1];



}


uint8_t write_register(uint16_t reg, uint16_t value){


	cof[0] = (uint8_t) (value >> 8);
	cof[1] = (uint8_t) (value & 0xFF);

	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, reg, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return 2;
	}

	return 0;

}



void write_config(){
	write_register(CONFIG, _config);
}

void write_mux_config(){
	write_register(MUX_CONFIG, _config);
}




// Functions to implement (if needed)


// Sleep Mode Enable  ||  Config Register



// Low Power Mode || Config Register












