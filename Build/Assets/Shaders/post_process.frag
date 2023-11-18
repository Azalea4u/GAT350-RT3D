#version 430

#define INVERT_MASK		(1 << 0)
#define GRAYSCALE_MASK	(1 << 1)
#define COLORTINT_MASK	(1 << 2)
#define GRAIN_MASK 		(1 << 3)
#define SCANLINE_MASK	(1 << 4)
#define RGB_MASK		(1 << 5)

in layout(location = 0) vec2 ftexcoord;
out layout(location = 0) vec4 ocolor;

uniform float time = 0;
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

vec4 colortint(in vec4 baseColor, in vec3 tint, in float intensity) {
    // Calculate luminance of the original color
    float luminance = dot(baseColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    // Mix the base color with the tint color based on the base color's luminance
    vec3 color = mix(baseColor.rgb, luminance * tint, intensity);
    return vec4(color, baseColor.a);
}

float random(vec2 st) 
{
	return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

vec4 grain(in vec4 color, float amount) {
    return color * random(gl_FragCoord.xy + time);
}

vec4 scanline(in vec4 color) {
    float scanline = sin(gl_FragCoord.y * 800.0) * 0.5 + 0.5; // 800.0 is an arbitrary number to determine the density of the scanlines
    return color * scanline;
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
    if (bool(params & COLORTINT_MASK)) post_process = colortint(post_process, tint, tintIntensity);
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