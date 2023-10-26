#include <iostream>
#include <exception>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ARP.h"
#include "../src/abonent.h"

class TestAbonent : public ::testing::Test
{
protected:
    void SetUp() override
    {
        abonent = new Abonent("192.168.3.2",25,AbonentType::REMOTE);

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
    //arrange
    int mask = 25;
    auto value = abonent->Mask();
    std::get<int>(value);

    //act

    //assert

    ASSERT_EQ(std::get<int>(value),mask);

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


int main(int argc, char* *argv)
{
  ::testing::InitGoogleTest();


   return RUN_ALL_TESTS();



}
