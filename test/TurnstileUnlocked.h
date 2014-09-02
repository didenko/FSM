#pragma once

namespace tools {
  namespace test {
    namespace fsm {

      class Unlocked: public TurnstileFSM::React {
      public:
        Unlocked( std::shared_ptr<TurnstileData> & content );
        std::type_index OnReceive( const TurnstileEvent & msg ) override;
        void OnArrive( const TurnstileEvent & msg ) override;
      private:
        static std::type_index idx_locked;
        static std::type_index idx_unlocked;
      };
    }
  }
}
