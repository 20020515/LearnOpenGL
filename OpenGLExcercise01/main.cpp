#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include"Shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
//declare
void processInput(GLFWwindow*);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
//
//float vertices[] = {
//    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
//         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
//         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
//        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
//        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
//};
float vertices[] = {
    //     ---- 位置 ---- - 纹理坐标 -
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
unsigned int indices[] = {
    0,1,2,
    2,3,0
};
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
float lastX;
float lastY;
bool firstMouse=true;
float lastW=0;
float lastS=0;
float lastA=0;
float lastD=0;
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(15.0f), glm::radians(180.0f), glm::vec3(0, 10.0f, 0));
int main(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
    if (window == nullptr) {
        std::cout << "open window failed" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    //Init GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("GLEW_Inite Error!/n");
        return -1;
    }
    //Inite ViewPort;
    glViewport(0, 0, 800, 600);
    //   glEnable(GL_CULL_FACE);//面剔除
    //   glCullFace(GL_BACK);//剔除背面
    Shader* shader =new Shader("vertexSource.txt", "fragmentSource.txt");
       //绘制VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    /*
    * unsigned int VAO[num]
    * glGenVertexArrays(num, VAO);
    */
    glBindVertexArray(VAO);
    //绘制VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    //Shader

    //Start draw
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5* sizeof(float), (void*)(0));
    glEnableVertexAttribArray(0);
    //clolor
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    //glEnableVertexAttribArray(1);
    //texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    //Texture

    unsigned int TexBuffer;
    glGenTextures(1, &TexBuffer);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TexBuffer);
    
    int width, height, nrChannel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannel, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        printf("Texture Load Err!\n");
        return -1;
    }
    unsigned int TexBufferB;
    glGenTextures(1, &TexBufferB);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, TexBufferB);
    unsigned char*data2=stbi_load("awesomeface.png",& width, &height, &nrChannel, 0);
    if (data2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        printf("Texture Load Err!\n");
    }
    stbi_image_free(data);
    //calculate tranformation
    
        //position
    //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0));
        
    //rotation
    //trans = glm::rotate(trans, glm::radians(45.0f),glm::vec3(0,0,1.0));
        //scale
    //trans = glm::scale(trans, glm::vec3(1.2f, 1.2f, 1.2f));
    
    //Instantiate Camera class
    //Camera camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, -1.0f, 0), glm::vec3(0, 1.0f, 0));
    
    //transform
    //model
    glm::mat4 modelMat;
    modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0, 0));
    //view
    glm::mat4 viewMat;
    //viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f));
    //projection
    glm::mat4 projMat;
    projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        //glm::mat4 trans;
        
        //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0, 0, 1.0f));
        //modelMat= glm::rotate(modelMat, (float)glfwGetTime() * glm::radians(0.5f), glm::vec3(0.5f, 1.0f, 0.0f));
        //Input
        processInput(window);
        //rendering
        glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //Texture
        //Bind TexTure

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TexBuffer);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, TexBufferB);
        camera.ProcessPositionMovement(lastW,lastA,lastD,lastS);
        viewMat = camera.GetViewMatrix();
        lastW = 0;
        lastS = 0;
        lastD = 0;
        lastA = 0;
        for (int i = 0;i < 10;++i) {
            glm::mat4 modelMat2; 
            modelMat2 = glm::translate(modelMat2, cubePositions[i]);
            modelMat2 = glm::rotate(modelMat2, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            //draw:
            shader->use();//use shader
            glUniform1i(glGetUniformLocation(shader->ID, "ourTexture"),0);
            glUniform1i(glGetUniformLocation(shader->ID, "ourFace"),3);
            glDrawArrays(GL_TRIANGLES, 0, 36);//use shader to draw VAO
            //glUniformMatrix4fv(glGetUniformLocation(shader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
            glUniformMatrix4fv(glGetUniformLocation(shader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat2));
            glUniformMatrix4fv(glGetUniformLocation(shader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        }
        
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        
        lastW=1;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        lastA=1;
    }
    else if (glfwGetKey(window, GLFW_KEY_A )== GLFW_PRESS){
        lastS=1;
    }
    else if (glfwGetKey(window, GLFW_KEY_D )== GLFW_PRESS){
        lastD=1;
    }
}
void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    if (firstMouse == true) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    float deltaX, deltaY;
    deltaX = xPos - lastX;
    deltaY = yPos - lastY;
    lastX = xPos;
    lastY = yPos;
    camera.ProcessMouseMovement(deltaX, deltaY);
}