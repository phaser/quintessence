precision mediump float;
uniform sampler2D sampler2d;
varying mediump vec2 myTexCoord;
void main(void)
{
  gl_FragColor = texture2D(sampler2d, myTexCoord);
}
