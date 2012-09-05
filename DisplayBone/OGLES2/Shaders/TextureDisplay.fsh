uniform sampler2D texture;

varying mediump vec2 fragTexCoord;

void main()
{
	gl_FragColor = texture2D(texture, fragTexCoord);
}
