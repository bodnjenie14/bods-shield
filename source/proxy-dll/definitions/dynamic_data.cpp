#include <std_include.hpp>
#include "dynamic_data.hpp"
#include "component/gsc_funcs.hpp"

#include <utilities/string.hpp>

namespace dynamic_data
{

	void load_dd(rapidjson::Value& object, void* buffer, void* mask, field* fields, size_t field_count)
	{
		if (!object.IsObject())
		{
			throw std::runtime_error("loading from something that isn't a json object");
		}

		for (const auto& [key, value] : object.GetObj())
		{
			if (!key.IsString())
			{
				continue;
			}

			const char* key_val = key.GetString();
			std::string_view key_v{ key_val };

			field* field{};

			if (!key_v.rfind("unk_", 0))
			{
				try
				{
					size_t loc = std::strtoull(&key_val[4], nullptr, 16);

					auto it = std::find_if(fields, fields + field_count, [loc](const dynamic_data::field& f) { return f.offset == loc; });

					if (it != fields + field_count)
					{
						field = it;
					}
					else
					{
						throw std::runtime_error(utilities::string::va("unknown field unk value '%s'", key_val));
					}
				}
				catch (const std::invalid_argument& e)
				{
					throw std::runtime_error(utilities::string::va("invalid field name '%s': '%s'", key_val, e.what()));
				}
			}
			else
			{
				uint32_t canon = gsc_funcs::canon_hash_pattern(key.GetString());

				auto it = std::find_if(fields, fields + field_count, [canon](const dynamic_data::field& f) { return f.canon_name == canon; });

				if (it != fields + field_count)
				{
					field = it;
				}
				else
				{
					throw std::runtime_error(utilities::string::va("unknown field name '%s'", key_val));
				}
			}

			logger::write(logger::LOG_TYPE_DEBUG, "load field %s (%lx) -> %llx", key_val, field->canon_name, field->size);

			// update the mask
			memset((byte*)mask + field->offset, 0xFF, field->size);

			byte* data = (byte*)buffer + field->offset;
			auto handle_field_val = [key_val, field, data](const rapidjson::Value& val, size_t idx) {
				switch (field->type)
				{
				case FT_UINT:
				{
					uint64_t u;
					if (val.IsBool())
					{
						u = val.GetBool() ? 1 : 0;
					}
					else if (val.IsNumber())
					{
						u = val.GetUint64();
					}
					else
					{
						throw std::runtime_error(utilities::string::va("field '%s' should be a number", key_val));
					}

					size_t len = field->size / field->array_size;
					switch (len)
					{
					case 1:
						*(data + len * idx) = (byte)u;
						break;
					case 2:
						*(uint16_t*)(data + len * idx) = (uint16_t)u;
						break;
					case 4:
						*(uint32_t*)(data + len * idx) = (uint32_t)u;
						break;
					case 8:
						*(uint64_t*)(data + len * idx) = (uint64_t)u;
						break;
					default:
						assert(0 && "field definition with bad size");
						break;
					}
				}
					break;
				case FT_INT:
				{
					int64_t u;
					if (val.IsBool())
					{
						u = val.GetBool() ? 1 : 0;
					}
					else if (val.IsNumber())
					{
						u = val.GetInt64();
					}
					else
					{
						throw std::runtime_error(utilities::string::va("field '%s' should be a number", key_val));
					}

					size_t len = field->size / field->array_size;
					switch (len)
					{
					case 1:
						*(int8_t*)(data + len * idx) = (int8_t)u;
						break;
					case 2:
						*(int16_t*)(data + len * idx) = (int16_t)u;
						break;
					case 4:
						*(int32_t*)(data + len * idx) = (int32_t)u;
						break;
					case 8:
						*(int64_t*)(data + len * idx) = (int64_t)u;
						break;
					default:
						assert(0 && "field definition with bad size");
						break;
					}
				}
					break;
				case FT_FLOAT:
				{
					if (!val.IsNumber())
					{
						throw std::runtime_error(utilities::string::va("field '%s' should be a number", key_val));
					}
					double u = val.GetDouble();

					size_t len = field->size / field->array_size;
					switch (len)
					{
					case 4:
						*(float*)(data + len * idx) = (float)u;
						break;
					case 8:
						*(double*)(data + len * idx) = u;
						break;
					default:
						assert(0 && "field definition with bad size");
						break;
					}
				}
				break;
				case FT_XHASH:
				{
					if (!val.IsString())
					{
						throw std::runtime_error(utilities::string::va("field '%s' should be a string", key_val));
					}
					const char* s = val.GetString();

					if (*s == '#') s++; // keep a "relative" compatibility with the bo4-source dump

					uint64_t hash = fnv1a::generate_hash_pattern(s);

					*(uint64_t*)(data + 0x10 * idx) = hash;
				}
					break;
				case FT_STRING:
				case FT_ENUM:
					// todo
				default:
					assert(0 && "unknown field type");
					return;
				}
			};

			if (value.IsArray())
			{
				auto arr = value.GetArray();

				if (field->array_size < arr.Size())
				{
					throw std::runtime_error(utilities::string::va("array definition too big for field '%s' (%lld < %lld)", key_val, field->array_size, arr.Size()));
				}

				size_t idx{};
				for (const auto& array_val : arr)
				{
					handle_field_val(array_val, idx++);
				}
			}
			else if (value.IsObject())
			{
				throw std::runtime_error(utilities::string::va("field '%s' can't be an object", key_val));
			}
			else
			{
				handle_field_val(value, 0);
			}
		}
	}
}