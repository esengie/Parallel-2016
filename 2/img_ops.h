#ifndef TBBHW_IMG_OPS_H
#define TBBHW_IMG_OPS_H

#include <vector>
#include <glob.h>

struct image {
    const size_t n;
    const size_t m;
    image(size_t n, size_t m);
private:
    std::vector<char> data;
};


#endif //TBBHW_IMG_OPS_H
