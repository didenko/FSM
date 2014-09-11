/*
    Copyright( c ) 2014, Vlad Didenko
    All rights reserved.

    This project as a whole and each piece of it individually
    are licensed for use and redistribution under the conditions
    stated in the included LICENSE file, also known as
    "The BSD 3-Clause" License as described at
    http ://opensource.org/licenses/BSD-3-Clause.
*/

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
