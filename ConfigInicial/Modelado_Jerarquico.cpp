
//Practica5. Modelado Jerarquico         Suarez Velasco Gabriela
//Fecha de entrega: 09 de marzo de 2025         317313521

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);


const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;


//For model DEFINIR VARIABLES 
float	hombro = 0.0f,
codo = 0.0f,
muñeca = 0.0f,
dedo1 = 0.0f,
dedo1a = 0.0f,
dedo1c = 0.0f,
dedo2 = 0.0f;
//DESDE AQUI
float dedo13 = 0.0f,


dedo2b = 0.0f,
dedo2c = 0.0f,

dedo3 = 0.0f,
dedo3a = 0.0f,
dedo3b = 0.0f,

dedo4 = 0.0f,
dedo4a = 0.0f,
dedo4b = 0.0f,

pulgar = 0.0f,
pulgar2 = 0.0f;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica5_Modelado jerarquico_Gabriela_Suarez", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	// use with Orthographic Projection




	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f,  0.5f, 0.5f,
		0.5f,  0.5f, 0.5f,
		-0.5f,  0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		-0.5f, -0.5f,-0.5f,
		 0.5f, -0.5f,-0.5f,
		 0.5f,  0.5f,-0.5f,
		 0.5f,  0.5f,-0.5f,
		-0.5f,  0.5f,-0.5f,
		-0.5f, -0.5f,-0.5f,

		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp



		//View set up 
		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));


		glBindVertexArray(VAO);

		//Model1
		model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f)); //hombro
		modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f)); //genera movimiento mueven el pibote y se debe de poner a la mitad del tamaño del objeto
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		color = glm::vec3(1.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//A

		//Model antebrazo 
		model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		color = glm::vec3(1.0f, 0.0f, 1.0);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//B

		//Model Palma
		model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(muñeca), glm::vec3(1.0f, 0.0f, 0.0f));
		modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
		color = glm::vec3(1.0, 3.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//C

		// Model Dedo1 
		model = glm::translate(modelTemp, glm::vec3(0.25f, 0.35f, 0.375f));
		model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); //D

		// Model Dedo1 A 
		model = glm::translate(modelTemp, glm::vec3(0.25f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo1a), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f)); // ACTUALIZAMOS modelTemp para que dedo13 dependa de dedo12
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); //E
		
	   //// Model Dedo1 C 
		model = glm::translate(modelTemp, glm::vec3(0.25f, 0.0f, 0.0f)); // parte de la segunda falange
		model = glm::rotate(model, glm::radians(dedo1c), glm::vec3(0.0f, 0.0f, 1.0f)); // Aplica la rotación
		model = glm::translate(model, glm::vec3(0.2f, 0.f, 0.0f)); // Ajusta la posición después de rotar
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f)); // Ajusta el tamaño de la tercera falange
		color = glm::vec3(0.0, 1.0f, 1.0f); // Color cian para diferenciar
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // Renderizar la tercera falange



		//Model dedo2 A
		model = glm::translate(modelTemp, glm::vec3(-0.35f, 0.35f, -0.375f));
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D


		//Model Dedo2 parte de enmedio
		model = glm::translate(modelTemp, glm::vec3(-0.40f, 0.40f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2b), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		// Model dedo2 C punta
		model = glm::translate(modelTemp, glm::vec3(0.45f, 0.0f, 0.0f)); // Traslada desde la punta de la segunda falange
		model = glm::rotate(model, glm::radians(dedo2c), glm::vec3(0.0f, 0.0f, 1.0f)); // Aplica la rotación
		model = glm::translate(model, glm::vec3(0.27f, 0.0f, 0.0f)); // Ajusta la posición después de rotar
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f)); // Ajusta el tamaño de la tercera falange
		color = glm::vec3(0.0, 1.0f, 1.0f); // Color cian para diferenciar
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // Renderizar la tercera falange

		//Model Dedo3 
		model = glm::translate(modelTemp, glm::vec3(-0.35f, 0.35f, -0.375f));
		model = glm::rotate(model, glm::radians(dedo3), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.25f));
		color = glm::vec3(1.0, 1.0f, 0.45f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D


		//Model Dedo3 parte de enmedio
		model = glm::translate(modelTemp, glm::vec3(-0.40f, 0.40f, 0.375f));
		model = glm::rotate(model, glm::radians(dedo3a), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0, 0.45f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		// Model Dedo3 punta
		model = glm::translate(modelTemp, glm::vec3(-0.45f, 0.45f, 0.375f)); // Traslada desde la punta de la segunda falange
		model = glm::rotate(model, glm::radians(dedo3b), glm::vec3(0.0f, 0.0f, 1.0f)); // Aplica la rotación
		model = glm::translate(model, glm::vec3(-0.2f, 0.0f, 0.0f)); // Ajusta la posición después de rotar
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.025f)); // Ajusta el tamaño de la tercera falange
		color = glm::vec3(0.0, 1.0f, 1.0f); // Color cian para diferenciar
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // Renderizar la tercera falange*/


		//Model dedo4 
		model = glm::translate(modelTemp, glm::vec3(0.30f, 0.35f, 0.375f));
		model = glm::rotate(model, glm::radians(dedo4), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D


		//Model Dedo4 parte de enmedio
		model = glm::translate(modelTemp, glm::vec3(0.35f, 0.35f, 0.375f));
		model = glm::rotate(model, glm::radians(dedo4a), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(1.0, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		// Model dedo4 punta
		model = glm::translate(modelTemp, glm::vec3(0.40f, 0.40f, 0.375f)); // Traslada desde la punta de la segunda falange
		model = glm::rotate(model, glm::radians(dedo4b), glm::vec3(0.0f, 0.0f, 1.0f)); // Aplica la rotación
		model = glm::translate(model, glm::vec3(0.18f, 0.f, 0.0f)); // Ajusta la posición después de rotar
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f)); // Ajusta el tamaño de la tercera falange
		color = glm::vec3(0.0, 1.0f, 1.0f); // Color cian para diferenciar
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // Renderizar la tercera falange

		// Model pulgar1
		model = glm::translate(modelTemp, glm::vec3(-0.32f, -0.35f, 0.1875f)); // Ajusta su posición más hacia la palma
		model = glm::rotate(model, glm::radians(pulgar), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotación en eje Y en lugar de Z
		modelTemp = model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.0f)); // Ajuste del pivote
		model = glm::scale(model, glm::vec3(0.3f, 0.1f, 0.08f));
		color = glm::vec3(1.0, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Model pulgar2 punta
		model = glm::translate(modelTemp, glm::vec3(0.08f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pulgar2), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotación en eje X para mejor realismo
		modelTemp = model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f)); // Ajuste del pivote
		model = glm::scale(model, glm::vec3(0.225f, 0.10f, 0.08f));
		color = glm::vec3(1.0, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		

		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot += 0.18f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot -= 0.18f;
	//Al hombro le di un limite de movimiento de 120 a -120
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && hombro < 120.0f)//hombro
		hombro += 0.18f; 
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && hombro > -120.0f)//hombro
		hombro -= 0.18f;
	//para el codo le di limites de 0 a 90
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && codo < 0.0f)//nueva codo
		codo += 0.18f;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && codo > 90.0f)//nueva codo
		codo -= 0.18f;
	//Para la miñeca de di limites de 15 a -15
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && muñeca < 15.0f)//nueva muñeca
		muñeca += 0.18f;
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && muñeca > - 15.0f)//nueva muñeca
		muñeca -= 0.18f;

	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)//nueva dedo1
		dedo1 += 0.18f;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)//nueva dedo1
		dedo1 -= 0.18f;
	
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)//nueva dedo2
		dedo2 += 0.18f;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)//nueva dedo2
		dedo2 -= 0.18f;

	
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)//nueva dedo3
		dedo3 += 0.005f;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)//nueva dedo3
		dedo3 -= 0.005f;

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)//nueva dedo3
		dedo3a += 0.008f;
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)//nueva dedo3
		dedo3a -= 0.008f;

	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)//nueva dedo3
		dedo3b += 0.008f;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)//nueva dedo3
		dedo3b -= 0.008f;

	// Dedo 4
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)//nueva dedo4
		dedo4 += 0.0005f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)//nueva dedo4
		dedo4 -= 0.0005f;

	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)//nueva dedo4
		dedo4a += 0.0009f;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)//nueva dedo4
		dedo4a -= 0.0009f;

	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)//nueva dedo4
		dedo4b += 0.0008f;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)//nueva dedo4
		dedo4b -= 0.0008f;

	//pulgares
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) //nueva pulgar
		pulgar += 0.5f;  
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) //nueva pulgar
		pulgar -= 0.5f;

	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) //nueva pulgar
		pulgar2 += 0.8f;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) //nueva pulgar
		pulgar2 -= 0.8f;
}