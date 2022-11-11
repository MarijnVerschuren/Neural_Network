#pragma once

#include "macro.hpp"

#include <cstdarg>
#include <Eigen/Dense>



namespace Neural {
	template<typename label_type, typename data_type>
	struct Data {
		label_type*	labels =	nullptr;
		data_type*	data =		nullptr;
		uint64_t		count =	0;

		~Data() {
			if (labels != nullptr)	{ delete[] labels; }
			if (data != nullptr)	{ delete[] data; }
		}

		void Initialize(const uint64_t count) {
			this->labels = new label_type[count];
			this->data = new data_type[count];
			this->count = count;
		}
	};


	template<uint64_t input_size, uint64_t output_size>
	class Network {
	private:
		// type, columns, rows
		Eigen::Matrix<double, Eigen::Dynamic, input_size>			input;
		Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>*		weights =		nullptr;
		Eigen::Matrix<double, Eigen::Dynamic, 1>*					biases =		nullptr;
		uint64_t													layer_count =	0;

	public:
		Network() {
			weights = new Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>(output_size, input_size);
			biases = new Eigen::Matrix<double, Eigen::Dynamic, 1>(input_size);
			layer_count = 1;
		}
		Network(uint64_t hidden_layer_count, ...) {
			weights = new Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>[hidden_layer_count + 1];
			biases = new Eigen::Matrix<double, Eigen::Dynamic, 1>[hidden_layer_count + 1];
			layer_count = hidden_layer_count + 1;

			uint64_t			i = 0;
			uint64_t			arg;
			uint64_t			in_size = input_size;
			std::va_list	list;
			va_start(list, hidden_layer_count);

			for (; i < hidden_layer_count; i++) {
				arg = va_arg(list, uint64_t);
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
			delete &input;
		}

		// Eigen::Matrix<double, Eigen::Dynamic, output_size>
	};
};