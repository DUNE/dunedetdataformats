/**
 * @file module.cpp
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "registrators2.hpp"

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

namespace py = pybind11;

namespace dunedaq::trgdataformats2::python {

PYBIND11_MODULE(_daq_trgdataformats2_py, m)
{

  m.doc() = "C++ implementation of the trgdataformats2 modules";

  register_trigger_primitive(m);
  // register_trigger_bitwords(m);
  register_trigger_activity(m);
  register_trigger_candidate(m);
}

} // namespace dunedaq::trgdataformats2::python
