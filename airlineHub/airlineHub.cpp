#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

struct airport {
	double x_coord;
	double y_coord;
	double max_distance;
	//airport(double x, double y) {x_coord = x; y_coord = y;}
};

ostream & operator<< (ostream & o, const airport & ap) {
	o << "Airport" << endl;
	o << "   X: " << ap.x_coord << endl;
	o << "   Y: " << ap.y_coord << endl;
	o << "      Max Distance: " << ap.max_distance;
	return o;
}

void readFile(string filename, vector<int> & inputLengths, vector<airport> & airports) {
	fstream f;
	f.open(filename, fstream::in);

	int numAirports;
	double xCoord;
	double yCoord;
	airport temp;

	while(f.peek() != EOF) {
		f >> numAirports;
		inputLengths.push_back(numAirports);

		for(int i = 0; i < numAirports; i++) {
			f >> temp.x_coord;
			f >> temp.y_coord;
			airports.push_back(temp);
		}
	}
	f.close();
}

vector<airport> findHubs(const vector<int> & inputLengths, const vector<airport> & airports) {
	vector<airport> hubs;

	airport hub;
	airport current;
	int offset;
	double max_distance;
	double distance;

	for (int i = 0; i < inputLengths.size(); ++i) { // Loop through each input
		for (int j = 0; j < inputLengths[i]; ++j) { // Loop through each airport in input set
			current = airports[offset+j];
			for (int t = 0; t < inputLengths[i]; ++t) { // Loop to compute all distances
				distance = sqrt( pow(airports[offset+t].x_coord - current.x_coord,2) 
					+ pow(airports[offset+t].y_coord - current.y_coord,2) );
				if (distance >= max_distance) {
					max_distance = distance;
					hub = current;
				}
			}
		}
		hub.max_distance = max_distance;
		hubs.push_back(hub);
		max_distance = 0;
		offset += inputLengths[i];
	}
	return hubs;
}


int main() {
	vector<int> inputLengths;
	vector<airport> airports;
	readFile("airlineInput.txt", inputLengths, airports);
	vector<airport> hubs = findHubs(inputLengths, airports);

	for (int i = 0; i < hubs.size(); ++i) {
		cout << hubs[i] << endl;
	}

}