#pragma once

#include "pproto/commands/base.h"

namespace pproto {
namespace error {

//--- 10 Ошибки общего плана ---
DECL_ERROR_CODE(product_license,           10, "fed7aeff-6e8f-4e34-94af-886c9d21de9f", u8"Лицензия для сервиса CobotCtl не обнаружена")
DECL_ERROR_CODE(protect_key,               10, "55ce44dd-3273-44ad-9af3-09f79a91b149", u8"Ключ аппаратной защиты для сервиса CobotCtl не обнаружен")


} // namespace error
} // namespace pproto
