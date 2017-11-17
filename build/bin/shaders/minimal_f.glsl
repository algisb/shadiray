#version 430 core

out vec4 fragColour;
uniform vec3 colour = vec3(1.0f, 0.0f, 0.0f);

void main()
{
    fragColour = vec4(colour, 1.0);
}
