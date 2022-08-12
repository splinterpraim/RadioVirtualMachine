#ifndef RVM_CONFIGCODE_PARSER_CLASS
#define RVM_CONFIGCODE_PARSER_CLASS

typedef struct some_struct_s some_struct;

namespace rvm
{
	class rvm_configcode_parser
	{
	public:
		rvm_configcode_parser();
		~rvm_configcode_parser();
		int parse(some_struct &confcode);
	private:
		int do_num;
		int ape_num;
	}
};

#endif // RVM_CONFIGCODE_PARSER_CLASS
