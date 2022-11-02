// Binary Broadcast Message (BBM) - 8

// See also: http://www.e-navigation.nl/asm

#include <iomanip>

#include "ais.h"

namespace mylibais {

	Ais8::Ais8(const char *nmea_payload, const size_t pad)
		: AisMsg(nmea_payload, pad), spare(0), dac(0), fi(0) {
		if (!CheckStatus()) {
			return;
		}

		// in bits w/o DAC/FI
		// TODO(schwehr): Verify if this is 46 or 56 (accumulated bits below).
		const int payload_len = num_bits - 56;
		if (payload_len < 0 || payload_len > 952) {
			status = AIS_ERR_BAD_BIT_COUNT;
			return;
		}

		assert(message_id == 8);

		bits.SeekTo(38);
		spare = bits.ToUnsignedInt(38, 2);
		dac = bits.ToUnsignedInt(40, 10);
		fi = bits.ToUnsignedInt(50, 6);
	}


} //mylibais

