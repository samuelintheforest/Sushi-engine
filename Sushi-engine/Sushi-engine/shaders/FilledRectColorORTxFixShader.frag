#version 330 core

out vec4 FragColor;
  
in vec4 vPxVal;
in float vIsTx;

void main()
{ 
    if (vIsTx == 0.0f)
    {
        FragColor = vPxVal;
    }
    else 
    {
        /* TODO */
    }
}
