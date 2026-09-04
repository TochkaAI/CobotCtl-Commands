#pragma once

#include "pproto/commands/base.h"

namespace pproto {
namespace error {

//--- 10 Ошибки общего плана ---
DECL_ERROR_CODE(product_license,           10, "73387aff-d4f8-461b-9789-b9600754420d", u8"Лицензия для сервиса CobotCtl не обнаружена")
DECL_ERROR_CODE(protect_key,               10, "14e27d0a-33a7-4018-abcd-05f5d0da3813", u8"Ключ аппаратной защиты для сервиса CobotCtl не обнаружен")

//---
DECL_ERROR_CODE(cobot_interface_not_init,  20, "e528314e-d9ee-47bb-bca2-82e486572ff7", u8"Интерфейс для подключения к коботу не инициализирован")
DECL_ERROR_CODE(cobot_connection,          20, "74f75fbf-8a7c-4de6-b901-59e83ac998a2", u8"Не удалось выполнить подключение к коботу")
DECL_ERROR_CODE(cobot_power_on,            20, "3fd768bc-cd8c-4f04-8e1c-cd02b91bc3fb", u8"Не удалось активировать кобота")
DECL_ERROR_CODE(cobot_power_on_ext,        20, "d5e1783f-dbf7-401d-879f-0c6eb968537d", u8"Не удалось активировать кобота. Детали: %1")
DECL_ERROR_CODE(cobot_running,             20, "d2ab88d6-232d-48e9-a03c-f6dcac44ead6", u8"Не удалось перевести кобота в рабочее состояние (Running)")
DECL_ERROR_CODE(cobot_running_state,       20, "c3a1f1cc-7cd2-4baf-8cbb-8157adad4083", u8"Кобот не находится в рабочем состоянии (Running)")
DECL_ERROR_CODE(cobot_power_off,           20, "4057fd33-3e57-480c-9d5c-060942322598", u8"Не удалось перевести кобота в состояние остановки")
DECL_ERROR_CODE(cobot_power_off_ext,       20, "625a7df3-61ae-488b-92b3-b2b2df0517c4", u8"Не удалось перевести кобота в состояние остановки. Детали: %1")
DECL_ERROR_CODE(cobot_api_interface,       20, "387f0eb0-0213-4f1e-b6d3-7c0ca06e9059", u8"Не удалось получить программный интерфейс %1")
DECL_ERROR_CODE(cobot_call_func,           20, "fe534da4-87e1-45a5-8be5-debab8c00413", u8"Не удалось вызвать функцию %1. Код ошибки: %2")
DECL_ERROR_CODE(aubo_exception,            20, "d5ff934c-98a3-4a4a-987e-535eb6521770", u8"Произошла исключительная ситуация при работе с AUBO SDK. Детали: %1")
DECL_ERROR_CODE(std_exception,             20, "4d8a4671-b5a7-4c66-83c2-9a4ac4c7e323", u8"Произошла исключительная ситуация при вызове функции %1. Детали: %2")
DECL_ERROR_CODE(cobot_path_buff_valid,     20, "f90d6c58-5650-455b-9dbd-8970d9612536", u8"Ошибка верификации данных для функции %1")
DECL_ERROR_CODE(no_active_executing_plan,  20, "6bebf22c-597b-4103-8a5c-1372c5afe2e9", u8"Ни один план не выполняется")
DECL_ERROR_CODE(plan_not_found,            20, "4e753576-bb91-4b51-920e-0282f63e4022", u8"План команд %1 не найден")
DECL_ERROR_CODE(plan_already_executing,    20, "9b9780ac-eae3-45b5-a06f-3f0ebbf1ecf6", u8"Выполняется другой план команд %1")
DECL_ERROR_CODE(plan_execution_stop,       20, "45875b0f-af98-4e06-90e7-7d0ac5c71af3", u8"Выполнение плана команд %1 остановлено принудительно")
DECL_ERROR_CODE(plan_execution_pause,      20, "759d3ec1-dc65-461f-b303-d4be2d051a5d", u8"Не удалось приостановить выполнение плана команд %1")
DECL_ERROR_CODE(plan_execution_resume,     20, "89809f89-b1c1-463a-917c-a5401bf31f4a", u8"Не удалось возобновить выполнение плана команд %1")


} // namespace error
} // namespace pproto
