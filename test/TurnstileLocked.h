#pragma once

namespace tools {
  namespace test {
    namespace fsm {

      class Locked: public TurnstileFSM::React {
      public:
        Locked( std::shared_ptr<TurnstileData> & content );
        std::type_index OnReceive( const TurnstileEvent & msg ) override;
        std::pair<bool, TurnstileEvent> OnArrive( const TurnstileEvent & msg ) override;
      private:
        static std::type_index idx_locked;
        static std::type_index idx_unlocked;
      };
    }
  }
}
