#include <fdc2214.h>

// Kacper Paraniuk 03/21/26

extern I2C_HandleTypeDef hi2c4;


uint8_t cof[2];
volatile uint16_t check[2];
HAL_StatusTypeDef ret;

// INIT ALL CHANNELS.

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

	check[0] = cof[1] | cof[0] << 8; // big endian 	(RECONSTRUCT BITS INTO A 16 BIT VALUE) assuming we are using big endian


	ret = HAL_I2C_Mem_Read(&hi2c4, FDC2214, DEVICE_ID, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -25;
	}

	check[1] = cof[1] | cof[0] << 8;
	if ((check[0] == MANUFACTURER_ID_val) && (check[1] == DEVICE_ID_val))
		return 0;
	else
		return -1;


}




uint8_t FDC2214_Init(void)

{


//	uint8_t i = 0; ineffective way to create a timer, may be worth testing without HAL_Delay


	// FDC2214 Register Setup.

	// R-COUNT || R-Count MAXIMIZED = Highest Accuracy (Num Bits of Accuracy)

	cof[0] = 0xFF;
	cof[1] = 0xFF;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, RCOUNT_CH0, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);      //	for (i = 0; i < 20; i++)
	HAL_Delay(20);

	//;

	if(ret != HAL_OK){
		return -1;
	}

	cof[0] = 0xFF;
	cof[1] = 0xFF;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, RCOUNT_CH1, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -2;
	}

	cof[0] = 0xFF;
	cof[1] = 0xFF;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, RCOUNT_CH2, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -3;
	}

	cof[0] = 0xFF;
	cof[1] = 0xFF;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, RCOUNT_CH3, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -4;
	}

	// OFFSET || NO OFFSET

	cof[0] = 0x00;
	cof[1] = 0x00;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, OFFSET_CH0, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -5;
	}

	cof[0] = 0x00;
	cof[1] = 0x00;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, OFFSET_CH1, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -6;
	}

	cof[0] = 0x00;
	cof[1] = 0x00;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, OFFSET_CH2, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -7;
	}


	cof[0] = 0x00;
	cof[1] = 0x00;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, OFFSET_CH3, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -8;
	}

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

	cof[0] = 0x00;
	cof[1] = 0x64;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, SETTLECOUNT_CH0, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -9;
	}

	cof[0] = 0x00;
	cof[1] = 0x64;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, SETTLECOUNT_CH1, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -10;
	}

	cof[0] = 0x00;
	cof[1] = 0x64;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, SETTLECOUNT_CH2, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);


	if(ret != HAL_OK){
		return -11;
	}

	cof[0] = 0x00;
	cof[1] = 0x64;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, SETTLECOUNT_CH3, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -12;
	}

	// CLOCK DIVIDERS || This register configures both F_IN_SEL & F_REF_Divder -> CHx_FIN_SEL -> b01 for differential config and between 0.01 Mhz and 8.75 Mhz
	// Bit pattern: 00 01 00 0000000001 = 0x1001

	cof[0] = 0x10; // differential pair divide by sensor F_IN by 1 (Divide by two for single is setting byte value to 0x11)
	cof[1] = 0x01; // 0x01 equals full clock speed. fREFx = (f_clk / FREF_divider)
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, CLOCK_DIVIDERS_C_CH0, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -13;
	}

	cof[0] = 0x10; // [13:12]
	cof[1] = 0x01; // [9:0]
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, CLOCK_DIVIDERS_C_CH1, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -14;
	}

	cof[0] = 0x10;
	cof[1] = 0x01;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, CLOCK_DIVIDERS_C_CH2, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -15;
	}

	cof[0] = 0x10;
	cof[1] = 0x01;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, CLOCK_DIVIDERS_C_CH3, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -16;
	}

	// Error CONFIG
	// controls which error conditions drive the interrupt pin.
	// 0x0000 -> No error conditions

	cof[0] = 0x00;
	cof[1] = 0x00;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, ERROR_CONFIG, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -17;
	}

	// DRIVE CURRENT

	// The goal is to achieve oscillation amplitude between 1.2 Vpk and 1.8 Vpk. Too low = insufficient oscillation, noisy reading. Too high = clipping, distorted result.


	// DRIVE_CURRENT: IDRIVE in bits [15:11]
	// 0x1F << 11 = 0b1111100000000000 = 0xF800
	// MAX CURRENT FOR FAST RISE TIME (for testing) -> 1.57 mA

	cof[0] = 0xF8;
	cof[1] = 0x00;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, DRIVE_CURRENT_CH0, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -18;
	}

	cof[0] = 0xF8;
	cof[1] = 0x00;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, DRIVE_CURRENT_CH1, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);


	if(ret != HAL_OK){
	    return -19;
	}

	cof[0] = 0xF8;
	cof[1] = 0x00;
	HAL_Delay(20);

	cof[0] = 0xF8;
	cof[1] = 0x00;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, DRIVE_CURRENT_CH3, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -20;
	}


	// MUX CONFIG

	// 0xC2 1100 0010 # Auto Scan Enable, Ch0, Ch1, Ch2, Ch3 single conversion on each sequence and loops. AND places neccessary bit with 2
	// 0x0C 0000 1101 # 1 bit for necessary setup + 101 for deglitch filter (10 Mhz)

	cof[0] = 0xC2; // 1100 0010
	cof[1] = 0x0C; // 0000 1101

	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, MUX_CONFIG, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);


	if(ret != HAL_OK){
		return -21;
	}


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

	cof[0] = 0x1A;
	cof[1] = 0x81;
	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, CONFIG, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(200);

	if(ret != HAL_OK){
		return -22;
	}


	// Verify Device / Manufacturer ID.

	return isConnected();
}




uint16_t read_register(uint16_t reg){

	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, reg, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(200);



	if(ret != HAL_OK){
		return -22;
	}

	return (cof[0] << 8) | cof[1];



}


uint16_t write_register(uint16_t reg, uint16_t value){


	cof[0] = (uint8_t) (value >> 8);
	cof[1] = (uint8_t) (value & 0xFF);

	ret = HAL_I2C_Mem_Write(&hi2c4, FDC2214, reg, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	if(ret != HAL_OK){
		return -23;
	}

	return 0;

}

// data = ( f_sensor * 2^28 ) / f_ref

uint32_t FDC2214_read_data(uint8_t channel) // read 28 bit value. (RAW)
{
	volatile uint32_t data;
	uint8_t pdata[4];

	switch (channel)
	{
	case 0:
		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_MSB_CH0, I2C_MEMADD_SIZE_8BIT, pdata, 2, 100); // size of two indicates two bytes.
		HAL_Delay(20);

		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_LSB_CH0, I2C_MEMADD_SIZE_8BIT, pdata + 2, 2, 100); // pdata + 2 = third item in the array
		HAL_Delay(20);

		data = ((pdata[0] << 24 | pdata[1] << 16 | pdata[2] << 8 | pdata[3]) & 0x0fffffff); // & masks off status bits. but they can be read also if wanted in the future.
		return data;
	case 1:
		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_MSB_CH1, I2C_MEMADD_SIZE_8BIT, pdata, 2, 100);
		HAL_Delay(20);

		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_LSB_CH1, I2C_MEMADD_SIZE_8BIT, pdata + 2, 2, 100);
		HAL_Delay(20);

		data = ((pdata[0] << 24 | pdata[1] << 16 | pdata[2] << 8 | pdata[3]) & 0x0fffffff);
		return data;
	case 2:
		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_MSB_CH2, I2C_MEMADD_SIZE_8BIT, pdata, 2, 100);
		HAL_Delay(20);

		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_LSB_CH2, I2C_MEMADD_SIZE_8BIT, pdata + 2, 2, 100);
		HAL_Delay(20);

		data = ((pdata[0] << 24 | pdata[1] << 16 | pdata[2] << 8 | pdata[3]) & 0x0fffffff);
		return data;
	case 3:
		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_MSB_CH3, I2C_MEMADD_SIZE_8BIT, pdata, 2, 100);
		HAL_Delay(20);

		HAL_I2C_Mem_Read(&hi2c4, FDC2214, DATA_LSB_CH3, I2C_MEMADD_SIZE_8BIT, pdata + 2, 2, 100);
		HAL_Delay(20);

		data = ((pdata[0] << 24 | pdata[1] << 16 | pdata[2] << 8 | pdata[3]) & 0x0fffffff); // strip status / error bits
		return data;
	default:
		return 0;
	}
}


// takes a capacitance_reading data and converts it into an actual capacitance
// the digitized output for each channel is proportional to the ratio of fSENSOR/fREF
// calculate Fsensor from reading.


float FDC2214_read_capacitance(uint8_t channel, float *cap_pf){

	uint64_t raw = FDC2214_read_data(channel);
	uint64_t f_sensor;

	// convert into f_sensor data

	f_sensor = (((float) raw) / ((float)(1UL << 28))) * FDC2214_F_REF; // datasheet equation

    /* Step 2: frequency -> total capacitance (pF) */

	float omega = 2.0f * 3.14159265f * f_sensor;
	float total_c = (1.0f/(FDC2214_L_HENRY * omega * omega));


	/* Step 3: Subtract Parallel Capacitor */

	*cap_pf = (total_c - (FDC2214_C_PARALLEL)) * (1e12);

	return 1;

}


float FDC2214_read_differential_capacitance(uint8_t accumulator){

	float c1;
	float c2;


	// eliminates any errors due to noise

	switch(accumulator){
	// 1st Accumulator
		case 1:
			FDC2214_read_capacitance(0, &c1);
			FDC2214_read_capacitance(1, &c2);
			return c2 - c1;

	// 2nd Accumulator
		case 2:
			FDC2214_read_capacitance(2, &c1);
			FDC2214_read_capacitance(3, &c2);
			return c2 - c1;

	}

	return -1;


}

uint8_t FDC2214_read_accumulator_height(uint8_t accumulator){

	float c_dif_reading = FDC2214_read_differential_capacitance(accumulator);

	return FDC2214_ACUM_HREF*(c_dif_reading - FDC2214_CAP_EMPTY); // formula from data-sheet (may want to alter this formula with reference capacitors or an adequate formula for calculating liquid level

}


uint8_t reset_fdc2214(){
	// Reset Registers in Device.

	return write_register(RESET_DEV, 0x8000);


}

int FDC2214_Check_Device_ID(){


	HAL_I2C_Mem_Read(&hi2c4, FDC2214, MANUFACTURER_ID, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);


	check[0] = cof[1] | cof[0] << 8;

	if(check[0] == MANUFACTURER_ID_val){
		return 1;
	}
	else{
		return -1;
	}

	HAL_I2C_Mem_Read(&hi2c4, FDC2214, DEVICE_ID, I2C_MEMADD_SIZE_8BIT, cof, 2, 100);
	HAL_Delay(20);

	check[1] = cof[1] | cof[0] << 8;

	if ((check[0] == MANUFACTURER_ID_val) && (check[1] == DEVICE_ID_val))
		return 1;
	else
		return 0;


}



// Functions to implement (if needed)


// Sleep Mode Enable  ||  Config Register



// Low Power Mode || Config Register












