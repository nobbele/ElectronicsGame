#include <Graphics/Sprite.h>

#include <Graphics/BufferObject.h>
#include <Graphics/VertexArray.h>
#include <Graphics/ShaderProgram.h>
#include <Graphics/Texture.h>
#include <Graphics/EGP.h>
#include <eg_containers.h>

BufferObject *Sprite::VBO, *Sprite::EBO;
VertexArray *Sprite::VAO;

float Sprite::staticSpriteVertices[] = {
		   // positions   // colors           // texture coords
	0,     0.0f,  0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f, // top right
	1,     0.0f, -1.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, // bottom right
	2,    -1.0f, -1.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // bottom left
	3,    -1.0f,  0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f  // top left
};
unsigned int Sprite::staticSpriteIndices[] = {  
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

void Sprite::InitializeStaticSpriteData() {
	Sprite::VAO = new VertexArray(Sprite::staticSpriteVertices);
	Sprite::VBO = new BufferObject(GL_ARRAY_BUFFER);
	Sprite::EBO = new BufferObject(GL_ELEMENT_ARRAY_BUFFER);

    VAO->Bind();

	VBO->Bind();
    VBO->Data(sizeof(Sprite::staticSpriteVertices), Sprite::staticSpriteVertices, GL_STATIC_DRAW);

	EBO->Bind();
    EBO->Data(sizeof(Sprite::staticSpriteIndices), Sprite::staticSpriteIndices, GL_STATIC_DRAW);

	// index attribute
	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // position attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(1 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // color attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // texture coord attribute 
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(3);
}
void Sprite::DestroyStaticSpriteData() {
	delete Sprite::VAO;
	delete Sprite::VBO;
	delete Sprite::EBO;
}

Sprite::Sprite(const ShaderProgram &shaderProgram, const Texture &texture, const Vector2<float> position, const Vector2<float> size)
	: shaderProgram(shaderProgram), texture(texture), position(position), size(size)
{
	if(!VBO || !EBO || !VAO) 
		Sprite::InitializeStaticSpriteData();
	this->vertexPositionsUniform = shaderProgram.GetUniformLocation("vertexPositions");
}

void Sprite::Draw() const {
	this->texture.Bind();
	this->shaderProgram.Use();

    Vector2<float> glSize = this->size;
    Vector2<float> fixedPosition = this->position;
    Vector2<float> glPosition = egpToGL(fixedPosition);

	float positions[] = {
		glPosition.x + glSize.x,    glPosition.y + glSize.y, // top right
		glPosition.x + glSize.x,    glPosition.y,            // bottom right
		glPosition.x,               glPosition.y,            // bottom left
		glPosition.x,               glPosition.y + glSize.y  // top left
	};

	glUniform2fv(this->vertexPositionsUniform, 4, positions);

	Sprite::VAO->Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}