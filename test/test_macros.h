#ifndef __TEST_MACROS_H__
#define __TEST_MACROS_H__

#define CREATE_GRID_INIT_SUITE_FUNC(gd, rows, cols, err)                  \
        int init_suite_##rows##cols(void)                                 \
        {                                                                 \
          cuz_init_gd (&gd, rows, cols, &err);                            \
          return err.code;                                                \
        }                                                                 \

#define CREATE_RND_GRID_INIT_SUITE_FUNC(gd, rows, cols, err)              \
        int init_suite_##rows##cols(void)                                 \
        {                                                                 \
          cuz_init_gd (&gd, rows, cols, &err);                            \
          cuz_randomize_gd (&gd);                                         \
          return err.code;                                                \
        }                                                                 \

#define CREATE_SRND_GRID_INIT_SUITE_FUNC(gd, rows, cols, err, seed)       \
        int init_suite_##rows##cols(void)                                 \
        {                                                                 \
          cuz_init_gd (&gd, rows, cols, &err);                            \
          srand (seed);                                                   \
          cuz_randomize_gd (&gd);                                         \
          return err.code;                                                \
        }                                                                 \



#endif
