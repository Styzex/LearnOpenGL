/*
 Copyright (c) 2026 Viktor Paraj

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <Types.h>
#include <Utils.h>
#include <Log.h>
#include <iostream>

Log::LogLevel Log::s_log_level = Log::LogLevel::Debug;
String Log::s_app_id = "App";

Log::Log(const String context_)
  : m_gl_context(context_),
    m_id(0),
    m_error_id(0),
    m_debug_id(0) {}

void Log::SetAppID(const String app_id_) {
  s_app_id = app_id_;
}

void Log::SetLogLevel(LogLevel log_level_) {
  s_log_level = log_level_;
}

void Log::Info(String message_ = "") {
  if (LogLevel::Info >= s_log_level) {
    std::cout
      << "[" <<s_app_id << "]"
      << "[INFO]"
      << "[" << StringToUpper(m_gl_context) << "]"
      << "[" << m_id << "]"
      << ": "
      << message_
      << std::endl;
    m_id++;
  }
}

void Log::Error(String message_) {
  if (LogLevel::Error >= s_log_level) {
    std::cout
      << "[" <<s_app_id << "]"
      << "[ERROR]"
      << "[" << StringToUpper(m_gl_context) << "]"
      << "[" << m_error_id << "]"
      << ": "
      << message_
      << std::endl;
    m_error_id++;
  }
}

void Log::Debug(String message_) {
  if (LogLevel::Debug >= s_log_level) {
    std::cout
      << "[" <<s_app_id << "]"
      << "[DEBUG]"
      << "[" << StringToUpper(m_gl_context) << "]"
      << "[" << m_debug_id << "]"
      << ": "
      << message_
      << std::endl;
    m_debug_id++;
  }
}
