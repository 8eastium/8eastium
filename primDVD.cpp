#include <iostream>
#include <ostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Vertex{
	float x;
	float y;
	float z;
};

int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(900, 600, " Voxel ", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	Vertex vertices[6];

	float x =  0.2f;
	float y = -0.3f;
	char direction = '4';

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(window);
		glfwPollEvents();
		float size = 0.15f;
		vertices[0] = {-size + x, -size + y, 0.0f};
		vertices[1] = { size + x,  size + y, 0.0f};
		vertices[2] = { size + x, -size + y, 0.0f};
		vertices[3] = {-size + x, -size + y, 0.0f};
		vertices[4] = {-size + x,  size + y, 0.0f};
		vertices[5] = { size + x,  size + y, 0.0f};

		uint32_t verts;
		glGenBuffers(1, &verts);
		glBindBuffer(GL_ARRAY_BUFFER, verts);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)*sizeof(vertices)/sizeof(vertices[0]),&vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3,(void*)0);

		glEnableVertexAttribArray(0);
		glViewport(0, 0, 900, 600);
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

		float speed = 0.01;
		switch(direction) {
			case '4'://45°
				x += speed;
				y += speed * 0.3f;
				if (x > 1 - 0.15) {
					direction = '3';
				} else if (y > 1 + 0.15) {
					direction = '1';
				}
				break;
			case '1'://135°
				x += speed;
				y -= speed * 0.3f;
				if (x > 1 - 0.15) {
					direction = '2';
				} else if (y < -1 + 0.15) {
					direction = '4';
				}
				break;
			case '2'://225°
				x -= speed;
				y -= speed * 0.3f;
				if (y < -1 + 0.15) {
					direction = '3';
				} else if (x < -1 + 0.15) {
					direction = '1';
				}
				break;
			case '3'://315°
				x -= speed;
				y += speed * 0.3f;
				if (y > 1 -0.15) {
					direction = '2';
				}if (x < -1 + 0.15) {
					direction = '4';
				}
				break;
			
		}




		//std::cout << x << " | " << y << "\t\t" << direction << "\t" <<std::endl; 
		int state = glfwGetKey(window, GLFW_KEY_SPACE);
		if (state == GLFW_PRESS)
		{
		    return 0;
		}

	}
	glfwTerminate();
}