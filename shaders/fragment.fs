#version 410 core
in vec4 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D image;

void main()
{    
    color = ourColor * texture(image, TexCoord);
    //color = vec4(ourColor);
    //color = vec4(1.0, 0.0, 0.0, 1.0);
}  