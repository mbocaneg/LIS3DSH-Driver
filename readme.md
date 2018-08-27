Simple platform agnostic driver for the LIS3DSH accelerometer manufactured by STMicroelectronics.
An example implementation is provided that targets the STM32F407VG MCU, using CubeMX middleware.

*Usage
The driver consists of 2 files; LIS3DSH.h and LIS3DSH.c held in the LIS3DSH directory. In order to
use this driver, the following function pointers must be populated(see LIS3DSH.h):

void (*SPI_Write_Reg)(uint8_t reg, uint8_t *data, uint16_t len);
void (*SPI_Read_Reg)(uint8_t reg, uint8_t *data, uint16_t len);
void (*SPI_CS_Set)(void);
void (*SPI_CS_Reset)(void);

As one can see, this is simply a light abstraction wrapper over SPI operations. To use this
library, refactor the SPI R/W operations on your MCU of choice (as 4 functions)to adhere to the function
pointers listed above. Then, have the function pointers point to the functions you declared. The following
shows example usage for the STM32 platform. See the included example project for a complete code listing.

//**main.c
//LIS3DSH.h and LIS3DSH.c are in a folder named LIS3DSH in same directory as this file
#include "LIS3DSH/LIS3DSH.h"
...

/* MCU specfic code  */
void _spi_cs_set(){
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
}

void _spi_cs_reset(){
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
}

void _spi_write_reg(uint8_t reg, uint8_t *data, uint16_t len){
	HAL_SPI_Transmit(&hspi1, data, len, 50);
}

void _spi_read_reg(uint8_t reg, uint8_t *data, uint16_t len){
	uint8_t read_reg = reg | 0x80;
	HAL_SPI_Transmit(&hspi1, &read_reg, 1, 50);
	HAL_SPI_Receive(&hspi1, data, len, 50);
}

...

int main(void) {
  ...
  //bind driver to MCU native SPI calls
  SPI_Read_Reg = _spi_read_reg;
	SPI_Write_Reg = _spi_write_reg;
	SPI_CS_Reset = _spi_cs_reset;
	SPI_CS_Set = _spi_cs_set;

  //initialize LIS3DSH
	Lis3dsh lis3dsh;
	LIS3DSH_init(&lis3dsh);
	...
}

*Pitch/Roll calculation
In order to calculate pich/roll, one must call the LIS3DSH_readXYZ(&lis3dsh)
function, giving it an argument of an LIS3DSH pointer. This simply populates
the fields of the LIS3DSH structure with raw accelerometer readings. To obtain
user readable values, one calls the LIS3DSH_calc_pitch_roll(&lis3dsh, &pitch, &roll)
function (after calling the LIS3DSH_readXYZ function), giving it arguments
of an LIS3DSH pointer, as well as float pointers for pitch and roll values. After
the function returns, these two float pointers will hold pitch/roll values (in degrees).
Example usage is shown below. See the included example project for a complete code listing.

...
while (1) {
	float pitch, roll;
	LIS3DSH_readXYZ(&lis3dsh);
	LIS3DSH_calc_pitch_roll(&lis3dsh, &pitch, &roll);

  printf("pitch in degrees: %f", pitch);
  printf("roll in degrees: %f", roll);
}
...
