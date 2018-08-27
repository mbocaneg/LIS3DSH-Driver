#include "LIS3DSH.h"

//LIS3DSH initialization function. Writes a value of 0x67 into control register to initialize accelerometer.
void LIS3DSH_init(Lis3dsh *lis3dsh) {
	SPI_CS_Reset();

	uint8_t data = 0x67;
	SPI_Write_Reg(CR4, &data, 2);

	SPI_CS_Set();

	lis3dsh->accX = 0;
	lis3dsh->accY = 0;
	lis3dsh->accZ = 0;

}

//function for reading accelerometer reading on X, Y and Z axes.
void LIS3DSH_readXYZ(Lis3dsh *lis3dsh){
	//variables used to hold raw accelerometer readings
	int16_t x, y, z;
	uint8_t spi_rx_buf[6];

	SPI_CS_Reset();

	//Start reading from X_L register. Subsequent registers hold X_H, Y_L, Y_H, and Z_L, Z_H values. Store these values in rx_buffer
	SPI_Read_Reg(OUTX_L, spi_rx_buf, 6);

	SPI_CS_Set();

	//complete accelerometer reading(signed 16 bits) is made up of 2 unsigned 8 bit readings(LOW and HIGH registers).
	//concatenate these 2 readings into a signed, 16 bit variable to construct actual value
	x = (spi_rx_buf[1] << 8) | spi_rx_buf[0] ;
	y = (spi_rx_buf[3] << 8) | spi_rx_buf[2] ;
	z = (spi_rx_buf[5] << 8) | spi_rx_buf[4] ;

	//set accelerometer readings of struct to the ones derived above, scaled by a factor of 2000 as configured.
	lis3dsh->accX = x / 2000.0;
	lis3dsh->accY = y / 2000.0;
	lis3dsh->accZ = z / 2000.0;
}

//calculates pitch and roll in degrees from accelerometer readings
void LIS3DSH_calc_pitch_roll(Lis3dsh *lis3dsh, float *pitch, float *roll){
	*pitch = 180 * atan2(lis3dsh->accY, lis3dsh->accZ) / M_PI;
	*roll = 180 * atan2(lis3dsh->accX, lis3dsh->accZ) / M_PI;
}
