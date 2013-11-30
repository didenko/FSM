#include "TurnstileTypes.h"
#include "TurnstileUnlocked.h"
#include "TurnstileLocked.h"

namespace tools {
  namespace test {
    namespace fsm {

      std::type_index Unlocked::idx_locked   = std::type_index( typeid(   Locked ) );
      std::type_index Unlocked::idx_unlocked = std::type_index( typeid( Unlocked ) );

      Unlocked::Unlocked( std::shared_ptr<TurnstileData> & content ) : React( content ) {};

      std::type_index Unlocked::operator()( const TurnstileEvent & msg ) {
        switch (msg) {
          case PUSH:
            cnt->pushes += 1;
            cnt->state_name = "locked";
            return idx_locked;
          case PAY:
            cnt->coins += 1;
            cnt->state_name = "unlocked";
            return idx_unlocked;
          case RESET:
            cnt->pushes = 0;
            cnt->coins  = 0;
            cnt->state_name = "unlocked";
            return idx_unlocked;
          default:
            throw std::invalid_argument("Unknown message");
        }
      };
    }
  }
}
