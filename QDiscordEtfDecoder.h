
// Parts of this file inspired by, or outright copied from erlpack:
// Copyright 2021 Craig Edwards and D++ contributors 
// Copyright(c) 2022 by wad(wad@inbox.lv)

#pragma once

const uint8_t ETF_FORMAT_VERSION = 131; // Current ETF format version in use

enum etf_token_type : uint8_t
{
	ett_distribution =    'D', // 68  Distribution header
	ett_new_float =       'F', // 70  Float64:IEEE float
	ett_bit_binary =      'M', // 77  UInt32:Len, UInt8:Bits, Len:Data
	ett_compressed =      'P', // 80  UInt4:UncompressedSize, N:ZlibCompressedData
	ett_smallint =        'a', // 97  UInt8:Int
	ett_integer =         'b', // 98  Int32:Int
	ett_float =           'c', // 99  31:Float String, Float in string format (formatted "%.20e", sscanf "%lf"). Superseded by ett_new_float
	ett_atom =            'd', // 100 UInt16:Len, Len:AtomName, max Len is 255
	ett_reference =	      'e', // 101 atom:Node, UInt32:ID, UInt8:Creation
	ett_port =            'f', // 102 atom:Node, UInt32:ID, UInt8:Creation
	ett_pid =             'g', // 103 atom:Node, UInt32:ID, UInt32:Serial, UInt8:Creation
	ett_small_tuple =     'h', // 104 UInt8:Arity, N:Elements
	ett_large_tuple =     'i', // 105 UInt32:Arity, N:Elements
	ett_nil =             'j', // 106 empty list
	ett_string =          'k', // 107 UInt16:Len, Len:Characters
	ett_list =            'l', // 108 UInt32:Len, Elements, Tail
	ett_binary =          'm', // 109 UInt32:Len, Len:Data
	ett_bigint_small =    'n', // 110 UInt8:n, UInt8:Sign, n:nums
	ett_bigint_large =    'o', // 111 UInt32:n, UInt8:Sign, n:nums
	ett_new_function =    'p', // 112 UInt32:Size, UInt8:Arity, 16*Uint6-MD5:Uniq, UInt32:Index, UInt32:NumFree, atom:Module, int:OldIndex, int:OldUniq, pid:Pid, NunFree*ext:FreeVars
	ett_export =          'q', // 113 atom:Module, atom:Function, smallint:Arity
	ett_new_reference =   'r', // 114 UInt16:Len, atom:Node, UInt8:Creation, Len*UInt32:ID
	ett_atom_small =      's', // 115 UInt8:Len, Len:AtomName
	ett_map =             't', // 116 UInt32:Airty, N:Pairs
	ett_function =        'u', // 117 UInt4:NumFree, pid:Pid, atom:Module, int:Index, int:Uniq, NumFree*ext:FreeVars
	ett_atom_utf8 =       'v', // 118 UInt16:Len, Len:AtomName, max Len is 255 characters (up to 4 bytes per)
	ett_atom_utf8_small = 'w'  // 119 UInt8:Len, Len:AtomName
};


struct etf_buffer
{
	etf_buffer(size_t initial);
	~etf_buffer() = default;

	std::vector<char> buf;
	size_t length = 0;
};


class etf_parser
{
public:
	etf_parser() = default;
	~etf_parser() = default;
	QJsonObject parse(const QByteArray& in);
private:
	QJsonValue inner_parse();
	uint8_t read_8_bits();
	uint16_t read_16_bits();
	uint32_t read_32_bits();
	uint64_t read_64_bits();
	const char* read_string(uint32_t length);
	QJsonValue process_atom(const char* atom, uint16_t length);
	QJsonValue decode_atom();
	QJsonValue decode_small_atom();
	QJsonValue decode_small_integer();
	QJsonValue decode_integer();
	QJsonValue decode_array(uint32_t length);
	QJsonValue decode_list();
	QJsonValue decode_tuple(uint32_t length);
	QJsonValue decode_nil();
	QJsonValue decode_map();
	QJsonValue decode_float();
	QJsonValue decode_new_float();
	QJsonValue decode_bigint(uint32_t digits);
	QJsonValue decode_bigint_small();
	QJsonValue decode_bigint_large();
	QJsonValue decode_binary();
	QJsonValue decode_string();
	QJsonValue decode_string_as_list();
	QJsonValue decode_tuple_small();
	QJsonValue decode_tuple_large();
	QJsonValue decode_compressed();
	QJsonValue decode_reference();
	QJsonValue decode_new_reference();
	QJsonValue decode_port();
	QJsonValue decode_pid();
	QJsonValue decode_export();

	size_t   _size = 0;
	size_t   _offset = 0;
	uint8_t* _data = nullptr;
};


class etf_builder
{
public:
	etf_builder() = default;
	~etf_builder() = default;
	QByteArray build(const QJsonObject& object);
private:
	void buffer_write(etf_buffer* pk, const char* bytes, size_t l);
	void append_version(etf_buffer* b);
	void append_nil(etf_buffer* b);
	void append_false(etf_buffer* b);
	void append_true(etf_buffer* b);
	void append_small_integer(etf_buffer* b, unsigned char d);
	void append_integer(etf_buffer* b, int32_t d);
	void append_unsigned_long_long(etf_buffer* b, unsigned long long d);
	void append_long_long(etf_buffer* b, long long d);
	void append_double(etf_buffer* b, double f);
	void append_atom(etf_buffer* b, const char* bytes, size_t size);
	void append_atom_utf8(etf_buffer* b, const char* bytes, size_t size);
	void append_binary(etf_buffer* b, const char* bytes, size_t size);
	void append_string(etf_buffer* b, const char* bytes, size_t size);
	void append_tuple_header(etf_buffer* b, size_t size);
	void append_nil_ext(etf_buffer* b);
	void append_list_header(etf_buffer* b, size_t size);
	void append_map_header(etf_buffer* b, size_t size);
	void inner_build(const QJsonValue& j, etf_buffer* b);
};
