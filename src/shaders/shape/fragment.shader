#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 shapeColour;
uniform float lightIntensity;
uniform vec3 viewPos;
uniform float specularStrength;
uniform vec3 lightPos;

void main()
{

    float ambient = 0.5;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos); // Direction of light, from light source to pixel
    float diffuse = max(dot(norm, lightDir), 0.0); 
    /* Calculate angle between normal and light direction, the bigger the angle, the lower the intensity until the angle is
    90 degrees, where the intensity is 0 */

    vec3 viewDir = normalize(viewPos - FragPos); // Direction from viewer to pixel
    vec3 reflectDir = reflect(-lightDir, norm); // Direction opposite to between the light direction and the normal
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32); // The greater the angle the lower the intensity
    float specular = specularStrength * spec; // Uses matteness, as defined by user

    vec3 result = (ambient + diffuse + specular) * shapeColour * lightIntensity; // Combines all light models
    FragColor = vec4(result, 1.0);
} 
