attribute highp   vec3 vertVertex;                                                
attribute mediump vec2 vertTexCoord;

varying mediump vec2 fragTexCoord;

void main() 
{
	fragTexCoord = vertTexCoord;

	gl_Position = vec4(vertVertex, 1.0);
}

