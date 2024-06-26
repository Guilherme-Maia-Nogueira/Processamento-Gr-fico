#include <iostream>
#include <string>
#include <assert.h>

 //GLM
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
//using namespace glm; //para n�o usar glm::

//Classe para manipula��o dos shaders
#include "Shader.h"

// Prot�tipo da fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Prot�tipos das fun��es
int quadrantes();
void drawScene(int VAO);

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 800, HEIGHT = 600;

// Fun��o MAIN
int main()
{
	// Inicializa��o da GLFW
	glfwInit();

	// Cria��o da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ola Triangulo! -- Guilherme Maia Nogueira", nullptr, nullptr);
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

	// Compilando e buildando o programa de shader
	Shader shader("../shaders/ortho.vs", "../shaders/ortho.fs");

	// Gerando um buffer simples, com a geometria de um tri�ngulo
	GLuint VAO = quadrantes();

	shader.Use();

	//Matriz de proje��o paralela ortogr�fica

	//Lista 2 - exerc�cio 1:
	//glm::mat4 projection = glm::ortho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);
	//Lista 2 - exerc�cio 2:
	//glm::mat4 projection = glm::ortho(0.0, 800.0, 600.0, 0.0, -1.0, 1.0);

	glm::mat4 projection = glm::ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	//Enviando para o shader a matriz como uma var uniform
	shader.setMat4("projection", glm::value_ptr(projection));

	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		
		// Limpa o buffer de cor
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		//Resolu��o do exercicio 4 da lista 2
		glViewport(width / 2, height / 2, width / 2, height / 2); //unidades de tela: pixel
		drawScene(VAO);

		////Resolu��o de parte do exercicio 5 lista 2
		////Primeira viewport (quadrante inferior esquerdo)
		//glViewport(0, 0, width / 2, height / 2); //unidades de tela: pixel
		//drawScene(VAO);

		////Segunda viewport (quadrante superior direito)
		//glViewport(width / 2, height / 2, width / 2, height / 2); //unidades de tela: pixel
		//drawScene(VAO);

		////Terceira viewport(quadrante superior esquerdo)
		//glViewport(0, height / 2, width / 2, height / 2); //unidades de tela: pixel
		//drawScene(VAO);

		////Quarta viewport(quadrante inferior direito)
		//glViewport(width / 2, 0, width / 2, height / 2); //unidades de tela: pixel
		//drawScene(VAO);

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
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

int quadrantes()
{
	// Coordenadas x, y e z do tri�ngulo 
	GLfloat vertices[] = {
		//x   y     z    r   g    b
		//Triangulo 0
		-0.5, 0.5, 0.0, 1.0, 0.0, 0.0,//v0
		 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,//v1
		 0.5, 0.5, 0.0, 0.0, 0.0, 1.0,//v2 
		//Triangulo 1
		 0.0, 0.0, 0.0, 1.0, 1.0, 0.0,//v3
		-0.5,-0.5, 0.0, 0.0, 1.0, 1.0,//v4
		 0.5,-0.5, 0.0, 1.0, 0.0, 1.0,//v5 
	};

	GLuint VBO, VAO;
	//Gera��o do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conex�o (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//                                              vertices.data()  
	//Gera��o do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de v�rtices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localiza��o no shader * (a localiza��o dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se est� normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 

	//Atributo 0 - posi��o
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo 1 - cor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Observe que isso � permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de v�rtice 
	// atualmente vinculado - para que depois possamos desvincular com seguran�a
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (� uma boa pr�tica desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}

void drawScene(int VAO)
{
	glBindVertexArray(VAO); //Conectando ao buffer de geometria

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDrawArrays(GL_LINE_LOOP, 0, 3);
	glDrawArrays(GL_LINE_LOOP, 3, 3);

	glDrawArrays(GL_POINTS, 0, 6);

	glBindVertexArray(0); //Desconectando o buffer de geometria
}

