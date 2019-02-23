#ifndef SPRITE_H
#define SPRITE_H

#include <Graphics/BufferObject.h>
#include <Graphics/VertexArray.h>
#include <Graphics/ShaderProgram.h>
#include <Graphics/Texture.h>
#include <eg_containers.h>

class Sprite {
	static BufferObject *VBO, *EBO;
	static VertexArray *VAO;

	static float staticSpriteVertices[];
	static unsigned int staticSpriteIndices[];
	static void InitializeStaticSpriteData();
	static void DestroyStaticSpriteData();

	const ShaderProgram &shaderProgram;
	const Texture &texture;

	GLint positionUniform;
	GLint sizeUniform;
public:
	Vector2<float> position;
	Vector2<float> size;

	Sprite(const ShaderProgram &shaderProgram, const Texture &texture, const Vector2<float> position, const Vector2<float> size);

	void Draw() const;
};

#endif