#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ARP.h"
#include "../src/ip_mask.h"
#include "../src/abonent.h"
#include "../src/interface_settings.h"
#include "../src/abonent_remote.h"
#include "../src/json_builder.h"

class AbonentTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        abonent = new abonent::Abonent("192.168.3.2",network::IP_Mask(25));

    }
    void TearDown() override
    {
        delete abonent;
    }
    abonent::Abonent *abonent;
};

class FromJsonBuilderTestFixture : public ::testing::Test
{
protected:
    void SetUp() override{

        in_file = new std::ifstream("settings.json");

        builder = new builder::FromJsonBuilder(*in_file);

    }
    void TearDown() override
    {
        delete builder;
        delete  in_file;
    }
    std::ifstream *in_file;
   builder::FromJsonBuilder *builder;
};

TEST_F(FromJsonBuilderTestFixture,ParseNoThrow){
    //arrange
    //act

    //assert
    ASSERT_NO_THROW(builder->MakeSettings());
}

TEST(FromJsonBuilderTest,ParseThrowInternal ){
    //arrange
    std::istringstream str(R"( { "abonents": [
                       {
                         "number": 1,
                         "address": "192.168.133.128",
                         "mask": 25
                       },
                       {
                         "number": 2,
                         "address": "192.168.133.245",
                         "mask": 25
                       }
                     ],
                     "arp": [
                       {
                         "number": 1,
                         "arp_address": "aa:bb:cc:22:33:55"
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
                     "time": 80,
                     "devicenumber": 1
                   })");
    builder::FromJsonBuilder bdr(str);
    //act

    //assert
    ASSERT_THROW(bdr.MakeSettings(),std::exception);
}
//FromJsonBuilder//
TEST(FromJsonBuilderTest,ParseThrowAbonents ){
    //arrange
    std::istringstream str(R"( {
  "internal": {
    "address": "192.168.132.128",
    "mask": "255.255.255.0"
  },
  "arp": [
    {
      "number": 1,
      "arp_address": "aa:bb:cc:22:33:55"
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
  "time": 80,
  "devicenumber": 1
})");
    builder::FromJsonBuilder bdr(str);
    //act

    //assert
    ASSERT_THROW(bdr.MakeSettings(),std::exception);
}
TEST(FromJsonBuilderTest,ParseThrowLan ){
    //arrange
    std::istringstream str(R"( {
  "internal": {
    "address": "192.168.132.128",
    "mask": "255.255.255.0"
  },
  "abonents": [
    {
      "number": 1,
      "address": "192.168.133.128",
      "mask": 25
    },
    {
      "number": 2,
      "address": "192.168.133.245",
      "mask": 25
    }
  ],
  "arp": [
    {
      "number": 1,
      "arp_address": "aa:bb:cc:22:33:55"
    }
  ],
  "inet": {
    "speed": 100,
    "mode": "FD",
    "type": "INET"
  },
  "protocol": 53,
  "time": 80,
  "devicenumber": 1
})");

    builder::FromJsonBuilder bdr(str);
    //act

    //assert
    ASSERT_THROW(bdr.MakeSettings(),std::exception);
}

TEST(FromJsonBuilderTest,ParseThrowArp ){
    //arrange
    std::istringstream str(R"( {
  "internal": {
    "address": "192.168.132.128",
    "mask": "255.255.255.0"
  },
  "abonents": [
    {
      "number": 1,
      "address": "192.168.133.128",
      "mask": 25
    },
    {
      "number": 2,
      "address": "192.168.133.245",
      "mask": 25
    }
  ],
  "lan": {
    "speed": 100,
    "mode": "FD",
    "type": "LAN"
  },
  "protocol": 53,
  "time": 80,
  "devicenumber": 1
})");
    builder::FromJsonBuilder bdr(str);
    //act
    //assert
    ASSERT_THROW(bdr.MakeSettings(),std::exception);
}

TEST(FromJsonBuilderTest,ParseThrowInet ){
    //arrange
    std::istringstream str(R"( {
  "internal": {
    "address": "192.168.132.128",
    "mask": "255.255.255.0"
  },
  "abonents": [
    {
      "number": 1,
      "address": "192.168.133.128",
      "mask": 25
    },
    {
      "number": 2,
      "address": "192.168.133.245",
      "mask": 25
    }
  ],
  "arp": [
    {
      "number": 1,
      "arp_address": "aa:bb:cc:22:33:55"
    }
  ],
  "lan": {
    "speed": 100,
    "mode": "FD",
    "type": "LAN"
  },
  "protocol": 53,
  "time": 80,
  "devicenumber": 1
})");
    builder::FromJsonBuilder bdr(str);
    //act
    //assert
    ASSERT_THROW(bdr.MakeSettings(),std::exception);
}
TEST(FromJsonBuilderTest,ParseNoThrowTime ){
    //arrange
    std::istringstream str(R"( {
  "internal": {
    "address": "192.168.132.128",
    "mask": "255.255.255.0"
  },
  "abonents": [
    {
      "number": 1,
      "address": "192.168.133.128",
      "mask": 25
    },
    {
      "number": 2,
      "address": "192.168.133.245",
      "mask": 25
    }
  ],
  "arp": [
    {
      "number": 1,
      "arp_address": "aa:bb:cc:22:33:55"
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
    //act
    //assert
    ASSERT_NO_THROW(bdr.MakeSettings());
}


TEST_F(AbonentTest,arp_address){
    //arrange
    const std::string adr = "192.168.3.2";
    //act

    //assert

    ASSERT_EQ(abonent->Address(),adr);

}

TEST_F(AbonentTest,ShortRecord){
    //    //arrange
    std::string mask = "25";
    auto value = abonent->Mask();


    //    //act

    //    //assert

    ASSERT_EQ(std::to_string(value.ShortRecord()),mask);
}



TEST(Abonent,FullRecord){

    //arrange
    const std::string value = "255.255.255.0";
    network::IP_Mask mask(value);
    const abonent::Abonent abonent("192.168.3.2",mask);
    //act

    //assert

    ASSERT_EQ(abonent.Mask().FullRecord(),value);
}

TEST(AbonentRemote,Number){

    //arrange
    abonent::AbonentRemote abonent("192.168.3.2",network::IP_Mask(25),5);
    const std::uint8_t value{5};
    //act


    //assert
    ASSERT_EQ(abonent.Number(),value);
}
TEST(ARPTest,Address){
    //arrange
    network::ARP arp("aa:bb:cc:22:33:55");

    const std::string str = "aabbcc223355";
    //act

    //assert

    ASSERT_EQ(arp.Address(),str);
}

TEST(ARPTest,ARPConstuctorThrow){
    //arrange


    //act

    //assert

    ASSERT_THROW(network::ARP("aa:bb:cc:22:33:5h"),std::exception);
}


TEST(IPMaskTest,IpmaskContructorThrow){
    //arrange


    //act

    //assert

    ASSERT_THROW(network::IP_Mask(54),std::exception);
    ASSERT_THROW(network::IP_Mask("255.255.255.54"),std::exception);
}

TEST(IPMaskTest,IpmaskContructorNothrow){
    //arrange


    //act

    //assert
    ASSERT_NO_THROW(network::IP_Mask(0));
    ASSERT_NO_THROW(network::IP_Mask(32));
    ASSERT_NO_THROW(network::IP_Mask(25));
    ASSERT_NO_THROW(network::IP_Mask("255.255.255.0"));
    ASSERT_NO_THROW(network::IP_Mask("255.255.255.128"));
    ASSERT_NO_THROW(network::IP_Mask("0.0.0.0"));
}


TEST(IPMaskTest,IpmaskSetMask){
    //arrange
    const std::string test_mask = "255.255.255.128";
    const std::string test_mask2 = "255.255.255.0";
    network::IP_Mask mask(test_mask2);
    network::IP_Mask mask2(24);
    //act
    mask.Mask(test_mask);
    mask2.Mask(25);
    mask.Mask(24);
    //assert
    ASSERT_EQ(mask.FullRecord(),test_mask2);
    ASSERT_EQ(mask2.FullRecord(),test_mask);
}


TEST(IPMaskTest,Less){
    //arrange
    network::IP_Mask mask1(24);
    network::IP_Mask mask2(25);
    //act

    //assert
    ASSERT_LT(mask2,mask1);

}
TEST(IPMaskTest,Greater){
    //arrange
    network::IP_Mask mask1(24);
    network::IP_Mask mask2(25);
    //act

    //assert
    ASSERT_GT(mask1,mask2);

}

TEST(IPMaskTest,Not_equal){
    //arrange
    network::IP_Mask mask1(24);
    network::IP_Mask mask2(25);

    //act

    //assert

    ASSERT_NE(mask1,mask2);
}


int main(int argc, char* *argv){

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
