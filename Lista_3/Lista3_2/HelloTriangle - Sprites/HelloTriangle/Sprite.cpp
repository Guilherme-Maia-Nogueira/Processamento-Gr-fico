#include "Sprite.h"

Sprite::~Sprite()
{
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
}

void Sprite::inicializar(GLuint texID, glm::vec3 pos, glm::vec3 escala, float angulo)
{
	this->texID = texID;
	this->pos = pos;
	this->escala = escala;
	this->angulo = angulo;

	////isJumping = false;
	//onGround = true;

	//jumpVel.x = 0.0;
	//jumpVel.y = 0.5;
	//vel = 5.0;

	// Aqui setamos as coordenadas x, y e z
	GLfloat vertices[] = {
		//x     y    z    r    g    b    s    t
		//Triangulo 0
		-0.5 , 0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0,  //v0
		-0.5 ,-0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,  //v1
		 0.5 , 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0,  //v2
		 //Triangulo 1	
	    -0.5 ,-0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,  //v1
		 0.5 ,-0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,  //v3
		 0.5 , 0.5, 0.0, 1.0, 0.0, 0.0, 1.0, 1.0   //v2
	};

	GLuint VBO;
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

	//Atributo 0 - posição
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo 1 - cor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Atributo 2 - coordenadas de textura
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0);
}

void Sprite::desenhar()
{
	atualizar();

	glBindTexture(GL_TEXTURE_2D, texID);
	glBindVertexArray(VAO); //Conectando ao buffer de geometria
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindTexture(GL_TEXTURE_2D, 0); //unbind
	glBindVertexArray(0); //unbind
}
//Move para direita
void Sprite::moveRight()
{
	if (pos.x >= 800) {
		pos.x = 1;
	}
	else
		pos.x += 6.0;
}
//Move para esquerda
void Sprite::moveLeft()
{
	if (pos.x <= 0) {
		pos.x = 799;
	}
	else
		pos.x -= 6.0;
}
//Move para cima
void Sprite::moveTop()
{
	if (pos.y >= 600) {
		pos.y = 1;
	}
	else
		pos.y += 6.0;
}
//Move para baixo
void Sprite::moveDown()
{
	if (pos.y <= 0) {
		pos.y = 799;
	}
	else
		pos.y -= 6.0;
}

void Sprite::atualizar()
{
	glm::mat4 model = glm::mat4(1); //matriz identidade
	model = glm::translate(model, pos);
	model = glm::rotate(model,glm::radians(angulo), glm::vec3(0.0, 0.0, 1.0));
	model = glm::scale(model, escala);
	shader->setMat4("model", glm::value_ptr(model));
}
