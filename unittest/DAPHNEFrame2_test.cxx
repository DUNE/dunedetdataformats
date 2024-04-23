
/**
 * @file Daphneframe2_test.cxx Daphneframe2 class Unit Tests
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2022.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "detdataformats/daphne/Daphneframe2.hpp"

#define BOOST_TEST_MODULE Daphneframe2_test

#include "boost/test/unit_test.hpp"

#include <string>
#include <vector>
#include <random>

BOOST_AUTO_TEST_SUITE(Daphneframe2_test)

BOOST_AUTO_TEST_CASE(WIBEthFrame_ADCDataMutators)
{
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(1,(1<<14)-1);
  std::vector<int> v;

  for(int i=0; i<320; i++) {
    v.push_back(dist(rng));
  }

  dunedaq::fddetdataformats::Daphneframe2 daphneframe2 {};
  for(int i=0; i<320; i++) {
    daphneframe2.set_adc(i, v[i]);
  }

  for(int i=0; i<320; i++) {
    BOOST_REQUIRE_EQUAL(daphneframe2.get_adc(i), v[i]);
  }

}

BOOST_AUTO_TEST_SUITE_END()
