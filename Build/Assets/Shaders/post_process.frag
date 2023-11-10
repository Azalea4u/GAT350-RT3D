#version 430

#define INVERT_MASK		(1 << 0)
#define GRAYSCALE_MASK	(1 << 1)
#define COLORTINT_MASK	(1 << 2)
#define GRAIN_MASK 		(1 << 3)
#define SCANLINE_MASK	(1 << 4)
#define RGB_MASK		(1 << 5)

in layout(location = 0) vec2 ftexcoord;
out layout(location = 0) vec4 ocolor;

uniform float blend = 1;
uniform uint params = 0;
uniform vec3 tint = {1, 0, 0};
uniform float tintIntensity = 0;
uniform vec4 redOffset = {0, 0, 0, 0};
uniform vec4 greenOffset = {0, 0, 0, 0};
uniform vec4 blueOffset = {0, 0, 0, 0};

layout(binding = 0) uniform sampler2D screenTexture;

vec4 invert(in vec4 color)
{
	return vec4(vec3(1) - color.rgb, color.a);
}

vec4 graysclae(in vec4 color)
{
	return vec4(vec3(0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b), color.a);
}

vec4 colortint(in vec4 baseColor) {
    vec3 tintedColor = mix(baseColor.rgb, tint, tintIntensity);
    return vec4(tintedColor, baseColor.a);
}


vec4 grain(in vec4 color, float amount) {
    float noise = fract(sin(dot(ftexcoord ,vec2(12.9898,78.233))) * 43758.5453);
    return mix(color, vec4(vec3(noise), 1.0), amount);
}

vec4 scanline(in vec4 color) {
    float scanlineEffect = sin(ftexcoord.y * 800.0) * 0.5 + 0.5; // 800.0 is an arbitrary number to determine the density of the scanlines
    return vec4(color.rgb * scanlineEffect, color.a);
}

vec4 rgbShift(in vec4 color, in vec2 texCoord, vec4 redOffset, vec4 greenOffset, vec4 blueOffset) {
    float r = texture(screenTexture, texCoord + redOffset.xy).r;
    float g = texture(screenTexture, texCoord + greenOffset.xy).g;
    float b = texture(screenTexture, texCoord + blueOffset.xy).b;
    return vec4(r, g, b, color.a); // Preserve the original alpha
}



void main() {
    vec4 basecolor = texture(screenTexture, ftexcoord);
    vec4 post_process = basecolor;

    // Apply effects based on the bitmask flags set in 'params'
    if (bool(params & INVERT_MASK)) post_process = invert(post_process);
    if (bool(params & GRAYSCALE_MASK)) post_process = graysclae(post_process);
    if (bool(params & COLORTINT_MASK)) post_process = colortint(post_process); // Placeholder for actual tint color and intensity
    if (bool(params & GRAIN_MASK)) post_process = grain(post_process, 0.5); // Placeholder for actual grain amount
    if (bool(params & SCANLINE_MASK)) post_process = scanline(post_process);
    if (bool(params & RGB_MASK)) {
         // These offset values should be set based on uniforms or constants
        vec4 redOffset = vec4(0.005, 0.0, 0.0, 0.0); // Example offset for red channel
        vec4 greenOffset = vec4(-0.005, 0.0, 0.0, 0.0); // Example offset for green channel
        vec4 blueOffset = vec4(0.0, 0.005, 0.0, 0.0); // Example offset for blue channel

        post_process = rgbShift(post_process, ftexcoord, redOffset, greenOffset, blueOffset);

    }

    ocolor = mix(basecolor, post_process, blend);
}