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


    class React {
    public:
      virtual std::type_index operator()( const Message & msg, std::shared_ptr<Content> ) {
        return std::type_index(typeid(this));
      };
    };


    typedef std::vector<std::shared_ptr<React>> Flux;


    class State {

    public:
      State( std::shared_ptr<React> rct, std::shared_ptr<Content> ctnt )
      : content( ctnt ), react( rct ) {};

      State() : content( nullptr ), react( nullptr ) {};

      std::type_index operator()( const Message & message ) {
        return (*react)( message, content );
      }

    private:
      std::shared_ptr<Content> content;
      std::shared_ptr<React> react;
    };


    FSM( Flux & flux, std::shared_ptr<Content> ctnt )
    : current( std::type_index( typeid( *( flux.at(0) ) ) ) )
    , content( ctnt )
    {
      for ( auto rct: flux ) {
        states[ std::type_index( typeid( *rct ) ) ] = State( rct, content );
      };
    };

    void operator()( const Message & msg ) {
      std::lock_guard<std::mutex> lock( fsm_mutex );
      current = states.at( current )( msg );
    };


  private:
    std::mutex fsm_mutex;

    std::shared_ptr<Content> content;
    std::type_index current;
    std::map<std::type_index, State> states;
  };
}