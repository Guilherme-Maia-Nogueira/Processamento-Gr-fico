#include <iostream>
#include <string>
#include <assert.h>

//STB IMAGE
#include<stb_image.h>

using namespace std;
//using namespace glm; //para n�o usar glm::

//Classe para manipula��o dos shaders
#include "Shader.h"

//Classe para manipula��o das sprites
#include "Sprite.h"

// Prot�tipo da fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Prot�tipos das fun��es
GLuint loadTexture(string texturePath);

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 800, HEIGHT = 600;

// Fun��o MAIN
int main()
{
	// Inicializa��o da GLFW
	glfwInit();

	// Inicializa��o da semente para gera��o de nros aleat�rios
	srand((int)glfwGetTime());

	// Cria��o da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lista 3 - Exercicio 1! -- Guilherme Maia Nogueira", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da fun��o de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d fun��es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;

	}

	// Obtendo as informa��es de vers�o
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;
	
	//Habilitar teste de profundidade
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS); //a cada ciclo

	//Habilitar o modo de transpar�ncia (blend - mistura de cores)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Compilando e buildando o programa de shader
	Shader shader("../shaders/tex.vs", "../shaders/tex.fs");

	GLuint texID = loadTexture("../../Textures/pixelWall.png");
	
	//Retangulo 1
	Sprite Ret1;
	Ret1.setShader(&shader);
	Ret1.inicializar(texID, glm::vec3(400.0, 300.0, 0.0), glm::vec3(150, 200, 1.0),1);
	//Retangulo 2
	Sprite Ret2;
	Ret2.setShader(&shader);
	Ret2.inicializar(texID, glm::vec3(200.0, 500.0, 0.0), glm::vec3(100, 50, 1.0),2);
	//Retangulo 3
	Sprite Ret3;
	Ret3.setShader(&shader);
	Ret3.inicializar(texID, glm::vec3(600.0, 100.0, 0.0), glm::vec3(50, 100, 1.0),3);
	
	//Ativando o buffer de textura 0 da opengl
	glActiveTexture(GL_TEXTURE0);

	shader.Use();

	//Matriz de proje��o paralela ortogr�fica
	glm::mat4 projection = glm::ortho(0.0,800.0,0.0,600.0,-1.0,1.0);
	//Enviando para o shader a matriz como uma var uniform
	shader.setMat4("projection", glm::value_ptr(projection));
	
	//Matriz de transforma��o do objeto (matriz de modelo)
	shader.setInt("texBuffer", 0);

	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height); //unidades de tela: pixel
		
		// Limpa o buffer de cor
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		Ret1.desenhar();
		Ret2.desenhar();
		Ret3.desenhar();

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	
	// Finaliza a execu��o da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);	
}

GLuint loadTexture(string texturePath)
{
	GLuint texID;

	// Gera o identificador da textura na mem�ria 
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//Configura��o do par�metro WRAPPING nas coords s e t
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Confiruga��o do par�metro FILTERING na minifica��o e magnifica��o da textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

