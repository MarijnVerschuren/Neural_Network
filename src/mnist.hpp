#pragma once
#include "macro.hpp"
#include "neural_network.hpp"



namespace Mnist {
	class Data_Set : public Neural::Data<int8_t, Eigen::Matrix<double, 28, 28>> {
	public:
		Data_Set(const char* label_file_name, const char* data_file_name, uint64_t max_length = -1);
		inline Eigen::Matrix<double, 28, 28>	get_data(uint64_t index)	override { return data[index]; }
		inline int8_t							get_label(uint64_t index)	override { return labels[index]; }
	};

	void print_mnist_data(const Eigen::Matrix<double, 28, 28>& dat);
}