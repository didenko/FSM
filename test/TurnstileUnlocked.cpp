/*
    Copyright( c ) 2014, Vlad Didenko
    All rights reserved.

    This project as a whole and each piece of it individually
    are licensed for use and redistribution under the conditions
    stated in the included LICENSE file, also known as
    "The BSD 3-Clause" License as described at
    http ://opensource.org/licenses/BSD-3-Clause.
*/

#include "TurnstileTypes.h"
#include "TurnstileUnlocked.h"
#include "TurnstileLocked.h"

namespace tools {
  namespace test {
    namespace fsm {

      Unlocked::Unlocked( std::shared_ptr<TurnstileData> & content ) : React( content ) {};

      std::type_index Unlocked::OnReceive( const TurnstileEvent & msg )
      {
        switch (msg) {
          case PUSH:
            cnt->pushes += 1;
            return idx_locked;
          case PAY:
            cnt->coins += 1;
            return idx_unlocked;
          case RESET:
            cnt->pushes = 0;
            cnt->coins  = 0;
            return idx_locked;
          default:
            throw std::invalid_argument("Unknown message");
        }
      };

      std::pair<bool, TurnstileEvent> Unlocked::OnArrive( const TurnstileEvent & msg )
      {
        cnt->state_name = "unlocked";
        return std::make_pair<bool, TurnstileEvent>( false, TurnstileEvent() );
      };
    }
  }
}
