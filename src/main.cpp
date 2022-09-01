#include "macro.hpp"
#include "neural_network.hpp"
#include "mnist.hpp"

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cmath>



int main(int argc, char** argv) {
	// 728 => 16 => 16 => 10
	Neural::Network<728, 10> net(2, 16, 16);

	Mnist::Data_Set dat("dat/test_labels.idx1-ubyte", "dat/test_images.idx3-ubyte", 200);
	Mnist::print_mnist_data(&dat);  // print data

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
Eigen::Matrix<f64, 2, 2> mat;
mat(0, 0) = 1;
mat(1, 0) = 2;
mat(0, 1) = 3;
mat(1, 1) = 4;
Eigen::Matrix<f64, 2, 1> vec;
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