#version 430 core
struct LightProperties //generic light properties to describe any light source
{
    int type;
    int enabled;
    vec3 colour;
    float strength;
    
    vec3 position;//only needed for point and spot
    vec3 direction;//only for spot and directional
    //TODO: add properties for spotlights
};

out vec4 fragColour;
////////////////////

in vec3 vNormal_cs;
in vec3 vDirLigt_cs;
in vec3 vPosition_cs;

uniform int numLights;
uniform LightProperties light[10];
uniform vec3 ambientColour = { 0.05f, 0.05f, 0.05f };

vec3 phong(vec3 _diffColour, vec3 _specColour, vec3 _normal, vec3 _eyeDirection, vec3 _lightDirection)
{
    float diff = max(0.0, dot(_normal, _lightDirection));
    vec3 diffuse = diff*_diffColour;

    float spec = pow(max(0.0, dot(reflect(_lightDirection, _normal)*-1.0f, _eyeDirection)),
    50.0f);//controls size of the highlight
    
    vec3 specular = spec * _specColour;
    return diffuse + specular;
}

void main()
{
    fragColour = vec4(ambientColour, 1.0f);
    for (int i = 0; i < numLights;i++)
    {
        vec3 eyeDirection_cs = normalize(vec3(0, 0, 0) - vPosition_cs);
        vec3 normal = normalize(vNormal_cs);
        switch(light[i].type)
        {
            case 0://DIRECTIONAL LIGHT
            {
                vec3 lightDirection_cs = light[i].direction;
                vec3 texColour = vec3(0.5f, 0.5f, 0.5f);//vec3(texture(tex1, vTexCoordOut)); //No texturing yet
                vec3 phong = phong(texColour, vec3(1.0f, 1.0f, 1.0f), normal, eyeDirection_cs, lightDirection_cs);
                
                fragColour = fragColour + vec4(light[i].colour + phong * light[i].strength, 1.0f);
                break;
            }
            
            case 1://POINT LIGHT
            {
                vec3 lightDirection_cs = light[i].position - vPosition_cs;
                float att = 1 / pow(length(lightDirection_cs), 2);
                lightDirection_cs = normalize(lightDirection_cs);
                vec3 texColour = vec3(0.5f, 0.5f, 0.5f);//vec3(texture(tex1, vTexCoordOut));
                vec3 phong = phong(texColour, vec3(1.0f, 1.0f, 1.0f), normal, eyeDirection_cs, lightDirection_cs);
                
                fragColour = fragColour + vec4(light[i].colour + phong * att * light[i].strength, 1.0f);
                break;
            }
        };
    }
}

