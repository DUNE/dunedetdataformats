/**
 * @file TriggerActivityData2.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERACTIVITYDATA2_HPP_
#define TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERACTIVITYDATA2_HPP_

#include "detdataformats/trigger/Types2.hpp"
#include <cstdint>

namespace dunedaq::trgdataformats2 {

struct TriggerActivityData
{
  enum class Type
  {
    kUnknown = 0,
    kTPC = 1,
    kPDS = 2,
  };

  enum class Algorithm
  {
    kUnknown = 0,
    kSupernova = 1,
    kPrescale = 2,
    kADCSimpleWindow = 3,
    kHorizontalMuon = 4,
    kMichelElectron = 5,
    kDBSCAN = 6,
    kPlaneCoincidence = 7,
    kChannelDistance = 8,
    kBundle = 9,
    kChannelAdjacency = 10,
  };

  // Update this version number if there are any changes to the in-memory representation of this class!
  static constexpr version_t s_trigger_activity_version = 2; // NOLINT(build/unsigned)
  
  version_t version = s_trigger_activity_version; // NOLINT(build/unsigned)
  timestamp_t time_start = INVALID_TIMESTAMP;
  timestamp_t time_end = INVALID_TIMESTAMP;
  timestamp_t time_peak = INVALID_TIMESTAMP;
  timestamp_t time_activity = INVALID_TIMESTAMP;
  channel_t channel_start = INVALID_CHANNEL; // NOLINT(build/unsigned)
  channel_t channel_end = INVALID_CHANNEL;   // NOLINT(build/unsigned)
  channel_t channel_peak = INVALID_CHANNEL;  // NOLINT(build/unsigned)
  uint64_t adc_integral = 0;                 // NOLINT(build/unsigned)
  uint16_t adc_peak = 0;                     // NOLINT(build/unsigned)
  detid_t detid = INVALID_DETID;             // NOLINT(build/unsigned)
  Type type = Type::kUnknown;                // NOLINT(build/unsigned)
  Algorithm algorithm = Algorithm::kUnknown; // NOLINT(build/unsigned)
};

} // namespace dunedaq::trgdataformats2

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGERACTIVITYDATA2_HPP_
