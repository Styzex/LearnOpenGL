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

#pragma once

#include <LearnOpenGL/Types.h>

class Log {
 public:
  enum class LogLevel {
    Debug = 0,
    Info = 1,
    Error = 2,
  };

 private:
  static Log::LogLevel s_log_level;
  static String s_app_id;
  String m_gl_context;
  int m_id;
  int m_error_id;
  int m_debug_id;

 public:
  explicit Log(const String context_);           // Constructor
  static void SetAppID(const String app_id_);    // App ID initializer
  static void SetLogLevel(LogLevel log_level_);  // Log level initializer
  void Info(String message_);
  void Error(String message_);
  void Debug(String message_);
};
