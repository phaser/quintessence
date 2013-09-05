uniform mat4 PMVMATRIX;
attribute vec4 a_position;
attribute vec4 a_color;
varying vec4 f_color;
void main()
{
	gl_Position = PMVMATRIX * a_position;
	f_color = a_color;
}
