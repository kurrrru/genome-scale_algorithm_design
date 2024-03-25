/*
list all the DNA sequences that encode a given protein sequence
*/
#include <iostream>
#include <string>
#include <vector>
#include <map>

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

void	protein_to_dna_sub(string protein, int pos, string dna, vector<string> &dna_list)
{
	if (pos == protein.size())
		return (dna_list.push_back(dna));
	for (int i = 0; i < amino_to_dna.at(protein[pos]).size(); i++)
		protein_to_dna_sub(protein, pos + 1, dna + amino_to_dna[protein[pos]][i], dna_list);
}

vector<string>	protein_to_dna(string protein)
{
	vector<string> dna_list;
	protein_to_dna_sub(">" + protein + "<", 0, "", dna_list);
	return (dna_list);
}

int	main(void)
{
	string protein;
	cin >> protein;
	vector<string> dna_list = protein_to_dna(protein);
	for (int i = 0; i < dna_list.size(); i++)
		cout << dna_list[i] << endl;
	return (0);
}
