
typedef struct {
    float4 _position;
    float4 _velocity;
    float4 _color;   
} Particle;

__kernel void particle_sys(__global Particle* particles, float dt, float4 gravity, __global float* C, __global float* D, __global float* F) {

  int i = get_global_id(0);
  int flag = gravity.w;
  if (flag != 0)
  {
    float4 pos = particles[i]._position;
    float4 dir1 = gravity - pos;
    float4 G = normalize(dir1);
    particles[i]._velocity += G * dt * 5;
  }
  particles[i]._position += particles[i]._velocity * dt;
}