#version 150

uniform sampler2D tex0;
out vec4 outputColor;

in vec2 texCoordVar;
in vec4 intensityOut;

void main()
{
    outputColor = intensityOut * texture(tex0, texCoordVar);
}

