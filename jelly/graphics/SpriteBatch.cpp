//
// Created by Maxime Blanc on 10/09/2021.
//

#include "SpriteBatch.h"

Jelly::SpriteBatch::SpriteBatch() : _vbo(0), _vao(0) {}

Jelly::SpriteBatch::~SpriteBatch() {
	if (_vbo != 0) glDeleteBuffers(1, &_vbo);
	if (_vao != 0) glDeleteVertexArrays(1, &_vao);
}

void Jelly::SpriteBatch::init() {
	_createVertexArray();
}

void Jelly::SpriteBatch::begin(Jelly::GlyphSortType sortType /* GlyphSortType::TEXTURE */) {
	_sortType = sortType;

	_renderBatches.clear();

	for(auto & g : _glyphs) {
		delete(g);
	}
	_glyphs.clear();
}

void Jelly::SpriteBatch::end() {
	_sortGlyphs();
	_createRenderBatches();
}

void Jelly::SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Color &color) {
	auto* newGlyph = new Glyph;
	newGlyph->texture = texture;
	newGlyph->depth = depth;

	newGlyph->topLeft.color = color;
	newGlyph->topLeft.setPosition(destRect.x, destRect.y + destRect.w);
	newGlyph->topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

	newGlyph->bottomLeft.color = color;
	newGlyph->bottomLeft.setPosition(destRect.x, destRect.y);
	newGlyph->bottomLeft.setUV(uvRect.x, uvRect.y);

	newGlyph->topRight.color = color;
	newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	newGlyph->topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

	newGlyph->bottomRight.color = color;
	newGlyph->bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
	newGlyph->bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

	_glyphs.push_back(newGlyph);
}

void Jelly::SpriteBatch::renderBatch() {
	glBindVertexArray(_vao);

	for (auto & rb : _renderBatches) {
		glBindTexture(GL_TEXTURE_2D, rb.texture);
		glDrawArrays(GL_TRIANGLES, rb.offset, rb.nVertices);
	}

	glBindVertexArray(0);
}

void Jelly::SpriteBatch::_createRenderBatches() {
	std::vector<Vertex> vertices;
	vertices.resize(_glyphs.size() * 6);

	if (_glyphs.empty()) return;

	int offset = 0;
	int cv = 0; // Current vertex
	_renderBatches.emplace_back(offset, 6, _glyphs[0]->texture);
	vertices[cv++] = _glyphs[0]->topLeft;
	vertices[cv++] = _glyphs[0]->bottomLeft;
	vertices[cv++] = _glyphs[0]->bottomRight;
	vertices[cv++] = _glyphs[0]->bottomRight;
	vertices[cv++] = _glyphs[0]->topRight;
	vertices[cv++] = _glyphs[0]->topLeft;
	offset += 6;

	for (int cg = 1; cg < _glyphs.size(); cg++) {
		if (_glyphs[cg]-> texture != _glyphs[cg - 1]-> texture) {
			_renderBatches.emplace_back(offset, 6, _glyphs[cg]->texture);
		} else {
			_renderBatches.back().nVertices += 6;
		}

		vertices[cv++] = _glyphs[cg]->topLeft;
		vertices[cv++] = _glyphs[cg]->bottomLeft;
		vertices[cv++] = _glyphs[cg]->bottomRight;
		vertices[cv++] = _glyphs[cg]->bottomRight;
		vertices[cv++] = _glyphs[cg]->topRight;
		vertices[cv++] = _glyphs[cg]->topLeft;

		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	// Orphan the buffer
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	// Upload the data
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Jelly::SpriteBatch::_createVertexArray() {
	if (_vao == 0) glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	if (_vbo == 0) glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	// Tell OpenGL to use attribute arrays
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
	// Color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));
	// UV attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, uv));

	glBindVertexArray(0);
}

void Jelly::SpriteBatch::_sortGlyphs() {
	switch(_sortType) {
		case Jelly::GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), _compareBackToFront);
			break;
		case Jelly::GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), _compareFrontToBack);
			break;
		case Jelly::GlyphSortType::TEXTURE:
			std::stable_sort(_glyphs.begin(), _glyphs.end(), _compareTexture);
			break;
		case Jelly::GlyphSortType::NONE:
			break;
	}
}

bool Jelly::SpriteBatch::_compareFrontToBack(Jelly::Glyph *a, Jelly::Glyph *b) {
	return a->depth < b->depth;
}

bool Jelly::SpriteBatch::_compareBackToFront(Jelly::Glyph *a, Jelly::Glyph *b) {
	return a->depth > b->depth;
}

bool Jelly::SpriteBatch::_compareTexture(Jelly::Glyph *a, Jelly::Glyph *b) {
	return a->texture < b->texture;
}
