#pragma once

#include "macro.hpp"
#include "math.hpp"

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

		inline virtual data_type	get_data(uint64_t index)	{ return data[index]; }
		inline virtual label_type	get_label(uint64_t index)	{ return labels[index]; }
	};


	class Network {
	private:
		// type, columns, rows
		// input is read straigth from data input // Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>		input;
		dynamic_f64_matrix*			weights =		nullptr;
		dynamic_f64_row_vector*		biases =		nullptr;
		// it is assumed that no more than ~4e9 nodes or layers are going to be used
		uint32_t				layer_count =	0;
		uint32_t				input_size =	0;
		uint32_t				output_size =	0;

	public:
		Network(uint32_t input_size, uint32_t output_size);
		Network(uint32_t input_size, std::initializer_list<uint32_t> layers, uint32_t output_size);
		~Network();

		void init_network();
		void init_network(const char* path);
		void store_network(const char* path);
		
		dynamic_f64_column_vector calculate(const dynamic_f64_matrix& input);
	};
};