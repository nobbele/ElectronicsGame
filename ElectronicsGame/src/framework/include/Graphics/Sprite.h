#ifndef SPRITE_H
#define SPRITE_H

#include <Graphics/BufferObject.h>
#include <Graphics/VertexArray.h>
#include <Graphics/ShaderProgram.h>
#include <Graphics/Texture.h>
#include <eg_containers.h>

#define SPRITE_OPTIMIZE 0

class Sprite {
	static BufferObject *VBO, *EBO;
	static VertexArray *VAO;

	static float staticSpriteVertices[];
	static unsigned int staticSpriteIndices[];
	static void InitializeStaticSpriteData();
	static void DestroyStaticSpriteData();

	Vector2<float> offset;

	const ShaderProgram &shaderProgram;
	const Texture &texture;

	GLint positionUniform;
	GLint sizeUniform;
public:
	Vector2<float> position;
	Vector2<float> size;
#if SPRITE_OPTIMIZE == 1
	mutable Vector2<float> old_position;
	mutable Vector2<float> old_size;
#endif

	Sprite(const ShaderProgram &shaderProgram, const Texture &texture, const Vector2<float> position, const Vector2<float> size);

	void CalibrateOffset();

	void Draw() const;
};

#endif