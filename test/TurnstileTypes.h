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
    }
  }
}
