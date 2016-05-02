#version 130
#extension GL_EXT_texture_array : enable

in vec2 in_Position; 

uniform sampler2DArray kinect_depths;
uniform sampler2DArray kinect_qualities;
uniform sampler3D cv_xyz;
uniform sampler3D cv_uv;

uniform float cv_min_d;
uniform float cv_max_d;
uniform int layer;

out vec2 geo_texcoord;
out vec3 geo_pos_es;
out vec3 geo_pos_cs;
out float geo_depth;
out float geo_lateral_quality;

void main() {

  vec3 coords = vec3(in_Position,layer);
  float depth = texture2DArray(kinect_depths, coords).r;

  // lookup from calibvolume
  float d_idx = (depth - cv_min_d)/(cv_max_d - cv_min_d);

  geo_pos_cs        = texture(cv_xyz, vec3(in_Position, d_idx)).rgb;
  geo_pos_es        = (gl_ModelViewMatrix * vec4(geo_pos_cs, 1.0)).xyz;
  geo_texcoord = texture(cv_uv,  vec3(in_Position, d_idx)).rg;
  geo_depth         = depth;
  geo_lateral_quality = texture2DArray(kinect_qualities, coords).r;

  gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(geo_pos_cs, 1.0);
}