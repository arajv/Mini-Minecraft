#version 150
// ^ Change this to version 130 if you have compatibility issues

// This is a fragment shader. If you've opened this file first, please
// open and read lambert.vert.glsl before reading on.
// Unlike the vertex shader, the fragment shader actually does compute
// the shading of geometry. For every pixel in your program's output
// screen, the fragment shader is run for every bit of geometry that
// particular pixel overlaps. By implicitly interpolating the position
// data passed into the fragment shader by the vertex shader, the fragment shader
// can compute what color to apply to its pixel based on things like vertex
// position, light position, and vertex color.

uniform vec4 u_Color; // The color with which to render this instance of geometry.
uniform sampler2D u_SkyDaySampler;
uniform sampler2D u_SkyNightSampler;
uniform float u_Time;

uniform vec4 u_CameraEye;

// These are the interpolated values out of the rasterizer, so you can't know
// their specific values without knowing the vertices that contributed to them
in vec4 fs_Nor;
in vec4 fs_LightVec;
in vec4 fs_Col;
in vec2 fs_UV;

in vec4 fs_Tangent;
in vec4 fs_Bitangent;

in vec4 fs_Pos;

in float fs_CosPow;
in float fs_Animate;

out vec4 out_Col; // This is the final output color that you will see on your
                  // screen for the pixel that is currently being processed.

void main()
{
    vec2 textCord = fs_UV;

    vec4 textCol = (texture(u_SkyDaySampler, textCord));

    vec4 day_col = vec4(textCol.rgb,textCol.a);

    textCol = (texture(u_SkyNightSampler, textCord));

    vec4 night_col = vec4(textCol.rgb,textCol.a);


    float lightAngle = mod(1 * u_Time,360);

    float dayFrac = clamp(sin(radians(lightAngle)),0.0,1.0);
    float nightFrac = clamp(sin(radians(lightAngle + 180)),0.0,1.0);

    out_Col = vec4(dayFrac* day_col.rgb + nightFrac* night_col.rgb ,night_col.a);

}
