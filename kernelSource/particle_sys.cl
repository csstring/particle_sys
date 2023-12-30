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
  Particle p = particles[i];
  float4 dir1 = float4(p._position.x, p._position.y, p._position.z,0);

  p._position.x -= dir1.x * dt;
  p._position.y -= dir1.y * dt;
  p._position.z -= dir1.z * dt;
//c : 1.59312  D : -0.225672 dt : 0.00166667
  C[i] = p._position.y;
  D[i] = dir1.y;
  particles[i] = p;
}