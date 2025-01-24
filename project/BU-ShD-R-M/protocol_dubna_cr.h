#ifndef PROTOCOL_DUBNA_CR_H_
#define PROTOCOL_DUBNA_CR_H_

#include <stdint.h>

#ifndef DUBNA_CR_MOD
#define DUBNA_CR_MOD 256
#endif /* DUBNA_CR_MOD */

uint8_t protocol_dubna_cr(uint16_t * dubna_frame, uint8_t dubna_frame_length);
uint8_t protocol_dubna_cr_ascii_high(uint16_t * dubna_frame, uint8_t dubna_frame_length);
uint8_t protocol_dubna_cr_ascii_low(uint16_t * dubna_frame, uint8_t dubna_frame_length);


#endif /* PROTOCOL_DUBNA_CR_H_ */