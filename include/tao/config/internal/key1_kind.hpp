// Copyright (c) 2020 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/config/

#ifndef TAO_CONFIG_INTERNAL_KEY1_KIND_HPP
#define TAO_CONFIG_INTERNAL_KEY1_KIND_HPP

namespace tao::config::internal
{
   enum class key1_kind : char
   {
      star = 0,
      minus = 1,
      name = 2,
      index = 3
   };

}  // namespace tao::config::internal

#endif