#ifndef TOOLS_HPP
#define TOOLS_HPP

#define HERE() do { printf("> %s\n", __func__); } while (0)

#define ERR()                                      \
    do {                                           \
        printf("ERROR DETECTED!\nFILE: %s, "       \
                   "FUNCTION: %s, LINE: %d\n\n",   \
                   __FILE__, __func__,  __LINE__); \
    } while (0)

#define ASSERT_OK()                                \
    do {                                           \
        if (!Ok()) {                               \
            ERR();                                 \
            Dump();                                \
            exit(EXIT_FAILURE);                    \
        }                                          \
    } while (0) 

#endif
