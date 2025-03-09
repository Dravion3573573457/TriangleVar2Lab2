#define GLEW_DLL  
#define GLFW_DLL  

#include <iostream>  
#include "GL/glew.h"  
#include "GLFW/glfw3.h"  
#include "ShaderLoader.h"

//Вершины треугольника
float pointer[] = {
    0.0f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f
};

//Индексы вершин треугольника
GLuint index[] = { 0, 1, 2 };

int main() {
    //Инициализация GLFW
    if (!glfwInit()) {
        std::cerr << "Ошибка не запустить GLFW" << std::endl;
        return 1;
    }

    //Параметры окна
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Создание окна
    GLFWwindow* window = glfwCreateWindow(512, 512, "Mainwindow", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    //Инициализация GLEW  
    GLenum ret = glewInit();
    if (GLEW_OK != ret) {
        std::cerr << "Ошибка не запустить GLEW" << glewGetErrorString(ret) << std::endl;
        return 1;
    }

    //Создание массива вершин (VAO), буфер вершин (VBO) и буфер индексов (EBO)
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointer), pointer, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Загрузка шейдеров из доп файлов
    GLuint shader_program = ShaderLoader::LoadShader("vertex_shader.glsl", "fragment_shader.glsl");

    //Основной цикл
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.4f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        //Активация шейдерной программы, чтобы opengl знал какие шейдеры использовать
        glUseProgram(shader_program);
        ShaderLoader::SetUniform1f(shader_program, "time", timeValue);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}