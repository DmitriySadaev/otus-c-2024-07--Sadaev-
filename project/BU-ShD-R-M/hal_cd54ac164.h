/*!
\file
\defgroup hal_cd54ac164
\brief Заголовочный файл hal_cd54ac164.h

*/

#ifndef HAL_CD54AC164_H_
#define HAL_CD54AC164_H_

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#ifndef CD54AC164_PORT
#define CD54AC164_PORT PORTD
#define CD54AC164_DDR DDRD
#endif /* CD54AC164_PORT */

#ifndef CD54AC164_DS
#define CD54AC164_DS PD6
#endif /* CD54AC164_DS */

#ifndef CD54AC164_CP
#define CD54AC164_CP PD7
#endif /* CD54AC164_CP */

#ifndef CD54AC164_Q0
#define CD54AC164_Q0 7U
#endif /* CD54AC164_Q0 */

#ifndef CD54AC164_Q1
#define CD54AC164_Q1 6U
#endif /* CD54AC164_Q1 */

#ifndef CD54AC164_Q2
#define CD54AC164_Q2 5U
#endif /* CD54AC164_Q2 */

#ifndef CD54AC164_Q3
#define CD54AC164_Q3 4U
#endif /* CD54AC164_Q3 */

#ifndef CD54AC164_Q4
#define CD54AC164_Q4 3U
#endif /* CD54AC164_Q4 */

#ifndef CD54AC164_Q5
#define CD54AC164_Q5 2U
#endif /* CD54AC164_Q5 */

#ifndef CD54AC164_Q6
#define CD54AC164_Q6 1U
#endif /* CD54AC164_Q6 */

#ifndef CD54AC164_Q7
#define CD54AC164_Q7 0U
#endif /* CD54AC164_Q7 */

#ifndef CD54AC164_STROB_DELAY_US
#define CD54AC164_STROB_DELAY_US 1U
#endif /* CD54AC164_STROB_DELAY_US */

void cd54ac164_init(void);
void cd54ac164_set(uint8_t data);

#endif /* HAL_CD54AC164_H_ */