#pragma once

#include "../FSM.h"

namespace tools {
  namespace test {
    namespace fsm {

      class TurnstileData {
      public:

        TurnstileData() : pushes(0), coins(0), state_name( "locked" ) {};

        unsigned long pushes;
        unsigned long coins;
        std::string state_name;
      };

      enum TurnstileEvent {
        PUSH,
        PAY,
        RESET
      };

      typedef FSM<TurnstileEvent, TurnstileData> TurnstileFSM;
    }
  }
}
