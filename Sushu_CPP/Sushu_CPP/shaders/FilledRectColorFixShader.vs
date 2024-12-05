#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec4 vertex_color;
out vec4 vertex_pos;
out mat4 transformMat;

uniform mat4 projection;
uniform mat4 camera;

void main()
{
  vertex_color = vec4(aCol.xyz, 1.0);
  oTxCoords = aTxCoords;
  vTxid = tx_id;
  vertex_pos = projection * camera * vec4(aPos, 1.0);
  transformMat = projection * camera;
  gl_Position = vertex_pos;
}


