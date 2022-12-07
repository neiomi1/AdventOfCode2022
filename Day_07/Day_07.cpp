#include "Day_07.h"

#include <chrono>
#include <sstream>


inline Directory read_entries(const std::string& filename) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_07\\" + filename };
	std::string line;


	std::vector<File> files;
	std::vector<Directory> subdirs;
	std::string name = "/";
	auto root = Directory(name, subdirs, files);

	auto current_dir = &root;
	long long mode = 0;

	std::cout << current_dir->name << "\n";

	std::vector<File> subdirfiles;
	std::vector<Directory> subdirsubdirs;
	std::string dirname;
	std::string fname;
	std::string ftype;

	while (std::getline(file, line)) {
		// check if command

		std::cout << current_dir->name << " at the moment :" << line << "\n";
		if (line[0] == '$') {
			mode = 0;
			auto it = line.find("cd");
			if (it < line.size()) {
				if (line.at(it+3) == '.') {
					current_dir = (*current_dir).parentDirectory;
					continue;
				}
				else {
					dirname = (line.substr(5));
					for (size_t i = 0; i < current_dir->subdirectories.size(); i++) {	
						if (current_dir->subdirectories.at(i).name == dirname) {
							current_dir = &current_dir->subdirectories.at(i);
							break;
						}
					}
					if (current_dir->name != dirname) {
						std::cout << "Could not find Directory '" << dirname << "' vs "  << current_dir->name << "\n";
					}
				}
				continue;
			}
			auto pos = line.find("ls");
			if (pos < line.size()) {
				mode = 1;
				continue;
			}
		}
		else {
			if (mode == 1) {
				if (line.substr(0, 3) == "dir") {
					dirname = line.substr(4);
					Directory child_dir(dirname, subdirsubdirs,subdirfiles);
					child_dir.parentDirectory = current_dir;
					current_dir->subdirectories.push_back(child_dir);
				}
				else {
					long long size;
					std::string _filename;
					std::istringstream(line) >> size >> _filename;
					auto dot = _filename.find(".");
					fname = _filename.substr(0, dot);
					ftype = _filename.substr(++dot);
					File f(fname, ftype, size);
					current_dir->size += size;
					current_dir->files.push_back(f);
				}
			}
		}

	}
	return root;
}

inline long long size(Directory* dir, long long max,long long& total) {
	long long current_size = 0;
	for (File& file : dir->files) {
		current_size += file.size;
	}
	for (Directory& subdir : dir->subdirectories) {
		current_size += size(&subdir, max, total);
	}
	if (current_size <= max) {
		total += current_size;
	}
	dir->size = current_size;
	return current_size;
}

inline void smallest_free(Directory* dir, long long required_space, long long& current_max, std::string& name) {
	std::cout << dir->name << " " << dir->size << " > " << required_space << " ? " << (dir->size > required_space) << " current " << current_max << " by " << name <<" smaller? " << (dir->size < current_max) << "\n";
	if (dir->size > required_space && dir->size < current_max) {
		current_max = dir->size;
		name = dir->name;
		for (Directory& subdir : dir->subdirectories) {
			smallest_free(&subdir, required_space, current_max, name);
		}
	}
}



int main() {
	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_06\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	auto root = read_entries("input.txt");
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";


	long long total = 0;
	start = std::chrono::high_resolution_clock::now();
	size(&root, (long long)100000, total);
	stop = std::chrono::high_resolution_clock::now();
	std::cout << "Sum of all Directories smaller than" << 100000 << ": " << total << "\n";
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 1 in " << duration.count() << " microseconds.\n";

	long long required = 30000000, max = 70000000;
	long long free_space = max - root.size;
	required -= free_space;
	std::string name;
	start = std::chrono::high_resolution_clock::now();
	smallest_free(&root, required , max, name);
	stop = std::chrono::high_resolution_clock::now();
	std::cout << std::format("Smallest Directory with {} size is '{}' with size {}", required, name, max) <<"\n";
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Calculated Part 2 in " << duration.count() << " microseconds.\n";

}

