#version 330 core

out vec4 FragColor;
  
in vec4 vPxVal;
in float vIsTx;

uniform sampler2D txs_0;
uniform sampler2D txs_1;
uniform sampler2D txs_2;
uniform sampler2D txs_3;
uniform sampler2D txs_4;
uniform sampler2D txs_5;
uniform sampler2D txs_6;
uniform sampler2D txs_7;
uniform sampler2D txs_8;
uniform sampler2D txs_9;
uniform sampler2D txs_10;
uniform sampler2D txs_11;
uniform sampler2D txs_12;
uniform sampler2D txs_13;
uniform sampler2D txs_14;
uniform sampler2D txs_15;

void main()
{ 
    if (vIsTx == -1.0f)
    {
        FragColor = vPxVal;
    }
    else if (vIsTx == 0.0f)
    {
        FragColor = texture(txs_0, vPxVal.xy);
    }
    else if (vIsTx == 1.0f)
    {
        FragColor = texture(txs_1, vPxVal.xy);
    }
    else if (vIsTx == 2.0f)
    {
        FragColor = texture(txs_2, vPxVal.xy);
    }
    else if (vIsTx == 3.0f)
    {
        FragColor = texture(txs_3, vPxVal.xy);
    }
    else if (vIsTx == 4.0f)
    {
        FragColor = texture(txs_4, vPxVal.xy);
    }
    else if (vIsTx == 5.0f)
    {
        FragColor = texture(txs_5, vPxVal.xy);
    }
    else if (vIsTx == 6.0f)
    {
        FragColor = texture(txs_6, vPxVal.xy);
    }
    else if (vIsTx == 7.0f)
    {
        FragColor = texture(txs_7, vPxVal.xy);
    }
    else if (vIsTx == 8.0f)
    {
        FragColor = texture(txs_8, vPxVal.xy);
    }
    else if (vIsTx == 9.0f)
    {
        FragColor = texture(txs_9, vPxVal.xy);
    }
    else if (vIsTx == 10.0f)
    {
        FragColor = texture(txs_10, vPxVal.xy);
    }
    else if (vIsTx == 11.0f)
    {
        FragColor = texture(txs_11, vPxVal.xy);
    }
    else if (vIsTx == 12.0f)
    {
        FragColor = texture(txs_0, vPxVal.xy);
    }
    else if (vIsTx == 13.0f)
    {
        FragColor = texture(txs_0, vPxVal.xy);
    }
    else if (vIsTx == 14.0f)
    {
        FragColor = texture(txs_0, vPxVal.xy);
    }
    else if (vIsTx == 15.0f)
    {
        FragColor = texture(txs_0, vPxVal.xy);
    }
    else 
    {
        FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }

}
