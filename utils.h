#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED

char* l_trim(char* s, char what = ' ');

char* r_trim(char* s, char what = ' ');

char* trim(char* s, char what = ' ');

char* get_file_extension(const char* file);

bool is_extension_supported(const char* extension);

#define custom_min(x, y) ((x) < (y) ? (x) : (y))
#define custom_max(x, y) ((x) > (y) ? (x) : (y))

#endif // UTILS_INCLUDED
