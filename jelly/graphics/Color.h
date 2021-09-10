//
// Created by Maxime Blanc on 10/09/2021.
//

#pragma once

#include <GL/glew.h>

namespace Jelly {
	struct Color {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;

		Color()=default;
		Color(GLubyte pr, GLubyte pg, GLubyte pb, GLubyte pa = 255) : r(pr), g(pg), b(pb), a(pa) {};

		static Color White() { return {255, 255, 255}; }
		static Color Black() { return {0, 0, 0}; }
	};

}