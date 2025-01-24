/*!
\file
\defgroup hal_sn74als165d
\brief Заголовочный файл hal_sn74als165d.h

*/

#ifndef HAL_SN74ALS165D_H_
#define HAL_SN74ALS165D_H_

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#ifndef SN74ALS165D_PORT
#define SN74ALS165D_PORT PORTA
#define SN74ALS165D_PORT_IN PINA
#define SN74ALS165D_DDR DDRA
#endif /* SN74ALS165D_PORT */

#ifndef SN74ALS165D_SER
#define SN74ALS165D_SER PA0
#endif /* SN74ALS165D_SER */

#ifndef SN74ALS165D_CLK
#define SN74ALS165D_CLK PA1
#endif /* SN74ALS165D_CLK */

#ifndef SN74ALS165D_SH_LD
#define SN74ALS165D_SH_LD PA2
#endif /* SN74ALS165D_SH_LD */

#ifndef SN74ALS165D_IN_SERIES_CONNECTED
#define SN74ALS165D_IN_SERIES_CONNECTED 2U
#endif /* SN74ALS165D_IN_SERIES_CONNECTED */

#ifndef SN74ALS165D_STROB_DELAY_US
#define SN74ALS165D_STROB_DELAY_US 1U
#endif /* SN74ALS165D_STROB_DELAY_US */

void sn74als165d_init(void);
void sn74als165d_read(uint8_t * sn74als165d_read_array);

#endif /* HAL_SN74ALS165D_H_ */