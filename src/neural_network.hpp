#pragma once

#include "macro.hpp"

#include <initializer_list>
#include <Eigen/Dense>



namespace Neural {
	template<typename label_type, typename data_type>
	struct Data {
		label_type*	labels =	nullptr;
		data_type*	data =		nullptr;
		uint64_t	count =		0;

		~Data() {
			if (labels != nullptr)	{ delete[] labels; }
			if (data != nullptr)	{ delete[] data; }
		}
	};


	class Network {
	private:
		// type, columns, rows
		// input is read straigth from data input // Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>		input;
		Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>*		weights =		nullptr;
		Eigen::Matrix<double, Eigen::Dynamic, 1>*					biases =		nullptr;
		uint64_t													layer_count =	0;

	public:
		Network(uint64_t input_size, uint64_t output_size);
		Network(uint64_t input_size, std::initializer_list<uint64_t> layers, uint64_t output_size);
		~Network();

		void init_network();
		void init_network(const char* path);
		void store_network(const char* path);
		// Eigen::Matrix<double, Eigen::Dynamic, output_size>
	};
};