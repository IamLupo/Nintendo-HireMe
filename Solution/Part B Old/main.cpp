#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <set>

#include "z3++.h"

using namespace z3;
using namespace std;

void draw(const string name, const vector<int> &v) {
	int i;
	
	cout << name << " = ";
	for(i = 0; i < v.size(); i++) {
		if(i != 0)
			cout << ", ";
		
		cout << v[i];
	}
	cout << endl;
}

bool reverse_part_b(const vector<int> &input, vector<int> &output) {
	int i, j, x;
	context c;
	string name;
	vector<expr> ex;
		
	//Generate variables
	for(i = 0; i < 32; i++) {
		name = "x" + to_string(i);
		ex.push_back(c.bv_const(name.c_str(), 8));
	}

	//Make Solver
	solver s(c);
	
	//Input the rules (watch function "draw_rules_part_b")
	s.add((ex[0] ^ ex[7] ^ ex[10] ^ ex[12] ^ ex[13] ^ ex[15] ^ ex[18] ^ ex[19] ^ ex[21] ^ ex[22] ^ ex[25] ^ ex[28] ^ ex[29] ^ ex[30] ^ ex[31]) == input[0]);
	s.add((ex[1] ^ ex[4] ^ ex[7] ^ ex[10] ^ ex[11] ^ ex[12] ^ ex[14] ^ ex[15] ^ ex[16] ^ ex[18] ^ ex[21] ^ ex[23] ^ ex[25] ^ ex[26] ^ ex[28]) == input[1]);
	s.add((ex[2] ^ ex[5] ^ ex[8] ^ ex[11] ^ ex[13] ^ ex[15] ^ ex[16] ^ ex[17] ^ ex[19] ^ ex[20] ^ ex[22] ^ ex[26] ^ ex[27] ^ ex[28] ^ ex[29]) == input[2]);
	s.add((ex[3] ^ ex[6] ^ ex[9] ^ ex[12] ^ ex[14] ^ ex[17] ^ ex[18] ^ ex[20] ^ ex[21] ^ ex[23] ^ ex[24] ^ ex[27] ^ ex[28] ^ ex[29] ^ ex[30]) == input[3]);
	s.add((ex[3] ^ ex[4] ^ ex[8] ^ ex[9] ^ ex[11] ^ ex[14] ^ ex[17] ^ ex[18] ^ ex[22] ^ ex[23] ^ ex[24] ^ ex[25] ^ ex[26] ^ ex[27] ^ ex[29]) == input[4]);
	s.add((ex[0] ^ ex[3] ^ ex[5] ^ ex[8] ^ ex[10] ^ ex[11] ^ ex[14] ^ ex[15] ^ ex[17] ^ ex[19] ^ ex[20] ^ ex[22] ^ ex[24] ^ ex[29] ^ ex[30]) == input[5]);
	s.add((ex[1] ^ ex[6] ^ ex[9] ^ ex[11] ^ ex[12] ^ ex[15] ^ ex[16] ^ ex[18] ^ ex[20] ^ ex[21] ^ ex[23] ^ ex[24] ^ ex[25] ^ ex[30] ^ ex[31]) == input[6]);
	s.add((ex[2] ^ ex[7] ^ ex[8] ^ ex[10] ^ ex[13] ^ ex[16] ^ ex[17] ^ ex[19] ^ ex[21] ^ ex[22] ^ ex[24] ^ ex[25] ^ ex[26] ^ ex[28] ^ ex[31]) == input[7]);
	s.add((ex[2] ^ ex[4] ^ ex[5] ^ ex[7] ^ ex[8] ^ ex[15] ^ ex[17] ^ ex[20] ^ ex[21] ^ ex[22] ^ ex[23] ^ ex[26] ^ ex[27] ^ ex[29] ^ ex[30]) == input[8]);
	s.add((ex[2] ^ ex[3] ^ ex[4] ^ ex[6] ^ ex[7] ^ ex[9] ^ ex[12] ^ ex[15] ^ ex[17] ^ ex[18] ^ ex[20] ^ ex[24] ^ ex[26] ^ ex[29] ^ ex[31]) == input[9]);
	s.add((ex[0] ^ ex[3] ^ ex[5] ^ ex[7] ^ ex[10] ^ ex[13] ^ ex[18] ^ ex[19] ^ ex[20] ^ ex[21] ^ ex[24] ^ ex[25] ^ ex[27] ^ ex[28] ^ ex[30]) == input[10]);
	s.add((ex[1] ^ ex[4] ^ ex[6] ^ ex[11] ^ ex[14] ^ ex[16] ^ ex[19] ^ ex[20] ^ ex[21] ^ ex[22] ^ ex[25] ^ ex[26] ^ ex[28] ^ ex[29] ^ ex[31]) == input[11]);
	s.add((ex[0] ^ ex[1] ^ ex[3] ^ ex[6] ^ ex[11] ^ ex[12] ^ ex[16] ^ ex[17] ^ ex[18] ^ ex[19] ^ ex[21] ^ ex[25] ^ ex[26] ^ ex[30] ^ ex[31]) == input[12]);
	s.add((ex[0] ^ ex[2] ^ ex[3] ^ ex[6] ^ ex[7] ^ ex[8] ^ ex[11] ^ ex[13] ^ ex[16] ^ ex[21] ^ ex[22] ^ ex[25] ^ ex[27] ^ ex[28] ^ ex[30]) == input[13]);
	s.add((ex[1] ^ ex[3] ^ ex[4] ^ ex[7] ^ ex[9] ^ ex[14] ^ ex[16] ^ ex[17] ^ ex[22] ^ ex[23] ^ ex[24] ^ ex[26] ^ ex[28] ^ ex[29] ^ ex[31]) == input[14]);
	s.add((ex[0] ^ ex[2] ^ ex[5] ^ ex[10] ^ ex[15] ^ ex[16] ^ ex[17] ^ ex[18] ^ ex[20] ^ ex[23] ^ ex[24] ^ ex[25] ^ ex[27] ^ ex[29] ^ ex[30]) == input[15]);
	s.add((ex[2] ^ ex[3] ^ ex[5] ^ ex[6] ^ ex[9] ^ ex[12] ^ ex[13] ^ ex[14] ^ ex[15] ^ ex[16] ^ ex[23] ^ ex[26] ^ ex[28] ^ ex[29] ^ ex[31]) == input[16]);
	s.add((ex[0] ^ ex[2] ^ ex[5] ^ ex[7] ^ ex[9] ^ ex[10] ^ ex[12] ^ ex[17] ^ ex[20] ^ ex[23] ^ ex[26] ^ ex[27] ^ ex[28] ^ ex[30] ^ ex[31]) == input[17]);
	s.add((ex[0] ^ ex[1] ^ ex[3] ^ ex[4] ^ ex[6] ^ ex[10] ^ ex[11] ^ ex[12] ^ ex[13] ^ ex[18] ^ ex[21] ^ ex[24] ^ ex[27] ^ ex[29] ^ ex[31]) == input[18]);
	s.add((ex[1] ^ ex[2] ^ ex[4] ^ ex[5] ^ ex[7] ^ ex[8] ^ ex[11] ^ ex[12] ^ ex[13] ^ ex[14] ^ ex[19] ^ ex[22] ^ ex[25] ^ ex[28] ^ ex[30]) == input[19]);
	s.add((ex[1] ^ ex[2] ^ ex[6] ^ ex[7] ^ ex[8] ^ ex[9] ^ ex[10] ^ ex[11] ^ ex[13] ^ ex[19] ^ ex[20] ^ ex[24] ^ ex[25] ^ ex[27] ^ ex[30]) == input[20]);
	s.add((ex[1] ^ ex[3] ^ ex[4] ^ ex[6] ^ ex[8] ^ ex[13] ^ ex[14] ^ ex[16] ^ ex[19] ^ ex[21] ^ ex[24] ^ ex[26] ^ ex[27] ^ ex[30] ^ ex[31]) == input[21]);
	s.add((ex[0] ^ ex[2] ^ ex[4] ^ ex[5] ^ ex[7] ^ ex[8] ^ ex[9] ^ ex[14] ^ ex[15] ^ ex[17] ^ ex[22] ^ ex[25] ^ ex[27] ^ ex[28] ^ ex[31]) == input[22]);
	s.add((ex[0] ^ ex[1] ^ ex[3] ^ ex[5] ^ ex[6] ^ ex[8] ^ ex[9] ^ ex[10] ^ ex[12] ^ ex[15] ^ ex[18] ^ ex[23] ^ ex[24] ^ ex[26] ^ ex[29]) == input[23]);
	s.add((ex[1] ^ ex[4] ^ ex[5] ^ ex[6] ^ ex[7] ^ ex[10] ^ ex[11] ^ ex[13] ^ ex[14] ^ ex[18] ^ ex[20] ^ ex[21] ^ ex[23] ^ ex[24] ^ ex[31]) == input[24]);
	s.add((ex[1] ^ ex[2] ^ ex[4] ^ ex[8] ^ ex[10] ^ ex[13] ^ ex[15] ^ ex[18] ^ ex[19] ^ ex[20] ^ ex[22] ^ ex[23] ^ ex[25] ^ ex[28] ^ ex[31]) == input[25]);
	s.add((ex[2] ^ ex[3] ^ ex[4] ^ ex[5] ^ ex[8] ^ ex[9] ^ ex[11] ^ ex[12] ^ ex[14] ^ ex[16] ^ ex[19] ^ ex[21] ^ ex[23] ^ ex[26] ^ ex[29]) == input[26]);
	s.add((ex[0] ^ ex[3] ^ ex[4] ^ ex[5] ^ ex[6] ^ ex[9] ^ ex[10] ^ ex[12] ^ ex[13] ^ ex[15] ^ ex[17] ^ ex[20] ^ ex[22] ^ ex[27] ^ ex[30]) == input[27]);
	s.add((ex[0] ^ ex[1] ^ ex[2] ^ ex[3] ^ ex[5] ^ ex[9] ^ ex[10] ^ ex[14] ^ ex[15] ^ ex[16] ^ ex[17] ^ ex[19] ^ ex[22] ^ ex[27] ^ ex[28]) == input[28]);
	s.add((ex[0] ^ ex[5] ^ ex[6] ^ ex[9] ^ ex[11] ^ ex[12] ^ ex[14] ^ ex[16] ^ ex[18] ^ ex[19] ^ ex[22] ^ ex[23] ^ ex[24] ^ ex[27] ^ ex[29]) == input[29]);
	s.add((ex[0] ^ ex[1] ^ ex[6] ^ ex[7] ^ ex[8] ^ ex[10] ^ ex[12] ^ ex[13] ^ ex[15] ^ ex[17] ^ ex[19] ^ ex[20] ^ ex[23] ^ ex[25] ^ ex[30]) == input[30]);
	s.add((ex[0] ^ ex[1] ^ ex[2] ^ ex[4] ^ ex[7] ^ ex[8] ^ ex[9] ^ ex[11] ^ ex[13] ^ ex[14] ^ ex[16] ^ ex[18] ^ ex[21] ^ ex[26] ^ ex[31]) == input[31]);

	//Check if there is a module
	if(s.check() != sat)
		return false;
	cout << "module satified" << endl;
	
	model m = s.get_model();
	
	//Debug model
	//cout << m << endl;

	// Get results
	for(i = 0; i < m.size(); i++) {
		//Get result in module
		func_decl v = m[i];

		//Get the module expression
		expr e = m.get_const_interp(v);

		//Convert expresion to integer
		Z3_get_numeral_int(e.ctx(), e, &x);

		//Get expression name
		name = v.name().str();
		
		//Save result
		for(j = 0; j < ex.size(); j++)
			if(name.compare(ex[j].decl().name().str()) == 0)
				output[j] = x;

		//Debug
		//cout << name << " = " << e << " " << x << endl;
	}

	return true;
}

void test_part_b() {
	vector<int> input, output(32, 0);

	//Expected Output =
	//	28, 198, 36, 35,  54,  234, 48,  64,  232, 21, 82, 169, 82, 124, 163, 3, 
	//	48, 142, 27, 129, 112, 35,  104, 247, 89,  24, 50, 186, 42, 73,  223, 146
	input = {
		196, 70, 60, 153, 104, 190, 152, 29, 15, 80,  124, 155, 82, 122, 158, 204,
		66,  97, 42, 182, 61,  218, 5,   19, 58, 196, 96,  74,  23, 20,  114, 171
	};
	
	cout << "Crack Part B" << endl;
	reverse_part_b(input, output);
	
	//Debug
	draw("Output", output);
}

int main(int argc, char* argv[]) {
	test_part_b();
	
	return 0;
}