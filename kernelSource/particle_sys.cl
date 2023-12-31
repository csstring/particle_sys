// typedef struct {
//     float3 _position;
//     float3 _velocity;
//     float3 _color;   
//     float _life;
//     float _radius;
// } Particle;

typedef struct {
    float4 _position;
    float4 _velocity;
    float4 _color;   
} Particle;

__kernel void particle_sys(__global Particle* particles, float dt, float4 gravity, __global float* C, __global float* D) {

  int i = get_global_id(0);
  float4 dir1 = float4(particles[i]._position.x, particles[i]._position.y, particles[i]._position.z,0);
  float2 tmp = float2(particles[i]._position.x, particles[i]._position.y);
  C[i] = tmp.y;
  D[i] = particles[i]._position.y;

  particles[i]._position.x -= dir1.x * dt;
  particles[i]._position.y -= dir1.y * dt;
  particles[i]._position.z -= dir1.z * dt;
}