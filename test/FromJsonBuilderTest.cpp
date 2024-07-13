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



TEST(FromJsonBuilderTest, ParseDescriptionNotINT) {
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
      "mask": 25,
      "description": 23
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