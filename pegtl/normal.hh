// Copyright (c) 2014-2017 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef PEGTL_NORMAL_HH
#define PEGTL_NORMAL_HH

#include "config.hh"
#include "apply_mode.hh"
#include "rewind_mode.hh"
#include "parse_error.hh"

#include "internal/demangle.hh"
#include "internal/rule_match_one.hh"

namespace PEGTL_NAMESPACE
{
   template< typename Rule >
   struct normal
   {
      template< typename Input, typename ... States >
      static void start( const Input &, States && ... )
      { }

      template< typename Input, typename ... States >
      static void success( const Input &, States && ... )
      { }

      template< typename Input, typename ... States >
      static void failure( const Input &, States && ... )
      { }

      template< typename Input, typename ... States >
      static void raise( const Input & in, States && ... )
      {
         using exception_t = typename Input::exception_t;
         throw exception_t( "parse error matching " + internal::demangle< Rule >(), in );
      }

      template< template< typename ... > class Action, typename Mark, typename Input, typename ... States >
      static void apply( const Mark & m, const Input & in, States && ... st )
      {
         using action_t = typename Input::action_t;
         Action< Rule >::apply( action_t( m, in.data() ), st ... );
      }

      template< apply_mode A, rewind_mode M, template< typename ... > class Action, template< typename ... > class Control, typename Input, typename ... States >
      static bool match( Input & in, States && ... st )
      {
         return internal::rule_match_one< Rule, A, M, Action, Control >::match( in, st ... );
      }
   };

} // namespace PEGTL_NAMESPACE

#endif
