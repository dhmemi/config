// Copyright (c) 2018 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/config/

#ifndef TAO_CONFIG_INTERNAL_NUMBER_STATE_HPP
#define TAO_CONFIG_INTERNAL_NUMBER_STATE_HPP

#include <cstddef>
#include <utility>
#include <string>

#include "pegtl.hpp"
#include "state.hpp"

namespace tao
{
   namespace config
   {
      namespace internal
      {
         struct number_state
         {
            template< typename Input, typename T >
            explicit number_state( const Input& in, const T& )
               : m_position( in.position() )
            {
            }

            number_state( const number_state& ) = delete;
            number_state( number_state&& ) = delete;

            ~number_state() = default;

            void operator=( const number_state& ) = delete;
            void operator=( number_state&& ) = delete;

            template< typename Input >
            void success( const Input&, state& st )
            {
               assert( m_value );
               assert( !st.lstack.empty() );

               st.lstack.back()->v.emplace_back( entry::make_atom( m_position, m_value ) );
            }

            template< typename Input, typename T >
            void success( const Input&, const T& )
            {
               assert( false );  // This function is required because json::jaxn::internal::rules::sor_value is recursive which is more than we need but difficult to prevent.
            }

            template< typename T >
            void number( const T n )
            {
               m_value = n;
            }

            json::value m_value;

            const pegtl::position m_position;
         };

      }  // namespace internal

   }  // namespace config

}  // namespace tao

#endif