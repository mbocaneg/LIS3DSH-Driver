#ifndef LIS3DSH_LIS3DSH_H_
#define LIS3DSH_LIS3DSH_H_

#include <inttypes.h>
#include <math.h>

//LIS3DSH REGISTERS
#define CR4 0x20
#define SR 0x27

#define OUTX_L 0x28
#define OUTX_H 0x29
#define OUTY_L 0x2A
#define OUTY_H 0x2B
#define OUTZ_L 0x2C
#define OUTZ_H 0x2D

//struct for holding LIS3DSH acceleration data.
typedef struct Lis3dsh_t {
	float accX;
	float accY;
	float accZ;

} Lis3dsh;

//function pointers for spi read/write and cs assert/deassert. Used to interface with native MCU SPI functions, regardless of platform.
void (*SPI_Write_Reg)(uint8_t reg, uint8_t *data, uint16_t len);
void (*SPI_Read_Reg)(uint8_t reg, uint8_t *data, uint16_t len);

void (*SPI_CS_Set)(void);
void (*SPI_CS_Reset)(void);

//LIS3DSH function prototypes for initialization, accelerometer reading, and pitch/roll calculation
void LIS3DSH_init(Lis3dsh *lis3dsh);
void LIS3DSH_readXYZ(Lis3dsh *lis3dsh);
void LIS3DSH_calc_pitch_roll(Lis3dsh *lis3dsh, float *pitch, float *roll);

#endif /* LIS3DSH_LIS3DSH_H_ */
