#pragma once

#define ASSERT(condition, message)                                             \
  {                                                                            \
    if (condition) {                                                           \
      std::cerr << message << std::endl;                                       \
      exit(1);                                                                 \
    }                                                                          \
  }

#define PANIC(condition, message)                                              \
  {                                                                            \
    if (condition) {                                                           \
      throw std::runtime_error(message);                                       \
    }                                                                          \
  }
