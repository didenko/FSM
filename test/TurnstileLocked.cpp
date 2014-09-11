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
#include "TurnstileLocked.h"
#include "TurnstileUnlocked.h"

namespace tools {
  namespace test {
    namespace fsm {

      Locked::Locked( std::shared_ptr<TurnstileData> & content ) : React( content )
      {
        content->state_name = "locked";
      };

      std::type_index Locked::OnReceive( const TurnstileEvent & msg )
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
          case RECURSE:
            cnt->recursed = true;
            return idx_locked;
          default:
            throw std::invalid_argument("Unknown message");
        }
      };

      std::pair<bool, TurnstileEvent> Locked::OnArrive( const TurnstileEvent & msg )
      {
        cnt->state_name = "locked";
        if ( msg == PUSH )
        {
          return std::make_pair<bool, TurnstileEvent>( true, RECURSE );
        }
        return std::make_pair<bool, TurnstileEvent>( false, TurnstileEvent() );
      };
    }
  }
}
