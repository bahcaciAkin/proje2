#version 120

uniform mat4 MVP;
attribute vec4 Position;
attribute vec3 Normal;

varying vec3 fresnel;


void main()
{
  
   gl_Position = MVP * Position;

   camera_position = mat3(gl_ModelViewMatrix) * Normal ;

   aci = dot( normalize(mat3(gl_ModelViewMatrix) * Normal), vec3( 0.0, 0.0, -1.0 ));

   fresnel = vec3(mix(vec3( 0.1, 0.1, 0.0 ), vec3( 0.2, 0.2, 0.2 ),cos(aci)));
}
