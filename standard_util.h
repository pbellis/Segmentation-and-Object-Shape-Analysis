#include <functional>
#include <chrono>
#include <string>
#include <vector>
#include <Windows.h>

long long timeit(std::function<void()> func);
//void files_in_directory(const std::string &dir, std::vector<const std::string> &files);