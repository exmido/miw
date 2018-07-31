/*
Copyright (c) <year> Mido

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef MIW_CPP_COMPILER
#define MIW_CPP_COMPILER

#include "miw.h"

namespace miw_cpp
{
	//VM_REGISTER
	enum VM_REGISTER
	{
		REG_FUN_START, //function start position
		REG_FUN_RETURN, //function return position

		REG_VAR_BEGIN, //function variable begin
		REG_VAR_END, //function variable end

		REG_UNKNOWN
	};

	//SYMBOL_STRING
	static const std::string SYMBOL_STRING[] =
	{
		//3 char
		"<<=",
		">>=",
		"->*",

		//2 char
		"+=",
		"-=",
		"*=",
		"/=",
		"%=",
		"&=",
		"^=",
		"|=",
		"||",
		"&&",
		"==",
		"!=",
		"<=",
		">=",
		"<<",
		">>",
		".*",
		"->",
		"::",

		//1 char
		"=",
		"|",
		"^",
		"&",
		"<",
		">",
		"+",
		"-",
		"*",
		"/",
		"%",
		"!",
		"~",
		"(",
		")",
		"[",
		"]",
		"{",
		"}",
		".",
		":",
		",",
		";",
		"\'",
		"\"",
		"\\"
	};

	//NOUSE_STRING
	static const std::string NOUSE_STRING[] =
	{
		//2 char
		"++",
		"--",

		//1 char
		"?"
	};

	//KEYWORD_STRING
	static const std::string KEYWORD_STRING[] =
	{
		"alignas",
		"alignof",
		"and",
		"and_eq",
		"asm",
		"atomic_cancel",
		"atomic_commit",
		"atomic_noexcept",
		"auto",
		"bitand",
		"bitor",
		"bool",
		"break",
		"case",
		"catch",
		"char",
		"char16_t",
		"char32_t",
		"class",
		"compl",
		"concept",
		"const",
		"constexpr",
		"const_cast",
		"continue",
		"decltype",
		"default",
		"delete",
		"do",
		"double",
		"dynamic_cast",
		"else",
		"enum",
		"explicit",
		"export",
		"extern",
		"false",
		"float",
		"for",
		"friend",
		"goto",
		"if",
		"import",
		"inline",
		"int",
		"long",
		"module",
		"mutable",
		"namespace",
		"new",
		"noexcept",
		"not",
		"not_eq",
		"nullptr",
		"operator",
		"or",
		"or_eq",
		"private",
		"protected",
		"public",
		"register",
		"reinterpret_cast",
		"requires",
		"return",
		"short",
		"signed",
		"sizeof",
		"static",
		"static_assert",
		"static_cast",
		"struct",
		"switch",
		"synchronized",
		"template",
		"this",
		"thread_local",
		"throw",
		"true",
		"try",
		"typedef",
		"typeid",
		"typename",
		"union",
		"unsigned",
		"using",
		"virtual",
		"void",
		"volatile",
		"wchar_t",
		"while",
		"xor",
		"xor_eq"
	};

	//TOKEN_TYPE
	enum TOKEN_TYPE
	{
		TOKEN_NUMBER,
		TOKEN_STRING,
		TOKEN_SYMBOL,

		TOKEN_UNKNOWN
	};

	//scanner_record
	class scanner_record
	{
	protected:
		char* ptr;
		std::string token;
		bool error;

		int line;
	};

	//compiler
	class compiler : public scanner_record
	{
	protected:
		char* end;
		const char* file;

	public:
		//compiler
		compiler(void* _ptr, size_t _size, const char* _file)
		{
			ptr = (char*)_ptr;
			token = "";
			error = false;

			line = 1;

			end = ptr + _size;
			file = _file;
		}

		//iserror
		int iserror(bool is = false)
		{
			return (error || is) ? line : 0;
		}

		//isbuffer
		size_t isbuffer()
		{
			size_t ret = end - ptr;
			return  ret > 0 ? ret : 0;
		}

		//scanner_save
		scanner_record scanner_save()
		{
			return *((scanner_record*)this);
		}

		//scanner_load
		void scanner_load(scanner_record& record)
		{
			*((scanner_record*)this) = record;
		}

		//scanner
		bool scanner(TOKEN_TYPE type, const std::string str = "", bool iscase = false)
		{
			if(error)
				return false;

			token = "";
			size_t size = end - ptr;

			if(size <= 0)
				return false;

			//null char and comment
			for(int comment = 0; size > 0; size = end - ptr)
			{
				if(size >= 2 && comment == 0 && ptr[0] == '/' && ptr[1] == '/') // //
				{
					comment = 1;
					++ptr;
				}
				else if(size >= 2 && comment == 0 && ptr[0] == '/' && ptr[1] == '*') // /*
				{
					comment = 2;
					++ptr;
				}
				else if(size >= 2 && comment == 2 && ptr[0] == '*' && ptr[1] == '/') // */
				{
					comment = 0;
					++ptr;
				}
				else if(comment == 0 && ptr[0] == '#') // #
				{
					comment = 1;
				}
				else if(*ptr == '\n')
				{
					if(comment == 1)
						comment = 0;

					++line;
				}
				else if(*ptr == '\0')
				{
					return false;
				}
				else if(comment == 0 && (type == TOKEN_UNKNOWN || *ptr != ' ') && (*ptr < 7 || *ptr > 13))
				{
					//7		\a	alert (beep)
					//8		\b	backspace
					//9		\t	tab
					//10	\n	newline
					//11	\v	vertical tab
					//12	\f	form feed (page feed)
					//13	\r	carriage return
					break;
				}

				++ptr;
			}

			if(size < 0)
				return false;

			char* p = ptr;
			int pcode = wctoi((utf8*)p);

			switch(type)
			{
			case TOKEN_NUMBER:
				if(pcode >= '0' && pcode <= '9') //number
				{
					do
					{
						pcode = wctoi(wcnext((utf8**)&p));
					} while(p < end && pcode >= '0' && pcode <= '9');

					goto _LABEL_OK;
				}
				return false;
			case TOKEN_STRING:
				if(pcode == '_' || (pcode >= 'A' && pcode <= 'Z') || (pcode >= 'a' && pcode <= 'z') || pcode > 0x7F) //string
				{
					do
					{
						pcode = wctoi(wcnext((utf8**)&p));
					} while(p < end && (pcode == '_' || (pcode >= 'A' && pcode <= 'Z') || (pcode >= 'a' && pcode <= 'z') || (pcode >= '0' && pcode <= '9') || pcode > 0x7F));

					goto _LABEL_OK;
				}
				return false;
			case TOKEN_SYMBOL:
				for(int i = 0; i < sizeof(NOUSE_STRING) / sizeof(NOUSE_STRING[0]); ++i)
				{
					size_t len = NOUSE_STRING[i].length();
					if(size >= len && !NOUSE_STRING[i].compare(0, len, p, len)) //no use
						return false;
				}

				for(int i = 0; i < sizeof(SYMBOL_STRING) / sizeof(SYMBOL_STRING[0]); ++i)
				{
					size_t len = SYMBOL_STRING[i].length();
					if(size >= len && !SYMBOL_STRING[i].compare(0, len, p, len)) //symbol
					{
						for(; len > 0; --len)
							++p;

						goto _LABEL_OK;
					}
				}
				return false;
			default:
				wcnext((utf8**)&p);
			}

		_LABEL_OK:
			size = p - ptr;
			token.assign(ptr, size);

			if(iscase)
				std::transform(token.begin(), token.end(), token.begin(), ::tolower);

			if(str.compare("") && str.compare(token))
				return false;

			ptr = p;
			return true;
		}

		//parser
		//<value>
		miw_node_value* parser_value()
		{
			miw_node_value* ret = new miw_node_value(line, file);
			ret->data_type = new miw_node_name(line, file);

			if(scanner(TOKEN_NUMBER))
			{
				int p = 0;

				if(!token.compare("0"))
				{
					if(scanner(TOKEN_UNKNOWN, "x", true))
						ret->u64 = wton<char, unsigned long long>(ptr, &p, 16); //strtoull(ptr, &p, 16);
					else
						ret->u64 = wton<char, unsigned long long>(ptr, &p, 8); //strtoull(ptr, &p, 8);

					if(p == 0)
						goto _LABEL_ERROR;

					ptr += p;
				}
				else
				{
					ret->u64 = wton<char, unsigned long long>(token.c_str(), &p); //strtoull(token.c_str(), &p, 10);
					if(p == 0)
						goto _LABEL_ERROR;
				}

				if(scanner(TOKEN_SYMBOL, ".")) //float
				{
					if(scanner(TOKEN_STRING, "f", true))
					{
						((miw_node_name*)ret->data_type)->data_name = "@f32";
						ret->f32 = (float)ret->u64;
					}
					else
					{
						--ptr;

						double d = wton<char, double>(ptr, &p); //strtod(ptr, &p);
						if(p == 0)
							goto _LABEL_ERROR;

						ptr += p;
						if(scanner(TOKEN_STRING, "f", true))
						{
							((miw_node_name*)ret->data_type)->data_name = "@f32";
							ret->f32 = (float)(d + ret->u64);
						}
						else
						{
							((miw_node_name*)ret->data_type)->data_name = "@f64";
							ret->f64 = d + ret->u64;

						}
					}
				}
				else //int
				{
					if(scanner(TOKEN_STRING, "u", true))
					{
						((miw_node_name*)ret->data_type)->data_name = "@u32";
						ret->u64 = (unsigned long long)ret->u64;
					}
					else if(scanner(TOKEN_STRING, "ll", true))
					{
						((miw_node_name*)ret->data_type)->data_name = "@s64";
						ret->s64 = (long long)ret->u64;
					}
					else if(scanner(TOKEN_STRING, "ull", true) || scanner(TOKEN_STRING, "llu", true))
					{
						((miw_node_name*)ret->data_type)->data_name = "@u64";
					}
					else
					{
						((miw_node_name*)ret->data_type)->data_name = "@s32";
						ret->s64 = (int)ret->u64;
					}
				}
			}
			else if(scanner(TOKEN_SYMBOL, ".")) //float
			{
				int p = 0;
				--ptr;

				ret->f64 = wton<char, double>(ptr, &p); //strtod(ptr, &p);

				if(p == 0)
					goto _LABEL_ERROR;

				ptr += p;
				if(scanner(TOKEN_STRING, "f", true))
				{
					((miw_node_name*)ret->data_type)->data_name = "@f32";
					ret->f32 = (float)ret->f64;
				}
				else
				{
					((miw_node_name*)ret->data_type)->data_name = "@f64";
				}
			}
			else if(scanner(TOKEN_STRING, "L")) //wchar_t
			{
				delete ret;

				ret = parser_value();
				if(ret == NULL)
					goto _LABEL_ERROR;

				//convert string
				if(ret->data_type->rtti(miw_node::rttype<miw_node_pointer>()))
				{
					miw_node_pointer* p = (miw_node_pointer*)ret->data_type;
					if(((miw_node_name*)p->data_type)->data_name.compare("@s8"))
						goto _LABEL_ERROR;

					((miw_node_name*)p->data_type)->data_name = "@wchat_t";

					char* wstr = new char[(wstrnum((utf8*)ret->ptr) + 1) * sizeof(wchar_t) / sizeof(char)];
					wstrcpy((wchar_t*)wstr, (utf8*)ret->ptr);

					delete[] ret->ptr;
					ret->ptr = wstr;
				}
				else //convert character
				{
					if(((miw_node_name*)ret->data_type)->data_name.compare("@s8"))
						goto _LABEL_ERROR;

					((miw_node_name*)ret->data_type)->data_name = "@wchar_t";

					wchar_t wc;
					itowc(wctoi((utf8*)&ret->s8), &wc);
					ret->s32 = (int)wc;
				}
			}
			else if(scanner(TOKEN_SYMBOL, "\'")) //character
			{
				((miw_node_name*)ret->data_type)->data_name = "@s8";

				if(scanner(TOKEN_SYMBOL, "\\")) //special character
				{
					if(scanner(TOKEN_UNKNOWN))
					{
						const char* ps8 = token.c_str();

						switch(ps8[0])
						{
						case '0':
							ret->s8 = 0;
							break;
						case 'a':
							ret->s8 = 7;
							break;
						case 'b':
							ret->s8 = 8;
							break;
						case 't':
							ret->s8 = 9;
							break;
						case 'n':
							ret->s8 = 10;
							break;
						case 'v':
							ret->s8 = 11;
							break;
						case 'f':
							ret->s8 = 12;
							break;
						case 'r':
							ret->s8 = 13;
							break;
						default:
							wstrcpy(&ret->s8, ps8); //maybe wchar_t
						}
					}
					else
					{
						goto _LABEL_ERROR;
					}
				}
				else if(scanner(TOKEN_UNKNOWN))
				{
					const char* ps8 = token.c_str();
					wstrcpy(&ret->s8, ps8); //maybe wchar_t
				}
				else
				{
					goto _LABEL_ERROR;
				}

				if(scanner(TOKEN_SYMBOL, "\'") == false)
					goto _LABEL_ERROR;
			}
			else if(scanner(TOKEN_SYMBOL, "\"")) //string
			{
				((miw_node_name*)ret->data_type)->data_name = "@s8";

				std::string str = "";
				while(isbuffer())
				{
					if(scanner(TOKEN_SYMBOL, "\""))
					{
						if(scanner(TOKEN_SYMBOL, "\"")) //next string
						{
							continue;
						}
						else
						{
							token = "\"";
							break;
						}
					}
					else if(scanner(TOKEN_SYMBOL, "\\")) //special character
					{
						if(scanner(TOKEN_UNKNOWN))
						{
							const char* ps8 = token.c_str();

							switch(ps8[0])
							{
							case '0':
								str += '\0';
								break;
							case 'a':
								str += '\a';
								break;
							case 'b':
								str += '\b';
								break;
							case 't':
								str += '\t';
								break;
							case 'n':
								str += '\n';
								break;
							case 'v':
								str += '\v';
								break;
							case 'f':
								str += '\f';
								break;
							case 'r':
								str += '\r';
								break;
							default:
								str += token; //maybe wchar_t
							}
						}
						else
						{
							goto _LABEL_ERROR;
						}
					}
					else if(scanner(TOKEN_UNKNOWN))
					{
						str += token; //maybe wchar_t
					}
					else
					{
						goto _LABEL_ERROR;
					}
				}

				if(token.compare("\""))
					goto _LABEL_ERROR;

				//copy string
				ret->ptr = new char[strlen(str.c_str()) + 1];
				wstrcpy(ret->ptr, str.c_str());

				//convert to ps8
				miw_node_pointer* p = new miw_node_pointer(line, file);
				p->data_type = ret->data_type;
				ret->data_type = p;
			}
			else if(scanner(TOKEN_STRING, "true")) //bool
			{
				((miw_node_name*)ret->data_type)->data_name = "@bool";
				ret->b = true;
			}
			else if(scanner(TOKEN_STRING, "false")) //bool
			{
				((miw_node_name*)ret->data_type)->data_name = "@bool";
				ret->b = false;
			}

			return ret;

		_LABEL_ERROR:
			delete ret;

			error = true;
			return NULL;
		}

		//<name>
		miw_node_name* parser_name()
		{
			if(scanner(TOKEN_STRING) == false)
				return NULL;

			miw_node_name* ret = new miw_node_name(line, file);

			if(!token.compare("signed")) //signed
			{
				if(scanner(TOKEN_STRING) == false)
					goto _LABEL_ERROR;

				ret->data_name = "@s";
			}
			else if(!token.compare("unsigned")) //unsigned
			{
				if(scanner(TOKEN_STRING) == false)
					goto _LABEL_ERROR;

				ret->data_name = "@u";
			}

			if(!token.compare("char")) //char
			{
				if(!ret->data_name.compare("@u"))
					ret->data_name = "@u8";
				else
					ret->data_name = "@s8";
			}
			else if(!token.compare("short")) //short
			{
				if(!ret->data_name.compare("@u"))
					ret->data_name = "@u16";
				else
					ret->data_name = "@s16";
			}
			else if(!token.compare("int")) //int
			{
				if(!ret->data_name.compare("@u"))
					ret->data_name = "@u32";
				else
					ret->data_name = "@s32";
			}
			else if(!token.compare("long")) //long
			{
				if(scanner(TOKEN_STRING, "long")) //long long
				{
					if(!ret->data_name.compare("@u"))
						ret->data_name = "@u64";
					else
						ret->data_name = "@s64";
				}
				else
				{
					switch(sizeof(long))
					{
					case 4:
						if(!ret->data_name.compare("@u"))
							ret->data_name = "@u32";
						else
							ret->data_name = "@s32";
						break;

					case 8:
						if(!ret->data_name.compare("@u"))
							ret->data_name = "@u64";
						else
							ret->data_name = "@s64";
						break;

					default:
						goto _LABEL_ERROR;
					}
				}
			}
			else if(!ret->data_name.compare(""))
			{
				if(!token.compare("void")) //void
				{
					ret->data_name = "@void";
				}
				else if(!token.compare("float")) //float
				{
					ret->data_name = "@f32";
				}
				else if(!token.compare("double")) //double
				{
					ret->data_name = "@f64";
				}
				else if(!token.compare("bool")) //bool
				{
					ret->data_name = "@bool";
				}
				else if(!token.compare("wchar_t")) //wchar_t
				{
					ret->data_name = "@wchar_t";
				}
				else if(!token.compare("auto")) //auto
				{
					ret->data_name = "@auto";
				}
				else //variable
				{
					for(int i = 0; i < sizeof(KEYWORD_STRING) / sizeof(KEYWORD_STRING[0]); ++i) //not keyword
					{
						if(!token.compare(KEYWORD_STRING[i]))
							goto _LABEL_ERROR;
					}

					ret->data_name = token;
				}
			}
			else
			{
				goto _LABEL_ERROR;
			}

			return ret;

		_LABEL_ERROR:
			delete ret;

			error = true;
			return NULL;
		}

		//<scope> -> "::"? <name> (("::" | "." | "->") <name>)* "::"?
		miw_node_scope* parser_scope(std::string endsymbol = "")
		{
			scanner_record record = scanner_save();

			miw_node_name* name = NULL;

			if(scanner(TOKEN_SYMBOL, "::"))
			{
				name = new miw_node_name(line, file);
				name->to_root();

				scanner_load(record);
			}
			else
			{
				name = parser_name();
			}

			if(name == NULL)
				return NULL;

			miw_node_scope* ret = new miw_node_scope(line, file);
			ret->data_value.push_back(name);

			while(scanner(TOKEN_SYMBOL, "::") || scanner(TOKEN_SYMBOL, ".") || scanner(TOKEN_SYMBOL, "->"))
			{
				name = parser_name();
				if(name == NULL)
				{
					if(endsymbol.compare(""))
					{
						endsymbol = "";
						break;
					}
					else
					{
						goto _LABEL_ERROR;
					}
				}

				ret->data_value.push_back(name);
			}

			if(endsymbol.compare(""))
			{
				delete ret;

				scanner_load(record);
				return NULL;
			}

			return ret;

		_LABEL_ERROR:
			delete ret;

			error = true;
			return NULL;
		}

		//<expression>	->	<layer14> (("=" | "+=" | "-=" | "*=" | "/=" | "%=" | "<<=" | ">>=" | "&=" | "^=" | "|=") <layer14>)*
		miw_node* parser_expression()
		{
			miw_node_exp* ret = NULL;

			miw_node* left = parser_layer1();

			while(scanner(TOKEN_SYMBOL, "=")
				|| scanner(TOKEN_SYMBOL, "+=") || scanner(TOKEN_SYMBOL, "-=")
				|| scanner(TOKEN_SYMBOL, "*=") || scanner(TOKEN_SYMBOL, "/=") || scanner(TOKEN_SYMBOL, "%=")
				|| scanner(TOKEN_SYMBOL, "<<=") || scanner(TOKEN_SYMBOL, ">>=")
				|| scanner(TOKEN_SYMBOL, "&=") || scanner(TOKEN_SYMBOL, "^=") || scanner(TOKEN_SYMBOL, "|="))
			{
				ret = new miw_node_exp(line, file);
				ret->data_op = new miw_node_name(line, file);

				miw_node* right = parser_layer1();
			}

			return ret ? ret : left;
		}

		//<layer14>		->	<layer13> ("||" <layer13>)*

		//<layer13>		->	<layer12> ("&&" <layer12>)*

		//<layer12>		->	<layer11> ("|" <layer11>)*

		//<layer11>		->	<layer10> ("^" <layer10>)*

		//<layer10>		->	<layer9> ("&" <layer9>)*

		//<layer9>		->	<layer8> (("==" | "!=") <layer8>)*

		//<layer8>		->	<layer7> (("<" | "<=" | ">" | ">=") <layer7>)*

		//<layer7>		->	<layer6> (("<<" | ">>") <layer6>)*

		//<layer6>		->	<layer5> (("+" | "-") <layer5>)*

		//<layer5>		->	<layer4> (("*" | "/" | "%") <layer4>)*

		//<layer4>		->	<layer3> ((".*" | "->*") <layer3>)*

		//<layer3>		->	("++" | "--" | "+" | "-" | "!" | "~" | "*" | "&" | ) <layer2>
		//				->	"(" <decl_type> <decl_value> ? ")" <layer2>
		//				->	("new" | "delete") <decl_type> <decl_value>? ("[" <expression> "]")
		//				->	"sizeof" "(" ((<decl_type> <decl_value>?) | <scope>) ")"

		//<layer2>		->	<layer1> ("++" | "--")
		//				->	<layer1> "(" <expression_list>? ")"
		//				->	<layer1> "[" <expression> "]"

		//<layer1>		->	"(" <expression> ")" | <value> | <scope>
		miw_node* parser_layer1()
		{
			miw_node* ret = NULL;

			//"(" <expression> ")"
			if(scanner(TOKEN_SYMBOL, "("))
			{
				ret = parser_expression();

				if(ret == NULL || scanner(TOKEN_SYMBOL, ")") == false)
					goto _LABEL_ERROR;
			}
			else
			{
				//<value>
				ret = parser_value();

				//<scope>
				if(ret == NULL)
					ret = parser_scope();
			}

			return ret;

		_LABEL_ERROR:
			if(ret)
				delete ret;

			error = true;
			return NULL;
		}

		//<expression_list>	-> <expression> ("," <expression>)*

		//<decl_modify>	->	"register"	//no use
		//				|	"static"
		//				|	"extern"	//no use
		//				|	"const"		//no use
		//				|	"volatile"	//no use
		//				|	"inline"	//no use
		//				|	"virtual"
		//				|	"friend"	//no use
		//				|	"typedef"	//no use
		//				|	"typename"	//no use
		bool parser_decl_modify()
		{
			return scanner(TOKEN_STRING, "register")
				|| scanner(TOKEN_STRING, "static")
				|| scanner(TOKEN_STRING, "extern")
				|| scanner(TOKEN_STRING, "const")
				|| scanner(TOKEN_STRING, "volatile")
				|| scanner(TOKEN_STRING, "inline")
				|| scanner(TOKEN_STRING, "virtual")
				|| scanner(TOKEN_STRING, "friend")
				|| scanner(TOKEN_STRING, "typedef")
				|| scanner(TOKEN_STRING, "typename");
		}

		//<class_header>	->	"class"
		//					|	"struct"
		//					|	"union"
		bool parser_class_header()
		{
			return scanner(TOKEN_STRING, "class")
				|| scanner(TOKEN_STRING, "struct")
				|| scanner(TOKEN_STRING, "union");
		}

		//<class_access>	->	"private"	//no use
		//					|	"protected"	//no use
		//					|	"public"	//no use
		bool parser_class_access()
		{
			return scanner(TOKEN_STRING, "private")
				|| scanner(TOKEN_STRING, "protected")
				|| scanner(TOKEN_STRING, "public");
		}

		//<decl_class>	->	<class_header> <scope>
		//				|	<class_header> <scope>? (":" <decl_modify>* <class_access>? <class_header>? <scope> ("," <decl_modify>* <class_access>? <class_header>? <scope>)*)?
		//					"{" ((<class_access> ":") | <decl>* "}"
		miw_node_class* parser_class()
		{
			if(parser_class_header() == false)
				return NULL;

			//mido check union

			miw_node_class* ret = new miw_node_class(line, file);

			miw_node_scope* data_name = parser_scope();
			if(data_name != NULL)
			{
				if(data_name->data_value.size() == 1)
				{
					ret->data_name = (*data_name->data_value.begin())->data_name;
				}
				else
				{
					delete ret;
					return (miw_node_class*)data_name; //empty class
				}
			}

			if(scanner(TOKEN_SYMBOL, ":"))
			{
				while(!iserror())
				{
					while(parser_decl_modify())
					{
						//mido check virtual
					}

					parser_class_access();
					parser_class_header();

					miw_node* data_base = parser_scope();
					if(data_base == NULL)
						goto _LABEL_ERROR;

					ret->data_base.push_back(data_base);

					if(scanner(TOKEN_SYMBOL, ",") == false)
						break;
				}
			}

			if(scanner(TOKEN_SYMBOL, "{"))
			{
				while(!iserror())
				{
					if(parser_class_access())
					{
						if(scanner(TOKEN_SYMBOL, ":") == false)
							goto _LABEL_ERROR;
					}
					else if(parser_decl(ret) == NULL)
					{
						break;
					}
				}

				if(scanner(TOKEN_SYMBOL, "}") == false)
					goto _LABEL_ERROR;
			}
			else
			{
				delete ret;
				return (miw_node_class*)data_name; //empty class
			}

			if(data_name)
				delete data_name;

			return ret;

		_LABEL_ERROR:
			if(data_name)
				delete data_name;

			delete ret;

			error = true;
			return NULL;
		}

		//<decl_namespace> ->

		//<decl_enum> ->

		//<decl_type>	->	<decl_modify>* <scope>
		miw_node_var* parser_decl_type()
		{
			scanner_record record = scanner_save();

			bool isstatic = false;
			bool isvirtual = false;

			while(parser_decl_modify())
			{
				if(!token.compare("static"))
					isstatic = true;
				else if(!token.compare("virtual"))
					isvirtual = true;
			}

			miw_node_scope* data_type = parser_scope();
			if(data_type == NULL)
			{
				scanner_load(record);
				return NULL;
			}

			miw_node_var* ret = new miw_node_var(line, file);
			ret->data_type = data_type;
			ret->data_isstatic = isstatic;

			return ret;
		}

		//<decl_ptr>	->	"&" <decl_modify>*
		//				|	<scope>? "*" ("*" | <decl_modify>)* "&"? <decl_modify>*
		std::pair<miw_node_var*, miw_node*> parser_decl_ptr(miw_node_var* ret)
		{
			if(ret == NULL)
				return std::pair<miw_node_var*, miw_node*>(NULL, NULL);

			//reference
			if(scanner(TOKEN_SYMBOL, "&"))
			{
				miw_node_reference* ref = new miw_node_reference(line, file);
				ret->data_type = ref->modify(ret->data_type);

				while(parser_decl_modify())
					;

				return std::pair<miw_node_var*, miw_node*>(ret, NULL);
			}

			//pointer
			miw_node* scope = parser_scope("::");
			if(scope != NULL)
			{
				if(scanner(TOKEN_SYMBOL, "*") == false)
					goto _LABEL_ERROR;
			}
			else if(scanner(TOKEN_SYMBOL, "*") == false)
			{
				return std::pair<miw_node_var*, miw_node*>(ret, scope);
			}

			miw_node_pointer* ptr = new miw_node_pointer(line, file);

			while(!iserror())
			{
				if(scanner(TOKEN_SYMBOL, "*"))
					ptr->modify(new miw_node_pointer(line, file));
				else if(parser_decl_modify() == false)
					break;
			}

			ret->data_type = ptr->modify(ret->data_type);

			//reference
			if(scanner(TOKEN_SYMBOL, "&"))
			{
				miw_node_reference* ref = new miw_node_reference(line, file);
				ret->data_type = ref->modify(ret->data_type);
			}

			return std::pair<miw_node_var*, miw_node*>(ret, scope);

		_LABEL_ERROR:
			if(scope)
				delete scope;

			error = true;
			return std::pair<miw_node_var*, miw_node*>(NULL, NULL);
		}

		//<decl_value>	-> 	<del_ptr>? "(" <decl_value> ")" ("(" <decl_parameter>? ")" <decl_modify>*)? ("[" <expression>? "]")*
		//				|	<del_ptr>? <scope> "(" <decl_parameter>? ")" <decl_modify>*
		//				|	<del_ptr>? <scope>? "[" <expression>? "]" ("[" <expression> "]")*
		//				|	<del_ptr> <scope>?
		//				|	<scope>
		std::pair<miw_node_var*, miw_node*> parser_decl_value(miw_node_var* ret)
		{
			if(ret == NULL)
				return std::pair<miw_node_var*, miw_node*>(NULL, NULL);

			scanner_record record = scanner_save();

			miw_node* data_type = ret->data_type;

			std::pair<miw_node_var*, miw_node*> var_scope = parser_decl_ptr(ret);
			if(var_scope.first == NULL)
				scanner_load(record);

			miw_node_scope* scope = parser_scope();
			if(scope == NULL)
			{
				if(var_scope.first == NULL)
					goto _LABEL_ERROR;

				data_type = ret->data_type;

				if(scanner(TOKEN_SYMBOL, "("))
				{
					miw_node* scope = var_scope.second;

					var_scope = parser_decl_value(ret);
					if(var_scope.first == NULL)
						goto _LABEL_ERROR;

					//check and reset scope
					if(var_scope.second == NULL)
					{
						var_scope.second = scope;
						scope = NULL;
					}
					else if(scope)
					{
						delete scope;
						goto _LABEL_ERROR;
					}

					if(scanner(TOKEN_SYMBOL, ")") == false)
						goto _LABEL_ERROR;
				}
				else
				{
					scope = parser_scope();

					if(scope == NULL && data_type == ret->data_type) //no modify
					{
						if(var_scope.second)
							delete var_scope.second;

						scanner_load(record);
						return std::pair<miw_node_var*, miw_node*>(NULL, NULL);
					}
				}
			}

			if(scope)
			{
				//name
				std::list<miw_node_name*>::iterator it = --scope->data_value.end();
				ret->data_name = (*it)->data_name;
				delete *it;

				//scope
				scope->data_value.erase(it);
				if(scope->data_value.size() > 0)
					ret->info_scope = scope;
				else
					delete scope;

				data_type = ret->data_type;
			}
			
			if(scanner(TOKEN_SYMBOL, "(")) //function
			{
				miw_node_fun* fun = new miw_node_fun(line, file);
				fun->data_scope = var_scope.second;
				fun->data_isstatic = false;
				var_scope.second = NULL;

				if(data_type == ret->data_type)
				{
					ret->data_type = fun->modify(data_type);
				}
				else if(ret->data_type->rtti(miw_node::rttype<miw_node_modify>())) //modify
				{
					((miw_node_modify*)ret->data_type)->modify(fun->modify(data_type));
				}
				else
				{
					delete fun;
					goto _LABEL_ERROR;
				}

				parser_decl_parameter(fun->data_parameter);

				if(scanner(TOKEN_SYMBOL, ")") == false)
					goto _LABEL_ERROR;
			}
			else if(scanner(TOKEN_SYMBOL, "[")) //array
			{
				//mido
			}

			return var_scope;

		_LABEL_ERROR:
			if(var_scope.second)
				delete var_scope.second;

			error = true;
			return std::pair<miw_node_var*, miw_node*>(NULL, NULL);
		}

		//<decl_init>	-> <decl_value> "=" (<decl_init_array> | <expression>)
		//				|	<decl_value> "(" <expression_list>? ")"
		//				|	<decl_value>
		miw_node_var* parser_decl_init(miw_node_var* ret)
		{
			scanner_record record = scanner_save();

			std::pair<miw_node_var*, miw_node*> var_scope = parser_decl_value(ret);
			if(var_scope.first)
			{
				if(ret->data_type->rtti(miw_node::rttype<miw_node_fun>())) //function
				{
					return ret;
				}
				else if(scanner(TOKEN_SYMBOL, "="))
				{
				}
				else if(scanner(TOKEN_SYMBOL, "("))
				{
				}

				return ret;
			}

			return NULL;

		_LABEL_ERROR:
			error = true;
			return NULL;
		}

		//<decl_init_array>	-> "{" ( (<decl_init_array> | <expression>) ("," (<decl_init_array> | <expression>))* )? "}"

		//<decl_list>	->	<decl_type> <decl_init> ("," <decl_init>)*
		bool parser_decl_list(std::list<miw_node_var*>& ret)
		{
			scanner_record record = scanner_save();

			miw_node_var* var = parser_decl_type();
			if(var)
			{
				do
				{
					miw_node_var* var_clone = (miw_node_var*)var->clone();

					if(parser_decl_init(var_clone))
					{
						ret.push_back(var_clone);
					}
					else if(ret.size() > 0)
					{
						delete var_clone;
						goto _LABEL_ERROR;
					}
					else
					{
						delete var_clone;
						delete var;

						scanner_load(record);
						return false;
					}
				} while(scanner(TOKEN_SYMBOL, ","));

				delete var;
				return true;
			}

			scanner_load(record);
			return false;

		_LABEL_ERROR:
			delete var;

			for(std::list<miw_node_var*>::iterator it = ret.begin(); it != ret.end(); ++it)
				delete (*it);

			ret.clear();

			error = true;
			return false;
		}

		//<decl_parameter>	->  <decl_type> <decl_init>? ("," (<decl_type> <decl_init>?))*
		bool parser_decl_parameter(std::list<miw_node*>& ret)
		{
			miw_node_var* var = parser_decl_type();
			if(var)
			{
				parser_decl_init(var);
				ret.push_back(var);

				while(scanner(TOKEN_SYMBOL, ","))
				{
					var = parser_decl_type();

					if(var)
					{
						parser_decl_init(var);
						ret.push_back(var);
					}
					else
					{
						goto _LABEL_ERROR;
					}
				}

				return true;
			}

			return false;

		_LABEL_ERROR:
			delete var;

			for(std::list<miw_node*>::iterator it = ret.begin(); it != ret.end(); ++it)
				delete (*it);

			ret.clear();

			error = true;
			return false;
		}

		//<decl_function>	->	<scope> "(" <decl_parameter>? ")" (":" <expression_list>)
		//					|	<scope> "::" "~" <name> "(" ")"
		miw_node_var* parser_decl_function()
		{
			scanner_record record = scanner_save();

			bool deconstruct = false;

			if(scanner(TOKEN_SYMBOL, "~"))
				deconstruct = true;

			miw_node_name* name = parser_name();
			if(name == NULL)
				return NULL;

			if(scanner(TOKEN_SYMBOL, "(") == false) //function
			{
				delete name;
				scanner_load(record);
				return NULL;
			}

			miw_node_var* ret = new miw_node_var(line, file);
			ret->data_name = deconstruct ? "~" + name->data_name : name->data_name;
			delete name;

			miw_node_fun* fun = new miw_node_fun(line, file);

			name = new miw_node_name(line, file); //give a void type
			name->data_name = "void";
			ret->data_type = fun->modify(name);

			if(deconstruct == false)
				parser_decl_parameter(fun->data_parameter);

			if(scanner(TOKEN_SYMBOL, ")") == false)
				goto _LABEL_ERROR;

			return ret;

		_LABEL_ERROR:
			delete ret;

			error = true;
			return false;
		}

		//<decl>	->	<decl_class> ";"
		//			|	<decl_namespace> ";"
		//			|	<decl_enum> ";"
		//			|	<decl_list> ";"
		//			|	<decl_function> (";" | <block>)
		miw_node_class* parser_decl(miw_node_class* parent = NULL)
		{
			scanner_record record;

			miw_node_class* cls = NULL;
			miw_node_var* fun = NULL;
			std::list<miw_node_var*> vars;

			//class
			cls = parser_class();
			if(cls)
			{
				if(cls->rtti(miw_node::rttype<miw_node_class>()))
				{
					if(scanner(TOKEN_SYMBOL, ";") == false)
						goto _LABEL_ERROR;

					if(cls->data_name.compare(""))
					{
						if(parent->reg_class(cls) == false)
							goto _LABEL_ERROR;
					}
					else
					{
						//mido reg to var
					}
				}
				else
				{
					if(scanner(TOKEN_SYMBOL, ";") == false)
						goto _LABEL_ERROR;

					//
					delete cls;
				}

				return parent;
			}

			//namespace

			//enum

			//variable
			if(parser_decl_list(vars))
			{
				if(scanner(TOKEN_SYMBOL, ";"))
				{
					for(std::list<miw_node_var*>::iterator it = vars.begin(); it != vars.end(); ++it)
					{
						if((*it)->data_type->rtti(miw_node::rttype<miw_node_fun>()))	//function
						{
							delete *it;
						}
						else if(parent->reg_variable(*it) == false)
						{
							delete *it;
							goto _LABEL_ERROR;
						}
					}

					return parent;
				}
				else if(scanner(TOKEN_SYMBOL, "{")) //mido
				{
					for(std::list<miw_node_var*>::iterator it = vars.begin(); it != vars.end(); ++it)
					{
						if((*it)->data_type->rtti(miw_node::rttype<miw_node_fun>())) //function
						{
							if(scanner(TOKEN_SYMBOL, "}")) //function
							{
								if(parent->reg_variable(*it) == false)
								{
									delete *it;
									goto _LABEL_ERROR;
								}

								return parent;
							}
						}
						else if(parent->reg_variable(*it) == false)
						{
							delete *it;
							goto _LABEL_ERROR;
						}
					}
				}

				for(std::list<miw_node_var*>::iterator it = vars.begin(); it != vars.end(); ++it)
					delete *it;

				goto _LABEL_ERROR;
			}

			//function
			fun = parser_decl_function();
			if(fun) //mido
			{
				if(scanner(TOKEN_SYMBOL, ";"))
				{
					delete fun;
				}
				else if(scanner(TOKEN_SYMBOL, "{"))
				{
					if(scanner(TOKEN_SYMBOL, "}") == false)
						goto _LABEL_ERROR;

					if(parent->reg_variable(fun) == false)
						goto _LABEL_ERROR;
				}

				return parent;
			}

			return NULL;

		_LABEL_ERROR:
			if(cls)
				delete cls;

			if(fun)
				delete fun;

			error = true;
			return NULL;
		}

		//<line>	->	<if> | <for>
		//			->	("break" | "continue" | "return" <expression>? | <decl_list> | <expression_list>) ";"

		//<block>	->	"{" <line>* "}"

		//<line_block>	->	<line> | <block>

		//<if>	->	"if" "(" <expression> ")" <line_block>
		//			("else" "if" "(" <expression> ")" <line_block>)*
		//			("else" <line_block>)?

		//<for>	->	"for" "(" (<decl_list> | <expression_list>)? ";" <expression>? ";" <expression_list>? ")" <line_block>
	};
};

#endif
