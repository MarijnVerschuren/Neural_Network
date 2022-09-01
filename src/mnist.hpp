#pragma once
#include "macro.hpp"
#include "neural_network.hpp"



namespace Mnist {
	struct Data_Set : public Neural::Data<int8, Eigen::Matrix<f64, 28, 28>> {
		Data_Set(const char* label_file_name, const char* data_file_name, uint32 max_length = -1);
	};

	void print_mnist_data(const Data_Set* dat);
}