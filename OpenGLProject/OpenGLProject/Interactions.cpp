#include "Interactions.h"

Interactions::Interactions() {
    std::cout << "Constructor called" << std::endl;
}

Interactions::~Interactions() {
    
    std::cout << "Destructor called" << std::endl;
}

void Interactions::Inputs(std::vector<Model>* models, GLFWwindow* window) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if (canRightClick) {
            std::cout << "clicked" << std::endl;
            canRightClick = false;

            Click(models, window);
        }
    }
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
        if (!canRightClick) {
            canRightClick = true;
        }
    }
}

void Interactions::Click(std::vector<Model>* models, GLFWwindow* window) {
    std::cout << "clicked" << std::endl;

    //send all the pending commands to the GPU very slow
    glFlush();
    //wait for the GPU to be finished with this frame very very slow
    glFinish();
    //configure memory alignment of glReadPixels
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //receive pixel data from the mouse position
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    unsigned char data[4];
    //glfwSetWindowSize(window, );
    int width, height;
    glfwGetWindowSize(window,&width, &height);
    std::cout << width << " " << height << std::endl;
    glReadPixels(xPos, height - yPos, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //print
    std::cout << "data:" << std::endl;
    std::cout << (int)data[0] << std::endl;
    std::cout << (int)data[1] << std::endl;
    std::cout << (int)data[2] << std::endl;
    std::cout << (int)data[3] << std::endl;
    int pickedID =
        data[0] +
        data[1] * 256 +
        data[2] * 256 * 256;
    std::cout << "found ID: " << pickedID << std::endl;

    //replace the model list with
    std::vector<Model> newModelsList = std::vector<Model>();
    for (int i = models->size() - 1; i >= 0; i--) {
        Model model = models->at(i);
       /* if (pickedID != models->at(i).ID) {
            std::cout << "modelsadded" << std::endl;
            newModelsList.push_back(models->at(i));
        }*/
        std::cout << "modelssize: " << models->size() << std::endl;
        if (pickedID == models->at(i).ID) {
            models->erase(models->begin() + i);
        }
        std::cout << "modelssize after: " << models->size() << std::endl;
    }
}