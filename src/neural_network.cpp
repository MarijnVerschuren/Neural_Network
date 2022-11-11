#include "neural_network.hpp"



Neural::Network::Network(uint64_t input_size, uint64_t output_size) {
	weights = new Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>(output_size, input_size);
	biases = new Eigen::Matrix<double, Eigen::Dynamic, 1>(input_size);
	layer_count = 1;
}
Neural::Network::Network(uint64_t input_size, std::initializer_list<uint64_t> layers, uint64_t output_size) {
	uint64_t hidden_layer_count = layers.size();
	weights = new Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>[hidden_layer_count + 1];
	biases = new Eigen::Matrix<double, Eigen::Dynamic, 1>[hidden_layer_count + 1];
	layer_count = hidden_layer_count + 1;

	uint64_t		i = 0;
	uint64_t		in_size = input_size;

	for (uint64_t size : layers) {
		weights[i].resize(size, in_size);
		biases[i].resize(size);
		in_size = size;
	}

	weights[hidden_layer_count].resize(output_size, in_size);
	biases[hidden_layer_count].resize(output_size);

	return;
}
Neural::Network::~Network() {
	delete[] weights;
	delete[] biases;
}

void Neural::Network::init_network() {

}
void Neural::Network::init_network(const char* path) {

}
void Neural::Network::store_network(const char* path) {

}