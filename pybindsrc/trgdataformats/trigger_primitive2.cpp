/**
 * @file trigger_primitive.cpp Python bindings for the trigger primitive formats
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "detdataformats/trigger/TriggerPrimitive2.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

namespace dunedaq::trgdataformats2::python {

void
register_trigger_primitive(py::module& m)
{


  py::class_<TriggerPrimitive> trigger_primitive(m, "TriggerPrimitive", py::buffer_protocol());
  trigger_primitive
    .def(py::init())
    .def(py::init([](py::capsule capsule) {
        auto tp = *static_cast<TriggerPrimitive*>(capsule.get_pointer());
        return tp;
		  } ))
    .def_property_readonly_static("s_trigger_primitive_version", [](py::object /*self*/) {return TriggerPrimitive::s_trigger_primitive_version;})
    .def_property_readonly("version", [](TriggerPrimitive& self) -> uint8_t {return self.version;})
    .def_property_readonly("time_start", [](TriggerPrimitive& self) -> uint64_t {return self.time_start;})
    .def_property_readonly("samples_to_peak", [](TriggerPrimitive& self) -> uint16_t {return self.samples_to_peak;})
    .def_property_readonly("samples_over_threshold", [](TriggerPrimitive& self) -> uint16_t {return self.samples_over_threshold;})
    .def_property_readonly("channel", [](TriggerPrimitive& self) -> uint32_t {return uint32_t(self.channel);})
    .def_property_readonly("adc_integral", [](TriggerPrimitive& self) -> uint32_t {return self.adc_integral;})
    .def_property_readonly("adc_peak", [](TriggerPrimitive& self) -> uint16_t {return self.adc_peak;})
    .def_property_readonly("detid", [](TriggerPrimitive& self) -> uint8_t {return self.detid;})
    .def_property_readonly("flag", [](TriggerPrimitive& self) -> uint8_t {return self.flag;})
    .def_static("sizeof", [](){ return sizeof(TriggerPrimitive); })
    ;

}

} // namespace dunedaq::trgdataformats2::python
