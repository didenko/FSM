#include "TurnstileTypes.h"
#include "TurnstileLocked.h"
#include "TurnstileUnlocked.h"

namespace tools {
  namespace test {
    namespace fsm {

      Locked::Locked()
        : idx_locked(   std::type_index( typeid(   Locked ) ) )
        , idx_unlocked( std::type_index( typeid( Unlocked ) ) )
      {};

      std::type_index Locked::operator()( const TurnstileEvent & msg, std::shared_ptr<TurnstileData> data) {
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
            data->state_name = "locked";
            return idx_locked;
        }
      };
    }
  }
}
