#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>


struct File {
	long long size;
	 std::string name;
	 std::string filetype;

	File( std::string name,  std::string filetype) : name(name), filetype(filetype){ };
	File( std::string name,  std::string filetype, long long size) : name(name), filetype(filetype), size(size) {};
	~File() {};
};

struct Directory {
	std::vector<Directory> subdirectories;
	Directory *parentDirectory;
	std::vector<File> files;
	 std::string name;
	long long size;

	Directory( std::string name, std::vector<Directory>& subdirectories, std::vector<File>& files) : name(name), subdirectories(subdirectories), files(files) {};
	~Directory() {};
};

inline Directory read_entries(const std::string& filename);


inline long long size(Directory* dir, int max, long long& total);
inline void smallest_free(Directory* dir, long long required_space, long long& current_max, std::string& name);
