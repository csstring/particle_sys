typedef struct {
    float3 _position;
    float3 _velocity;
    float3 _color;   
    float _life;
    float _radius;
} Particle;

__kernel void particle_sys(__global Particle* particles, float dt) {

  int i = get_global_id(0);
  float3 gravity = (float3)(0.0f, -9.8f, 0.0f);

  // particles[i]._velocity += gravity * dt;
  particles[i]._position += particles[i]._velocity * dt;
}