#pragma once

namespace tools {
  namespace test {
    namespace fsm {

      class Locked: public TurnstileFSM::React {
      public:
        Locked(void);
        std::type_index operator()( const TurnstileEvent & msg, std::shared_ptr<TurnstileData> data) override;
      private:
        std::type_index idx_locked;
        std::type_index idx_unlocked;
      };
    }
  }
}
