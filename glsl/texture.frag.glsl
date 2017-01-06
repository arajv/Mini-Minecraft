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
uniform sampler2D u_Sampler;
uniform sampler2D u_SamplerNMap;
uniform float u_Time;

uniform vec4 u_CameraEye;

uniform vec4 u_LightVec;

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

const vec4 eveningLight = vec4(0.99,0.36,0.32,0);


void main()
{

        ///////////////////////////////////////////////////////
        //Normalize the tangent and the bitangent

        vec4 tangent = normalize(fs_Tangent);
        vec4 bitangent = normalize(fs_Bitangent);
        vec4 normal = normalize(fs_Nor);
        vec4 newNormal;


        vec4 textNorm = texture(u_SamplerNMap, fs_UV);
        textNorm = normalize(textNorm*2.0 - 1.0);

        mat4 tbnMat;

        tbnMat[0][0] = tangent.x;
        tbnMat[0][1] = tangent.y;
        tbnMat[0][2] = tangent.z;
        tbnMat[0][3] = 0;

        tbnMat[1][0] = bitangent.x;
        tbnMat[1][1] = bitangent.y;
        tbnMat[1][2] = bitangent.z;
        tbnMat[1][3] = 0;

        tbnMat[2][0] = normal.x;
        tbnMat[2][1] = normal.y;
        tbnMat[2][2] = normal.z;
        tbnMat[2][3] = 0;

        tbnMat[3][0] = 0;
        tbnMat[3][1] = 0;
        tbnMat[3][2] = 0;
        tbnMat[3][3] = 1;

        newNormal = tbnMat * textNorm;

        //////////////////////////////////////////////////////////////////////
        //Lambertian Part

        // Calculate the diffuse term for Lambert shading
        float diffuseTerm = dot(normalize(newNormal), normalize(u_LightVec));
        // Avoid negative lighting values
        diffuseTerm = clamp(diffuseTerm, 0, 1);

        float ambientTerm = 0.4;

        //////////////////////////////////////////////////////////////////////
        //Day and night

        float lightAngle = mod(1 * u_Time,360);


        float dayLightFrac = sin(radians(lightAngle));

        diffuseTerm = diffuseTerm * dayLightFrac;


        float lightIntensity = diffuseTerm + ambientTerm;   //Add a small float value to the color multiplier
                                                            //to simulate ambient lighting. This ensures that faces that are not
                                                            //lit by our point light are not completely black.


        ///////////////////////////////////////////////////////////////////
        //Specular highlight part

        vec4 viewVec = normalize(u_CameraEye - fs_Pos);
        //vec4 lVec = normalize(fs_LightVec - fs_Pos);
        vec4 lVec = normalize(u_LightVec);//normalize(fs_Pos - fs_LightVec);
        vec4 hVec = normalize((viewVec + lVec));


        vec4 specularHighlight = vec4(0,0,0,1);
        specularHighlight = max(pow(dot(hVec,normalize(newNormal)), fs_CosPow),0) * ( vec4(1,1,1,1) );

        specularHighlight.rgb = clamp(specularHighlight.rgb * clamp(fs_CosPow * fs_CosPow, 0.0, 1.0),0.0,1.0);

        specularHighlight.rgb = specularHighlight.rgb * dayLightFrac;

        if(lightAngle >180 || lightAngle < 360){
            specularHighlight.rgb = specularHighlight.rgb * 0.0;
            dayLightFrac = 1;
        }



        ////////////////////////////////////////////////////////////////////
        //Animation of Texture
        vec2 textCord = fs_UV;
        if(fs_Animate == 1.0)
        {
            float displaceFrac = 1/160.0;
            textCord.x = clamp(textCord.x + mod(u_Time,10)*displaceFrac,0,1);

        }

        vec4 textCol = (texture(u_Sampler, textCord));

        ////////////////////////////////////////////////////////////////////
        // Compute final shaded color

        out_Col = vec4(  ((textCol.rgb )* lightIntensity + specularHighlight.rgb) , textCol.a)  ;
}
