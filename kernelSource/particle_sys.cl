
typedef struct {
    float4 _position;
    float4 _velocity;
    float4 _color;   
} Particle;

__kernel void particle_sys(__global Particle* particles, float dt, float4 gravity, __global float* C, __global float* D, __global float* F) {

  int i = get_global_id(0);
  float4 pos = particles[i]._position;
  pos.w = 0;
  float4 dir1 = gravity - pos;
  // float r = sqrt(dot(dir1, dir1));
  float4 G = normalize(dir1);
  // // float2 tmp = float2(particles[i]._position.x, particles[i]._position.y);
  // // c : 4000.38  D : 6.2488e-08 dt : 0.005 0 0 -4 x y 0
  particles[i]._velocity += G * dt * 5;
  // C[i] = r;
  // D[i] = r*r;
  // F[i] = r;
  particles[i]._position += particles[i]._velocity * dt;
  // pos.x += dir1.x * dt;
  // pos.y += dir1.y * dt;
  // pos.z += dir1.z * dt;
  // C[i] = particles[i]._position.x;
  // D[i] = particles[i]._position.y;
  // particles[i]._position = pos;
}