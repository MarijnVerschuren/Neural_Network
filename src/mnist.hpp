#pragma once
#include "macro.hpp"
#include "neural_network.hpp"



namespace Mnist {
	typedef Eigen::Matrix<double, 28, 28> mnist_data;

	struct Data_Set : public Neural::Data<int8_t, mnist_data> {
		Data_Set(const char* label_file_name, const char* data_file_name, uint64_t max_length = -1);
	};

	void print_mnist_data(const Data_Set* dat);
}