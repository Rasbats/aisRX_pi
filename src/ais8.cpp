// Binary Broadcast Message (BBM) - 8

// See also: http://www.e-navigation.nl/asm

#include <iomanip>

#include "ais2.h"

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

	// IMO Circ 289 - Meteorological and Hydrographic data
// See also Circ 236
	Ais8_1_31::Ais8_1_31(const char *nmea_payload, const size_t pad)
		: Ais8(nmea_payload, pad), position_accuracy(0), utc_day(0), utc_hour(0),
		  utc_min(0), wind_ave(0), wind_gust(0), wind_dir(0), wind_gust_dir(0),
		  air_temp(0.0), rel_humid(0), dew_point(0.0), air_pres(0.0),
		  air_pres_trend(0), horz_vis(0.0), water_level(0.0),
		  water_level_trend(0), surf_cur_speed(0.0), surf_cur_dir(0),
		  cur_speed_2(0.0), cur_dir_2(0), cur_depth_2(0), cur_speed_3(0.0),
		  cur_dir_3(0), cur_depth_3(0), wave_height(0.0), wave_period(0),
		  wave_dir(0), swell_height(0.0), swell_period(0), swell_dir(0),
		  sea_state(0), water_temp(0.0), precip_type(0), salinity(0.0),
		  ice(0), spare2(0) {
	  assert(dac == 1);
	  assert(fi == 31);
	  /*
	  if (!CheckStatus()) {
		return;
	  }
	  if (num_bits != 360) {
		status = AIS_ERR_BAD_BIT_COUNT;
		return;
	  }*/

	  bits.SeekTo(56);
	  position = bits.ToAisPoint(56, 49);
	  position_accuracy = bits[105];
	  utc_day = bits.ToUnsignedInt(106, 5);
	  utc_hour = bits.ToUnsignedInt(111, 5);
	  utc_min = bits.ToUnsignedInt(116, 6);

	  wind_ave = bits.ToUnsignedInt(122, 7);  // kts
	  wind_gust = bits.ToUnsignedInt(129, 7);  // kts
	  wind_dir = bits.ToUnsignedInt(136, 9);
	  wind_gust_dir = bits.ToUnsignedInt(145, 9);
	  air_temp = bits.ToInt(154, 11) / 10.;  // C
	  rel_humid = bits.ToUnsignedInt(165, 7);
	  dew_point = bits.ToInt(172, 10)/ 10.;  // TODO(schwehr): How is this mapped?
	  air_pres = (bits.ToUnsignedInt(182, 9) + 800) / 100.0;  // Pa
	  air_pres_trend = bits.ToUnsignedInt(191, 2);

	  horz_vis = bits.ToUnsignedInt(193, 8) / 10.;  // NM
	  water_level = bits.ToUnsignedInt(201, 12) / 100. - 10;  // m
	  water_level_trend = bits.ToUnsignedInt(213, 2);

	  surf_cur_speed = bits.ToUnsignedInt(215, 8) / 10.;
	  surf_cur_dir = bits.ToUnsignedInt(223, 9);
	  cur_speed_2 = bits.ToUnsignedInt(232, 8) / 10.;  // kts
	  cur_dir_2 = bits.ToUnsignedInt(240, 9);
	  cur_depth_2 = bits.ToUnsignedInt(249, 5);  // m
	  cur_speed_3 = bits.ToUnsignedInt(254, 8) / 10.;  // kts
	  cur_dir_3 = bits.ToUnsignedInt(262, 9);
	  cur_depth_3 = bits.ToUnsignedInt(271, 5);  // m

	  wave_height = bits.ToUnsignedInt(276, 8);  // m

	  wave_period = bits.ToUnsignedInt(284, 6);
	  wave_dir = bits.ToUnsignedInt(290, 9);
	  swell_height = bits.ToUnsignedInt(299, 8) / 10.;
	  swell_period = bits.ToUnsignedInt(307, 6);
	  swell_dir = bits.ToUnsignedInt(313, 9);
	  sea_state = bits.ToUnsignedInt(322, 4);  // beaufort scale - Table 1.2
	  water_temp = bits.ToInt(326, 10) / 10.;
	  precip_type = bits.ToUnsignedInt(336, 3);
	  salinity = bits.ToUnsignedInt(339, 9) / 10.;
	  ice = bits.ToUnsignedInt(348, 2);  // yes/no/undef/unknown
	  spare2 = bits.ToUnsignedInt(350, 10);

	 // assert(bits.GetRemaining() == 0);
	 // status = AIS_OK;
	}

	//********** Weather FI 11 ************************

	Ais8_1_11::Ais8_1_11(const char *nmea_payload, const size_t pad)
		: Ais8(nmea_payload, pad), day(0), hour(0), minute(0), wind_ave(0),
		wind_gust(0), wind_dir(0), wind_gust_dir(0), air_temp(0.0), rel_humid(0),
		dew_point(0.0), air_pres(0.0), air_pres_trend(0), horz_vis(0.0),
		water_level(0.0), water_level_trend(0), surf_cur_speed(0.0),
		surf_cur_dir(0), cur_speed_2(0.0), cur_dir_2(0), cur_depth_2(0),
		cur_speed_3(0.0), cur_dir_3(0), cur_depth_3(0), wave_height(0.0),
		wave_period(0), wave_dir(0), swell_height(0.0), swell_period(0),
		swell_dir(0), sea_state(0), water_temp(0.0), precip_type(0),
		salinity(0.0), ice(0), spare2(0), extended_water_level(0) {

		assert(dac == 1);
		assert(fi == 11);
		bits.SeekTo(56);
		// Reverse order lat/lng!
		// TODO(schwehr): Reverse order, or just reverse bit count? Compare 6.1.14!
		double y = bits.ToInt(56, 24) / 60000.0;
		double x = bits.ToInt(80, 25) / 60000.0;
		position = AisPoint(x, y);

		day = bits.ToUnsignedInt(105, 5);
		hour = bits.ToUnsignedInt(110, 5);
		minute = bits.ToUnsignedInt(115, 6);
		wind_ave = bits.ToUnsignedInt(121, 7);
		wind_gust = bits.ToUnsignedInt(128, 7);
		wind_dir = bits.ToUnsignedInt(135, 9);
		wind_gust_dir = bits.ToUnsignedInt(144, 9);
		air_temp = bits.ToUnsignedInt(153, 11) / 10. - 60;
		rel_humid = bits.ToUnsignedInt(164, 7);
		dew_point = bits.ToUnsignedInt(171, 10) / 10. - 20;  // TODO(schwehr): verify
		air_pres = bits.ToUnsignedInt(181, 9) + 800;
		air_pres_trend = bits.ToUnsignedInt(190, 2);
		horz_vis = bits.ToUnsignedInt(192, 8) / 10.;
		// TODO(schwehr): verify for -10.0 to 30.0
		water_level = bits.ToUnsignedInt(200, 9) / 10. - 10;
		water_level_trend = bits.ToUnsignedInt(209, 2);
		surf_cur_speed = bits.ToUnsignedInt(211, 8) / 10.;
		surf_cur_dir = bits.ToUnsignedInt(219, 9);
		cur_speed_2 = bits.ToUnsignedInt(228, 8) / 10.;
		cur_dir_2 = bits.ToUnsignedInt(236, 9);
		cur_depth_2 = bits.ToUnsignedInt(245, 5);
		cur_speed_3 = bits.ToUnsignedInt(250, 8) / 10.;
		cur_dir_3 = bits.ToUnsignedInt(258, 9);
		cur_depth_3 = bits.ToUnsignedInt(267, 5);

		wave_height = bits.ToUnsignedInt(272, 8) / 10.;
		wave_period = bits.ToUnsignedInt(280, 6);
		wave_dir = bits.ToUnsignedInt(286, 9);
		swell_height = bits.ToUnsignedInt(295, 8) / 10.;
		swell_period = bits.ToUnsignedInt(303, 6);
		swell_dir = bits.ToUnsignedInt(309, 9);

		sea_state = bits.ToUnsignedInt(318, 4);
		// TODO(schwehr): verify for -10.0 to +50.0
		water_temp = bits.ToUnsignedInt(322, 10) / 10. - 10;
		precip_type = bits.ToUnsignedInt(332, 3);
		salinity = bits.ToUnsignedInt(335, 9) / 10.0;  // Part per mil (1/1000).
		ice = bits.ToUnsignedInt(344, 2);
		// There is no way to know which meaning to attach to the following 6 bits
		// TODO(schwehr): how to treat this spare vrs water level?
		spare2 = bits.ToUnsignedInt(346, 6);
		bits.SeekRelative(-6);
		extended_water_level = bits.ToUnsignedInt(346, 6);

		//assert(bits.GetRemaining() == 0);
		//status = AIS_OK;

	}

	
} //mylibais

