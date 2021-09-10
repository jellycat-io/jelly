//
// Created by Maxime Blanc on 10/09/2021.
//

#pragma once

#include "Vertex.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

namespace Jelly {
	enum class GlyphSortType { NONE, FRONT_TO_BACK, BACK_TO_FRONT, TEXTURE };

	struct Glyph {
		GLuint texture;
		float depth;

		Jelly::Vertex topLeft;
		Jelly::Vertex bottomLeft;
		Jelly::Vertex topRight;
		Jelly::Vertex bottomRight;
	};

	class RenderBatch {
	public:
		GLint offset;
		GLint nVertices;
		GLint texture;
	public:
		RenderBatch(GLuint pOffset, GLuint pNVertices, GLuint pTexture) : offset(pOffset), nVertices(pNVertices), texture(pTexture) {};
	};

	class SpriteBatch {
	private:
		GLuint _vbo;
		GLuint _vao;

		GlyphSortType _sortType;
		std::vector<Glyph *> _glyphs;
		std::vector<RenderBatch> _renderBatches;

	public:
		SpriteBatch();
		~SpriteBatch();

		void init();

		void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void end();

		void draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color);

		void renderBatch();

	private:
		void _createRenderBatches();
		void _createVertexArray();
		void _sortGlyphs();

		static bool _compareFrontToBack(Glyph* a, Glyph* b);
		static bool _compareBackToFront(Glyph* a, Glyph* b);
		static bool _compareTexture(Glyph* a, Glyph* b);
	};
}
