#include "argumented-definitions.h"

#include <cstdarg>
#include <iostream>
#include <sstream>

#define SIMPLE_LOG(var_name) \
std::cout << #var_name << ": " << var_name << std::endl

static std::string strip_name(const std::string &name) {
  size_t pos = name.rfind('/');
  return pos == std::string::npos ? name : name.substr(pos + 1);
}

static std::string get_header(int line, const char *func, const char *file) {
  return "LOG: [" + strip_name(file) + "::" + func + "::" + std::to_string(line) + "]  ";
}

template<typename T>
static void more_complicated_log(const char *var_name, const T &val, int line, const char *func, const char *file) {
  std::cout << get_header(line, func, file) << var_name << ": " << val << std::endl;
}

#define MORE_COMPLICATED_LOG(var_name) more_complicated_log(#var_name, var_name, __LINE__, __FUNCTION__, __FILE__)


#define FIELD_GENERATOR(type, name, default_val)      \
public:                                               \
type get_##name() const {                             \
  return name;                                        \
}                                                     \
void set_##name(const type &val) {                    \
  name = val;                                         \
}                                                     \
private:                                              \
type name{default_val}

struct tmp_t {
  tmp_t() = default;

FIELD_GENERATOR(int, a, 10);
FIELD_GENERATOR(std::string, str, "abacaba");
FIELD_GENERATOR(double, d, 0.1);
};

static void log_printf_internal(int line, const char *func, const char *file, const char *fmt, ...) {
  va_list va;
  va_start(va, fmt);
  printf("%s", get_header(line, func, file).c_str());
  vprintf(fmt, va);
  va_end(va);
}

#define SUPER_PRINTF_LOG(fmt, ...) log_printf_internal(__LINE__, __FUNCTION__, __FILE__, fmt, ##__VA_ARGS__)


class logger_t {
public:
  logger_t(int line, const char *func, const char *file) :
    line(line),
    func(func),
    file(file),
    ss() {}

  ~logger_t() {
    std::cout << get_header(line, func.c_str(), file.c_str()) << ss.str();
  }

  std::stringstream &get() {
    return ss;
  }

private:
  int line;
  std::string func;
  std::string file;

  std::stringstream ss;
};

#define SUPER_SS_LOG logger_t(__LINE__, __FUNCTION__, __FILE__).get()

void check_argumented_definitions() {
  int a = 10;
  SIMPLE_LOG(a);
  SIMPLE_LOG(1);
  MORE_COMPLICATED_LOG(a);

  tmp_t tmp;
  tmp.set_a(12);
  tmp.set_str("Lol");

  MORE_COMPLICATED_LOG(tmp.get_a());
  #line 1000000
  SUPER_PRINTF_LOG("tmp.get_str(): %s\n", tmp.get_str().c_str());
  SUPER_PRINTF_LOG("int a: %d; int d: %lf\n", tmp.get_a(), tmp.get_d());

  SUPER_PRINTF_LOG("Abacaba\n");

  #line 150 "strange-file.cpp"

  SUPER_SS_LOG << "tmp.get_d(): " << tmp.get_d() << std::endl;
}
