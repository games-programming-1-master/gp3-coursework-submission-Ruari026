#version 330 core

out vec4 FragColor;

in vec3 vertWorldPos;
in vec2 vertTexCoord;

uniform sampler2D myTexture;
  
uniform vec4 minColor;
uniform vec4 maxColor;
uniform vec4 fogColor;

uniform vec3 cameraPos;
int fogDistance = 30;

void main()
{
    // Getting the base color of the object from it's texture & UV coordinates (textures are greyscale to act as a lerp point between two colors)
    vec4 texColor = texture(myTexture, vertTexCoord);
    vec4 baseColor = mix(maxColor, minColor, texColor);

    // Blit

    // Fog Based on pixel's distance from the player
    float dist = distance(vertWorldPos, cameraPos);

    // Finalising pixel color
    vec4 finalColor = mix(baseColor, fogColor, (dist / fogDistance));
    FragColor = vec4(finalColor.xyz, 1);
}