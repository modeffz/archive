#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <iostream>

// Функция для компиляции шейдера
GLuint CompileShader(GLenum type, const char* source) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
      char infoLog[512];
      glGetShaderInfoLog(shader, 512, nullptr, infoLog);
      std::cout << "Ошибка компиляции шейдера: " << infoLog << std::endl;
  }
  return shader;
}

// Вершинный шейдер
const char* vertexShaderSource = R"(
  #version 330 core
  layout(location = 0) in vec3 aPos;
  void main() {
      gl_Position = vec4(aPos, 1.0);
  }
)";

// Фрагментный шейдер
const char* fragmentShaderSource = R"(
  #version 330 core
  out vec4 FragColor;
  void main() {
      FragColor = vec4(0.0f, 0.8f, 0.2f, 1.0);
  }
)";

int main() {
  // Инициализация SDL2
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cout << "Ошибка инициализации SDL2!\n";
      return -1;
  }

  SDL_Window* window = SDL_CreateWindow("OpenGL + SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
  if (!window) {
      std::cout << "Ошибка создания окна!\n";
      return -1;
  }

  SDL_GLContext glContext = SDL_GL_CreateContext(window);
  if (!glContext) {
      std::cout << "Ошибка создания OpenGL контекста!\n";
      return -1;
  }

  glewExperimental = GL_TRUE;
  glewInit();

  // Компиляция шейдеров
  GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
  GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

  // Создание шейдерной программы
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Вершины треугольника
  float vertices[] = {
      -0.5f, -0.5f, 0.0f,  // Левый нижний угол
       0.5f, -0.5f, 0.0f,  // Правый нижний угол
       0.0f,  0.5f, 0.0f   // Верхний угол
  };

  // Буферы OpenGL
  GLuint VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Основной цикл
  bool running = true;
  SDL_Event e;
  while (running) {
      while (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT) {
              running = false;
          }
      }

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shaderProgram);
      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      
      SDL_GL_SwapWindow(window);
  }

  // Очистка памяти
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);
  SDL_GL_DeleteContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
