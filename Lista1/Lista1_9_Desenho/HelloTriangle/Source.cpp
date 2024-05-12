#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

//Classe para manipulação dos shaders
#include "Shader.h"

// Protótipo da função de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Protótipos das funções
int casa();

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 800, HEIGHT = 600;

// Função MAIN
int main()
{
	// Inicialização da GLFW
	glfwInit();

	// Criação da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lista 1 - Exercicio 9: Guilherme Nogueira", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informações de versão
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Compilando e buildando o programa de shader
	Shader shader("../shaders/helloTriangle.vs", "../shaders/helloTriangle.fs");

	// Gerando um buffer simples, com a geometria de um triângulo
	GLuint VAO = casa();
	
	// Enviando a cor desejada (vec4) para o fragment shader
	// Utilizamos a variáveis do tipo uniform em GLSL para armazenar esse tipo de info
	// que não está nos buffers
	GLint colorLoc = glGetUniformLocation(shader.ID, "inputColor");
	
	shader.Use();
	
	// Loop da aplicação - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
		glfwPollEvents();

		// Limpa o buffer de cor
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //cor de fundo = Branco
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(1);
		glPointSize(1);

		glBindVertexArray(VAO); //Conectando ao buffer de geometria

		shader.setVec4("inputColor", 0.5f, 1.0f, 0.5f, 1.0f);//Casa - Cor verde
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		shader.setVec4("inputColor", 1.0f, 0.0f, 0.0f, 1.0f);//Telhado - Vermelho
		glDrawArrays(GL_TRIANGLES, 4, 3);
		shader.setVec4("inputColor", 0.5f, 0.25f, 0.0f, 1.0f);//Porta - Marrom
		glDrawArrays(GL_TRIANGLE_STRIP, 7, 4);
		shader.setVec4("inputColor", 0.0f, 0.0f, 1.0f, 1.0f);//Janela left - Azul
		glDrawArrays(GL_TRIANGLE_FAN , 11, 4);
		shader.setVec4("inputColor", 0.0f, 0.0f, 1.0f, 1.0f);//Janela right - Azul
		glDrawArrays(GL_TRIANGLE_FAN, 15, 4);
		shader.setVec4("inputColor", 0.0f, 0.0f, 0.0f, 1.0f);//Casa - Contorno preto
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		shader.setVec4("inputColor", 1.0f, 0.7f, 0.2f, 1.0f);//Chao - Laranja
		glDrawArrays(GL_LINES, 19, 20);

		glBindVertexArray(0); //Desconectando o buffer de geometria

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
	// Finaliza a execução da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Função de callback de teclado - É chamada sempre que uma tecla for pressionada, ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int casa()
{
	// Aqui setamos as coordenadas x, y e z do triângulo e as armazenamos de forma
	// sequencial, já visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do vértice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO único ou em VBOs separados
	GLfloat vertices[] = {
		 //x   y   z
		   0.5,0.0,0.0,//v0 - Casa
		  -0.5,0.0,0.0,//v1
		  -0.5,-0.99,0.0,//v2
		   0.5,-0.99,0.0,//v3
		   0.0,0.5,0.0,//v4 - Triangulo
		   0.5,0.0,0.0,//v5
		  -0.5,0.0,0.0,//v6
		   0.1,-0.5,0.0,//v7 - Porta
		   0.1,-0.99,0.0,//v8 
		  -0.1,-0.5,0.0,//v9
		  -0.1,-0.99,0.0,//v10
		  -0.2,-0.1,0.0,//v11 - Janela left
		  -0.2,-0.3,0.0,//v12 
		  -0.4,-0.3,0.0,//v13
		  -0.4,-0.1,0.0,//v14
		   0.2,-0.1,0.0,//v15 - Janela right
		   0.2,-0.3,0.0,//v16 
		   0.4,-0.3,0.0,//v17
		   0.4,-0.1,0.0,//v18
		  -0.5,-1.0,0.0,//v19 - Chao
		   0.5,-1.0,0.0,//v20 
	};

	GLuint VBO, VAO;
	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//                                              vertices.data()  
	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);

	return VAO;
}


