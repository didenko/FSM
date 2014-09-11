#pragma once

namespace tools {
  namespace test {
    namespace fsm {

      class Unlocked: public TurnstileFSM::React {
      public:
        Unlocked( std::shared_ptr<TurnstileData> & content );
        std::type_index OnReceive( const TurnstileEvent & msg ) override;
        std::pair<bool, TurnstileEvent> OnArrive( const TurnstileEvent & msg ) override;
      };
    }
  }
}
