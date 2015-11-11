/*
 * Alignments.h
 *
 *  Created on: May 25, 2012
 *      Author: fritz
 */

#ifndef ALIGNMENTS_H_
#define ALIGNMENTS_H_

#include <string.h>
#include <vector>
#include <math.h>
#include "api/BamAux.h"
#include "api/BamMultiReader.h"
#include "api/BamWriter.h"
#include "Paramer.h"
using namespace BamTools;
using namespace std;

typedef unsigned short ushort;
typedef unsigned int uint;

struct str_event{
	short length;
	int pos;
	int read_pos;
};
struct aln_str{
	int RefID;
	int pos;
	bool strand;
	std::vector<CigarOp> cigar;
	ushort mq;
	ushort nm;
	ushort length;
	int read_pos_start;
	int read_pos_stop;
};

class Alignment {

private:
	BamAlignment * al;
	bool includes_SV;
	pair<string,string> alignment;
	bool is_computed;
	int32_t orig_length;
	int stop;
	 std::vector<CigarOp> translate_cigar(std::string cigar);
	 size_t get_length(std::vector<CigarOp> CigarData);

	 int get_id(RefVector ref, std::string chr);
public:
	Alignment(){
	    stop=0;
		orig_length=0;
		al=NULL;
		is_computed=false;
		includes_SV=false;
	}
	~Alignment(){
		alignment.first.clear();
		alignment.second.clear();
		delete al;
	}
	void setAlignment(BamAlignment * al);
	void setRef(string sequence);
	void computeAlignment();

	pair<string,string> getSequence();
	int32_t getPosition();
	int32_t getRefID();
	bool getStrand();
	uint16_t getMappingQual();
	string getName();
	vector<CigarOp> getCigar();
	string getQualitValues();
	size_t getRefLength();
	size_t getOrigLen();
	BamAlignment * getAlignment();
	float getIdentity();
	void initAlignment();
	int getAlignmentFlag();
	string getQueryBases();
	string getQualities();
	string getTagData();
	vector<aln_str> getSA(RefVector ref);
	void initSequence();
	int get_stop(){
		return stop;
	}
	vector<str_event> get_events_CIGAR();
	vector<str_event> get_events_MD(int min_length);
	 void get_coords(aln_str tmp,int & start,int &stop);
	 bool supports_SV(){
		 return this->includes_SV;
	 }
	 void set_supports_SV(bool flag){
		 this->includes_SV=flag;
	 }
	 bool get_is_save();
	 double get_num_mismatches(std::string md);
	 double get_scrore_ratio();
	 std::string get_md();
	 double get_avg_indel_length_Cigar();
};


#endif /* ALIGNMENTS_H_ */