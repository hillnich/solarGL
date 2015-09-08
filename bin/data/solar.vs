#version 150

// Grab pipeline values
uniform mat4 modelViewProjectionMatrix;
uniform float time;
in vec4 position;
in vec2 texcoord;
out vec2 texCoordVar;
out vec3 pos;

void main()
{

    // Set up the position
    pos = position.xyz * 0.03;
    texCoordVar = texcoord;
    gl_Position = modelViewProjectionMatrix * position;


}
