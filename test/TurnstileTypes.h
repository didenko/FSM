#pragma once

#include "../FSM.h"

namespace tools {
  namespace test {
    namespace fsm {

      class TurnstileData {
      public:

        TurnstileData() : pushes(0), coins(0), state_name( "" ) {};

        unsigned long pushes;
        unsigned long coins;
        std::string state_name;
      };

      enum TurnstileEvent {
        PUSH,
        PAY,
        RESET,
        UNHANDLED
      };

      typedef FSM<TurnstileEvent, TurnstileData> TurnstileFSM;
    }
  }
}
