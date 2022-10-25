#version 410
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
//layout (location = 2) in vec2 aTexCoord;

out vec4 ourColor;
//out vec2 TexCoord;

//uniform mat4 projection;

void main()
{
    //TexCoord = aTexCoord;
    ourColor = aColor;
    gl_Position = vec4(aPos, 1.0);
}