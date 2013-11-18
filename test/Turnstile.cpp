#include "TurnstileTypes.h"
#include "TurnstileLocked.h"
#include "TurnstileUnlocked.h"
#include "Turnstile.h"

namespace tools {
  namespace test {
    namespace fsm {

      Turnstile::Turnstile(void)
      : stats( std::make_shared<TurnstileData>() )
      {
        flux.push_back( std::make_shared<Locked>() );
        flux.push_back( std::make_shared<Unlocked>() );
        fsm = std::unique_ptr<TurnstileFSM>( new TurnstileFSM( flux, stats ) );
      };

      void Turnstile::operator()( const TurnstileEvent & msg ) {
        (*fsm)( msg );
      };


      unsigned long Turnstile::Pushed() { return stats->pushes; };
      unsigned long Turnstile::Paid()   { return stats->coins;  };
      std::string Turnstile::Now()      { return stats->state_name; };

    }
  }
}