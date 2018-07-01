#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "morphlib.h"

using namespace std;
using namespace morph;
using namespace chrono;

void apply_erosion(BinaryImage& img, BinaryImage& out) {
	for (int y = 0; y < img.height; ++y) {
		for (int x = 0; x < img.width; ++x) {
			bool hit = false;
			for (int i = 0; i < 16; ++i) {
				int dy = (i / 4) - 1;
				int dx = (i % 4) - 1;
				if (img.pixel(x + dx, y + dy)) {
					hit = true;
					break;
				}
			}

			out.set_pixel(x, y, hit);
		}
	}
}

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("Usage: morph <infile> <outfile>\n");
		return -1;
	} 

	BinaryImage img(argv[1]);
	printf("Width %d, height %d\n", img.width, img.height);

	BinaryImage out(img.width, img.height, new char[img.width * img.height]);

	auto start = high_resolution_clock::now();
	apply_erosion(img, out);
	auto end = high_resolution_clock::now();

	auto time_span = duration_cast<duration<double>>(end - start);

	printf("Erosion operation spent %lfs.\n", time_span.count());

	out.write(argv[2]);

	system("pause");
}