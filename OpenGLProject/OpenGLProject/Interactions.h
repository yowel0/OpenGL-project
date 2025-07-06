#ifndef INTERACTIONS_CLASS_H
#define INTERACTIONS_CLASS_H

//#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Model.h"

class Interactions
{
public:
	Interactions();
	~Interactions();
	void Inputs(std::vector<Model>* models, GLFWwindow* window);
	void Click(std::vector<Model>* models, GLFWwindow* window);
private:
	bool canRightClick = true;
};

#endif
