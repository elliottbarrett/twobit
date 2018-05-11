uniform sampler2D texture;
uniform float time;

const float noiseStrength = 21.0;

void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    vec2 coords = gl_TexCoord[0].xy;

    // float x = (gl_TexCoord[0].x + 4) * (gl_TexCoord[0].y + 4);
    // * (time * 10);
    float fy = float(coords.y);
    float fx = float(coords.x);

    float x = (fx + 4.0) * (fy + 4.0) * (time * 10.0);

    vec4 grain = vec4(mod((mod(x, 13.0) + 1.0) * (mod(x, 123.0) + 1.0), 0.01)-0.005) * noiseStrength;

    // multiply it by the color
    gl_FragColor = grain + (gl_Color * pixel);
}
