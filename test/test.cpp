#include <iostream>
#include <exception>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ARP.h"
#include "../src/ip_mask.h"
#include "../src/abonent.h"
#include "../src/interface_settings.h"

class TestAbonent : public ::testing::Test
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

TEST_F(TestAbonent,arp_address){
    //arrange
    const std::string adr = "192.168.3.2";
    //act

    //assert

    ASSERT_EQ(abonent->Address(),adr);

}

TEST_F(TestAbonent,Mask_int){
    //    //arrange
    std::string mask = "25";
    auto value = abonent->Mask();


    //    //act

    //    //assert

    ASSERT_EQ(std::to_string(value.ShortRecord()),mask);
}



TEST(Abonent,Mask_string){

    //arrange
    const std::string value = "255.255.255.0";
    IP_Mask mask(value);
    const Abonent abonent("192.168.3.2",mask);
    //act

    //assert

    ASSERT_EQ(abonent.Mask().FullRecord(),value);
}



TEST(arp_test,arp_to_string){
    //arrange
    network::ARP arp("aa:bb:cc:22:33:55");
    const std::string str = "aabbcc223355";
    //act

    //assert

    ASSERT_EQ(arp.ToString(),str);
}

TEST(arp_test,arp_constructor_throw){
    //arrange


    //act

    //assert

    ASSERT_THROW(network::ARP("aa:bb:cc:22:33:5h"),std::exception);

}

TEST(InterfaceSettings,InterfaceSettings_ToString){
    //arrange
    using namespace std::string_literals;
    InterfaceSettings setting{100,"FD"s,InterfaceType::INET};

    //act

    //assert
    ASSERT_EQ(setting.ToString(),"100FD"s);
    ASSERT_NE(setting.ToString(),"100HD"s);
}

TEST(IPMask,ipmask_constructor_throw){
    //arrange


    //act

    //assert

    ASSERT_THROW(IP_Mask(54),std::exception);
    ASSERT_THROW(IP_Mask("255.255.255.54"),std::exception);
}

TEST(IPMask,ipmask_constructor_nothrow){
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


TEST(IPMask,ipmask_MASK){
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


TEST(IPMask,less){
    //arrange
    IP_Mask mask1(24);
    IP_Mask mask2(25);
    //act

    //assert
    ASSERT_LT(mask2,mask1);

}
TEST(IPMask,greater){
    //arrange
    IP_Mask mask1(24);
    IP_Mask mask2(25);
    //act

    //assert
    ASSERT_GT(mask1,mask2);

}

TEST(IPMask,not_equal){
    //arrange
    IP_Mask mask1(24);
    IP_Mask mask2(25);

    //act

    //assert

    ASSERT_NE(mask1,mask2);
}


int main(int argc, char* *argv)
{

    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}
