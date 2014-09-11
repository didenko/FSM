#pragma once

#include "TurnstileTypes.h"

namespace tools {
  namespace test {
    namespace fsm {

      // Implementation of the Turnstile FSM example from:
      // http://en.wikipedia.org/wiki/Finite_state_machine#Example:_a_turnstile
      // Added RESET event to better test state.
      class Turnstile {
      public:

        Turnstile(void);

        void operator()( const TurnstileEvent & msg );

        unsigned long Pushed();
        unsigned long Paid();
        std::string Now();
        bool Recursed();

      private:

        TurnstileFSM::Flux flux;
        std::unique_ptr<TurnstileFSM> fsm;
        std::shared_ptr<TurnstileData> stats;
      };
    }
  }
}
