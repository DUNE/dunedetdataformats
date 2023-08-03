/**
 * @file trigger_primitive.cpp Python bindings for the trigger primitive formats
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "trgdataformats/TriggerCandidateData.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dunedaq::trgdataformats::python {

void
register_trigger_bitwords(py::module& m)
{
  py::class_<TriggerCandidateData> py_triggerbits(m, "TriggerBits", py::buffer_protocol());

  py_triggerbits.def("string_to_fragment_type_value", &trgdataformats::string_to_fragment_type_value);

}

} // namespace dunedaq::trgdataformats::python
