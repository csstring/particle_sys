__kernel void vector_add(__global const int *A, __global const int *B, __global float *C) {
 
    // Get the index of the current element to be processed
    int i = get_global_id(0);

    // Do the operation
    C[i] = 2.0f * 0.5f;
}