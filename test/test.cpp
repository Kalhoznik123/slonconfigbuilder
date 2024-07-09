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

class FromJsonBuilderTestFixture : public ::testing::Test {
protected:
  void SetUp() override {

    in_file = new std::ifstream("settings.json");

    builder = new builder::FromJsonBuilder(*in_file);
  }
  void TearDown() override {
    delete builder;
    delete in_file;
  }
  std::ifstream *in_file{};
  builder::FromJsonBuilder *builder{};
};

TEST_F(FromJsonBuilderTestFixture, ParseNoThrow) {
  // arrange
  // act

  // assert
  ASSERT_NO_THROW(builder->MakeSettings());
}

TEST(FromJsonBuilderTest, ParseNoThrowTime) {
  // arrange
  std::istringstream str(R"( {
  "internal": {
    "addres": "192.168.132.128",
    "mask": "255.255.255.0"
  },
  "abonents": [
    {
      "number": 1,
      "addres": "192.168.133.128",
      "mask": 25
    },
    {
      "number": 2,
      "addres": "192.168.133.245",
      "mask": 25
    }
  ],
  "arp": [
    {
      "number": 1,
      "arp_addres": "aa:bb:cc:22:33:55"
    }
  ],
  "lan": {
    "speed": 100,
    "mode": "FD",
    "type": "LAN"
  },
  "inet": {
    "speed": 100,
    "mode": "FD",
    "type": "INET"
  },
  "protocol": 53,
  "devicenumber": 1
})");
  builder::FromJsonBuilder bdr(str);
  // act
  // assert
  ASSERT_NO_THROW(bdr.MakeSettings());
}

TEST(FromJsonBuilderTest, ParseNoUniqueIPThrowTime) {
  // arrange
  std::istringstream str(R"( {
  "internal": {
    "addres": "192.168.132.128",
    "mask": "255.255.255.0"
  },
  "abonents": [
    {
      "number": 1,
      "addres": "192.168.133.128",
      "mask": 25
    },
    {
      "number": 2,
      "addres": "192.168.133.128",
      "mask": 25
    }
  ],
  "arp": [
    {
      "number": 1,
      "arp_addres": "aa:bb:cc:22:33:55"
    }
  ],
  "lan": {
    "speed": 100,
    "mode": "FD",
    "type": "LAN"
  },
  "inet": {
    "speed": 100,
    "mode": "FD",
    "type": "INET"
  },
  "protocol": 53,
  "devicenumber": 1
})");
  builder::FromJsonBuilder bdr(str);
  // act
  // assert
  ASSERT_THROW(bdr.MakeSettings(), std::logic_error);
}

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

TEST(AbonentRemote, Number) {

  // arrange
  abonent::AbonentRemote abonent("192.168.3.2", network::IP_Mask(25), 5);
  const std::uint8_t value{5};
  // act

  // assert
  ASSERT_EQ(abonent.Number(), value);
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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
