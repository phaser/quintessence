attribute highp vec4	myVertex;
attribute mediump vec4	myUV;
uniform mediump mat4	myPMVMatrix;
varying mediump vec2	myTexCoord;
void main()
{
   gl_Position = myPMVMatrix * myVertex;
   myTexCoord = myUV.st;
}
