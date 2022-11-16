#include "macro.hpp"
#include "neural_network.hpp"
#include "mnist.hpp"

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cmath>



int main(int argc, char** argv) {
	Math::init_random();  // set seed using random device (random device is wayyy to slow to work continuosly)

	// 784 => 16 => 16 => 10
	Neural::Network net(784, { 16, 16 }, 10);
	net.init_network();  // init with random wieghts and biasses for now

	uint16_t data_count = 200;
	Mnist::Data_Set dat("dat/test_labels.idx1-ubyte", "dat/test_images.idx3-ubyte", data_count);
	for (uint8_t i = 0; i < data_count; i++) {
		Mnist::print_mnist_data(dat.get_data(i));
		auto res = net.calculate(dat.get_data(i));
		uint16_t index = 0;  // find max
		std::cout << res << "\n";
		for (uint16_t j = 0; j < 10; j++) { if (res[j] > res[index]) { res[index] = res[j];  index = j; } }
		std::cout << "calc: " << index << "\t\tans: " << (int)dat.get_label(i) << "\n";
	}

	// programm cant exit propperly due to eigen matrecies that are still allocated
	return 0;
}

// https://www.youtube.com/watch?v=tIeHLnjs5U8&list=WL&index=2  math
// https://aleksandarhaber.com/starting-with-eigen-c-matrix-library/  use when arrived at math section
// http://yann.lecun.com/exdb/mnist/


/*  // init with array
float data[] = {1,2,3,4};
Map<Vector3f> v1(data);       // uses v1 as a Vector3f object
Map<ArrayXf>  v2(data,3);     // uses v2 as a ArrayXf object
Map<Array22f> m1(data);       // uses m1 as a Array22f object
Map<MatrixXf> m2(data,2,2);   // uses m2 as a MatrixXf object
*/

/*  // vec * mat
Eigen::Matrix<double, 2, 2> mat;
mat(0, 0) = 1;
mat(1, 0) = 2;
mat(0, 1) = 3;
mat(1, 1) = 4;
Eigen::Matrix<double, 2, 1> vec;
vec(0) = 1;
vec(1) = 2;

std::cout << mat * 0.25 << "\n";
std::cout << vec * 0.25 << "\n";
std::cout << mat * vec << "\n";
*/


// idea:
// network => network core
// mnist gets own network class with apropriate code
// network core gets virtual functions
// or make generalized verison and implement it


/* console app idea:
	[================================]
	[			VARIABLES			 ]
	[			VARIABLES			 ]
	[  NEURONS / WEIGHTS / BIASSSES  ]
	[  NEURONS / WEIGHTS / BIASSSES  ]
	[  NEURONS / WEIGHTS / BIASSSES  ]
	[  NEURONS / WEIGHTS / BIASSSES  ]
	[		OPTIONS / KEYBINDS		 ]
	[================================]

	display all relevant non weight / bias value up top
	
	display for a givven layer its neurons with weights / biases
	make options to display these as arrays or images

	add all options / keybinds
*/