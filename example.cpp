/*
   Copyright 2020 Alexander Chernenko (achernenko@mail.ru)
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "register_type.hpp"

namespace Detail {

static const uint32_t SyncCtrl_RegAddr = 0x13;

enum class SyncCtrl_RegBitMask : Register32BitType {
  CLK_DIV_B0 = REGISTER_BITMASK_BIT(0),
  CLK_DIV_B1 = REGISTER_BITMASK_BIT(1),
  CE_PLL = REGISTER_BITMASK_BIT(2),
  EN_CXO = REGISTER_BITMASK_BIT(3),
  EN_CLK_DIV = REGISTER_BITMASK_BIT(4),
  EN_CLK2_C2M = REGISTER_BITMASK_BIT(5),
  EN_EXT_CLK = REGISTER_BITMASK_BIT(6),
  SRR_SELA = REGISTER_BITMASK_BIT(8),
  SRR_SELB = REGISTER_BITMASK_BIT(9),
  EN_SRR = REGISTER_BITMASK_BIT(11),
  AllBits = (CLK_DIV_B0 | CLK_DIV_B1 | CE_PLL | EN_CXO | EN_CLK_DIV |
             EN_CLK2_C2M | EN_EXT_CLK | SRR_SELA | SRR_SELB | EN_SRR)
};

enum class SyncCtrl_RegBitMaskDefault : Register32BitType {
  CLK_DIV_B0 = REGISTER_BITMASK_DEFAULT_TRUE(0),
  CLK_DIV_B1 = REGISTER_BITMASK_DEFAULT_TRUE(1),
  CE_PLL = REGISTER_BITMASK_DEFAULT_FALSE(2),
  EN_CXO = REGISTER_BITMASK_DEFAULT_FALSE(3),
  EN_CLK_DIV = REGISTER_BITMASK_DEFAULT_FALSE(4),
  EN_CLK2_C2M = REGISTER_BITMASK_DEFAULT_FALSE(5),
  EN_EXT_CLK = REGISTER_BITMASK_DEFAULT_FALSE(6),
  SRR_SELA = REGISTER_BITMASK_DEFAULT_TRUE(8),
  SRR_SELB = REGISTER_BITMASK_DEFAULT_TRUE(9),
  EN_SRR = REGISTER_BITMASK_DEFAULT_FALSE(11),
  AllBits = (CLK_DIV_B0 | CLK_DIV_B1 | CE_PLL | EN_CXO | EN_CLK_DIV |
             EN_CLK2_C2M | EN_EXT_CLK | SRR_SELA | SRR_SELB | EN_SRR)
};

#pragma pack(push, 1)

struct SyncCtrl_RegBits {
  bool CLK_DIV_B0 : 1;
  bool CLK_DIV_B1 : 1;
  bool CE_PLL : 1;
  bool EN_CXO : 1;
  bool EN_CLK_DIV : 1;
  bool EN_CLK2_C2M : 1;
  bool EN_EXT_CLK : 1;
  const bool _NOT_USED_7 : 1;
  bool SRR_SELA : 1;
  bool SRR_SELB : 1;
  const bool _NOT_USED_10 : 1;
  bool EN_SRR : 1;
  const bool _NOT_USED_12 : 1;
  const bool _NOT_USED_13 : 1;
  const bool _NOT_USED_14 : 1;
  const bool _NOT_USED_15 : 1;
  const uint16_t _NOT_USED_16_31 : 16;
};

#pragma pack(pop)

}  // namespace Detail

using SyncCtrl_Reg = Register32BitTypeAbstract<
    Detail::SyncCtrl_RegBitMask, Detail::SyncCtrl_RegBitMaskDefault,
    Detail::SyncCtrl_RegBits, decltype(Detail::SyncCtrl_RegAddr),
    Detail::SyncCtrl_RegAddr>;

int main(int argc, char *argv[]) try {
  SyncCtrl_Reg sync_ctrl_reg{};

  std::cout << "sync_ctrl_reg:\n" << std::hex;
  std::cout << "\tregister addr   "
            << "0x" << sync_ctrl_reg.getAddress() << '\n';

  std::cout << "clear all bits:\n";
  sync_ctrl_reg->clearAllBits();
  std::cout << "\tregister value  "
            << "0x" << sync_ctrl_reg.getValue() << '\n';

  std::cout << "set all bits:\n";
  sync_ctrl_reg->setAllBits();
  std::cout << "\tregister value  "
            << "0x" << sync_ctrl_reg.getValue() << '\n';

  std::cout << "set defaults:\n";
  sync_ctrl_reg->setAllDefaults();
  std::cout << "\tregister value  "
            << "0x" << sync_ctrl_reg.getValue() << '\n';

  std::cout << "set CE_PLL bit:\n";
  sync_ctrl_reg->Bits.CE_PLL = true;
  std::cout << "\tregister value  "
            << "0x" << sync_ctrl_reg.getValue() << '\n';

  std::cout << "clear CE_PLL bit:\n";
  sync_ctrl_reg->Bits.CE_PLL = false;
  std::cout << "\tregister value  "
            << "0x" << sync_ctrl_reg.getValue() << '\n';
  return 0;
} catch (...) {
  std::cerr << "\nunexpected exception\n";
  return 0;
}
