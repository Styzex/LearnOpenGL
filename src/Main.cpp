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
#pragma region Includes
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <math.h>


#include <LearnOpenGL/GLBuffers.hpp>
#include <LearnOpenGL/Log.hpp>
#include <LearnOpenGL/Shader.hpp>
#include <LearnOpenGL/Types.hpp>
#include <LearnOpenGL/Utils.hpp>


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

static void framebuffer_size_callback(GLFWwindow *window_, int width_,
                                      int height_) {
  glViewport(0, 0, width_, height_);
}

static void processExitInput(GLFWwindow *window_) {
  if (glfwGetKey(window_, GLFW_KEY_ESCAPE)) {
    glfwSetWindowShouldClose(window_, true);
  }
}

static String getOpenGLVersion() {
  const unsigned char *version = glGetString(GL_VERSION);
  String ver = reinterpret_cast<const char *>(version);
  return "Using OpenGL version " + ver;
}

#pragma region Main
int main() {
  Engine::Log::SetAppID("LearnOpenGL");
  Engine::Log::SetLogLevel(Engine::Log::LogLevel::Debug);
  Engine::Log Logger{"Main"};

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,
                 GL_TRUE); // Requests the OpenGL Debug context

  GLFWwindow *window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Window", NULL, NULL);

  if (window == NULL) {
    Logger.Error("Failed to create OpenGL window context");
    glfwTerminate();
    return -1;
  } else {
    Logger.Info("Created new OpenGL context");
  }

  glfwMakeContextCurrent(window);

  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    Logger.Error("Failed to initialize GLAD");
    return -1;
  }

  glfwSetFramebufferSizeCallback(
      window, framebuffer_size_callback); // Sets the framebufferSizeCallback
                                          // so that our window doesn't change
                                          // it's defined size

  Logger.Info(getOpenGLVersion()); // Log OpenGL version of the window

  // Enables OpenGL debug messages
  GLint flags = 0;
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(OpenGL::DebugCallback, &Logger);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr,
                          GL_TRUE);
    Logger.Info("Enabled OpenGL debug messages");
  }

#pragma region Shaders

  // Load shaders
  GLfloat vertices[] = {
      -0.5f,     -0.5f * float(sqrt(3)) / 3,    0.0f,
      0.5f,      -0.5f * float(sqrt(3)) / 3,    0.0f,
      0.0f,      0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
      -0.5f / 2, 0.5f * float(sqrt(3)) / 6,     0.0f,
      0.5f / 2,  0.5f * float(sqrt(3)) / 6,     0.0f,
      0.0f,      -0.5f * float(sqrt(3)) / 3,    0.0f,
  };

  GLuint indices[] = {
      0, 3, 5, // Lower left triangle
      3, 2, 4, // Lower right triangle
      5, 4, 1, // Upper center tirangle
  };

  OpenGL::Shader defaultShader(
      "C:\\Dev\\LearnOpenGL\\shaders\\default.vert.glsl",
      "C:\\Dev\\LearnOpenGL\\shaders\\default.frag.glsl");

  VAO VAO1;
  VAO1.Bind();

  VBO VBO1(vertices, sizeof(vertices));
  EBO EBO1(indices, sizeof(indices));

  VAO1.LinkVBO(VBO1, 0);
  VAO1.UnBind();
  VBO1.UnBind();
  EBO1.UnBind();

#pragma region Render Loop
  // Render loop
  while (!glfwWindowShouldClose(window)) {
    processExitInput(window);
    glfwSwapBuffers(window);
    glfwPollEvents();

    // Specifies the Color used by OpenGL to clear the buffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // Clears the buffer with the specified color by glClearColor
    glClear(GL_COLOR_BUFFER_BIT);

    defaultShader.Activate();
    VAO1.Bind();

    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
  }

  glfwTerminate();
  Logger.Info("Terminated OpenGL context");
  return 0;
}
