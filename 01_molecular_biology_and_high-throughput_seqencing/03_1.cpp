/*
Given the set of all exons of an organism, write a program 
that compute the ratio z(XY) between the observed and the 
expected occurrence of every pair of consecutive codons XY. 
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

map<char, vector<string> >	amino_to_codon = {
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

map<string, char> codon_to_amino = {
	{"GCT", 'A'}, {"GCC", 'A'}, {"GCA", 'A'}, {"GCG", 'A'},
	{"TGT", 'C'}, {"TGC", 'C'},
	{"GAT", 'D'}, {"GAC", 'D'},
	{"GAA", 'E'}, {"GAG", 'E'},
	{"TTT", 'F'}, {"TTC", 'F'},
	{"GGT", 'G'}, {"GGC", 'G'}, {"GGA", 'G'}, {"GGG", 'G'},
	{"CAT", 'H'}, {"CAC", 'H'},
	{"ATT", 'I'}, {"ATC", 'I'}, {"ATA", 'I'},
	{"AAA", 'K'}, {"AAG", 'K'},
	{"TTA", 'L'}, {"TTG", 'L'}, {"CTT", 'L'}, {"CTC", 'L'}, {"CTA", 'L'}, {"CTG", 'L'},
	{"ATG", 'M'},
	{"AAT", 'N'}, {"AAC", 'N'},
	{"CCT", 'P'}, {"CCC", 'P'}, {"CCA", 'P'}, {"CCG", 'P'},
	{"CAA", 'Q'}, {"CAG", 'Q'},
	{"CGT", 'R'}, {"CGC", 'R'}, {"CGA", 'R'}, {"CGG", 'R'}, {"AGA", 'R'}, {"AGG", 'R'},
	{"TCT", 'S'}, {"TCC", 'S'}, {"TCA", 'S'}, {"TCG", 'S'}, {"AGT", 'S'}, {"AGC", 'S'},
	{"ACT", 'T'}, {"ACC", 'T'}, {"ACA", 'T'}, {"ACG", 'T'},
	{"GTT", 'V'}, {"GTC", 'V'}, {"GTA", 'V'}, {"GTG", 'V'},
	{"TGG", 'W'},
	{"TAT", 'Y'}, {"TAC", 'Y'},
	{"ATG", '>'},
	{"TAA", '<'}, {"TAG", '<'}, {"TGA", '<'}
};

map<char, vector<double> >	normalize(map<string, double> &observed)
{
	map<char, vector<double> > probability;

	for (auto dna: amino_to_codon)
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

string	translate(string exon)
{
	string	protein;

	for (int i = 0; i < exon.size(); i += 3)
		protein += codon_to_amino[exon.substr(i, 3)];
	return (protein);
}

void calculate_expect(vector<string> proteins, map<char, vector<double> > probability, map<pair<string, string>, double> &expect)
{
	for (auto protein: proteins)
	{
		for (int i = 0; i < protein.size() - 1; i++)
		{
			if (protein[i] == '>' || protein[i + 1] == '>' || protein[i] == '<' || protein[i + 1] == '<')
				continue;
			for (int j = 0; j < amino_to_codon[protein[i]].size(); j++)
			{
				for (int k = 0; k < amino_to_codon[protein[i + 1]].size(); k++)
				{
					pair<string, string> codon_pair = make_pair(amino_to_codon[protein[i]][j], amino_to_codon[protein[i + 1]][k]);
					if (expect.find(codon_pair) != expect.end())
						expect[codon_pair] += probability[protein[i]][j] * probability[protein[i + 1]][k];
					else
						expect[codon_pair] = probability[protein[i]][j] * probability[protein[i + 1]][k];
				}
			}
		}
	}
}

int	main(void)
{
	map<string, double>					observed;
	map<pair<string, string>, double>	observed_codon_pair;
	map<pair<string, string>, double>	expect;
	int									num_exon;
	string								exon;
	vector<string>						exons;
	vector<string>						proteins;
	string								codon;
	pair<string, string>				codon_pair;


	cin >> num_exon;
	for (int i = 0; i < num_exon; i++)
	{
		cin >> exon;
		exons.push_back(exon);
		proteins.push_back(translate(exon));
		for (int j = 0; j < exon.size(); j += 3)
		{
			codon = exon.substr(j, 3);
			if (observed.find(codon) != observed.end())
				observed[codon] += 1;
			else
				observed[codon] = 1;
			if (j + 5 < exon.size())
			{
				codon_pair = make_pair(exon.substr(j, 3), exon.substr(j + 3, 3));
				if (observed_codon_pair.find(codon_pair) != observed_codon_pair.end())
					observed_codon_pair[codon_pair] += 1;
				else
					observed_codon_pair[codon_pair] = 1;
			}
		}
	}
	map<char, vector<double> > probability = normalize(observed);
	calculate_expect(proteins, probability, expect);
	for (auto codon_pair: expect)
	{
		if (observed_codon_pair.find(codon_pair.first) != observed_codon_pair.end())
			cout << codon_pair.first.first << codon_pair.first.second << " " << observed_codon_pair[codon_pair.first] / codon_pair.second << endl;
		else
			cout << codon_pair.first.first << codon_pair.first.second << " " << 0 << endl;
	}
}
