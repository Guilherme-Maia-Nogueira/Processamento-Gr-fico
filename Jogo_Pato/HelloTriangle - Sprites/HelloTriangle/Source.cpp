
#include <iostream>
#include <string>
#include <assert.h>
#include <stb_image.h>

using namespace std;

//Classe para manipulação dos shaders
#include "Shader.h"

//Classe para manipulação das sprites
#include "Sprite.h"

// Protótipo da função de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Protótipos das funções
GLuint loadTexture(string texturePath);

// Protótipos das funções
bool colisao(float perX, float perY, float widthPer, float heightPer, float obsX, float obsY, float widthObs, float heightObs);

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 800, HEIGHT = 600;

//Variaveis globais
Sprite pato;
int gmOver = 0; // Variavel para impedir movimentos após game over
int pontos = 0; // Variavel para contar quantidade de macas coletadas e encerrar execucao
int quantPont = 1;// Variavel para limitar a quantidade de pocoes a serem coletadas, valor de 1 - 3
int main()
{
	// Inicialização da GLFW
	glfwInit();

	// Inicialização da semente para geração de nros aleatórios
	srand((int)glfwGetTime());

	// Criação da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "##### Duck Game #####", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;

	}

	// Obtendo as informações de versão
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;
	
	//Habilitar teste de profundidade
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS); //a cada ciclo

	//Habilitar o modo de transparância (blend - mistura de cores)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Compilando e buildando o programa de shader
	//Shader shader("../shaders/helloTriangle.vs", "../shaders/helloTriangle.fs");
	Shader shader("../shaders/tex.vs", "../shaders/tex.fs");

	//Background de natureza
	GLuint texID_backGround = loadTexture("../../Textures/pato/PixelArt/BackGround/nature_1/orig.png");
	//espada_1
	GLuint texID_espada_1 = loadTexture("../../Textures/craftpix/PNG/Transperent/espada.png");
	//Game Over
	GLuint texID_gameOver = loadTexture("../../Textures/gameOver/gameOver.png");
	//Vitoria
	GLuint texID_vitoria = loadTexture("../../Textures/gameOver/vitoria.png");
	//Pato Direita
	GLuint texID_patoR = loadTexture("../../Textures/pato/patoRight.png");
	//Pato Esquerda
	GLuint texID_patoL = loadTexture("../../Textures/pato/patoLeft.png");
	//Limao
	GLuint texID_limao = loadTexture("../../Textures/Limao/limao.png");
	//Placar (0,1,2,3)
	GLuint texID_placar_zero = loadTexture("../../Textures/Placar/0.png");
	GLuint texID_placar_um = loadTexture("../../Textures/Placar/1.png");
	GLuint texID_placar_dois = loadTexture("../../Textures/Placar/2.png");
	GLuint texID_placar_tres = loadTexture("../../Textures/Placar/3.png");

	//Criação das sprites
	
	Sprite background;
	background.setShader(&shader);
	background.inicializar(texID_backGround, glm::vec3(400.0, 300.0, 0.0), glm::vec3(1920.0/2.0, 1200.0/2.0, 1.0));

	Sprite espada_1;
	espada_1.setShader(&shader);
	espada_1.inicializar(texID_espada_1, glm::vec3(400.0, 900.0, 0.0), glm::vec3(32.0, 32.0, 1.0));

	Sprite espada_2;
	espada_2.setShader(&shader);
	espada_2.inicializar(texID_espada_1, glm::vec3(600.0, 1080.0, 0.0), glm::vec3(32.0, 32.0, 1.0));
	
	Sprite limao;
	limao.setShader(&shader);
	limao.inicializar(texID_limao, glm::vec3(200.0, 1200.0, 0.0), glm::vec3(55.0, 65.0, 1.0));

	pato.setShader(&shader);
	pato.inicializar(texID_patoR, glm::vec3(300.0, 120.0, 0.0), glm::vec3(128.0, 183.0, 1.0));

	Sprite gameOver;
	gameOver.setShader(&shader);
	gameOver.inicializar(texID_gameOver, glm::vec3(400.0, 300.0, 0.0), glm::vec3(350.0, 205.0, 1.0));

	Sprite vitoria;
	vitoria.setShader(&shader);
	vitoria.inicializar(texID_vitoria, glm::vec3(400.0, 300.0, 0.0), glm::vec3(350.0, 205.0, 1.0));

	Sprite placar;
	placar.setShader(&shader);
	placar.inicializar(texID_placar_zero, glm::vec3(790.0, 550.0, 0.0), glm::vec3(60.0, 82.0, 1.0));

	Sprite placarUm;
	placarUm.setShader(&shader);
	placarUm.inicializar(texID_placar_um, glm::vec3(790.0, 550.0, 0.0), glm::vec3(60.0, 82.0, 1.0));

	Sprite placarDois;
	placarDois.setShader(&shader);
	placarDois.inicializar(texID_placar_dois, glm::vec3(790.0, 550.0, 0.0), glm::vec3(60.0, 82.0, 1.0));

	Sprite placarTres;
	placarTres.setShader(&shader);
	placarTres.inicializar(texID_placar_tres, glm::vec3(790.0, 550.0, 0.0), glm::vec3(60.0, 82.0, 1.0));



	//Ativando o buffer de textura 0 da opengl
	glActiveTexture(GL_TEXTURE0);

	shader.Use();

	//Matriz de projeção paralela ortográfica
	glm::mat4 projection = glm::ortho(0.0,800.0,0.0,600.0,-1.0,1.0);
	//Enviando para o shader a matriz como uma var uniform
	shader.setMat4("projection", glm::value_ptr(projection));
	
	//Matriz de transformação do objeto (matriz de modelo)
	shader.setInt("texBuffer", 0);
	bool win = false;

	glfwPollEvents();

	//tratamento
	if (quantPont <= 0 || quantPont >= 4) {
		glfwTerminate();
		return 0;
	}
	// Loop da aplicação - "game loop"

	while (!glfwWindowShouldClose(window))
	{
		
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
		glfwPollEvents();

		// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height); //unidades de tela: pixel
		
		// Limpa o buffer de cor
		glClear(GL_COLOR_BUFFER_BIT);

		background.desenhar(); 
		espada_1.desenhar();
		espada_2.desenhar();
		limao.desenhar();
		placar.desenhar();
		pato.desenhar();

		// Validação adicionada para para o jogo quando uma espada_1 encostar no pato
		if((gmOver == 0) && (pontos < quantPont))
		{
			espada_1.cair(false);
			espada_2.cair(false);
			limao.cair(false);
		}

		//Chamada do método de colisao
		bool auxespada_1 = colisao(pato.GetXPos(), pato.GetYPos(), 128.0, 183.0, espada_1.GetXPos(), espada_1.GetYPos(), 32.0, 32.0);
		bool auxespada_2 = colisao(pato.GetXPos(), pato.GetYPos(), 128.0, 183.0, espada_2.GetXPos(), espada_2.GetYPos(), 32.0, 32.0);
		bool aux_limao = colisao(pato.GetXPos(), pato.GetYPos(), 128.0, 183.0, limao.GetXPos(), limao.GetYPos(), 32.0, 32.0);
		
		if (win) {
			vitoria.desenhar();
			glfwPollEvents();
		}
		if(aux_limao && !win){
			pontos++;
			switch(pontos){
			case 1: placar = placarUm; break;
			case 2: placar = placarDois;break;
			case 3: placar = placarTres;break;
			}
		
			if(pontos >= quantPont){
				vitoria.desenhar();
				glfwPollEvents();
				win = true;
			}else
				limao.cair(true);
		}
		if (auxespada_1 || auxespada_2) {
			gmOver = 1; // Após atualização para 1, não permite mexer a posição do pato
			gameOver.desenhar();	
			glfwPollEvents();
		}

		
		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	
	// Finaliza a execução da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Função de callback de teclado - só pode ter uma instância (deve ser estática se
// estiver dentro de uma classe) - É chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	// Game Over ou Vitoria
	if (key == GLFW_KEY_KP_ENTER || key == GLFW_KEY_ENTER || key == GLFW_KEY_SPACE || key == GLFW_KEY_ESCAPE)
	{
		glfwTerminate();
	}
	//Move para direita
	if ((key == GLFW_KEY_D || key == GLFW_KEY_RIGHT) && ((gmOver == 0) && (pontos < quantPont)))
	{
		GLuint texID_patoR = loadTexture("../../Textures/pato/patoRight.png");
		pato.switchSide(texID_patoR);
		pato.moveRight();
	}
	//Move para esquerda
	if ((key == GLFW_KEY_A || key == GLFW_KEY_LEFT) && ((gmOver == 0) && (pontos < quantPont)))
	{
		GLuint texID_patoL = loadTexture("../../Textures/pato/patoLeft.png");
		pato.switchSide(texID_patoL);
		pato.moveLeft();
	}
}

bool colisao(float perX, float perY, float widthPer, float heightPer, float obsX, float obsY, float widthObs, float heightObs)
{
	//Pontos Personagem
	float xmaxPer = perX + widthPer / 6;
	float ymaxPer = perY + heightPer / 6;
	float xminPer = perX - widthPer / 6;
	float yminPer = perY - heightPer / 6;

	//pontos Obstaculo
	float xmaxObs = obsX + widthObs / 6;
	float ymaxObs = obsY + heightObs / 6;
	float xminObs = obsX - widthObs / 6;
	float yminObs = obsY - heightObs / 6;

	//testa colisões
	bool collisionX = xmaxPer >= xminObs && 
		xmaxObs >= xminPer;
	bool collisionY = ymaxPer >= yminObs && 
		ymaxObs >= yminPer;

	return collisionX && collisionY;
}

GLuint loadTexture(string texturePath)
{
	GLuint texID;

	// Gera o identificador da textura na memória 
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//Configuração do parâmetro WRAPPING nas coords s e t
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Confirugação do parâmetro FILTERING na minificação e magnificação da textura
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

