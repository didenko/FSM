#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <typeindex>
#include <mutex>

namespace tools {

  template <typename Message, typename Content>
  class FSM {
  public:

    // Never send events to one's own FSM from inside React descendant classes.
    // They will dead-lock. That will be especially painfull if circles back to
    // the FSM via a long chain of calls
    class React {
    protected:
      std::shared_ptr<Content> cnt;
    public:
      React( std::shared_ptr<Content> & content ) : cnt( content ) {};
      virtual std::type_index OnReceive( const Message & msg ) = 0;
    };


    typedef std::vector<std::shared_ptr<React>> Flux;


    FSM( const Flux & flux )
    : current( std::type_index( typeid( *( flux.at(0) ) ) ) )
    {
      for ( auto rct: flux ) {
        states[ std::type_index( typeid( *rct ) ) ] = State( rct );
      };
    };

    void operator()( const Message & msg ) {
      std::lock_guard<std::mutex> lock( fsm_mutex );
      current = states.at( current ).OnReceive( msg );
    };


  private:


    class State {

    public:
      State( const std::shared_ptr<React> & rct )
      : react( rct ) {};

      State() : react( nullptr ) {};

      std::type_index OnReceive( const Message & message ) {
        return react->OnReceive( message );
      }

    private:
      std::shared_ptr<React> react;
    };


    std::mutex fsm_mutex;

    std::type_index current;
    std::map<std::type_index, State> states;
  };
}
