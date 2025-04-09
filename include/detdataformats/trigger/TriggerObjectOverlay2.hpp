/**
 * @file TriggerObjectOverlay2.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGEROBJECTOVERLAY2_HPP_
#define TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGEROBJECTOVERLAY2_HPP_

#include "detdataformats/trigger/TriggerActivityData2.hpp"
#include "detdataformats/trigger/TriggerCandidateData2.hpp"
#include "detdataformats/trigger/TriggerPrimitive2.hpp"

namespace dunedaq::trgdataformats2 {

template<class DataType, class InputType>
struct TriggerObjectOverlay
{
  using data_t = DataType;
  using input_t = InputType;
  data_t data;
  uint64_t n_inputs;
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wpedantic"
  input_t inputs[]; // Non-standard flexible array member, but alternatives are worse
  #pragma GCC diagnostic pop
};

using TriggerActivity = TriggerObjectOverlay<TriggerActivityData, TriggerPrimitive>;

using TriggerCandidate = TriggerObjectOverlay<TriggerCandidateData, TriggerActivityData>;

} // namespace dunedaq::trgdataformats2

#endif // TRGDATAFORMATS_INCLUDE_TRGDATAFORMATS_TRIGGEROBJECTOVERLAY_HPP_
