#version 430

layout (binding = 0) uniform sampler2D scene;

out vec4 FragColor;
in vec2 TexCoords;

uniform vec2 sunPos;

const float exposure = 1.0f;
const float decay = 0.96f;
const float density = 0.99f;
const float weight = 0.3f;
const int NUM_SAMPLES = 100;

void main() {
    vec2 lightPositionOnScreen = (sunPos + 1.0f) * 0.5f;

	vec2 deltaTextCoord = vec2(TexCoords - lightPositionOnScreen.xy);
	vec2 textCoo = TexCoords;
	deltaTextCoord *= 1.0f / float(NUM_SAMPLES) * density;
	float illuminationDecay = 1.0f;

	for(int i = 0; i < NUM_SAMPLES; i++) {
        textCoo -= deltaTextCoord;
        vec4 samp = texture(scene, textCoo);

        samp *= illuminationDecay * weight;
        FragColor += samp;
        illuminationDecay *= decay;
    }
    FragColor *= exposure;
}