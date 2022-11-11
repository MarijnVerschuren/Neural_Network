#include "mnist.hpp"

#include <fstream>
#include <iostream>



Mnist::Data_Set::Data_Set(const char* label_file_name, const char* data_file_name, uint64_t max_length) {
	uint64_t label_count = 0;
	uint64_t data_count = 0;

	std::fstream label_file(label_file_name, std::fstream::in | std::fstream::ate | std::fstream::binary);
	std::fstream data_file(data_file_name, std::fstream::in | std::fstream::ate | std::fstream::binary);

	if ((!label_file || !label_file.is_open()) || (!data_file || !data_file.is_open())) { return; }

	const uint64_t label_file_size = label_file.tellg();
	const uint64_t data_file_size = data_file.tellg();
	label_file.seekg(4);
	data_file.seekg(4);

	label_file.read((char*)&label_count, 4);
	data_file.read((char*)&data_count, 4);
	data_file.seekg(16);  // skip the row and column count we asume 28x28 (this doesnt change troughout this dataset)

	if (label_count != data_count) { return; }
	count = BS32(label_count);  // file format stores data in big_endian form
	if (count > max_length) { count = max_length; }

	this->labels =	new int8_t[count];
	this->data =	new mnist_data[count];
	this->count =	count;

	label_file.read((char*)labels, count);
	int8_t temp_buffer[784];
	for (uint64_t i = 0; i < count; i++) {
		data_file.read((char*)temp_buffer, 784);
		// cast image data to double and normalizing it from a range of [0, 255] to a range of [0, 1]
		data[i] = Eigen::Map<Eigen::Matrix<uint8_t, 28, 28>>((uint8_t*)temp_buffer).cast<double>() / 255;
	}

	label_file.close();
	data_file.close();
}

void Mnist::print_mnist_data(const Data_Set* dat) {
	uint8_t current;
	for (uint64_t i = 0; i < dat->count; i++) {
		for (uint8_t j = 0; j < 28; j++) {
			for (uint8_t k = 0; k < 28; k++) {
				current = (uint8_t)std::round(dat->data[i](k, j) * 255);
				if (current > 127) { printf("\033[7m..\033[m"); }  // "%02x", current
				else if (current != 0) { printf("\033[100m..\033[m"); }  // "%02x", current
				else { printf("\033[0m..\033[m"); }  // "00"
			}
			printf("\n");
		}
		printf(" => %d\n\n", dat->labels[i]);
	}
}