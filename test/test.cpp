#include <iostream>
#include <exception>
#include <fstream>
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
        abonent = new Abonent("192.168.3.2",IP_Mask(25));

    }
    void TearDown() override
    {
        delete abonent;
    }
    Abonent *abonent;
};

class FromJsonBuilderTest : public ::testing::Test
{
protected:
    void SetUp() override{

        in_file = new std::ifstream("settings.json");

        builder = new FromJsonBuilder(*in_file);

    }
    void TearDown() override
    {
        delete builder;
        delete  in_file;
    }
    std::ifstream *in_file;
    FromJsonBuilder *builder;
};

TEST_F(FromJsonBuilderTest,ParseNoThrow){
    //arrange
    //act

    //assert
    ASSERT_NO_THROW(builder->MakeSettings());
}



//FromJsonBuilder//

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
    IP_Mask mask(value);
    const Abonent abonent("192.168.3.2",mask);
    //act

    //assert

    ASSERT_EQ(abonent.Mask().FullRecord(),value);
}

TEST(AbonentRemote,Number){

    //arrange
    AbonentRemote abonent("192.168.3.2",IP_Mask(25),5);
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

    ASSERT_THROW(IP_Mask(54),std::exception);
    ASSERT_THROW(IP_Mask("255.255.255.54"),std::exception);
}

TEST(IPMaskTest,IpmaskContructorNothrow){
    //arrange


    //act

    //assert
    ASSERT_NO_THROW(IP_Mask(0));
    ASSERT_NO_THROW(IP_Mask(32));
    ASSERT_NO_THROW(IP_Mask(25));
    ASSERT_NO_THROW(IP_Mask("255.255.255.0"));
    ASSERT_NO_THROW(IP_Mask("255.255.255.128"));
    ASSERT_NO_THROW(IP_Mask("0.0.0.0"));
}


TEST(IPMaskTest,IpmaskSetMask){
    //arrange
    const std::string test_mask = "255.255.255.128";
    const std::string test_mask2 = "255.255.255.0";
    IP_Mask mask(test_mask2);
    IP_Mask mask2(24);
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
    IP_Mask mask1(24);
    IP_Mask mask2(25);
    //act

    //assert
    ASSERT_LT(mask2,mask1);

}
TEST(IPMaskTest,Greater){
    //arrange
    IP_Mask mask1(24);
    IP_Mask mask2(25);
    //act

    //assert
    ASSERT_GT(mask1,mask2);

}

TEST(IPMaskTest,Not_equal){
    //arrange
    IP_Mask mask1(24);
    IP_Mask mask2(25);

    //act

    //assert

    ASSERT_NE(mask1,mask2);
}


int main(int argc, char* *argv){

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
