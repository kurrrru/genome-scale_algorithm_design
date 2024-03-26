/*
Given the observed frequency of every codon in a species, 
normalize it into probabilities and write a program, that
given a protein sequence, samples a random DNA sequence that
encodes that protein under such codon usage probabilities.
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <ctime>

using namespace std;

map<char, vector<string> >	amino_to_dna = {
	{'A', {"GCT", "GCC", "GCA", "GCG"}},
	{'C', {"TGT", "TGC"}},
	{'D', {"GAT", "GAC"}},
	{'E', {"GAA", "GAG"}},
	{'F', {"TTT", "TTC"}},
	{'G', {"GGT", "GGC", "GGA", "GGG"}},
	{'H', {"CAT", "CAC"}},
	{'I', {"ATT", "ATC", "ATA"}},
	{'K', {"AAA", "AAG"}},
	{'L', {"TTA", "TTG", "CTT", "CTC", "CTA", "CTG"}},
	{'M', {"ATG"}},
	{'N', {"AAT", "AAC"}},
	{'P', {"CCT", "CCC", "CCA", "CCG"}},
	{'Q', {"CAA", "CAG"}},
	{'R', {"CGT", "CGC", "CGA", "CGG", "AGA", "AGG"}},
	{'S', {"TCT", "TCC", "TCA", "TCG", "AGT", "AGC"}},
	{'T', {"ACT", "ACC", "ACA", "ACG"}},
	{'V', {"GTT", "GTC", "GTA", "GTG"}},
	{'W', {"TGG"}},
	{'Y', {"TAT", "TAC"}},
	{'>', {"ATG"}},
	{'<', {"TAA", "TAG", "TGA"}}
};

map<char, vector<double> >	normalize(map<string, double> &observed)
{
	map<char, vector<double> > probability;
	for (auto dna: amino_to_dna)
	{
		if (dna.first == '>' || dna.first == '<')
			continue;
		double sum = 0;
		for (auto codon: dna.second)
			sum += observed[codon];
		for (auto codon: dna.second)			
			probability[dna.first].push_back(observed[codon] / sum);
	}
	return (probability);
}

string	generate_dna(map<char, vector<double> > &probability, string protein)
{
	string dna = amino_to_dna['>'][0];
	srand(time(NULL));
	for (int i = 0; i < protein.size(); i++)
	{
		vector<double> &prob = probability[protein[i]];
		double r = (double)rand() / RAND_MAX;
		double sum = 0;
		for (int j = 0; j < prob.size(); j++)
		{
			sum += prob[j];
			if (r < sum)
			{
				dna += amino_to_dna[protein[i]][j];
				break;
			}
		}
	}
	double r = (double)rand() / RAND_MAX;
	if (r < 1.0/3.0)
		dna += amino_to_dna['<'][0];
	else if (r < 2.0/3.0)
		dna += amino_to_dna['<'][1];
	else
		dna += amino_to_dna['<'][2];
	return (dna);
}

int main(void)
{
	map<string, double> observed;
	string codon;
	double frequency;
	int N;
	cin >> N;
	while (N-- && cin >> codon >> frequency)
	{
		if (observed.find(codon) != observed.end())
			observed[codon] += frequency;
		else
			observed[codon] = frequency;
	}
	map<char, vector<double> > probability = normalize(observed);
	string protein;
	cin >> protein;
	cout << generate_dna(probability, protein) << endl;
	return (0);
}
