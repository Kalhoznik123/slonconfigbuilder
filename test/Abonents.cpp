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

class AbonentTest : public ::testing::Test {
protected:
  void SetUp() override {
    abonent = new abonent::Abonent("192.168.3.2", network::IP_Mask(25));
  }
  void TearDown() override { delete abonent; }
  abonent::Abonent *abonent{};
};
TEST_F(AbonentTest, arp_address) {
  // arrange
  const std::string adr = "192.168.3.2";
  // act

  // assert

  ASSERT_EQ(abonent->Ip_addres(), adr);
}

TEST_F(AbonentTest, ShortRecord) {
  //    //arrange
  std::string mask = "25";
  auto value = abonent->Mask();

  //    //act

  //    //assert

  ASSERT_EQ(std::to_string(value.ShortRecord()), mask);
}

TEST(Abonent, FullRecord) {

  // arrange
  const std::string value = "255.255.255.0";
  network::IP_Mask mask(value);
  const abonent::Abonent abonent("192.168.3.2", mask);
  // act

  // assert

  ASSERT_EQ(abonent.Mask().FullRecord(), value);
}

TEST(AbonentRemoteTest, Number) {

  // arrange
  abonent::AbonentRemote abonent("192.168.3.2", network::IP_Mask(25), 5);
  const std::uint8_t value{5};
  // act

  // assert
  ASSERT_EQ(abonent.Number(), value);
}
