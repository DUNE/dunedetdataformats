/**
 * @file TriggerPrimitive2.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERPRIMITIVE2_HPP_
#define TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERPRIMITIVE2_HPP_

#include "detdataformats/trigger/Types2.hpp"

#include <bitset>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <type_traits>

namespace dunedaq::trgdataformats2 {

/**
 * @brief A single energy deposition on a TPC or PDS channel
 */


struct TriggerPrimitive
{
  static constexpr uint8_t s_trigger_primitive_version = 2;

  // Metadata.
  uint8_t version;
  uint8_t flag;
  uint8_t detid;

  // Physics data.
  uint8_t channel_lowbyte;
  uint8_t channel_middlebyte;
  uint8_t channel_highbyte;

  unsigned short samples_over_threshold;
  uint64_t time_start;
  unsigned short samples_to_peak;

  unsigned int adc_integral;
  unsigned short adc_peak;

  TriggerPrimitive()
    : version(s_trigger_primitive_version)
    , flag(0)
    , detid(INVALID_DETID)
    , channel_lowbyte(INVALID_TP_CHANNEL & 0XFF)
    , channel_middlebyte((INVALID_TP_CHANNEL & 0XFF00) >> 8)
    , channel_highbyte((INVALID_TP_CHANNEL & 0XFF0000) >> 16)
    , samples_over_threshold(INVALID_SAMPLES_OVER_THRESHOLD)
    , time_start(INVALID_TIMESTAMP)
    , samples_to_peak(INVALID_SAMPLES_TO_PEAK)
    , adc_integral(0)
    , adc_peak(0)
   {}

  uint64_t Channel() { return channel_lowbyte + (channel_middlebyte << 8) + (channel_highbyte << 12); };

  void SetChannel(uint64_t channel) {
    channel_lowbyte = channel & 0XFF;
    channel_middlebyte = (channel & 0XFF00) >> 8;
    channel_highbyte = (channel & 0XFF0000) >> 16;
  }

} __attribute__((packed));

} // namespace dunedaq::trgdataformats

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERPRIMITIVE2_HPP_
