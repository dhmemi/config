// Copyright (c) 2018-2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/config/

#ifndef TAO_CONFIG_INTERNAL_PHASE1_APPEND_HPP
#define TAO_CONFIG_INTERNAL_PHASE1_APPEND_HPP

#include <cassert>
#include <string>

#include "array.hpp"
#include "concat.hpp"
#include "entry.hpp"
#include "json.hpp"
#include "json_traits.hpp"
#include "key1.hpp"
#include "object.hpp"
#include "ref2.hpp"

namespace tao::config::internal
{
   template< typename V >
   void phase1_append_star( array& a, const key1& path, const V& value )
   {
      for( auto& c : a.array ) {
         phase1_append( c, path, value );
      }
   }

   template< typename V >
   bool phase1_append_star( concat& c, const key1& path, const V& value )
   {
      for( auto& e : c.concat ) {
         switch( e.kind() ) {
            case entry_kind::value:
               // TODO: Error or ignore?
               continue;
            case entry_kind::reference:
               // TODO: Error or ignore?
               continue;
            case entry_kind::array:
               for( auto& c : e.get_array().array ) {
                  phase1_append( c, path, value );
               }
               continue;
            case entry_kind::object:
               for( auto& c : e.get_object().object ) {
                  phase1_append( c.second, path, value );
               }
               continue;
         }
         assert( false );
      }
      return true;
   }

   template< typename V >
   bool phase1_append_name( concat& c, const std::string& name, const key1& path, const V& value )
   {
      c.back_ensure_kind( entry_kind::object );
      return phase1_append( c.concat.back().get_object().object[ name ], path, value );
   }

   template< typename V >
   bool phase1_append_index( concat& c, const std::size_t index, const key1& path, const V& value )
   {
      assert( false );  // TODO
   }

   inline bool phase1_append( concat& c, const json_t& value )
   {
      c.concat.emplace_back( value );
      return true;
   }

   inline bool phase1_append( concat& c, const ref2& value )
   {
      c.concat.emplace_back( value );
      return true;
   }

   inline bool phase1_append( concat& c, const entry_kind k )
   {
      c.back_ensure_kind( k );
      return true;
   }

   template< typename V >
   bool phase1_append( concat& c, const key1& path, const V& value )
   {
      if( path.empty() ) {
         return phase1_append( c, value );
      }
      switch( path.at( 0 ).kind() ) {
         case key1_kind::star:
            return phase1_append_star( c, pop_front( path ), value );
         case key1_kind::minus:
            assert( false );  // TODO
         case key1_kind::name:
            return phase1_append_name( c, path.at( 0 ).get_name(), pop_front( path ), value );
         case key1_kind::index:
            return phase1_append_index( c, path.at( 0 ).get_index(), pop_front( path ), value );
      }
      assert( false );
   }

   template< typename V >
   void phase1_append( object& o, const key1& path, const V& value )
   {
      assert( !path.empty() );

      phase1_append( o.object[ path.front().get_name() ], pop_front( path ), value );
   }

}  // namespace tao::config::internal

#endif