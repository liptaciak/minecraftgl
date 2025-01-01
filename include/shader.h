#ifndef SHADER_H
#define SHADER_H

#include <stdbool.h>

unsigned int create_shader(const char *vertex_path, const char *fragment_path);
void use_shader(unsigned int id);

void set_bool(unsigned int id, const char *name, bool value);
void set_int(unsigned int id, const char *name, int value);
void set_float(unsigned int id, const char *name, float value);

#endif /* SHADER_H */
