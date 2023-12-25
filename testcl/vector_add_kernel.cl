__kernel void vector_add(__global const int *A, __global const int *B, __global int *C) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);
    typedef struct {
    float3 _position;
    float3 _velocity;
    float3 _color;   
    float _life;
    float _radius;
    } Particle;
    // Do the operation
    C[i] = sizeof(Particle);
}