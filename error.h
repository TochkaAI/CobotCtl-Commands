#pragma once

#include "pproto/commands/base.h"

namespace pproto {
namespace error {

//--- 10 Ошибки общего плана ---
DECL_ERROR_CODE(product_license,           10, "73387aff-d4f8-461b-9789-b9600754420d", u8"Лицензия для сервиса CobotCtl не обнаружена")
DECL_ERROR_CODE(protect_key,               10, "14e27d0a-33a7-4018-abcd-05f5d0da3813", u8"Ключ аппаратной защиты для сервиса CobotCtl не обнаружен")

//---
DECL_ERROR_CODE(cobot_connection,          20, "74f75fbf-8a7c-4de6-b901-59e83ac998a2", u8"Не удалось выполнить подключение к коботу")
DECL_ERROR_CODE(cobot_power_on,            20, "3fd768bc-cd8c-4f04-8e1c-cd02b91bc3fb", u8"Не удалось активировать кобота")
DECL_ERROR_CODE(cobot_power_on_ext,        20, "d5e1783f-dbf7-401d-879f-0c6eb968537d", u8"Не удалось активировать кобота. Детали: %1")
DECL_ERROR_CODE(cobot_running,             20, "d2ab88d6-232d-48e9-a03c-f6dcac44ead6", u8"Не удалось перевести кобота в рабочее состояние")
DECL_ERROR_CODE(cobot_api_interface,       20, "387f0eb0-0213-4f1e-b6d3-7c0ca06e9059", u8"Не удалось получить программный интерфейс %1")
DECL_ERROR_CODE(cobot_call_func,           20, "fe534da4-87e1-45a5-8be5-debab8c00413", u8"Не удалось вызвать функцию %1. Код ошибки: %2")
DECL_ERROR_CODE(cobot_path_buff_valid,     20, "f90d6c58-5650-455b-9dbd-8970d9612536", u8"Ошибка верификации данных для функции %1")
DECL_ERROR_CODE(plan_not_found,            20, "4e753576-bb91-4b51-920e-0282f63e4022", u8"План команд %1 не найден")
DECL_ERROR_CODE(plan_already_executing,    20, "9b9780ac-eae3-45b5-a06f-3f0ebbf1ecf6", u8"Выполняется другой план команд")
DECL_ERROR_CODE(plan_execution_stop,       20, "45875b0f-af98-4e06-90e7-7d0ac5c71af3", u8"Выполнение плана команд %1 остановлено")


} // namespace error
} // namespace pproto
