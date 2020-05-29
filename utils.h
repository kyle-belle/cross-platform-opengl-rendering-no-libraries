#ifndef UTILS_INCLUDED
#define UTILS_INCLUDED
#include <string.h>
#include <functional>

struct cmp_str
{
public:
   bool operator()(const char* a, const char* b)
   {
      return !strcmp(a, b);
   }
};

char* l_trim(char* s, char what = ' ');

char* r_trim(char* s, char what = ' ');

char* trim(char* s, char what = ' ');

/* std::vector<char*> */char** split(const char* s, unsigned int* count, char splitter = ' ');

char* get_file_extension(const char* file);

bool is_extension_supported(const char* extension);
#define str_equals(lhs, rhs) (!strcmp(lhs, rhs))
#define str_equals_case_insensitive(lhs, rhs) (!strcasecmp(lhs, rhs))
#define custom_min(x, y) ((x) < (y) ? (x) : (y))
#define custom_max(x, y) ((x) > (y) ? (x) : (y))

#endif // UTILS_INCLUDED
