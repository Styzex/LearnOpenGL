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

#include <glad/glad.h>

#include <LearnOpenGL/GLBuffers.hpp>

// VBO Class
VBO::VBO(GLfloat* vertices_, GLsizeiptr size_) {
  glGenBuffers(1, &m_Id);
  glBindBuffer(GL_ARRAY_BUFFER, m_Id);
  glBufferData(GL_ARRAY_BUFFER, size_, vertices_, GL_STATIC_DRAW);
}

void VBO::Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_Id); }
void VBO::UnBind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
void VBO::Delete() { glDeleteBuffers(1, &m_Id); }
VBO::~VBO() { this->Delete(); }

// VAO Class
VAO::VAO() { glGenVertexArrays(1, &m_Id); }

void VAO::LinkVBO(VBO& VBO_, GLuint layout_) {
  VBO_.Bind();
  glVertexAttribPointer(layout_, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
  glEnableVertexAttribArray(layout_);
  VBO_.UnBind();
}
void VAO::Bind() { glBindVertexArray(m_Id); }
void VAO::UnBind() { glBindVertexArray(0); }
void VAO::Delete() { glDeleteVertexArrays(1, &m_Id); }
VAO::~VAO() { this->Delete(); }

// EBO Class
EBO::EBO(GLuint* indices_, GLsizeiptr size_) {
  glGenBuffers(1, &m_Id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_, indices_, GL_STATIC_DRAW);
}

void EBO::Bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id); }
void EBO::UnBind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
void EBO::Delete() { glDeleteBuffers(1, &m_Id); }
EBO::~EBO() { this->Delete(); }
