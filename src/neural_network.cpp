#include "neural_network.hpp"



Neural::Network::Network(uint32_t input_size, uint32_t output_size) {
	this->weights = new Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>(output_size, input_size);
	this->biases = new Eigen::Matrix<double, Eigen::Dynamic, 1>(input_size);
	this->layer_count = 1;
	this->input_size = input_size;
	this->output_size = output_size;
}
Neural::Network::Network(uint32_t input_size, std::initializer_list<uint32_t> layers, uint32_t output_size) {
	uint32_t hidden_layer_count = layers.size();
	this->weights = new Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>[hidden_layer_count + 1];
	this->biases = new Eigen::Matrix<double, Eigen::Dynamic, 1>[hidden_layer_count + 1];
	this->layer_count = hidden_layer_count + 1;
	this->input_size = input_size;
	this->output_size = output_size;

	uint32_t		i = 0;
	uint32_t		in_size = input_size;

	for (uint32_t size : layers) {
		this->weights[i].resize(size, in_size);
		this->biases[i].resize(size);
		in_size = size; i++;
	}

	this->weights[hidden_layer_count].resize(output_size, in_size);
	this->biases[hidden_layer_count].resize(output_size);

	return;
}
Neural::Network::~Network() {
	delete[] this->weights;
	delete[] this->biases;
}

// init network with random weights and biasses
void Neural::Network::init_network() {
	uint32_t rows, cols;
	for (uint32_t i = 0; i < this->layer_count; i++) {
		rows = this->weights[i].rows();  // same as bias.rows
		cols = this->weights[i].cols();
		for (uint32_t j = 0; j < rows; j++) {
			this->biases[i](j, 0) = Math::rand_uniform(-5, 5);
			for (uint32_t k = 0; k < cols; k++) {
				this->weights[i](j, k) = Math::rand_uniform(-5, 5);
			}
		}
	}
}
// TODO: load from file
void Neural::Network::init_network(const char* path) {

}
// TODO: store in file
void Neural::Network::store_network(const char* path) {

}

dynamic_f64_column_vector Neural::Network::calculate(const dynamic_f64_matrix& input) {
	// it is assumed that the input data is normalized (between 0 and 1), and that the right ammount of data is passed
	dynamic_f64_row_vector accumulator = (this->weights[0] * input.reshaped(this->input_size, 1) + this->biases[0]);
	// accumulator = 1 / (1 + accumulator.exp());
	for (uint32_t i = 1;; i++) {
		for (uint32_t j = 0; j < accumulator.rows(); j++) { accumulator(j, 0) = Math::sigma(accumulator(j, 0)); }
		if (i == this->layer_count) { break; }
		accumulator = (this->weights[i] * accumulator + this->biases[i]);
	}
	return accumulator;
}