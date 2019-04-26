// Copyright (c) 2018-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/config/

#ifndef TAO_CONFIG_INTERNAL_PHASE2_TRAITS_HPP
#define TAO_CONFIG_INTERNAL_PHASE2_TRAITS_HPP

#include "annotation.hpp"
#include "format_traits.hpp"
#include "json.hpp"

namespace tao
{
   namespace config
   {
      namespace internal
      {
         template< typename T >
         struct phase2_traits
            : public format_traits< T >
         {
         };

         template<>
         struct phase2_traits< void >
            : public format_traits< void >
         {
            static constexpr const bool enable_implicit_constructor = false;

            template< typename Value >
            using public_base = annotation;
         };

      }  // namespace internal

   }  // namespace config

}  // namespace tao

#endif