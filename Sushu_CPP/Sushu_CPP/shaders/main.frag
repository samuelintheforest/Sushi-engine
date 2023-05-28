#version 330 core

out vec4 FragColor;

in vec4 vertex_color;
in vec2 oTxCoords;
in float vTxid;
in vec4 vertex_pos;
in mat4 transformMat;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;
uniform sampler2D texture6;
uniform sampler2D texture7;
uniform sampler2D texture8;
uniform sampler2D texture9;
uniform sampler2D texture10;
uniform sampler2D font_atlas;
uniform float iTime;

const vec2 vp = vec2(20.0, 24.0);

float median(float r, float g, float b) {
	return max(min(r, g), min(max(r, g), b));
}

float roundedFrame(vec2 pos, vec2 size, float radius, float thickness)
{
  float d = length(max(abs(oTxCoords - pos),size) - size) - radius;
  return smoothstep(0.55, 0.45, abs(d / thickness) * 5.0);
}

void main()
{
    // bool stat = gl_FragCoord.x > 1920.0 / 2.0 - 16 * 6 && gl_FragCoord.x < 1920.0 / 2.0 + 4 * 16 && gl_FragCoord.y > 1080.0 / 2.0 - 32 * 4 && gl_FragCoord.y < 1080.0 / 2.0 + 32 * 2;
    bool stat = false;
    vec4 final_color;
    if (1.0f == vTxid)
    {
        // if(gl_FragCoord.x < 1920.0 / 2.0)
        // {   
        //     vec4 tmp_color = mix(texture(texture1, oTxCoords), vec4(1.0f - vertex_color.x, 1.0f - vertex_color.y, 1.0f - vertex_color.z, vertex_color.w), 0.0); 
        //     FragColor = vec4(1.0 - tmp_color.x, 1.0 - tmp_color.y, 1.0 - tmp_color.z, tmp_color.w);
        // } else {
        final_color = mix(texture(texture1, oTxCoords), vertex_color, 0.0);
        // }
    } else if (2.0f == vTxid)
    {
        if(stat)
        {   
            vec4 tmp_color = mix(texture(texture2, oTxCoords), vec4(1.0f - vertex_color.x, 1.0f - vertex_color.y, 1.0f - vertex_color.z, vertex_color.w), 0.0); 
            final_color = vec4(1.0 - tmp_color.x, 1.0 - tmp_color.y, 1.0 - tmp_color.z, tmp_color.w);
        } else {
        final_color = mix(texture(texture2, oTxCoords), vertex_color, 0.0);
        }
    } else if (3.0f == vTxid)
    {
        if(stat)
        {   
            vec4 tmp_color = mix(texture(texture3, oTxCoords), vec4(1.0f - vertex_color.x, 1.0f - vertex_color.y, 1.0f - vertex_color.z, vertex_color.w), 0.0); 
            final_color = vec4(1.0 - tmp_color.x, 1.0 - tmp_color.y, 1.0 - tmp_color.z, tmp_color.w);
        } else {
        final_color = mix(texture(texture3, oTxCoords), vertex_color, 0.0);
        }
    } else if (4.0f == vTxid)
    {
        if(stat)
        {   
            vec4 tmp_color = mix(texture(texture4, oTxCoords), vec4(1.0f - vertex_color.x, 1.0f - vertex_color.y, 1.0f - vertex_color.z, vertex_color.w), 0.0); 
            final_color = vec4(1.0 - tmp_color.x, 1.0 - tmp_color.y, 1.0 - tmp_color.z, tmp_color.w);
        } else {
        final_color = mix(texture(texture4, oTxCoords), vertex_color, 0.0);
        }
    } else if (5.0f == vTxid)
    {

        if(stat)
        {   
            vec4 tmp_color = mix(texture(texture5, oTxCoords), vec4(1.0f - vertex_color.x, 1.0f - vertex_color.y, 1.0f - vertex_color.z, vertex_color.w), 0.0); 
            final_color = vec4(1.0 - tmp_color.x, 1.0 - tmp_color.y, 1.0 - tmp_color.z, tmp_color.w);
        } else {
        final_color = mix(texture(texture5, oTxCoords), vertex_color, 0.0);
        }
    } else if (6.0f == vTxid)
    {
        if(stat)
        {   
            vec4 tmp_color = mix(texture(texture6, oTxCoords), vec4(1.0f - vertex_color.x, 1.0f - vertex_color.y, 1.0f - vertex_color.z, vertex_color.w), 0.0); 
            final_color = vec4(1.0 - tmp_color.x, 1.0 - tmp_color.y, 1.0 - tmp_color.z, tmp_color.w);
        } else {
        final_color = mix(texture(texture6, oTxCoords), vertex_color, 0.0);
        }
    } else if (7.0f == vTxid)
    {
        final_color = mix(texture(texture7, oTxCoords), vertex_color, 0.0);
    } else if (8.0f == vTxid)
    {
        final_color = mix(texture(texture8, oTxCoords), vertex_color, 0.0);
    } else if (9.0f == vTxid)
    {
        final_color = mix(texture(texture9, oTxCoords), vertex_color, 0.0);
    } else if (10.0f == vTxid)
    {
        final_color = mix(texture(texture10, oTxCoords), vertex_color, 0.0);
    } else if (1000.0f == vTxid) // Font texture
    {
        vec3 v_sample = texture(font_atlas, oTxCoords).rgb;
	    ivec2 sz = textureSize(font_atlas, 0).xy;
	    float dx = dFdx(oTxCoords.x) * sz.x;
	    float dy = dFdy(oTxCoords.y) * sz.y;
	    float toPixels = 8.0 * inversesqrt(dx * dx + dy * dy);
	    float sigDist = median(v_sample.r, v_sample.g, v_sample.b);
	    float w = fwidth(sigDist);
	    float opacity = smoothstep(0.5 - w, 0.5 + w, sigDist);
	    if(stat)
        {   
            final_color = vec4(vec3(1.0 - vertex_color.x, 1.0 - vertex_color.y, 1.0 - vertex_color.z), opacity);
        } else {
            final_color = vec4(vec3(vertex_color.xyz), opacity);
        }
    }else
    {
        // vec3 frameColor = vec3(vertex_color.xyz);
        // vec2 size = vec2(1410.0, 365.0);
        // float intensity = roundedFrame(vec2( -520.0, -200.0 - 330.0 ), size, 100, 3.0);
        // vec3 col = vec3(1.0);
        // col = mix(col, frameColor, intensity);



        /*

                // Parameters
        vec3 circleColor = vec3(vertex_color.x, vertex_color.y, vertex_color.z);
        float thickness = 1.0;
        // Control with mouse
        // thickness = iMouse.x / iResolution.x;
        float fade = 0.005;

        // -1 -> 1 local space, adjusted for aspect ratio
        vec2 uv = vec2((transformMat * vec4(vec2(vertex_pos / 1.0f * 2.0 - 1.0).xy, 0.0f, 0.0f)).xy);
        //float aspect = iResolution.x / iResolution.y;
        //uv.x *= aspect;
    
        // Calculate distance and fill circle with white
        float distance = 1.0 - length(uv);
        vec3 color = vec3(smoothstep(0.0, fade, distance));
        color *= vec3(smoothstep(thickness + fade, thickness, distance));

        // Set output color
        final_color = vec4(color, 1.0);
        final_color.rgb *= circleColor;

        */


        /*
        float t = iTime * 10.0 + 200;
	    vec2 uv = vertex_pos.xy ;
        vec2 p0 = (uv - 0.5) * vp;
        vec2 hvp = vp * 0.5;
	    vec2 p1d = vec2(cos( t / 98.0),  sin( t / 178.0)) * hvp - p0;
	    vec2 p2d = vec2(sin(-t / 124.0), cos(-t / 104.0)) * hvp - p0;
	    vec2 p3d = vec2(cos(-t / 165.0), cos( t / 45.0))  * hvp - p0;
        float sum = 0.5 + 0.5 * (
		    cos(length(p1d) / 30.0) +
		    cos(length(p2d) / 20.0) +
		    sin(length(p3d) / 25.0) * sin(p3d.x / 20.0) * sin(p3d.y / 15.0)
        );
        final_color = vec4(vec2(fract(sum)).xy, 1.0, 1.0);
        */


        final_color = vec4(vertex_color.xyz, 1.0);

    }
    FragColor = final_color;
}