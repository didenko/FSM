#include "TurnstileTypes.h"
#include "TurnstileUnlocked.h"
#include "TurnstileLocked.h"

namespace tools {
  namespace test {
    namespace fsm {

      Unlocked::Unlocked()
        : idx_locked(   std::type_index( typeid(   Locked ) ) )
        , idx_unlocked( std::type_index( typeid( Unlocked ) ) )
      {};

      std::type_index Unlocked::operator()( const TurnstileEvent & msg, const std::shared_ptr<TurnstileData> & data) {
        switch (msg) {
          case PUSH:
            data->pushes += 1;
            data->state_name = "locked";
            return idx_locked;
          case PAY:
            data->coins += 1;
            data->state_name = "unlocked";
            return idx_unlocked;
          case RESET:
            data->pushes = 0;
            data->coins  = 0;
            data->state_name = "unlocked";
            return idx_unlocked;
        }
      };
    }
  }
}
