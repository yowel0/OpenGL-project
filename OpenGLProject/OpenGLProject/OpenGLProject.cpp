// OpenGLProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdlib>
#include <list>
#include "Model.h"
#include "Interactions.h"
#include "glm/glm.hpp"

const unsigned int width  = 1000;
const unsigned int height = 800;


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::vector<Model> models = std::vector<Model>();

    //create a window of width 800, height 600, name LearnOpenGL
    GLFWwindow* window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
    //check if the window was succesfully created
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //Inctroduce the window to the current context
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //load glad
    gladLoadGL();

    //create a glad viewport
    glViewport(0, 0, width, height);


    Shader shaderProgram("default.vert", "default.frag");
    Shader colorShaderProgram("default.vert", "id.frag");
    
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    

    //lightShader.Activate();
    //glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    //glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    // Texture
    //Texture popcat("pop_cat.png", "diffuse", GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    //popcat.TexUnit(shaderProgram, "tex0", 0);

    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 0.0f));
    //camera.Matrix(shaderProgram, "camMatrix");

    //Creating models
    int ModelID = 0;

    int cubesAmount = 700;
    int maxRandom = 50;
    for (int i = 0; i < cubesAmount; i++) {
        Model cube("models/cube/scene.gltf", ModelID++);
        cube.position = glm::vec3(rand() % (maxRandom * 2 + 1) - maxRandom, rand() % (maxRandom * 2 + 1) - maxRandom, rand() % (maxRandom * 2 + 1) - maxRandom);
        models.push_back(cube);
        //cubes.push_back(cube);
    }
    Model sword("models/sword/scene.gltf", ModelID++);
    models.push_back(sword);
    //Model bunny("models/bunny/scene.gltf", ModelID++);
    //models.push_back(bunny);
    Model scroll("models/scroll/scene.gltf", ModelID++);
    scroll.position += glm::vec3(10,0,0);
    models.push_back(scroll);
    Model map("models/map/scene.gltf",ModelID++);
    models.push_back(map);
    //Model grindstone("model/grindstone.gltf");

    Interactions* interactions = new Interactions();
    interactions->~Interactions();

    //render loop
    while (!glfwWindowShouldClose(window))
    {
        //specify background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        //clear the buffer with using the background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //---Render Colors for input
        camera.Inputs(window);
        camera.updateMatrix(45.0f,0.1f, 1000.0f);

        for (int i = models.size() - 1; i >= 0; i--) {
            Model* model = &models[i];
            model->Draw(colorShaderProgram, camera);
        }

        //click
        if (interactions != NULL)
            interactions->Inputs(&models, window);
        

        //---Render Textures
        //specify background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        //clear the buffer with using the background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (int i = models.size() - 1; i >= 0; i--) {
            Model* model = &models[i];
            model->Draw(shaderProgram, camera);
        }

        /*bunny.Draw(shaderProgram, camera);
        scroll.Draw(shaderProgram, camera);
        map.Draw(shaderProgram, camera);*/
        //grindstone.Draw(shaderProgram, camera);

        glfwSwapBuffers(window);

        //process all GLFW events
        glfwPollEvents();
    }
    // Delete all created opbjects
    shaderProgram.Delete();
    //destroy window and terminate glfw on exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
