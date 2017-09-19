#include "company.h"
#include <iostream>
#include <vector>

using namespace std;


CompanyTracker::CompanyTracker (int n)

{
	numCompanies = n;
	companies = new Company* [numCompanies];
	for (int i = 0; i < numCompanies; ++i) {
		companies[i] = new Company ();
	}

	pointerCompany2 = new Company();
	pointerCompany1 = new Company();
}

CompanyTracker::~CompanyTracker() {
	for (int i = 0; i < numCompanies; i++) {
		delete companies[i];
	}
	delete[] companies;
	delete pointerCompany1;
	delete pointerCompany2;
	for (unsigned i=0; i < mergedHolder.size(); i++) { 
		delete mergedHolder[i]; 
	}
}

Company* CompanyTracker::findLargestCompany(int i, Company* pointerCompany) {
	if (companies[i] -> parent == nullptr) {
		return companies[i];
	}
	else {
		pointerCompany -> parent = companies[i];
		while (pointerCompany -> parent != nullptr) {   
			pointerCompany = pointerCompany -> parent;
		}
		return pointerCompany; 
	}
}

void CompanyTracker::merge (int i, int j) {
	if ((i >= 0 && j >= 0) && (i < numCompanies && j < numCompanies)) {
		if ((inSameCompany(i,j) == false)) {
			Company* iLarge = findLargestCompany(i, pointerCompany1);
			Company* jLarge = findLargestCompany(j, pointerCompany2);

			Company* mergedCompany = new Company(iLarge, jLarge); 
			iLarge -> parent = mergedCompany;
			jLarge -> parent = mergedCompany;

			mergedHolder.push_back(mergedCompany); 
			return; 
		}
		else {
			return;
		}
	}
	else {
		return;
	}
}


void CompanyTracker::split (int i) {  
	Company* companyToSplit;
	if ((i >= 0) && (i < numCompanies)) {
		if (companies[i] -> parent != nullptr) { 
			companyToSplit = findLargestCompany(i,pointerCompany1); 
			companyToSplit -> merge1 -> parent = companyToSplit -> parent;
			companyToSplit -> merge2 -> parent = companyToSplit -> parent;  
			companyToSplit = nullptr;
			return;
		} 
		else {
			return; 
		}  
	}
	else {
		return;
	}
}

bool CompanyTracker::inSameCompany (int i, int j) {

	if ((companies[i] -> parent == nullptr && companies[j]->parent == nullptr) && (i != j)) {
		return false;
	}

	else if (i == j) {
		return true;
	}

	else if (findLargestCompany(i,pointerCompany1) == findLargestCompany(j, pointerCompany2)) {
		return true;
	}
	else {
		return false; 
	}
}
