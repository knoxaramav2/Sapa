#ifndef NTRANS
#define NTRANS


//holds 16 potential transmitters
union transmitter
{
	struct
	{
		//ionizers
		unsigned short pos_hi : 1;//strong charge increase
		unsigned short pos_lo : 1;//weak charge increase
		unsigned short neg_hi : 1;//strong charge decrease
		unsigned short neg_lo : 1;//weak charge decrease

		//propagators
		unsigned short axo_str : 1;//strengthens target connections
		unsigned short axo_wkn : 1;//weakens target connections

		//modulators
	};
};

#endif