/**
 * @file trigger_primitive.cpp Python bindings for the trigger primitive formats
 *
 * This is part of the DUNE DAQ Software Suite, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "detdataformats/trigger/TriggerObjectOverlay2.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <cstring>

namespace py = pybind11;

namespace dunedaq {
namespace trgdataformats2 {
namespace python {

/*
 Doesn't work
*/
struct TriggerActivityHolder {


  TriggerActivityHolder(void* ptr, size_t size) {
    m_size = size;
    m_data.reset(new uint8_t[m_size]);
    std::memcpy(m_data.get(), ptr, size);
  }

  TriggerActivity* ptr() { return reinterpret_cast<TriggerActivity*>(m_data.get());  }

  size_t m_size;
  std::unique_ptr<uint8_t[]> m_data;
  
};

void
register_trigger_activity(py::module& m)
{


  py::class_<TriggerActivityData> trigger_activity_data(m, "TriggerActivityData", py::buffer_protocol());
  trigger_activity_data
    .def(py::init())
    .def(py::init([](py::capsule capsule) {
        auto tp = *static_cast<TriggerActivityData*>(capsule.get_pointer());
        return tp;
		  } ))
    .def(py::init([](py::bytes bytes){
      py::buffer_info info(py::buffer(bytes).request());
      auto tp = *static_cast<TriggerActivityData*>(info.ptr);
      return tp;
    }))
    .def_property_readonly("version", [](TriggerActivityData& self) -> uint16_t {return self.version;})
    .def_property_readonly("time_start", [](TriggerActivityData& self) -> uint64_t {return self.time_start;})
    .def_property_readonly("time_end", [](TriggerActivityData& self) -> uint64_t {return self.time_end;})
    .def_property_readonly("time_peak", [](TriggerActivityData& self) -> uint64_t {return self.time_peak;})
    .def_property_readonly("time_activity", [](TriggerActivityData& self) -> uint64_t {return self.time_activity;})
    .def_property_readonly("channel_start", [](TriggerActivityData& self) -> int32_t {return self.channel_start;})
    .def_property_readonly("channel_end", [](TriggerActivityData& self) -> int32_t {return self.channel_end;})
    .def_property_readonly("channel_peak", [](TriggerActivityData& self) -> int32_t {return self.channel_peak;})
    .def_property_readonly("adc_integral", [](TriggerActivityData& self) -> uint32_t {return self.adc_integral;})
    .def_property_readonly("adc_peak", [](TriggerActivityData& self) -> uint32_t {return self.adc_peak;})
    .def_property_readonly("detid", [](TriggerActivityData& self) -> uint16_t {return self.detid;})
    .def_property_readonly("type", [](TriggerActivityData& self) -> TriggerActivityData::Type {return self.type;})
    .def_property_readonly("algorithm", [](TriggerActivityData& self) -> TriggerActivityData::Algorithm {return self.algorithm;})
    .def_static("sizeof", [](){ return sizeof(TriggerActivityData); })
    ;


  py::enum_<TriggerActivityData::Type>(trigger_activity_data, "Type")
    .value("kUnknown", TriggerActivityData::Type::kUnknown)
    .value("kTPC", TriggerActivityData::Type::kTPC)
    .value("kPDS", TriggerActivityData::Type::kPDS);

  py::enum_<TriggerActivityData::Algorithm>(trigger_activity_data, "Algorithm")
    .value("kUnknown", TriggerActivityData::Algorithm::kUnknown)
    .value("kSupernova", TriggerActivityData::Algorithm::kSupernova)
    .value("kPrescale", TriggerActivityData::Algorithm::kPrescale)
    .value("kADCSimpleWindow", TriggerActivityData::Algorithm::kADCSimpleWindow)
    .value("kHorizontalMuon", TriggerActivityData::Algorithm::kHorizontalMuon)
    .value("kMichelElectron", TriggerActivityData::Algorithm::kMichelElectron)
    .value("kDBSCAN", TriggerActivityData::Algorithm::kDBSCAN)
    .value("kPlaneCoincidence", TriggerActivityData::Algorithm::kPlaneCoincidence)
    .value("kBundle", TriggerActivityData::Algorithm::kBundle)
    .value("kChannelDistance", TriggerActivityData::Algorithm::kChannelDistance)
    .value("kChannelAdjacency", TriggerActivityData::Algorithm::kChannelAdjacency);

  py::class_<TriggerActivity>(m, "TriggerActivityOverlay", py::buffer_protocol())
      .def(py::init())
      .def(py::init([](py::capsule capsule) {
        auto tp = *static_cast<TriggerActivity*>(capsule.get_pointer());
        return tp;
		  } ))
      .def_property_readonly("data", [](TriggerActivity& self) -> TriggerActivityData& {return self.data;})
      .def("__len__", [](TriggerActivity& self){ return self.n_inputs; })
      .def("sizeof", [](TriggerActivity& self){ return sizeof(TriggerActivity)+self.n_inputs*sizeof(TriggerPrimitive); })
    ;


    py::class_<TriggerActivityHolder>(m, "TriggerActivity", py::buffer_protocol())
      // .def(py::init())
      .def(py::init([](py::capsule capsule) {
          auto ta_ptr = static_cast<TriggerActivity*>(capsule.get_pointer());
          TriggerActivityHolder tah(ta_ptr, sizeof(TriggerActivity)+ta_ptr->n_inputs*sizeof(TriggerPrimitive));
          return tah;
        }))
      .def(py::init([](py::bytes bytes){
          py::buffer_info info(py::buffer(bytes).request());
          TriggerActivityHolder tah(info.ptr, info.size);

          return tah;
        }))

      .def("get_bytes",
          [](TriggerActivityHolder& tah) -> py::bytes {
            return py::bytes(reinterpret_cast<char*>(tah.ptr()), tah.m_size);
          }, py::return_value_policy::reference_internal
      )
      .def_property_readonly("data", [](TriggerActivityHolder& self) -> TriggerActivityData& {return self.ptr()->data;})
      .def("n_inputs", [](TriggerActivityHolder& self){ return self.ptr()->n_inputs; })
      .def("__len__", [](TriggerActivityHolder& self){ return self.ptr()->n_inputs; })
      .def("__getitem__",
            [](TriggerActivityHolder &self, size_t i) -> const TriggerPrimitive& {
                if (i >= self.ptr()->n_inputs) {
                    throw py::index_error();
                }
                return self.ptr()->inputs[i];
            }, py::return_value_policy::reference_internal)
      .def("sizeof", [](TriggerActivityHolder& self){ return self.m_size; })
      
      ;
}

} // namespace python
} // namespace trgdataformats2
} // namespace dunedaq
