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

String StringToUpper(const String& str_) {
  String return_string;
  for (size_t i = 0; i < str_.size(); i++) {
    return_string.push_back(std::toupper(str_[i]));
  }
  return return_string;
}
