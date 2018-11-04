#include "network.h"
#include "random.h"
using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>

void Network:: resize(const size_t &n) {
	
	values.clear();
	for (size_t i(0); i<n; ++i) {
		
		values.push_back(RNG.normal(0, 1));
	}
}

size_t Network:: size() const {

	return values.size();
}

size_t Network:: set_values(const std::vector<double>& vec) {
	 
	 size_t changed_vals(0);
	 vector<double> copie = vec;
	 if (vec.size() > values.size()) {
		 
		 int diff = vec.size() - values.size(); 
		 for (int i(0); i < diff; ++i) {
			 
			copie.pop_back();
		 }
		 if (same_size(copie, values)) {
			 
			values.swap(copie);
			changed_vals = copie.size();
		 } else {
			 
			cerr << "Error: couldn't swap values./n";
		 }
		 
	 } else if (vec.size() < values.size()) {
		 
		 int diff = values.size() - vec.size();
		 int indice = values.size() - diff; ///l'indice du tableau à partir duquel on doit stocker les valeurs
		 vector<double> stock; ///stock les valeurs de values qu'on veut garder (car vec est plus petit que values, seuls les premières valeurs seront modifiées)
		 for (int i(indice); i < values.size(); ++i) {
			 
			stock.push_back(values[i]);
		 }
		 for (int i(0); i<diff; i++) {
			 
			values.pop_back();
		 }
		 if (same_size(vec, values)) {
			 
			 values.swap(copie);
			 changed_vals = values.size();
			 
		 } else {
			 cerr << "Error: couldn't swap values./n";
		 }
		 
		 for (int i(0); i<diff; ++i) {
			 
			if (i< stock.size()) {
				values.push_back(stock[i]);
			}
		 }
		 
	 } else {
		 
		 values.swap(copie);
		 changed_vals = values.size();
	 }
	 
	 return changed_vals;
}

bool Network:: same_size(const vector<double> v1, const vector<double> v2) const {
	
	return (v1.size() == v2.size());
}

size_t Network::degree(const size_t &_n) const {
	
	return links.count(_n);
}

std::vector<size_t> Network::neighbors(const size_t& nb) const {
	
	vector<size_t> vec;
	auto key = links.equal_range(nb);
	for (auto i(key.first); i != key.second; ++i) {
		
		vec.push_back(i->second);
	}
	return vec;
}

std::vector<double> Network::sorted_values() const {
	
	vector<double> sorted = values;
	
	sort(sorted.begin(), sorted.end());
	reverse(begin(sorted), end(sorted));
	
	return sorted;
}

double Network::value(const size_t & _n) const {

	if (_n < values.size()) {
		
		return values[_n];
	} else {
		
		cerr << "Error: node not found.";
	}
}

bool Network::add_link(const size_t& a, const size_t& b) {
	
	if (a < values.size() && b < values.size() && a != b) {
		
		bool no_link (true);
		auto key = links.equal_range(a);
		for (auto i = key.first;  i != key.second; ++i) {
			
			///see if the link already exists or not
			if (i->second == b) { no_link = false;}
		}
		if (no_link == true) {
			
			links.insert({{a,b}, {b,a}});
			return true;
		}
	}
	return false;
}

size_t Network::random_connect(const double& mean) {
	
	size_t links_created(0);
	links.clear();
	int nodes;
	vector<int> chosen;
	
	for (int i(0); i< values.size(); ++i) {
		
		chosen.clear();
		nodes = RNG.poisson(mean);
		chosen.resize(nodes);
		
		for (int n(0); n< chosen.size(); ++n) {
			
			RNG.uniform_int(chosen, 0, values.size() -1);	
		}		
		
		for (int j(0); j<chosen.size(); ++j) {
			
			if(add_link(i, chosen[j]) == true) {	
				links_created += 1;
			}
		}
	}
	return links_created;
}
