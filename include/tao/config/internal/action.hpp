// Copyright (c) 2018-2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/config/

#ifndef TAO_CONFIG_INTERNAL_ACTION_HPP
#define TAO_CONFIG_INTERNAL_ACTION_HPP

#include <cassert>

#include "entry_kind.hpp"
#include "grammar.hpp"
#include "json.hpp"
#include "key1_guard.hpp"
#include "pegtl.hpp"
#include "phase1_append.hpp"
#include "phase1_remove.hpp"

namespace tao::config::internal
{
   template< typename Rule >
   struct action
      : pegtl::nothing< Rule >
   {};

   template<>
   struct action< rules::assign_head >
   {
      template< typename State >
      static void apply0( State& st )
      {
         phase1_remove( st.root, st.prefix + st.suffix );
      }
   };

   template<>
   struct action< json::jaxn::internal::rules::begin_array >
   {
      template< typename State >
      static void apply0( State& st )
      {
         phase1_append( st.root, st.prefix + st.suffix, entry_kind::array );
      }
   };

   template<>
   struct action< json::jaxn::internal::rules::begin_object >
   {
      template< typename State >
      static void apply0( State& st )
      {
         phase1_append( st.root, st.prefix + st.suffix, entry_kind::object );
      }
   };

   // Temporary (?) hack for arrays, during phase1 an implicit key1 index is interpreted as being relative to the last array of the target concat instead of an absolute index.

   template<>
   struct action< rules::value_list >
   {
      template< typename State >
      static void apply0( State& st )
      {
         assert( !st.suffix.empty() );

         if( st.suffix.back().kind() == key1_kind::append ) {
            st.suffix.back().set_append_flag();  // TODO: Update st.suffix.back().position, too???
         }
      }
   };

   template<>
   struct action< rules::element_list >
      : pegtl::instantiate< key1_guard >
   {};

}  // namespace tao::config::internal

#endif
