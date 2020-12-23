// Copyright (c) 2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/config/

#ifndef TAO_CONFIG_INTERNAL_KEY_GRAMMAR_HPP
#define TAO_CONFIG_INTERNAL_KEY_GRAMMAR_HPP

#include "json.hpp"
#include "pegtl.hpp"

namespace tao::config::internal::rules
{
   namespace jaxn = tao::json::jaxn::internal::rules;

   // clang-format off
   struct dot : pegtl::one< '.' > {};
   struct minus : pegtl::one< '-' > {};

   struct index : pegtl::plus< pegtl::digit > {};

   struct ident_first : pegtl::ranges< 'a', 'z', 'A', 'Z', '_' > {};
   struct ident_other : pegtl::ranges< 'a', 'z', 'A', 'Z', '0', '9', '-', '-', '_' > {};
   struct ident : pegtl::seq< ident_first, pegtl::star< ident_other > > {};

   struct at_quote : pegtl::at< pegtl::one< '\'', '"' > > {};

   struct quoted_choice : jaxn::string_fragment {};
   struct quoted : pegtl::if_must< at_quote, quoted_choice > {};

   struct key_other : pegtl::sor< ident, quoted, index, minus > {};
   struct key_first : pegtl::sor< ident, quoted > {};

   struct key : pegtl::seq< key_first, pegtl::star_must< dot, key_other > > {};
   // clang-format on

}  // namespace tao::config::internal::rules

#endif