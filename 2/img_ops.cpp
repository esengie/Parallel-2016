#include "img_ops.h"

std::random_device rd;
std::mt19937 rng(rd());
std::uniform_int_distribution<int> uni(0,255);

const int NUM_IMAGES = 100;

image::image(size_t n, size_t m) : n(n), m(m), data(n*m) {
    for (char &elem : data){
        elem = uni(rng);
    }
}

void find_max(image *input_image, vector<size_t> *maxes ) {
    for ( int i = 0; i < input_image->N; ++i ) {
        output_image->data[i] = input_image->data[i] + 32;
    }
}

bool detect_with_A( image *input_image ) {
    for ( int i = 0; i < input_image->N; ++i ) {
        if ( input_image->data[i] == 'a' )
            return true;
    }
    return false;
}

bool detect_with_B( image *input_image ) {
    for ( int i = 0; i < input_image->N; ++i ) {
        if ( input_image->data[i] == 'b' )
            return true;
    }
    return false;
}

image *get_next_image() {
    if ( img_number < NUM_IMAGES ) {
        if ( img_number%a_frequency == 0 ) a = true;
        if ( img_number%b_frequency == 0 ) b = true;
        return new image(a, b);
    } else {
        return nullptr;
    }
}


void output_image( image *input_image, bool found_a, bool found_b ) {
    bool a = false, b = false;
    int a_i = -1, b_i = -1;
    for ( int i = 0; i < input_image->N; ++i ) {
        if ( input_image->data[i] == 'a' ) { a = true; a_i = i; }
        if ( input_image->data[i] == 'b' ) { b = true; b_i = i; }
    }
    printf("Detected feature (a,b)=(%d,%d)=(%d,%d) at (%d,%d) for image %p:%d\n",
           a, b, found_a, found_b, a_i, b_i, input_image, input_image->data[0]);
}