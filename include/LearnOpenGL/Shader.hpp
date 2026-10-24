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

#include <glad/glad.h>
#include <LearnOpenGL/Types.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

String get_file_contents(const char* filename);

namespace OpenGL {

class Shader {
 private:
  void Delete();

 public:
  // Reference ID of the Shader Program
  GLuint ID;
  // Constructor that build the Shader Program from 2 different shaders
  Shader(const char* vertexFile, const char* fragmentFile);
  ~Shader();

  // Activates the Shader Program
  void Activate();
  // Deletes the Shader Program
};

}  // namespace OpenGL
