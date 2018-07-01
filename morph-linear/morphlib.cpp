#include "morphlib.h"

#include <iostream>
#include <fstream>

void write_int(std::ostream& stream, int value) {
	stream.put((value >> 24) & 0xFF);
	stream.put((value >> 16) & 0xFF);
	stream.put((value >> 8 ) & 0xFF);
	stream.put((value      ) & 0xFF);
}

int read_int(std::istream& stream) {
	char b3, b2, b1, b0;
	stream.get(b3).get(b2).get(b1).get(b0);
	int ret = (b3 << 24) | (b2 << 16) | (b1 << 8) | (b0 & 0xFF);
	return ret;
}

namespace morph {
	
	BinaryImage::BinaryImage(const std::string& path) {
		std::ifstream ifs;
		ifs.open(path.c_str(), std::ifstream::in);

		std::cout << "Open file " << path << ", " << ifs.good() << std::endl;

		width = read_int(ifs);
		height = read_int(ifs);

		int size = width * height;
		bytes = new char[size];

		ifs.read(bytes, size);
		ifs.close();
	}

	BinaryImage::BinaryImage(int _w, int _h, char* _data)
		: width(_w), height(_h), bytes(_data) {}

	BinaryImage::~BinaryImage() {
		delete[] bytes;
	}

	void BinaryImage::write(const std::string& path) {
		std::ofstream ofs;
		ofs.open(path.c_str(), std::ofstream::out);

		write_int(ofs, width);
		write_int(ofs, height);

		ofs.write(bytes, width * height);

		ofs.close();
	}

};
