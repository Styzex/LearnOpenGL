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
#include <GLFW/glfw3.h>
#include <Log.h>
#include <Types.h>

constexpr int window_width = 1280;
constexpr int window_height = 720;

static void framebuffer_size_callback(GLFWwindow* window_, int width_, int height_) {
  glViewport(0, 0, width_, height_);
}

static void processExitInput(GLFWwindow* window_) {
  if (glfwGetKey(window_, GLFW_KEY_ESCAPE)) {
    glfwSetWindowShouldClose(window_, true);
  }
}

static String getOpenGLVersion() {
  const unsigned char* version = glGetString(GL_VERSION);
  String ver = reinterpret_cast<const char*>(version);
  return "Using OpenGL version " + ver;
}

int main(void) {
  Log::SetAppID("LearnOpenGL");
  Log::SetLogLevel(Log::LogLevel::Debug);
  Log Logger("Main");

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  GLFWwindow* window = glfwCreateWindow(window_width, window_height, "Window", NULL, NULL);
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

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // Sets the framebufferSizeCallback so that our window doesn't change it's defined size

  Logger.Info(getOpenGLVersion());  // Log OpenGL version of the window

  // Render loop
  while (!glfwWindowShouldClose(window)) {
    processExitInput(window);
    glfwSwapBuffers(window);
    glfwPollEvents();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);  // Specifies the Color used by OpenGL to clear the buffer
    glClear(GL_COLOR_BUFFER_BIT);  // Clears the buffer with the specified color by glClearColor
  }

  glfwTerminate();
  Logger.Info("Terminated OpenGL context");
  return 0;
}
