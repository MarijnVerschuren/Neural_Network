#include "mnist.hpp"

#include <fstream>
#include <iostream>



Mnist::Data_Set::Data_Set(const char* label_file_name, const char* data_file_name, uint32 max_length) {
	uint32 label_count = 0;
	uint32 data_count = 0;

	std::fstream label_file(label_file_name, std::fstream::in | std::fstream::ate | std::fstream::binary);
	std::fstream data_file(data_file_name, std::fstream::in | std::fstream::ate | std::fstream::binary);

	if ((!label_file || !label_file.is_open()) || (!data_file || !data_file.is_open())) { return; }

	const uint64 label_file_size = label_file.tellg();
	const uint64 data_file_size = data_file.tellg();
	label_file.seekg(4);
	data_file.seekg(4);

	label_file.read((int8*)&label_count, 4);
	data_file.read((int8*)&data_count, 4);
	data_file.seekg(16);  // skip the row and column count we asume 28x28 (this doesnt change troughout this dataset)

	if (label_count != data_count) { return; }
	count = BS32(label_count);  // file format stores data in big_endian form
	if (count > max_length) { count = max_length; }

	Initialize(count);

	label_file.read(labels, count);
	int8 temp_buffer[784];
	for (uint32 i = 0; i < count; i++) {
		data_file.read(temp_buffer, 784);
		// cast image data to f64 and normalizing it from a range of [0, 255] to a range of [0, 1]
		data[i] = Eigen::Map<Eigen::Matrix<uint8, 28, 28>>((uint8*)temp_buffer).cast<f64>() / 255;
	}

	label_file.close();
	data_file.close();
}

void Mnist::print_mnist_data(const Data_Set* dat) {
	uint8 current;
	for (uint32 i = 0; i < dat->count; i++) {
		for (uint32 j = 0; j < 28; j++) {
			for (uint32 k = 0; k < 28; k++) {
				current = (uint8)std::round(dat->data[i](k, j) * 255);
				if (current > 127) { printf("\033[7m..\033[m"); }  // "%02x", current
				else if (current != 0) { printf("\033[100m..\033[m"); }  // "%02x", current
				else { printf("\033[0m..\033[m"); }  // "00"
			}
			printf("\n");
		}
		printf(" => %d\n\n", dat->labels[i]);
	}
}