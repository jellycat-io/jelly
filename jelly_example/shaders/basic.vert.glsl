#version 410 core
// The vertex shader operates on each vertex.

// Input data from the VBO. Each vertex is 2 floats.
in vec2 position;
in vec4 color;
in vec2 uv;

out vec4 frag_color;
out vec2 frag_position;
out vec2 frag_uv;

uniform mat4 P;

void main() {
    // Set the x,y position on the screen.
    gl_Position.xy = (P * vec4(position.x, position.y, 0.0, 1)).xy;
    // Z is zero because 2D.
    gl_Position.z = 0.0;
    // Coordinates are normalized.
    gl_Position.w = 1.0;

    frag_color = color;
    frag_position = position;
    frag_uv = vec2(uv.x, 1.0 - uv.y);
}
