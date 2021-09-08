#version 410 core
// The fragment shader iperates on each pixel in a given polygon.
in vec2 frag_position;
in vec4 frag_color;
in vec2 frag_uv;

// 4 components vector that gets outputted to the screen for each pixel.
out vec4 color;

uniform float time;
uniform sampler2D sampler;

void main() {
    vec4 texture_color = texture(sampler, frag_uv);
    // color = texture_color * frag_color;
    color = vec4(
        frag_color.r * (cos(frag_position.x * 2.0 + time) + 1.0) * 0.5,
        frag_color.g * (cos(frag_position.y * 2.0 + time) + 1.0) * 0.5,
        frag_color.b * (cos(frag_position.x * 2.0 + time) + 1.0) * 0.5,
        frag_color.a
    ) * texture_color;
}
