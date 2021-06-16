#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>
#include <unordered_set>
#include <random>
#include <algorithm>
#include <thread>
#include "Bag.h"
#include "Package.h"
#define BAG_MAX_WEIGHT 45.0

using namespace std;
using namespace chrono;

typedef struct Stow_bag {
	double weight;
	double WEIGHT_LIMIT;
	bool open;
	string location;
	string bagCode;
	vector<string> packages;
};

string genTBAnum();
string genBagCode();
Stow_bag genNewBag();
Stow_bag closeBagAndReplace(Stow_bag old_bag);
void ListStructVector(vector<Stow_bag> vec);
vector<string> GenLocation(int clusters);

unsigned seed = system_clock::now().time_since_epoch().count();
minstd_rand0 generator(seed);
vector<string> cluslets;

int main()
{
	vector<Stow_bag> OpenBags;
	int bag_count, bags=0,clusts;
	unsigned short int second = 1000;
	vector<string> vec;
	
	
	

	cout << "No. of bags to open: ";
	while (!(cin >> bag_count)) {//checks that input is an int
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invlaid input(NaN). Try Again." << endl;
	}
	auto start = high_resolution_clock::now();
	for(int i =0; i<bag_count;++i) {
		Stow_bag vec_bag = genNewBag();
		OpenBags.push_back(vec_bag);
		bags += 1;
	} 
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Opened " << bag_count << " bags in " << duration.count() << " microseconds\n";
	cout << "Open Bags: " << OpenBags.size() << endl;
	//ListStructVector(OpenBags);
	cout << "No. of clusters: ";
	cin >> clusts;

	GenLocation(clusts);

	for (auto it : cluslets) {
		cout << it << endl;
	}
    system("pause");
    return 0;
}

string genTBAnum() {
	vector<int> vec;
	time_t now;
	time(&now);
	srand((unsigned)now);
	unsigned short int num;
	for (int i = 0; i < 12; ++i) {//generate 12 random nums
		num = rand() % 10;
		vec.push_back(num);
	}
	ostringstream out;
	for (int j : vec) {//combines random nums into one string
		out << j;
	}
	return "TBA" + out.str();
}

string genBagCode() {

	static unordered_set<string> BagIDs;
	string bagcolors[5] = { "ORG", "BLK", "GRN", "BLU", "YLW" };
	string color;
	
	int BagNum= (generator() % 1000);
	color = bagcolors[generator() % 5];
	string BagCode = to_string(BagNum) + "-" + color;
	ostringstream sstream;
	while(BagIDs.count(BagCode)) {
		BagCode.clear();
		BagNum = (generator() % 1000);
		color = bagcolors[generator() % 5];
		BagCode = to_string(BagNum)+ "-" + color;
	}
	sstream << setw(7) << setfill('0') << BagCode;
	BagIDs.insert(sstream.str());
	return sstream.str();
}

Stow_bag genNewBag() {
	Stow_bag bag;
	bag.open = true;
	bag.weight = 0.0;
	bag.bagCode = genBagCode();
	bag.WEIGHT_LIMIT = BAG_MAX_WEIGHT;
	return bag;
}

Stow_bag closeBagAndReplace(Stow_bag old_bag) {
	//close bag already opened
	old_bag.open = false;

	//open new bag & fill values
	Stow_bag new_bag;
	new_bag.bagCode = genBagCode();
	new_bag.location = old_bag.location;
	new_bag.weight = 0.0;
	new_bag.open = true;
	new_bag.WEIGHT_LIMIT = BAG_MAX_WEIGHT;

	return new_bag;
}

void ListStructVector(vector<Stow_bag> vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << i+1 << ". "<< vec[i].bagCode << endl;
	}
}

vector<string> GenLocation(int clusters) {//Fix array out-of-bounds read errors
	int cluster_no, roll;
	string output;
	string alphabet[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
		"L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

	
	if (clusters <= 26) {
		for (int i = 1; i <= clusters; i++) {
			cluslets.push_back(alphabet[i - 1]);
		}
	}
	else if (clusters > 26) {
		roll = 1 + (clusters / 26);
		for (int j = 1; j <= clusters; j++) {
			output = to_string(roll) + alphabet[(j % 26)-1];//out of bounds read error
			cluslets.push_back(output);
		}
		//for (auto it = cluslets[26]; it < cluslets.size(); ++it) { //Operator mismatches at it < cluslets.size(); ++it operators

		//}
	}
	else {
		exit(3);
	}
	
	return cluslets;
}