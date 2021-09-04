// River Information Systems ECE-TRANS-SC3-2006-10r-RIS.pdf
// http://www.unece.org/fileadmin/DAM/trans/doc/finaldocs/sc3/ECE-TRANS-SC3-176e.pdf

#include "ais2.h"

namespace mylibais {
	// River Information Systems ECE-TRANS-SC3-2006-10r-RIS.pdf
	Ais8_200_41::Ais8_200_41(const char *nmea_payload, const size_t pad)
		: Ais8(nmea_payload, pad), version(0), country(), section(0), type(0), objectnumber(0), hectometre(0), signal(0), orientation(0), impact(0), 
		light_status(0), spare(0) {

		assert(dac == 200);
		assert(fi == 41);

		//if (!CheckStatus()) {
		//	return;
		//}
		if (num_bits != 168) {
			status = AIS_ERR_BAD_BIT_COUNT;
			return;
		}

		bits.SeekTo(56);
		// version section number             17 bits
		version = bits.ToUnsignedInt(56, 3);

		// country section number             17 bits
		country = bits.ToString(59, 12);
		
		 // Fairway section number             17 bits
		section = bits.ToUnsignedInt(71, 17);

		// Object code                30 bits
		type = bits.ToUnsignedInt(88, 3);

		// Object code                30 bits
		objectnumber = bits.ToUnsignedInt(91, 4);


		// Fairway hectometre                 17 bits
		hectometre = bits.ToUnsignedInt(95, 17);

		// Signal                              1 bits
		signal = bits.ToUnsignedInt(112, 4);

		// Orientation
		orientation = bits.ToUnsignedInt(116, 9);

		// impact
		impact = bits.ToUnsignedInt(125, 3);

		// status
		light_status = bits.ToUnsignedInt(128, 30);

		 // Spare                               2 bits
		spare = bits.ToUnsignedInt(158, 10);
	   
		assert(bits.GetRemaining() == 0);

		status = AIS_OK;

	}


	Ais8_200_44::Ais8_200_44(const char *nmea_payload, const size_t pad)
		: Ais8(nmea_payload, pad), version(0), country(), section(0), object(), hectometre(0), spare(0), text() {

		int num_bits = sizeof nmea_payload;

		assert(dac == 200);
		assert(fi == 44);

		//if (!CheckStatus()) {
		//	return;
		//}

		bits.SeekTo(56);
		// version 3 bits
		version = bits.ToUnsignedInt(56, 3);

		// country code             12 bits
		country = bits.ToString(59, 12);
	
		 // Fairway section number             17 bits
		section = bits.ToUnsignedInt(71, 17);

		// Object code                30 bits
		object = bits.ToString(88, 30);

		// Fairway hectometre                 17 bits
		hectometre = bits.ToUnsignedInt(118, 17);

		 // Spare                               1 bit
		spare = bits.ToUnsignedInt(135, 1);

		//const size_t text_size = 6 * ((num_bits - 136) / 6);

		size_t text_size = 6 * (bits.GetRemaining() / 6);

		int start_spare;

		if (text_size == bits.GetRemaining()) {
			text = bits.ToString(136, text_size);
			start_spare = 136 + text_size;
			spare1 = bits.ToUnsignedInt(0, 6);
		}
		else {
			text_size = text_size + 6;
			// text                           222-450 bits
			text = bits.ToString(136, text_size);

			int rem_bits = bits.GetRemaining() - text_size;
			start_spare = 136 + text_size;

			// Spare1                               6 bits
			spare1 = bits.ToUnsignedInt(0, 6);

		}

		
/*	   
		//assert(bits.GetRemaining() == 0);

		status = AIS_OK;
*/
	}



} // namespace mylibais
