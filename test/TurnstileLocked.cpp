#include "TurnstileTypes.h"
#include "TurnstileLocked.h"
#include "TurnstileUnlocked.h"

namespace tools {
  namespace test {
    namespace fsm {

      std::type_index Locked::idx_locked   = std::type_index( typeid(   Locked ) );
      std::type_index Locked::idx_unlocked = std::type_index( typeid( Unlocked ) );

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
