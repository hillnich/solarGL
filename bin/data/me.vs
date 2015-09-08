#version 150

// Grab pipeline values
uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
in vec4 position;
in vec3 normal;
in vec2 texcoord;
out vec2 texCoordVar;
out vec4 intensityOut;

// Grab my input uniform
uniform vec3 lightPos;

void main()
{
    // Do lighting calculations
    mat3 normalMat = transpose(inverse(mat3(modelViewMatrix)));
    vec3 vertexNormal = normalize(normalMat * normal);
    float intensity = max(dot(vertexNormal, lightPos), 0.0);
    vec4 ambient = vec4(0.15, 0.15, 0.15, 1.0);
    intensityOut = vec4(1,1,1,1) * intensity + ambient;
    intensityOut.w = 1.0;
        
    // Set up the position and texture
    texCoordVar = texcoord;
    gl_Position = modelViewProjectionMatrix * position;


}
