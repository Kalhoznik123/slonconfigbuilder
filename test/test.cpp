#include "ARP.h"
#include "abonent.h"
#include "abonent_remote.h"
#include "interface_settings.h"
#include "ip_mask.h"
#include "json_builder.h"
#include "parsers.h"
#include "yaml_builder.h"
#include <exception>
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>


TEST(FromYamlBuilderTest, ParseNoThrowTime) {
  // arrange
  std::istringstream str(R"(
protocol: 53
time: 80
devicenumber: 1
inet:
    speed: 100
    mode: FD
    type: INET
lan:
    speed: 100
    mode: FD
    type: LAN
arp:
  - number: 1
    arp_address: 'aa:bb:cc:22:33:55'
  - number: 2
    arp_address: 'aa:cc:cc:ff:33:55'
abonents:
  - number: 1
    address: '192.168.133.128'
    mask: 24
  - number: 2
    address: '192.168.133.245'
    mask: 25
internal:
    address : '192.168.132.128'
    mask : '255.255.255.0'
)");
  builder::FromYamlBuilder bdr(str);
  // act
  // assert
  ASSERT_NO_THROW(bdr.MakeSettings());
}

TEST(ARPTest, Address) {
  // arrange
  network::ARP arp("aa:bb:cc:22:33:55");

  const std::string str = "aabbcc223355";
  // act

  // assert

  ASSERT_EQ(arp.Address(), str);
}

TEST(ARPTest, ARPConstuctorThrow) {
  // arrange
  // act
  // assert
  ASSERT_THROW(network::ARP("aa:bb:cc:22:33:5h"), std::exception);
}




int main(int argc, char **argv) {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
