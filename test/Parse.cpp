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


TEST(ParserInterfaceTest, Parse) {
  // arrange

  parsers::interface_parser::InterfaceParseRes res;
  const std::string value = "100FD";

  // act
  bool ok = parsers::Parse<
      parsers::interface_parser::interface_parser<std::string::const_iterator>>(
      value, res);

  // assert

  ASSERT_EQ(ok, true);
}

TEST(ParserInterfaceTest, ParseWhithSpaces) {
  // arrange
  using parser =
      parsers::interface_parser::interface_parser<std::string::const_iterator>;

  parsers::interface_parser::InterfaceParseRes res;
  const std::string value = "100     FD";

  // act

  bool ok = parsers::Parse<parser>(value, res);

  // assert

  ASSERT_TRUE(ok);
}

TEST(ParserInterfaceTest, Result) {
  // arrange
  using parser =
      parsers::interface_parser::interface_parser<std::string::const_iterator>;

  parsers::interface_parser::InterfaceParseRes res;
  parsers::interface_parser::InterfaceParseRes res2;
  const std::string value_FD = "100FD";
  const std::string value_HD = "50HD";
  // act
  parsers::Parse<parser>(value_FD, res);
  parsers::Parse<parser>(value_HD, res2);
  // assert

  ASSERT_EQ(res.mode, std::string("FD"));
  ASSERT_EQ(res.speed, 100);

  ASSERT_EQ(res2.mode, std::string("HD"));
  ASSERT_EQ(res2.speed, 50);
}

TEST(ParserInternalAbonentTest, IP_AdressResult) {
  // arrange
  using parser = parsers::internal_abonent_parser::internal_abonent_parser<
      std::string::const_iterator>;
  parsers::internal_abonent_parser::IAbonentParseRes res;
  parsers::internal_abonent_parser::IAbonentParseRes res2;
  parsers::internal_abonent_parser::IAbonentParseRes res3;

  const std::string value = "192.168.3.0 24";
  const std::string value2 = "22.22.33.0 24";
  const std::string value3 = "1.1.123.0 24";
  // act
  parsers::Parse<parser>(value, res);
  parsers::Parse<parser>(value2, res2);
  parsers::Parse<parser>(value3, res3);
  // assert

  ASSERT_EQ(res.ip_address, std::string("192.168.3.0"));
  ASSERT_EQ(res2.ip_address, std::string("22.22.33.0"));
  ASSERT_EQ(res3.ip_address, std::string("1.1.123.0"));
}

TEST(ParserInternalAbonentTest, MaskIntType) {
  // arrange

  parsers::internal_abonent_parser::IAbonentParseRes res;
  const std::string value = "192.168.3.0 24";

  // act
  parsers::Parse<parsers::internal_abonent_parser::internal_abonent_parser<
      std::string::const_iterator>>(value, res);
  // p

  // assert

  ASSERT_EQ(boost::get<int>(res.mask), 24);
}

TEST(ParserInternalAbonentTest, ParseFail) {
  // arrange
  using parser = parsers::internal_abonent_parser::internal_abonent_parser<
      std::string::const_iterator>;
  parsers::internal_abonent_parser::IAbonentParseRes res;
  parsers::internal_abonent_parser::IAbonentParseRes res2;
  parsers::internal_abonent_parser::IAbonentParseRes res3;
  const std::string value = "192.12368.1.0 24";
  const std::string value2 = "112312392.168.2.0 24";
  const std::string value3 = "192.16453453458.2.0 24";
  // act
  bool ok = parsers::Parse<parser>(value, res);
  bool ok2 = parsers::Parse<parser>(value2, res2);
  bool ok3 = parsers::Parse<parser>(value3, res3);
  // p

  // assert

  ASSERT_FALSE(ok);
  ASSERT_FALSE(ok2);
  ASSERT_FALSE(ok3);
}

TEST(ParserInternalAbonentTest, MaskStringType) {
  // arrange

  parsers::internal_abonent_parser::IAbonentParseRes res;
  const std::string value = "192.168.3.0 255.255.255.0";

  // act

  parsers::Parse<parsers::internal_abonent_parser::internal_abonent_parser<
      std::string::const_iterator>>(value, res);

  // assert

  ASSERT_EQ(boost::get<std::string>(res.mask), "255.255.255.0");
}

TEST(ParserRemoteAbonentTest, ParseResult_Mask_string) {
  // arrange
  parsers::remote_abonent_parser::RAbonentParseRes res;
  std::string value = "25      192.168.3.0 255.255.255.0";

  // act

  bool ok =
      parsers::Parse<parsers::remote_abonent_parser::remote_abonent_parser<
          std::string::const_iterator>>(value, res);

  // assert
  ASSERT_TRUE(ok);
  ASSERT_EQ(res.devicenumber, 25);
  ASSERT_EQ(res.ip_address, "192.168.3.0");
  ASSERT_EQ(boost::get<std::string>(res.mask), "255.255.255.0");
}

TEST(ParserRemoteAbonentTest, ParseResult_Mask_int) {
  // arrange
  parsers::remote_abonent_parser::RAbonentParseRes res;
  std::string value = "25 192.168.3.0 24";

  // act

  bool ok =
      parsers::Parse<parsers::remote_abonent_parser::remote_abonent_parser<
          std::string::const_iterator>>(value, res);

  // assert
  ASSERT_TRUE(ok);
  ASSERT_EQ(res.devicenumber, 25);
  ASSERT_EQ(res.ip_address, "192.168.3.0");
  ASSERT_EQ(boost::get<int>(res.mask), 24);
}

TEST(ParserRemoteAbonentTest, ParseResult) {
  // arrange
  parsers::remote_abonent_parser::RAbonentParseRes res;
  std::string value = "25  24";

  // act

  bool ok =
      parsers::Parse<parsers::remote_abonent_parser::remote_abonent_parser<
          std::string::const_iterator>>(value, res);

  // assert
  ASSERT_FALSE(ok);
}

TEST(ParserARPAddressTest, ParseResult) {
  // arrange
  parsers::ARP_address_parser::ARPAddressParseRes res;
  std::string value = "4 aabbcc444455";

  parsers::ARP_address_parser::ARPAddressParseRes res2;
  std::string value2 = "99 44bbcc444455";

  // act
  parsers::Parse<parsers::ARP_address_parser::ARP_address_parser<
      std::string::const_iterator>>(value, res);
  parsers::Parse<parsers::ARP_address_parser::ARP_address_parser<
      std::string::const_iterator>>(value2, res2);
  // assert
  ASSERT_EQ(res.number, 4);
  ASSERT_EQ(res.ARP_address, "aabbcc444455");

  ASSERT_EQ(res2.number, 99);
  ASSERT_EQ(res2.ARP_address, "44bbcc444455");
}

TEST(ParserARPAddressTest, ParseFail) {

  // arrange
  parsers::ARP_address_parser::ARPAddressParseRes res;
  std::string value = "4 aabycc444455";

  parsers::ARP_address_parser::ARPAddressParseRes res3;
  std::string value3 = "4 --aabbcc444455";

  // act

  bool ok = parsers::Parse<parsers::ARP_address_parser::ARP_address_parser<
      std::string::const_iterator>>(value, res);
  bool ok3 = parsers::Parse<parsers::ARP_address_parser::ARP_address_parser<
      std::string::const_iterator>>(value3, res3);

  // assert
  ASSERT_FALSE(ok);
  // ASSERT_FALSE(ok2);

  ASSERT_FALSE(ok3);
}
