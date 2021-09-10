//
// Created by Maxime Blanc on 06/09/2021.
//

#include "ImageLoader.h"
#include "IOManager.h"
#include "Logger.h"
#include "jelly/vendors/picoPNG.h"
#include <fmt/core.h>


Jelly::GLTexture Jelly::ImageLoader::LoadPNG(const std::string &filepath) {
	GLTexture texture = {};

	std::vector<unsigned char> in;
	std::vector<unsigned char> out;
	unsigned long width, height;

	if (!IOManager::ReadFileToBuffer(filepath, in)) Logger::Error(fmt::format("Failed to load {} to buffer", filepath.c_str()));

	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());
	if (errorCode != 0) Logger::Error(fmt::format("decodePNG failed with error: {}", errorCode));

	glGenTextures(1, &(texture.id));
	glBindTexture(GL_TEXTURE_2D, texture.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	texture.width = (GLint)width;
	texture.height = (GLint)height;

	return texture;
}
