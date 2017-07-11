#pragma once

#define PRINT_MATRIX(x)                                 \
    std::cout << #x << std::endl;                       \
    for (std::size_t i = 0; i < x.size1(); i++) {       \
        for (std::size_t j = 0; j < x.size2(); j++) {   \
            std::cout << "  " << x(i, j) << " ";        \
        }                                               \
        std::cout << std::endl;                         \
    }

#define PRINT_VECTOR(x)                                 \
    std::cout << #x << std::endl;                       \
    for (std::size_t i = 0; i < x.size(); i++) {        \
        std::cout << "  " << x(i) << ", ";              \
    }                                                   \
    std::cout << std::endl;

