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


TEST(IPMaskTest, IpmaskContructorThrow) {
  // arrange

  // act

  // assert

  ASSERT_THROW(network::IP_Mask(54), std::exception);
  ASSERT_THROW(network::IP_Mask("255.255.255.54"), std::exception);
}

TEST(IPMaskTest, IpmaskContructorNothrow) {
  // arrange

  // act

  // assert
  ASSERT_NO_THROW(network::IP_Mask(0));
  ASSERT_NO_THROW(network::IP_Mask(32));
  ASSERT_NO_THROW(network::IP_Mask(25));
  ASSERT_NO_THROW(network::IP_Mask("255.255.255.0"));
  ASSERT_NO_THROW(network::IP_Mask("255.255.255.128"));
  ASSERT_NO_THROW(network::IP_Mask("0.0.0.0"));
}

TEST(IPMaskTest, IpmaskSetMask) {
  // arrange
  const std::string test_mask = "255.255.255.128";
  const std::string test_mask2 = "255.255.255.0";
  network::IP_Mask mask(test_mask2);
  network::IP_Mask mask2(24);
  // act
  mask.Mask(test_mask);
  mask2.Mask(25);
  mask.Mask(24);
  // assert
  ASSERT_EQ(mask.FullRecord(), test_mask2);
  ASSERT_EQ(mask2.FullRecord(), test_mask);
}

TEST(IPMaskTest, Less) {
  // arrange
  network::IP_Mask mask1(24);
  network::IP_Mask mask2(25);
  // act

  // assert
  ASSERT_LT(mask2, mask1);
}
TEST(IPMaskTest, Greater) {
  // arrange
  network::IP_Mask mask1(24);
  network::IP_Mask mask2(25);
  // act

  // assert
  ASSERT_GT(mask1, mask2);
}