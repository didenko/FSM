#pragma once

namespace tools {
  namespace test {
    namespace fsm {

      class Unlocked: public TurnstileFSM::React {
      public:
        Unlocked( std::shared_ptr<TurnstileData> & content );
        std::type_index operator()( const TurnstileEvent & msg ) override;
      private:
        static std::type_index idx_locked;
        static std::type_index idx_unlocked;
      };
    }
  }
}
