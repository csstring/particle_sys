
typedef struct {
    float4 _position;
    float4 _velocity;
    float3 _color;
    float _life;   
} Particle;

__kernel void particle_sys(__global Particle* particles, float dt, float4 gravity, __global float* C, __global float* D, __global float* F) {

  int i = get_global_id(0);
  int flag = gravity.w;
  float4 pos = particles[i]._position;
  if (flag != 0)
  {
    float4 dir1 = gravity - pos;
    float4 G = normalize(dir1);
    particles[i]._velocity += G * dt * 5;
  }
  particles[i]._position += particles[i]._velocity * dt;

  float dis = distance(pos.xy, gravity.xy) / sqrt(12.0f);
  float value = mix(1.0f, 0.1f, dis);
  float r = fabs(dis * 6.0f - 3.0f) - 1.0f;
  float g = 2.0 - fabs(dis * 6.0f - 2.0f);
  float b = 2.0 - fabs(dis * 6.0f - 4.0f);

  // particles[i]._color = float3(r, g, b) * value;
  particles[i]._color = float3(0.3f);
}