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
