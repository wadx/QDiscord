
// Parts of this file inspired by, or outright copied from erlpack:
// Copyright 2021 Craig Edwards and D++ contributors 
// Copyright(c) 2022 by wad(wad@inbox.lv)

#include "stdafx.h"
#include "QDiscordEtfDecoder.h"
#include <QtCore/QtEndian>
#include "QDiscordLogging.h"
#include <zlib.h>


void store_16_bits(void* to, uint16_t val)
{
	qToBigEndian<uint16_t>(val, to);
}


void store_32_bits(void* to, uint32_t val)
{
	qToBigEndian<uint32_t>(val, to);
}


void store_64_bits(void* to, uint64_t val)
{
	qToBigEndian<uint64_t>(val, to);
}


uint16_t etf_byte_order_16(uint16_t from)
{
	return qFromBigEndian<uint16_t>(from);
}


uint32_t etf_byte_order_32(uint32_t from)
{
	return qFromBigEndian<uint32_t>(from);
}


uint64_t etf_byte_order_64(uint64_t from)
{
	return qFromBigEndian<uint64_t>(from);
}


etf_buffer::etf_buffer(size_t initial)
{
	buf.resize(initial);
	length = 0;
}


uint8_t etf_parser::read_8_bits()
{
	if (_offset + sizeof(uint8_t) > _size)
	{
		qCWarning(MAIN, ) << "ETF: read_8_bits() past end of buffer";
		return 0;
	}
	auto val = *reinterpret_cast<const uint8_t*>(_data + _offset);
	_offset += sizeof(uint8_t);
	return val;
}


uint16_t etf_parser::read_16_bits()
{
	if (_offset + sizeof(uint16_t) > _size)
	{
		qCWarning(MAIN, ) << "ETF: read_16_bits() past end of buffer";
		return 0;
	}
	uint16_t val = etf_byte_order_16(*reinterpret_cast<const uint16_t*>(_data + _offset));
	_offset += sizeof(uint16_t);
	return val;
}


uint32_t etf_parser::read_32_bits()
{
	if (_offset + sizeof(uint32_t) > _size)
	{
		qCWarning(MAIN, ) << "ETF: read_32_bits() past end of buffer";
		return 0;
	}
	uint32_t val = etf_byte_order_32(*reinterpret_cast<const uint32_t*>(_data + _offset));
	_offset += sizeof(uint32_t);
	return val;
}


uint64_t etf_parser::read_64_bits()
{
	if (_offset + sizeof(uint64_t) > _size)
	{
		qCWarning(MAIN, ) << "ETF: read_64_bits() past end of buffer";
		return 0l;
	}
	uint64_t val = etf_byte_order_64(*reinterpret_cast<const uint64_t*>(_data + _offset));
	_offset += sizeof(val);
	return val;
}


const char* etf_parser::read_string(uint32_t length)
{
	if (_offset + length > _size)
	{
		return nullptr;
	}
	const uint8_t* str = _data + _offset;
	_offset += length;
	return (const char*)str;
}


QJsonValue etf_parser::process_atom(const char* atom, uint16_t length)
{
	if (!atom)
	{
		return QJsonValue();
	}
	QJsonValue value;
	if (length >= 3 && length <= 5)
	{
		if (length == 3 && strncmp(atom, "nil", 3) == 0)
		{
			return value;
		}
		else if (length == 4 && strncmp(atom, "null", 4) == 0)
		{
			return value;
		}
		else if (length == 4 && strncmp(atom, "true", 4) == 0)
		{
			value = true;
			return value;
		}
		else if (length == 5 && strncmp(atom, "false", 5) == 0)
		{
			value = false;
			return value;
		}
	}
	value = QLatin1String(atom, length);
	return value;
}


QJsonValue etf_parser::decode_atom()
{
	auto length = read_16_bits();
	const char* atom = read_string(length);
	return process_atom(atom, length);
}


QJsonValue etf_parser::decode_small_atom()
{
	auto length = read_8_bits();
	const char* atom = read_string(length);
	return process_atom(atom, length);
}


QJsonValue etf_parser::decode_small_integer()
{
	QJsonValue j;
	j = (uint8_t)read_8_bits();
	return j;
}


QJsonValue etf_parser::decode_integer()
{
	QJsonValue j;
	j = (int32_t)read_32_bits();
	return j;
}

QJsonValue etf_parser::decode_array(uint32_t length)
{
	QJsonArray array;
	for (uint32_t i = 0; i < length; ++i)
	{
		array.append(inner_parse());
	}
	return array;
}

QJsonValue etf_parser::decode_list()
{
	const uint32_t length = read_32_bits();
	auto array = decode_array(length);
	const auto tailMarker = read_8_bits();
	if (tailMarker != ett_nil)
	{
		return QJsonValue();
	}
	return array;
}


QJsonValue etf_parser::decode_tuple(uint32_t length)
{
	return decode_array(length);
}


QJsonValue etf_parser::decode_nil()
{
	return QJsonValue();
}


QJsonValue etf_parser::decode_map()
{
	const uint32_t length = read_32_bits();
	QJsonObject map;
	for (uint32_t i = 0; i < length; ++i)
	{
		const QJsonValue key = inner_parse();
		const QJsonValue value = inner_parse();
		map[key.toString()] = value;
	}
	return map;
}


QJsonValue etf_parser::decode_float()
{
	const uint8_t FLOAT_LENGTH = 31;
	const char* floatStr = read_string(FLOAT_LENGTH);
	if (!floatStr)
	{
		return QJsonValue();
	}
	double number;
	char nullTerimated[FLOAT_LENGTH + 1] = { 0 };
	memcpy(nullTerimated, floatStr, FLOAT_LENGTH);
	auto count = sscanf_s(nullTerimated, "%lf", &number);
	if (count != 1)
	{
		return QJsonValue();
	}
	QJsonValue j = number;
	return j;
}


QJsonValue etf_parser::decode_new_float()
{
	union {
		uint64_t ui64;
		double df;
	} val;
	val.ui64 = read_64_bits();
	QJsonValue j = val.df;
	return j;
}


QJsonValue etf_parser::decode_bigint(uint32_t digits)
{
	const uint8_t sign = read_8_bits();
	if (digits > 8)
	{
		qCWarning(MAIN, ) << "ETF: big integer larger than 8 bytes unsupported";
		return QJsonValue();
	}
	uint64_t value = 0;
	uint64_t b = 1;
	for (uint32_t i = 0; i < digits; ++i)
	{
		uint64_t digit = read_8_bits();
		value += digit * b;
		b <<= 8;
	}
	if (digits <= 4)
	{
		if (sign == 0)
		{
			QJsonValue j = QString::number(static_cast<uint32_t>(value));
			return j;
		}
		const bool isSignBitAvailable = (value & (1 << 31)) == 0;
		if (isSignBitAvailable)
		{
			int32_t negativeValue = -static_cast<int32_t>(value);
			QJsonValue j = QString::number(negativeValue);
			return j;
		}
	}
	if (sign == 0)
	{
		QJsonValue j = QString::number(value);
		return j;
	}
	else
	{
		QJsonValue j = QString::number(-((int64_t)value));
		return j;
	}
}


QJsonValue etf_parser::decode_bigint_small()
{
	const auto bytes = read_8_bits();
	return decode_bigint(bytes);
}


QJsonValue etf_parser::decode_bigint_large()
{
	const auto bytes = read_32_bits();
	return decode_bigint(bytes);
}


QJsonValue etf_parser::decode_binary()
{
	const auto length = read_32_bits();
	const char* str = read_string(length);
	if (!str)
	{
		return QJsonObject();
	}
	QJsonValue j = QLatin1String(str, length);
	return j;
}


QJsonValue etf_parser::decode_string()
{
	const auto length = read_16_bits();
	const char* str = read_string(length);
	if (str == NULL)
	{
		return QJsonObject();
	}
	QJsonValue j = QLatin1String(str, length);
	return j;
}


QJsonValue etf_parser::decode_string_as_list()
{
	const auto length = read_16_bits();
	QJsonArray array;
	if (_offset + length > _size)
	{
		qCWarning(MAIN, ) << "String list past end of buffer";
		return QJsonValue();
	}
	for (uint16_t i = 0; i < length; ++i)
	{
		array.push_back(decode_small_integer());
	}
	return array;
}


QJsonValue etf_parser::decode_tuple_small()
{
	return decode_tuple(read_8_bits());
}


QJsonValue etf_parser::decode_tuple_large()
{
	return decode_tuple(read_32_bits());
}


QJsonValue etf_parser::decode_compressed()
{
	const uint32_t uncompressedSize = read_32_bits();
	unsigned long sourceSize = uncompressedSize;
	std::vector<uint8_t> outBuffer;
	outBuffer.reserve(uncompressedSize);
	const int ret = uncompress((Bytef*)outBuffer.data(), &sourceSize, (const unsigned char*)(_data + _offset), (uLong)(_size - _offset));
	_offset += sourceSize;
	if (ret != Z_OK)
	{
		qCWarning(MAIN, ) << "ETF compressed value: decompresson error";
		return QJsonValue();
	}
	uint8_t* old_data = _data;
	size_t old_size = _size;
	size_t old_offset = _offset;
	_data = outBuffer.data();
	_size = uncompressedSize;
	_offset = 0;
	QJsonValue j = inner_parse();
	_data = old_data;
	_size = old_size;
	_offset = old_offset;
	return j;
}


QJsonValue etf_parser::decode_reference()
{
	QJsonObject reference;
	reference["node"] = inner_parse();
	QJsonArray array;
	array.append(QJsonValue((int)read_32_bits()));
	reference["id"] = array;
	reference["creation"] = read_8_bits();
	return reference;
}


QJsonValue etf_parser::decode_new_reference()
{
	QJsonObject reference;
	uint16_t len = read_16_bits();
	reference["node"] = inner_parse();
	reference["creation"] = QJsonValue((int)read_8_bits());
	QJsonArray array;
	for (uint16_t i = 0; i < len; ++i)
	{
		array.append(QJsonValue((int)read_32_bits()));
	}
	reference["id"] = array;
	return reference;
}


QJsonValue etf_parser::decode_port()
{
	QJsonObject port;
	port["node"] = inner_parse();
	port["id"] = QJsonValue((int)read_32_bits());
	port["creation"] = QJsonValue((int)read_8_bits());
	return port;
}


QJsonValue etf_parser::decode_pid()
{
	QJsonObject pid;
	pid["node"] = inner_parse();
	pid["id"] = QJsonValue((int)read_32_bits());
	pid["serial"] = QJsonValue((int)read_32_bits());
	pid["creation"] = QJsonValue((int)read_8_bits());
	return pid;
}


QJsonValue etf_parser::decode_export()
{
	QJsonObject exp;
	exp["mod"] = inner_parse();
	exp["fun"] = inner_parse();
	exp["arity"] = inner_parse();
	return exp;
}


QJsonValue etf_parser::inner_parse()
{
	if (_offset >= _size)
	{
		qCWarning(MAIN, ) << "Read past end of ETF buffer";
		return QJsonValue();
	}
	const uint8_t type = read_8_bits();
	switch (type)
	{
	case ett_distribution:
		qCWarning(MAIN, ) << "Distribution headers are not supported";
		return QJsonValue();
	case ett_smallint:
		return decode_small_integer();
	case ett_integer:
		return decode_integer();
	case ett_float:
		return decode_float();
	case ett_new_float:
		return decode_new_float();
	case ett_atom:
		return decode_atom();
	case ett_atom_small:
		return decode_small_atom();
	case ett_small_tuple:
		return decode_tuple_small();
	case ett_large_tuple:
		return decode_tuple_large();
	case ett_nil:
		return decode_nil();
	case ett_string:
		return decode_string_as_list();
	case ett_list:
		return decode_list();
	case ett_map:
		return decode_map();
	case ett_binary:
		return decode_binary();
	case ett_bigint_small:
		return decode_bigint_small();
	case ett_bigint_large:
		return decode_bigint_large();
	case ett_reference:
		return decode_reference();
	case ett_new_reference:
		return decode_new_reference();
	case ett_port:
		return decode_port();
	case ett_pid:
		return decode_pid();
	case ett_export:
		return decode_export();
	case ett_compressed:
		return decode_compressed();
	default:
		qCWarning(MAIN, ) << "Unknown data type in ETF";
		return QJsonValue();
	}
}


QJsonObject etf_parser::parse(const QByteArray& in)
{
	_offset = 0;
	_size = in.size();
	_data = (uint8_t*)in.data();
	const uint8_t version = read_8_bits();
	if (version == ETF_FORMAT_VERSION)
	{
		return inner_parse().toObject();
	}
	else
	{
		qCWarning(MAIN, ) << "Incorrect ETF version";
		return QJsonObject();
	}
}


void etf_builder::buffer_write(etf_buffer* pk, const char* bytes, size_t l)
{
	if (pk->length + l > pk->buf.size())
	{
		// Grow buffer 2x to avoid excessive re-allocations.
		pk->buf.resize((pk->length + l) * 2);
	}
	memcpy(pk->buf.data() + pk->length, bytes, l);
	pk->length += l;
}


void etf_builder::append_version(etf_buffer* b)
{
	static unsigned char buf[1] = { ETF_FORMAT_VERSION };
	buffer_write(b, (const char*)buf, 1);
}


void etf_builder::append_nil(etf_buffer* b)
{
	static unsigned char buf[5] = { ett_atom_small, 3, 'n', 'i', 'l' };
	buffer_write(b, (const char*)buf, 5);
}


void etf_builder::append_false(etf_buffer* b)
{
	static unsigned char buf[7] = { ett_atom_small, 5, 'f', 'a', 'l', 's', 'e' };
	buffer_write(b, (const char*)buf, 7);
}

void etf_builder::append_true(etf_buffer* b)
{
	static unsigned char buf[6] = { ett_atom_small, 4, 't', 'r', 'u', 'e' };
	buffer_write(b, (const char*)buf, 6);
}


void etf_builder::append_small_integer(etf_buffer* b, unsigned char d)
{
	unsigned char buf[2] = { ett_smallint, d };
	buffer_write(b, (const char*)buf, 2);
}


void etf_builder::append_integer(etf_buffer* b, int32_t d)
{
	unsigned char buf[5];
	buf[0] = ett_integer;
	store_32_bits(buf + 1, d);
	buffer_write(b, (const char*)buf, 5);
}


void etf_builder::append_unsigned_long_long(etf_buffer* b, unsigned long long d)
{
	unsigned char buf[1 + 2 + sizeof(unsigned long long)];
	buf[0] = ett_bigint_small;
	unsigned char bytes_enc = 0;
	while (d > 0)
	{
		buf[3 + bytes_enc] = d & 0xFF;
		d >>= 8;
		bytes_enc++;
	}
	buf[1] = bytes_enc;
	buf[2] = 0;
	buffer_write(b, (const char*)buf, 1 + 2 + bytes_enc);
}


void etf_builder::append_long_long(etf_buffer* b, long long d)
{
	unsigned char buf[1 + 2 + sizeof(unsigned long long)];
	buf[0] = ett_bigint_small;
	buf[2] = d < 0 ? 1 : 0;
	unsigned long long ull = d < 0 ? -d : d;
	unsigned char bytes_enc = 0;
	while (ull > 0) {
		buf[3 + bytes_enc] = ull & 0xFF;
		ull >>= 8;
		bytes_enc++;
	}
	buf[1] = bytes_enc;
	buffer_write(b, (const char*)buf, 1 + 2 + bytes_enc);
}


void etf_builder::append_double(etf_buffer* b, double f)
{
	unsigned char buf[1 + 8] = { 0 };
	buf[0] = ett_new_float;
	union type_punner
	{
		uint64_t ui64;
		double df;
	};
	type_punner p;
	p.df = f;
	store_64_bits(buf + 1, p.ui64);
	buffer_write(b, (const char*)buf, 1 + 8);
}


void etf_builder::append_atom(etf_buffer* b, const char* bytes, size_t size)
{
	if (size < 255)
	{
		unsigned char buf[2] = { ett_atom_small, (unsigned char)size };
		buffer_write(b, (const char*)buf, 2);
		buffer_write(b, (const char*)bytes, size);
	}
	else
	{
		unsigned char buf[3];
		buf[0] = ett_atom;
		if (size > 0xFFFF)
		{
			qCWarning(MAIN, ) << "ETF: Atom too large";
			return;
		}
		store_16_bits(buf + 1, static_cast<uint16_t>(size));
		buffer_write(b, (const char*)buf, 3);
		buffer_write(b, (const char*)bytes, size);
	}
}


void etf_builder::append_atom_utf8(etf_buffer* b, const char* bytes, size_t size)
{
	if (size < 255)
	{
		unsigned char buf[2] = { ett_atom_utf8_small, (unsigned char)size };
		buffer_write(b, (const char*)buf, 2);
		buffer_write(b, (const char*)bytes, size);
	}
	else
	{
		unsigned char buf[3];
		buf[0] = ett_atom_utf8;
		if (size > 0xFFFF)
		{
			qCWarning(MAIN, ) << "ETF: Atom too large";
			return;
		}
		store_16_bits(buf + 1, static_cast<uint16_t>(size));
		buffer_write(b, (const char*)buf, 3);
		buffer_write(b, (const char*)bytes, size);
	}
}


void etf_builder::append_binary(etf_buffer* b, const char* bytes, size_t size)
{
	unsigned char buf[5];
	buf[0] = ett_binary;
	store_32_bits(buf + 1, static_cast<uint32_t>(size));
	buffer_write(b, (const char*)buf, 5);
	buffer_write(b, (const char*)bytes, size);
}


void etf_builder::append_string(etf_buffer* b, const char* bytes, size_t size)
{
	unsigned char buf[3];
	buf[0] = ett_string;
	store_16_bits(buf + 1, static_cast<uint16_t>(size));
	buffer_write(b, (const char*)buf, 3);
	buffer_write(b, (const char*)bytes, size);
}


void etf_builder::append_tuple_header(etf_buffer* b, size_t size)
{
	if (size < 256)
	{
		unsigned char buf[2];
		buf[0] = ett_small_tuple;
		buf[1] = (unsigned char)size;
		buffer_write(b, (const char*)buf, 2);
	}
	else
	{
		unsigned char buf[5];
		buf[0] = ett_large_tuple;
		store_32_bits(buf + 1, static_cast<uint32_t>(size));
		buffer_write(b, (const char*)buf, 5);
	}
}


void etf_builder::append_nil_ext(etf_buffer* b)
{
	static unsigned char buf[1] = { ett_nil };
	buffer_write(b, (const char*)buf, 1);
}


void etf_builder::append_list_header(etf_buffer* b, size_t size)
{
	unsigned char buf[5];
	buf[0] = ett_list;
	store_32_bits(buf + 1, static_cast<uint32_t>(size));
	buffer_write(b, (const char*)buf, 5);
}


void etf_builder::append_map_header(etf_buffer* b, size_t size)
{
	unsigned char buf[5];
	buf[0] = ett_map;
	store_32_bits(buf + 1, static_cast<uint32_t>(size));
	buffer_write(b, (const char*)buf, 5);
}


void etf_builder::inner_build(const QJsonValue& value, etf_buffer* buffer)
{
	if (value.isDouble())
	{
		double decimal = value.toDouble();
		if (std::floor(decimal) == decimal)
		{
			int64_t number = std::floor(decimal);
			if (number >= 0 && number <= 127)
			{
				unsigned char num = (unsigned char)number;
				append_small_integer(buffer, num);
			}
			else if (number >= std::numeric_limits<uint32_t>::max() - 1)
			{
				append_unsigned_long_long(buffer, number);
			}
			else
			{
				int32_t num32 = (int32_t)number;
				append_integer(buffer, num32);
			}
		}
		else
		{
			append_double(buffer, decimal);
		}
	}
	else if (value.isNull())
	{
		append_nil(buffer);
	}
	else if (value.isBool())
	{
		bool truthy = value.toBool();
		if (truthy)
		{
			append_true(buffer);
		}
		else
		{
			append_false(buffer);
		}
	}
	else if (value.isString())
	{
		const std::string s = value.toString().toStdString();
		append_binary(buffer, s.c_str(), s.length());
	}
	else if (value.isArray())
	{
		QJsonArray array = value.toArray();
		const size_t length = array.size();
		if (length == 0)
		{
			append_nil_ext(buffer);
		}
		else
		{
			if (length > std::numeric_limits<uint32_t>::max() - 1)
			{
				qCWarning(MAIN, ) << "ETF encode: List too large for ETF";
				return;
			}
		}
		append_list_header(buffer, length);
		for (size_t index = 0; index < length; ++index)
		{
			QJsonValue element = array.at(index);
			inner_build(element, buffer);
		}
		append_nil_ext(buffer);
	}
	else if (value.isObject())
	{
		QJsonObject object = value.toObject();
		const size_t length = object.size();
		if (length > std::numeric_limits<uint32_t>::max() - 1)
		{
			qCWarning(MAIN, ) << "ETF encode: Map too large for ETF";
			return;
		}
		append_map_header(buffer, length);
		for (auto iter = object.begin(); iter != object.end(); ++iter)
		{
			QJsonValue jstr = iter.key();
			inner_build(jstr, buffer);
			inner_build(iter.value(), buffer);
		}
	}
}


QByteArray etf_builder::build(const QJsonObject& object)
{
	etf_buffer pk(1024 * 1024);
	append_version(&pk);
	QJsonValue value = object;
	inner_build(value, &pk);
	return QByteArray(pk.buf.data(), pk.length);
}


