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

#include <LearnOpenGL/Shader.hpp>
#include <LearnOpenGL/Types.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

// Reads a text file and outputs a string with everything in the text file
String get_file_contents(const char* filename) {
  std::ifstream in(filename, std::ios::binary);
  if (in) {
    String contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return (contents);
  }
  throw(errno);
}

// Constructor that builds the Shader Program from 2 different shaders
OpenGL::Shader::Shader(const char* vertexFile, const char* fragmentFile) {
  // Read vertexFile and fragmentFile and store the strings
  String vertexCode = get_file_contents(vertexFile);
  String fragmentCode = get_file_contents(fragmentFile);

  // Convert the shader source strings into character arrays
  const char* vertexSource = vertexCode.c_str();
  const char* fragmentSource = fragmentCode.c_str();

  // Create Vertex Shader Object and get its reference
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // Attach Vertex Shader source to the Vertex Shader Object
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  // Compile the Vertex Shader into machine code
  glCompileShader(vertexShader);

  // Create Fragment Shader Object and get its reference
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  // Attach Fragment Shader source to the Fragment Shader Object
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  // Compile the Vertex Shader into machine code
  glCompileShader(fragmentShader);

  // Create Shader Program Object and get its reference
  ID = glCreateProgram();
  // Attach the Vertex and Fragment Shaders to the Shader Program
  glAttachShader(ID, vertexShader);
  glAttachShader(ID, fragmentShader);
  // Wrap-up/Link all the shaders together into the Shader Program
  glLinkProgram(ID);

  // Delete the now useless Vertex and Fragment Shader objects
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

// Activates the Shader Program
void OpenGL::Shader::Activate() { glUseProgram(ID); }

// Deletes the Shader Program
void OpenGL::Shader::Delete() { glDeleteProgram(ID); }

OpenGL::Shader::~Shader() { this->Delete(); }
