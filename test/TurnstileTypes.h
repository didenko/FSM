/*
    Copyright( c ) 2014, Vlad Didenko
    All rights reserved.

    This project as a whole and each piece of it individually
    are licensed for use and redistribution under the conditions
    stated in the included LICENSE file, also known as
    "The BSD 3-Clause" License as described at
    http ://opensource.org/licenses/BSD-3-Clause.
*/

#pragma once

#include "../FSM.h"

namespace tools {
  namespace test {
    namespace fsm {

      class TurnstileData {
      public:

        TurnstileData() : pushes(0), coins(0), recursed(false), state_name( "" ) {};

        unsigned long pushes;
        unsigned long coins;
        bool recursed;
        std::string state_name;
      };

      enum TurnstileEvent {
        PUSH,
        PAY,
        RESET,
        RECURSE,
        UNHANDLED
      };

      typedef FSM<TurnstileEvent, TurnstileData> TurnstileFSM;

      class Locked;
      class Unlocked;
      const std::type_index idx_locked( typeid(Locked) );
      const std::type_index idx_unlocked( typeid(Unlocked) );
    }
  }
}
