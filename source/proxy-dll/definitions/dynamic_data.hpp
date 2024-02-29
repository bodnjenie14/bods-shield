#pragma once

namespace dynamic_data
{
	enum field_type
	{
		FT_UINT = 0,
		FT_INT,
		FT_FLOAT,
		FT_ENUM,
		FT_STRING,
		FT_XHASH,
		FT_COUNT
	};

	struct field
	{
		uint32_t canon_name;
		field_type type{};
		size_t size{};
		size_t array_size{};
		size_t offset{};
	};

	void load_dd(rapidjson::Value& object, void* buffer, void* mask, field* fields, size_t field_count);
}