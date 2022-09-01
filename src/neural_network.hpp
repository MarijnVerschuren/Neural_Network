#pragma once

#include "macro.hpp"

#include <cstdarg>
#include <Eigen/Dense>



namespace Neural {
	template<typename label_type, typename data_type>
	struct Data {
		label_type*	labels =	nullptr;
		data_type*	data =		nullptr;
		uint64		count =	0;

		~Data() {
			if (labels != nullptr)	{ delete[] labels; }
			if (data != nullptr)	{ delete[] data; }
		}

		void Initialize(const uint64 count) {
			this->labels = new label_type[count];
			this->data = new data_type[count];
			this->count = count;
		}
	};


	template<uint64 input_size, uint64 output_size>
	class Network {
	private:
		// type, columns, rows
		Eigen::Matrix<f64, Eigen::Dynamic, input_size>			input;
		Eigen::Matrix<f64, Eigen::Dynamic, Eigen::Dynamic>*		weights =		nullptr;
		Eigen::Matrix<f64, Eigen::Dynamic, 1>*					biases =		nullptr;
		uint64													layer_count =	0;

	public:
		Network() {
			weights = new Eigen::Matrix<f64, Eigen::Dynamic, Eigen::Dynamic>(output_size, input_size);
			biases = new Eigen::Matrix<f64, Eigen::Dynamic, 1>(input_size);
			layer_count = 1;
		}
		Network(uint64 hidden_layer_count, ...) {
			weights = new Eigen::Matrix<f64, Eigen::Dynamic, Eigen::Dynamic>[hidden_layer_count + 1];
			biases = new Eigen::Matrix<f64, Eigen::Dynamic, 1>[hidden_layer_count + 1];
			layer_count = hidden_layer_count + 1;

			uint64			i = 0;
			uint64			arg;
			uint64			in_size = input_size;
			std::va_list	list;
			va_start(list, hidden_layer_count);

			for (; i < hidden_layer_count; i++) {
				arg = va_arg(list, uint64);
				weights[i].resize(arg, in_size);
				biases[i].resize(arg);
				in_size = arg;
			}

			va_end(list);

			weights[hidden_layer_count].resize(output_size, in_size);
			biases[hidden_layer_count].resize(output_size);

			return;
		}
		~Network() {
			delete[] weights;
			delete[] biases;
			input.resize(0, 0);  // make sure the data is unalocated
		}

		// Eigen::Matrix<f64, Eigen::Dynamic, output_size>
	};
};