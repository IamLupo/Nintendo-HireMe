#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

/*
	Part A:
		for(u8 j=0;j<32;j++) {
			output[j]=confusion[input[j]];
			input[j]=0;
		}
		
	Part B:
		for(u8 j=0;j<32;j++)
			for(u8 k=0;k<32;k++)
				input[j]^=output[k]*((diffusion[j]>>k)&1);
	
	Part C:
		for(u8 i=0;i<16;i++)
			output[i]=confusion[input[i*2]]^confusion[input[i*2+1]+256];
*/

static vector<int> confusion_a = {
	0xac,0xd1,0x25,0x94,0x1f,0xb3,0x33,0x28,0x7c,0x2b,0x17,0xbc,0xf6,0xb0,0x55,0x5d,
	0x8f,0xd2,0x48,0xd4,0xd3,0x78,0x62,0x1a,0x02,0xf2,0x01,0xc9,0xaa,0xf0,0x83,0x71,
	0x72,0x4b,0x6a,0xe8,0xe9,0x42,0xc0,0x53,0x63,0x66,0x13,0x4a,0xc1,0x85,0xcf,0x0c,
	0x24,0x76,0xa5,0x6e,0xd7,0xa1,0xec,0xc6,0x04,0xc2,0xa2,0x5c,0x81,0x92,0x6c,0xda,
	0xc6,0x86,0xba,0x4d,0x39,0xa0,0x0e,0x8c,0x8a,0xd0,0xfe,0x59,0x96,0x49,0xe6,0xea,
	0x69,0x30,0x52,0x1c,0xe0,0xb2,0x05,0x9b,0x10,0x03,0xa8,0x64,0x51,0x97,0x02,0x09,
	0x8e,0xad,0xf7,0x36,0x47,0xab,0xce,0x7f,0x56,0xca,0x00,0xe3,0xed,0xf1,0x38,0xd8,
	0x26,0x1c,0xdc,0x35,0x91,0x43,0x2c,0x74,0xb4,0x61,0x9d,0x5e,0xe9,0x4c,0xbf,0x77,
	0x16,0x1e,0x21,0x1d,0x2d,0xa9,0x95,0xb8,0xc3,0x8d,0xf8,0xdb,0x34,0xe1,0x84,0xd6,
	0x0b,0x23,0x4e,0xff,0x3c,0x54,0xa7,0x78,0xa4,0x89,0x33,0x6d,0xfb,0x79,0x27,0xc4,
	0xf9,0x40,0x41,0xdf,0xc5,0x82,0x93,0xdd,0xa6,0xef,0xcd,0x8d,0xa3,0xae,0x7a,0xb6,
	0x2f,0xfd,0xbd,0xe5,0x98,0x66,0xf3,0x4f,0x57,0x88,0x90,0x9c,0x0a,0x50,0xe7,0x15,
	0x7b,0x58,0xbc,0x07,0x68,0x3a,0x5f,0xee,0x32,0x9f,0xeb,0xcc,0x18,0x8b,0xe2,0x57,
	0xb7,0x49,0x37,0xde,0xf5,0x99,0x67,0x5b,0x3b,0xbb,0x3d,0xb5,0x2d,0x19,0x2e,0x0d,
	0x93,0xfc,0x7e,0x06,0x08,0xbe,0x3f,0xd9,0x2a,0x70,0x9a,0xc8,0x7d,0xd8,0x46,0x65,
	0x22,0xf4,0xb9,0xa2,0x6f,0x12,0x1b,0x14,0x45,0xc7,0x87,0x31,0x60,0x29,0xf7,0x73
};

static vector<int> confusion_b = {
	0x2c,0x97,0x72,0xcd,0x89,0xa6,0x88,0x4c,0xe8,0x83,0xeb,0x59,0xca,0x50,0x3f,0x27,
	0x4e,0xae,0x43,0xd5,0x6e,0xd0,0x99,0x7b,0x7c,0x40,0x0c,0x52,0x86,0xc1,0x46,0x12,
	0x5a,0x28,0xa8,0xbb,0xcb,0xf0,0x11,0x95,0x26,0x0d,0x34,0x66,0x22,0x18,0x6f,0x51,
	0x9b,0x3b,0xda,0xec,0x5e,0x00,0x2a,0xf5,0x8f,0x61,0xba,0x96,0xb3,0xd1,0x30,0xdc,
	0x33,0x75,0xe9,0x6d,0xc8,0xa1,0x3a,0x3e,0x5f,0x9d,0xfd,0xa9,0x31,0x9f,0xaa,0x85,
	0x2f,0x92,0xaf,0x67,0x78,0xa5,0xab,0x03,0x21,0x4f,0xb9,0xad,0xfe,0xf3,0x42,0xfc,
	0x17,0xd7,0xee,0xa3,0xd8,0x80,0x14,0x2e,0xa0,0x47,0x55,0xc4,0xff,0xe5,0x13,0x3f,
	0x81,0xb6,0x7a,0x94,0xd0,0xb5,0x54,0xbf,0x91,0xa7,0x37,0xf1,0x6b,0xc9,0x1b,0xb1,
	0x3c,0xb6,0xd9,0x32,0x24,0x8d,0xf2,0x82,0xb4,0xf9,0xdb,0x7d,0x44,0xfb,0x1e,0xd4,
	0xea,0x5d,0x35,0x69,0x23,0x71,0x57,0x01,0x06,0xe4,0x55,0x9a,0xa4,0x58,0x56,0xc7,
	0x4a,0x8c,0x8a,0xd6,0x6a,0x49,0x70,0xc5,0x8e,0x0a,0x62,0xdc,0x29,0x4b,0x42,0x41,
	0xcb,0x2b,0xb7,0xce,0x08,0xa1,0x76,0x1d,0x1a,0xb8,0xe3,0xcc,0x7e,0x48,0x20,0xe6,
	0xf8,0x45,0x93,0xde,0xc3,0x63,0x0f,0xb0,0xac,0x5c,0xba,0xdf,0x07,0x77,0xe7,0x4e,
	0x1f,0x28,0x10,0x6c,0x59,0xd3,0xdd,0x2d,0x65,0x39,0xb2,0x74,0x84,0x3d,0xf4,0xbd,
	0xc7,0x79,0x60,0x0b,0x4d,0x33,0x36,0x25,0xbc,0xe0,0x09,0xcf,0x5b,0xe2,0x38,0x9e,
	0xc0,0xef,0xd2,0x16,0x05,0xbe,0x53,0xf7,0xc2,0xc6,0xa2,0x24,0x98,0x1c,0xad,0x04
};

static vector<unsigned int> diffusion = {
	0xf26cb481,0x16a5dc92,0x3c5ba924,0x79b65248,0x2fc64b18,0x615acd29,0xc3b59a42,0x976b2584,
	0x6cf281b4,0xa51692dc,0x5b3c24a9,0xb6794852,0xc62f184b,0x5a6129cd,0xb5c3429a,0x6b978425,
	0xb481f26c,0xdc9216a5,0xa9243c5b,0x524879b6,0x4b182fc6,0xcd29615a,0x9a42c3b5,0x2584976b,
	0x81b46cf2,0x92dca516,0x24a95b3c,0x4852b679,0x184bc62f,0x29cd5a61,0x429ab5c3,0x84256b97
};

//Watch function "draw_reverse_confusion"
static vector<vector<int>> confusion_a_reverse = {
	{106},{26},{24,94},{89},{56},{86},{227},{195},
	{228},{95},{188},{144},{47},{223},{70},{},
	{88},{},{245},{42},{247},{191},{128},{10},
	{204},{221},{23},{246},{83,113},{131},{129},{4},
	{},{130},{240},{145},{48},{2},{112},{158},
	{7},{253},{232},{9},{118},{132,220},{222},{176},
	{81},{251},{200},{6,154},{140},{115},{99},{210},
	{110},{68},{197},{216},{148},{218},{},{230},
	{161},{162},{37},{117},{},{248},{238},{100},
	{18},{77,209},{43},{33},{125},{67},{146},{183},
	{189},{92},{82},{39},{149},{14},{104},{184,207},
	{193},{75},{},{215},{59},{15},{123},{198},
	{252},{121},{22},{40},{91},{239},{41,181},{214},
	{196},{80},{34},{},{62},{155},{51},{244},
	{233},{31},{32},{255},{119},{},{49},{127},
	{21,151},{157},{174},{192},{8},{236},{226},{103},
	{},{60},{165},{30},{142},{45},{65},{250},
	{185},{153},{72},{205},{71},{137,171},{96},{16},
	{186},{116},{61},{166,224},{3},{134},{76},{93},
	{180},{213},{234},{87},{187},{122},{},{201},
	{69},{53},{58,243},{172},{152},{50},{168},{150},
	{90},{133},{28},{101},{0},{97},{173},{},
	{13},{},{85},{5},{120},{219},{175},{208},
	{135},{242},{66},{217},{11,194},{178},{229},{126},
	{38},{44},{57},{136},{159},{164},{55,64},{249},
	{235},{27},{105},{},{203},{170},{102},{46},
	{73},{1},{17},{20},{19},{},{143},{52},
	{111,237},{231},{63},{139},{114},{167},{211},{163},
	{84},{141},{206},{107},{},{179},{78},{190},
	{35},{36,124},{79},{202},{54},{108},{199},{169},
	{29},{109},{25},{182},{241},{212},{12},{98,254},
	{138},{160},{},{156},{225},{177},{74},{147}
};

//Watch function "draw_reverse_confusion"
static vector<vector<int>> confusion_b_reverse = {
        {53},{151},{},{87},{255},{244},{152},{204},
        {180},{234},{169},{227},{26},{41},{},{198},
        {210},{38},{31},{110},{102},{},{243},{96},
        {45},{},{184},{126},{253},{183},{142},{208},
        {190},{88},{44},{148},{132,251},{231},{40},{15},
        {33,209},{172},{54},{177},{0},{215},{103},{80},
        {62},{76},{131},{64,229},{42},{146},{230},{122},
        {238},{217},{70},{49},{128},{221},{71},{14,111},
        {25},{175},{94,174},{18},{140},{193},{30},{105},
        {189},{165},{160},{173},{7},{228},{16,207},{89},
        {13},{47},{27},{246},{118},{106,154},{158},{150},
        {157},{11,212},{32},{236},{201},{145},{52},{72},
        {226},{57},{170},{197},{},{216},{43},{83},
        {},{147},{164},{124},{211},{67},{20},{46},
        {166},{149},{2},{},{219},{65},{182},{205},
        {84},{225},{114},{23},{24},{139},{188},{},
        {101},{112},{135},{9},{220},{79},{28},{},
        {6},{4},{162},{},{161},{133},{168},{56},
        {},{120},{81},{194},{115},{39},{59},{1},
        {252},{22},{155},{48},{},{73},{239},{77},
        {104},{69,181},{250},{99},{156},{85},{5},{121},
        {34},{75},{78},{86},{200},{91,254},{17},{82},
        {199},{127},{218},{60},{136},{117},{113,129},{178},
        {185},{90},{58,202},{35},{232},{223},{245},{119},
        {240},{29},{248},{196},{107},{167},{249},{159,224},
        {68},{125},{12},{36,176},{187},{3},{179},{235},
        {21,116},{61},{242},{213},{143},{19},{163},{97},
        {100},{130},{50},{138},{63,171},{214},{195},{203},
        {233},{},{237},{186},{153},{109},{191},{206},
        {8},{66},{144},{10},{51},{},{98},{241},
        {37},{123},{134},{93},{222},{55},{},{247},
        {192},{137},{},{141},{95},{74},{92},{108}
};

//Draw
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

void draw_hex(const string name, const vector<int> &v) {
	int i;
	
	cout << name << " = ";
	for(i = 0; i < v.size(); i++) {
		stringstream stream;
		
		if(i != 0)
			cout << ", ";
		
		stream << std::hex << v[i];
		cout << "0x" << stream.str();
	}
	cout << endl;
}

void draw_reverse_confusion(const vector<int> &confusion, const string name) {
	int i, j;
	vector<vector<int>> r;
	
	//Generate
	for(i = 0; i < 256; i++) {
		r.push_back({});
		
		for(j = 0; j < 256; j++)
			if(i == confusion[j])
				r[i].push_back(j);
	}
	
	//Draw
	cout << "static vector<vector<int>> " << name << " = {";
	for(i = 0; i < 256; i++) {
		if(i % 8 == 0)
			cout << endl << "	";
		
		cout << "{";
		
		for(j = 0; j < r[i].size(); j++) {
			if(j != 0)
				cout << ",";
			
			cout << r[i][j];
		}
		
		cout << "}";
		
		if(i != 255)
			cout << ",";
	}
	cout << endl << "};" << endl;
}

void draw_rules_part_b() {
	int i, j, t;
	vector<vector<int>> r;
	
	//init
	t = 0;
	
	for(i = 0; i < 32; i++)
		for(j = 0; j < 32; j++)
			if((diffusion[i] >> j) % 2 == 1)
				r.push_back({i, j});
	
	//Draw
	for(i = 0; i < r.size(); i++) {
		if(t != r[i][0]) {
			cout << ") == input[" << t << "] " << endl << endl;
			t = r[i][0];
			
			cout << "(ex[" << r[i][1] << "]";
		} else if(i != 0)
			cout << " ^ ex[" << r[i][1] << "]";
		else
			cout << "(ex[" << r[i][1] << "]";
	}
	cout << ") == input[" << t << "] " << endl << endl;
}

//Reverse
/*
	Used in Part A and C
*/
vector<vector<int>> reverse_confusion(const vector<vector<int>> &confusion_reverse, const vector<int> &output) {
	int i, j, k;
	vector<int> v, temp_v;
	vector<vector<int>> input, temp_input;
	
	for(i = 0; i < output.size(); i++) {
		v = confusion_reverse[output[i]];
		
		if(v.size() == 0)
			return {};
		
		if(i == 0) {
			for(j = 0; j < v.size(); j++)
				input.push_back({v[j]});
		} else {
			temp_input.clear();
			for(j = 0; j < v.size(); j++) {
				for(k = 0; k < input.size(); k++) {
					temp_v = input[k];
					temp_v.push_back(v[j]);
					temp_input.push_back(temp_v);
				}
			}
			input = temp_input;
		}
	}
	
	return input;
}

// Look at "Part B" directory
vector<int> reverse_part_b(const vector<int> &input) {
	vector<int> output;
	
	output = input;
	
	output[5] ^= output[0];
	output[10] ^= output[0];
	output[12] ^= output[0];
	output[13] ^= output[0];
	output[15] ^= output[0];
	output[17] ^= output[0];
	output[18] ^= output[0];
	output[22] ^= output[0];
	output[23] ^= output[0];
	output[27] ^= output[0];
	output[28] ^= output[0];
	output[29] ^= output[0];
	output[30] ^= output[0];
	output[31] ^= output[0];
	output[6] ^= output[1];
	output[11] ^= output[1];
	output[12] ^= output[1];
	output[14] ^= output[1];
	output[18] ^= output[1];
	output[19] ^= output[1];
	output[20] ^= output[1];
	output[21] ^= output[1];
	output[23] ^= output[1];
	output[24] ^= output[1];
	output[25] ^= output[1];
	output[28] ^= output[1];
	output[30] ^= output[1];
	output[31] ^= output[1];
	output[7] ^= output[2];
	output[8] ^= output[2];
	output[9] ^= output[2];
	output[13] ^= output[2];
	output[15] ^= output[2];
	output[16] ^= output[2];
	output[17] ^= output[2];
	output[19] ^= output[2];
	output[20] ^= output[2];
	output[22] ^= output[2];
	output[25] ^= output[2];
	output[26] ^= output[2];
	output[28] ^= output[2];
	output[31] ^= output[2];
	output[4] ^= output[3];
	output[5] ^= output[3];
	output[9] ^= output[3];
	output[10] ^= output[3];
	output[12] ^= output[3];
	output[13] ^= output[3];
	output[14] ^= output[3];
	output[16] ^= output[3];
	output[18] ^= output[3];
	output[21] ^= output[3];
	output[23] ^= output[3];
	output[26] ^= output[3];
	output[27] ^= output[3];
	output[28] ^= output[3];
	output[6] ^= output[4];
	output[8] ^= output[4];
	output[9] ^= output[4];
	output[12] ^= output[4];
	output[20] ^= output[4];
	output[22] ^= output[4];
	output[23] ^= output[4];
	output[26] ^= output[4];
	output[27] ^= output[4];
	output[28] ^= output[4];
	output[30] ^= output[4];
	output[7] ^= output[5];
	output[9] ^= output[5];
	output[10] ^= output[5];
	output[13] ^= output[5];
	output[20] ^= output[5];
	output[23] ^= output[5];
	output[24] ^= output[5];
	output[25] ^= output[5];
	output[27] ^= output[5];
	output[29] ^= output[5];
	output[31] ^= output[5];
	output[6] ^= output[7];
	output[7] ^= output[6];
	output[8] ^= output[6];
	output[11] ^= output[6];
	output[12] ^= output[6];
	output[13] ^= output[6];
	output[14] ^= output[6];
	output[20] ^= output[6];
	output[22] ^= output[6];
	output[25] ^= output[6];
	output[31] ^= output[6];
	output[10] ^= output[7];
	output[12] ^= output[7];
	output[14] ^= output[7];
	output[15] ^= output[7];
	output[21] ^= output[7];
	output[22] ^= output[7];
	output[23] ^= output[7];
	output[24] ^= output[7];
	output[25] ^= output[7];
	output[30] ^= output[7];
	output[31] ^= output[7];
	output[9] ^= output[8];
	output[13] ^= output[8];
	output[14] ^= output[8];
	output[16] ^= output[8];
	output[17] ^= output[8];
	output[26] ^= output[8];
	output[29] ^= output[8];
	output[30] ^= output[8];
	output[10] ^= output[9];
	output[14] ^= output[9];
	output[15] ^= output[9];
	output[17] ^= output[9];
	output[18] ^= output[9];
	output[27] ^= output[9];
	output[30] ^= output[9];
	output[31] ^= output[9];
	output[11] ^= output[10];
	output[12] ^= output[10];
	output[13] ^= output[10];
	output[15] ^= output[10];
	output[18] ^= output[10];
	output[19] ^= output[10];
	output[24] ^= output[10];
	output[25] ^= output[10];
	output[28] ^= output[10];
	output[29] ^= output[10];
	output[31] ^= output[10];
	output[12] ^= output[11];
	output[13] ^= output[11];
	output[19] ^= output[11];
	output[25] ^= output[11];
	output[28] ^= output[11];
	output[29] ^= output[11];
	output[13] ^= output[12];
	output[14] ^= output[12];
	output[15] ^= output[12];
	output[17] ^= output[12];
	output[18] ^= output[12];
	output[20] ^= output[12];
	output[21] ^= output[12];
	output[25] ^= output[12];
	output[26] ^= output[12];
	output[27] ^= output[12];
	output[31] ^= output[12];
	output[17] ^= output[13];
	output[19] ^= output[13];
	output[20] ^= output[13];
	output[22] ^= output[13];
	output[24] ^= output[13];
	output[28] ^= output[13];
	output[29] ^= output[13];
	output[31] ^= output[13];
	output[16] ^= output[14];
	output[17] ^= output[14];
	output[18] ^= output[14];
	output[21] ^= output[14];
	output[23] ^= output[14];
	output[25] ^= output[14];
	output[28] ^= output[14];
	output[30] ^= output[14];
	output[17] ^= output[15];
	output[18] ^= output[15];
	output[19] ^= output[15];
	output[20] ^= output[15];
	output[21] ^= output[15];
	output[22] ^= output[15];
	output[26] ^= output[15];
	output[29] ^= output[15];
	output[31] ^= output[15];
	output[16] ^= output[19];
	output[19] ^= output[16];
	output[20] ^= output[16];
	output[21] ^= output[16];
	output[25] ^= output[16];
	output[26] ^= output[16];
	output[28] ^= output[16];
	output[29] ^= output[16];
	output[30] ^= output[16];
	output[19] ^= output[17];
	output[20] ^= output[17];
	output[22] ^= output[17];
	output[25] ^= output[17];
	output[27] ^= output[17];
	output[28] ^= output[17];
	output[31] ^= output[17];
	output[19] ^= output[18];
	output[20] ^= output[18];
	output[23] ^= output[18];
	output[24] ^= output[18];
	output[29] ^= output[18];
	output[30] ^= output[18];
	output[20] ^= output[19];
	output[25] ^= output[19];
	output[30] ^= output[19];
	output[31] ^= output[19];
	output[20] ^= output[21];
	output[21] ^= output[20];
	output[22] ^= output[20];
	output[23] ^= output[20];
	output[24] ^= output[20];
	output[25] ^= output[20];
	output[27] ^= output[20];
	output[31] ^= output[20];
	output[22] ^= output[21];
	output[23] ^= output[21];
	output[24] ^= output[21];
	output[26] ^= output[21];
	output[28] ^= output[21];
	output[29] ^= output[21];
	output[23] ^= output[22];
	output[26] ^= output[22];
	output[28] ^= output[22];
	output[30] ^= output[22];
	output[31] ^= output[22];
	output[24] ^= output[23];
	output[27] ^= output[23];
	output[28] ^= output[23];
	output[29] ^= output[23];
	output[30] ^= output[23];
	output[25] ^= output[24];
	output[27] ^= output[24];
	output[28] ^= output[24];
	output[30] ^= output[24];
	output[26] ^= output[25];
	output[27] ^= output[25];
	output[28] ^= output[25];
	output[29] ^= output[25];
	output[30] ^= output[25];
	output[31] ^= output[25];
	output[31] ^= output[26];
	output[28] ^= output[27];
	output[29] ^= output[27];
	
	output[27] ^= output[30];
	output[26] ^= output[27] ^ output[29] ^ output[30];
	output[25] ^= output[26] ^ output[28] ^ output[29] ^ output[31];
	output[24] ^= output[25] ^ output[27] ^ output[28] ^ output[30];
	output[23] ^= output[24] ^ output[25] ^ output[26] ^ output[27] ^ output[28] ^ output[30];
	output[22] ^= output[24] ^ output[25] ^ output[26] ^ output[29] ^ output[31];
	output[21] ^= output[22] ^ output[23] ^ output[24] ^ output[25] ^ output[27] ^ output[29];
	output[20] ^= output[22] ^ output[23] ^ output[25] ^ output[26] ^ output[30];
	output[19] ^= output[22] ^ output[25] ^ output[28] ^ output[30];
	output[18] ^= output[19] ^ output[21] ^ output[22] ^ output[24] ^ output[25] ^ output[27] ^ output[28] ^ output[29] ^ output[30] ^ output[31];
	output[17] ^= output[18] ^ output[20] ^ output[21] ^ output[23] ^ output[24] ^ output[26] ^ output[28] ^ output[29] ^ output[30];
	output[16] ^= output[17] ^ output[19] ^ output[20] ^ output[22] ^ output[25] ^ output[27] ^ output[28] ^ output[29];
	output[15] ^= output[17] ^ output[19] ^ output[20] ^ output[22] ^ output[24] ^ output[28] ^ output[29] ^ output[31];
	output[14] ^= output[15] ^ output[16] ^ output[17] ^ output[18] ^ output[20] ^ output[21] ^ output[22] ^ output[23] ^ output[24] ^ output[27] ^ output[29] ^ output[30] ^ output[31];
	output[13] ^= output[14] ^ output[15] ^ output[16] ^ output[19] ^ output[21] ^ output[24] ^ output[26] ^ output[27] ^ output[30];
	output[12] ^= output[13] ^ output[14] ^ output[15] ^ output[18] ^ output[19] ^ output[20] ^ output[23] ^ output[25] ^ output[26] ^ output[27] ^ output[29];
	output[11] ^= output[14] ^ output[19] ^ output[24] ^ output[25] ^ output[30];
	output[10] ^= output[13] ^ output[18] ^ output[24] ^ output[29];
	output[9] ^= output[12] ^ output[15] ^ output[17] ^ output[27] ^ output[28] ^ output[31];
	output[8] ^= output[11] ^ output[14] ^ output[15] ^ output[16] ^ output[19] ^ output[26] ^ output[30] ^ output[31];
	output[7] ^= output[8] ^ output[9] ^ output[10] ^ output[11] ^ output[12] ^ output[14] ^ output[21] ^ output[22] ^ output[24] ^ output[25] ^ output[31];
	output[6] ^= output[7] ^ output[11] ^ output[12] ^ output[13] ^ output[14] ^ output[15] ^ output[20] ^ output[22] ^ output[23] ^ output[25] ^ output[30] ^ output[31];
	output[5] ^= output[6] ^ output[7] ^ output[8] ^ output[9] ^ output[11] ^ output[13] ^ output[23] ^ output[25] ^ output[27] ^ output[29] ^ output[30] ^ output[31];
	output[4] ^= output[6] ^ output[8] ^ output[11] ^ output[12] ^ output[20] ^ output[21] ^ output[22] ^ output[25] ^ output[26] ^ output[28] ^ output[30];
	output[3] ^= output[6] ^ output[9] ^ output[12] ^ output[14] ^ output[17] ^ output[18] ^ output[20] ^ output[21] ^ output[23] ^ output[24] ^ output[27] ^ output[28] ^ output[29] ^ output[30];
	output[2] ^= output[5] ^ output[8] ^ output[11] ^ output[13] ^ output[15] ^ output[16] ^ output[17] ^ output[19] ^ output[20] ^ output[22] ^ output[26] ^ output[27] ^ output[28] ^ output[29];
	output[1] ^= output[4] ^ output[7] ^ output[10] ^ output[11] ^ output[12] ^ output[14] ^ output[15] ^ output[16] ^ output[18] ^ output[21] ^ output[23] ^ output[25] ^ output[26] ^ output[28];
	output[0] ^= output[7] ^ output[10] ^ output[12] ^ output[13] ^ output[15] ^ output[18] ^ output[19] ^ output[21] ^ output[22] ^ output[25] ^ output[28] ^ output[29] ^ output[30] ^ output[31];
		
	return output;
}

/*
	Part A and B are reverse in loop of 256
	
	A can have multiple inputs
	B only have one output
*/
bool bruteforce_ab_loop(const vector<vector<int>> &inputs, int level, int max) {
	int i;
	vector<int> output;
	
	if(level == max) {
		draw_hex("Found final input", inputs[0]);
		
		return true;
	}
	
	for(i = 0; i < inputs.size(); i++) {
		output = reverse_part_b(inputs[i]);
		
		vector<vector<int>> gen_inputs = reverse_confusion(confusion_a_reverse, output);
		
		if(gen_inputs.size() != 0)
			if(bruteforce_ab_loop(gen_inputs, level + 1, max))
				return true;
	}
	
	return false;
}

bool bruteforce_part_c(vector<int> &input, const string &text, int level) {
	int i, j, k, v;
	vector<int> a, b;
	
	if(level == 16) {
		//vector<vector<int>> inputs;
		//inputs.push_back(input);
		
		if(bruteforce_ab_loop({input}, 0, 256))
			exit(0);
		else
			return true;
	}
	
	for(i = 0; i < 256; i++) {
		v = (int)text[level];
		a = confusion_a_reverse[v ^ i];
		b = confusion_b_reverse[i];
		
		for(j = 0; j < a.size(); j++) {
			for(k = 0; k < b.size(); k++) {
				input[level * 2] = a[j];
				input[(level * 2) + 1] = b[k];
				bruteforce_part_c(input, text, level + 1);
			}
		}
	}
}

//Proves
void test_part_a() {
	int i;
	vector<vector<int>> input;
	vector<int> output;

	//Expected input = 
	//	83, 64, 48,  145, 99,  79,  81,  161, 35, 191, 82,  133, 82,  8,   172, 89,
	//	81, 96, 246, 60,  233, 145, 196, 254, 75, 204, 200, 66,  232, 209, 163, 61
	output = {
		28, 198, 36, 35,  54,  234, 48,  64,  232, 21, 82, 169, 82, 124, 163, 3,
		48, 142, 27, 129, 112, 35,  104, 247, 89,  24, 50, 186, 42, 73,  223, 146,
	};
	
	cout << "Crack Part A" << endl;
	input = reverse_confusion(confusion_a_reverse, output);

	//Debug
	for(i = 0; i < input.size(); i++)
		draw("input[" + to_string(i) + "]", input[i]);
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
	output = reverse_part_b(input);

	//Debug
	draw("Output", output);
}

void test_part_c() {
	vector<int> input(32, 0);
	string text = "Hire me!!!!!!!!";
	//string text = "Reverse me fast ";
	
	cout << "Crack Part C" << endl;
	bruteforce_part_c(input, text, 0);
}

int main() {
	//draw_reverse_confusion(confusion_a, "confusion_a_reverse");
	//draw_reverse_confusion(confusion_b, "confusion_b_reverse");
	
	//test_part_a();
	//test_part_b();
	test_part_c();
	
	return 0;
}
