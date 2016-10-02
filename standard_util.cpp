#include "standard_util.h"

long long timeit(std::function<void()> func) {
	auto begin = std::chrono::high_resolution_clock::now();

	func();

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

	return duration;
}

// TODO
// Make platform independant
/*void files_in_directory(const std::string &dir, std::vector<const std::string> &files) {
	HANDLE dir_handle;
	WIN32_FIND_DATA file_data;

	if ((dir_handle = FindFirstFile((dir + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE) {
		return;
	}
	else {
		do {
			const std::string file_name = file_data.cFileName;
			const std::string full_file_name = dir + "/" + file_name;
			const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

			if (file_name[0] == '.') continue;
			if (is_directory) continue;

			files.push_back(full_file_name);

		} while (FindNextFile(dir_handle, &file_data));
	}
}*/