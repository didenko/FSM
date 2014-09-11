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

    static const std::type_index idx_nochange;

    // Never send events to one's own FSM from inside React descendant classes.
    // They will dead-lock. That will be especially painfull if circles back to
    // the FSM via a long chain of calls. This is why an FSM is not passed into
    // React classes. In most cases the desired workflow can be achieved by
    // returning a <true, messageValue> pair from OnArrive method and proper
    // state graph.

    class React {
    protected:
      std::shared_ptr<Content> cnt;
    public:
      React( std::shared_ptr<Content> & content ) : cnt( content ) {};
      virtual std::type_index OnReceive( const Message & msg ) = 0;
      virtual std::pair<bool, Message> OnArrive( const Message & msg )
      {
        return std::make_pair<bool, Message>( false, Message() );
      };
    };


    typedef std::vector<std::shared_ptr<React>> Flux;


    FSM( const Flux & flux )
    : current( std::type_index( typeid( *( flux.at(0) ) ) ) )
    {
      for ( auto rct: flux ) {
        states[ std::type_index( typeid( *rct ) ) ] = State( rct );
      };
    };

    void operator()( const Message & message )
    {
      std::lock_guard<std::mutex> lock( fsm_mutex );
      auto msg = message;
      bool has_message = true;
      while ( has_message )
      {
        has_message = false;
        auto next = states.at( current ).OnReceive( msg );
        if ( next != idx_nochange )
        {
          current = next;
          auto followup = states.at( current ).OnArrive( msg );
          if ( followup.first )
          {
            msg = followup.second;
            has_message = true;
          }
        }
      }
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

      std::pair<bool, Message> OnArrive( const Message & message )
      {
        return react->OnArrive( message );
      }

    private:
      std::shared_ptr<React> react;
    };


    std::mutex fsm_mutex;

    std::type_index current;
    std::map<std::type_index, State> states;
  };

  template <typename Message, typename Content>
  const std::type_index FSM<Message, Content>::idx_nochange = std::type_index( typeid(nullptr) );
}
