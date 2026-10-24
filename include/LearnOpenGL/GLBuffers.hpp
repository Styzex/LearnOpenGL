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

class VBO {
 private:
  GLuint m_Id;
  void Delete();

 public:
  VBO(GLfloat* vertices_, GLsizeiptr size);
  ~VBO();
  void Bind();
  void UnBind();
};

class VAO {
 private:
  GLuint m_Id;
  void Delete();

 public:
  VAO();
  ~VAO();
  void LinkVBO(VBO& VBO_, GLuint layout);
  void Bind();
  void UnBind();
};

class EBO {
 private:
  GLuint m_Id;
  void Delete();

 public:
  EBO(GLuint* indices_, GLsizeiptr size_);
  ~EBO();
  void Bind();
  void UnBind();
};
