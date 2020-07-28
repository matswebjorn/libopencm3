/** @addtogroup crc_file CRC peripheral API
@ingroup peripheral_apis

@author @htmlonly &copy; @endhtmlonly 2012 Karl Palsson <karlp@remake.is>

*/

/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2012 Karl Palsson <karlp@remake.is>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/crc.h>

/**@{*/

void crc_reset(void)
{
	CRC_CR |= CRC_CR_RESET;
}

/**
 * Writes a data word to the register, the write operation stalling until
 * the computation is complete.
 * @param[in] data new 8 bit word to add to the CRC calculator
 * @returns int32 Computed CRC result
 */
uint32_t crc_calculate8(uint8_t data)
{
	CRC_DR = data;
	/* Data sheet says this blocks until it's ready.... */
	return CRC_DR;
}

/**
 * Writes a data word to the register, the write operation stalling until
 * the computation is complete.
 * @param[in] data new 16 bit word to add to the CRC calculator
 * @returns int32 Computed CRC result
 */
uint32_t crc_calculate16(uint16_t data)
{
	CRC_DR = data;
	/* Data sheet says this blocks until it's ready.... */
	return CRC_DR;
}

/**
 * Writes a data word to the register, the write operation stalling until
 * the computation is complete.
 * @param[in] data new 32 bit word to add to the CRC calculator
 * @returns int32 Computed CRC result
 */
uint32_t crc_calculate(uint32_t data)
{
	CRC_DR = data;
	/* Data sheet says this blocks until it's ready.... */
	return CRC_DR;
}

/**
 * Add a block of data to the CRC calculator and return the final result.
 * Writes data words consecutively to the register, the write operation
 * stalling until the computation of each word is complete, then
 * returns the final result
 * @param[in] datap pointer to an array of 32 bit data words.
 * @param[in] size length of data, in 32 bit increments
 * @return final CRC calculator value
 */
uint32_t crc_calculate_block(uint32_t *datap, int size)
{
	int i;

	for (i = 0; i < size; i++) {
		CRC_DR = datap[i];
	}

	return CRC_DR;
}

/**
 * Add a buffer of bytes to the CRC calculator and return the final result.
 * Writes data words consecutively to the register, the write operation
 * stalling until the computation of each word is complete, then
 * returns the final result
 * @param[in] datap pointer to an array of 8 bit data words.
 * @param[in] size length of data, in 8 bit increments
 * @return final CRC calculator value
 */
uint32_t crc_calculate_buf(uint8_t *datap, int size)
{
	unsigned i;

	for (i = 0; i < size / sizeof(uint32_t); i++) {
		CRC_DR = ((uint32_t*)datap)[i];
	}
	i *= sizeof(uint32_t) / sizeof(uint16_t);
	if (i < size / sizeof(uint16_t)) {
		CRC_DR = ((uint16_t*)datap)[i++];
	}
	i *= sizeof(uint16_t) / sizeof(uint8_t);
	if (i < size / sizeof(uint8_t)) {
		CRC_DR = ((uint8_t*)datap)[i];
	}

	return CRC_DR;
}

/**@}*/

